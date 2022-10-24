//COMP710 Les Mcilroy

//This Include:
#include "enemymanager.h"

//Local include:
#include "entitypoolmanager.h"
#include "imgui/imgui_impl_sdl.h"
#include "renderer.h"
#include "enemy.h"
#include "box2d/box2d.h"
#include "player.h"
#include "logmanager.h"
#include "inlinehelpers.h"
//Library includes


EnemyManager::EnemyManager()
	:m_spawnDelay(.3) //TODO up spawnrate over time
	, m_spawnDelayCounter(m_spawnDelay)
	, m_enemyHealthMultiplier(1)
	, m_enemyDamageMultiplier(1)
	, m_baseHealth(100)
{
}

EnemyManager::~EnemyManager()
{
	delete m_pPoolManager;
	m_pPoolManager = 0;
}

bool
EnemyManager::Initialise(Renderer& renderer, Player& player, b2World& b2world)
{
	m_screenCenter = { float(renderer.GetWidth()) / 2, float(renderer.GetHeight() / 2) };
	m_pRenderer = &renderer;
	m_pB2world = &b2world;
	m_pPlayer = &player;
	m_pPoolManager = new EntityPoolManager(&renderer, &b2world, &player);

	return false;
}

void
EnemyManager::Process(float deltaTime, InputSystem & inputSystem)
{
	m_pPoolManager->Process(deltaTime, inputSystem);

	m_spawnDelayCounter += deltaTime;

	m_spawnDelay -= deltaTime * 0.001;
	if (m_spawnDelayCounter > m_spawnDelay)
	{
		//SpawnEnemyRandomPositionRange(Vector2(0, m_screenCenter.x * 2), Vector2(0, m_screenCenter.y / 2), 100, 5);
		SpawnEnemyRandomPositionCircle(5, 5);
		m_spawnDelayCounter = 0;
	}
}

void EnemyManager::Draw(Renderer & renderer)
{
	m_pPoolManager->Draw(renderer);
}

void
EnemyManager::DebugDraw()
{
	ImGui::Text("Enemy Manager");
	ImGui::Text("Spawn Delay %f", m_spawnDelay);
	m_pPoolManager->DebugDraw();

}

void EnemyManager::ResetPool()
{
	m_pPoolManager->Reset();
	m_spawnDelay = 0.3;

}

void EnemyManager::CreateEnemy(int totalHealth, int xpValue, int posX, int posY)
{
	m_pPoolManager->CreateEnemy(totalHealth, xpValue, posX, posY);
}

void 
EnemyManager::SpawnEnemyRandomPositionRange(Vector2 xRange, Vector2 yRange, int totalHealth, int xpValue)
{
	Vector2 pos = Vector2(GetRandom(xRange.x, xRange.y), GetRandom(yRange.x, yRange.y));
	m_pPoolManager->CreateEnemy(totalHealth, xpValue, pos.x, pos.y);
}

void
EnemyManager::SpawnEnemyRandomPositionCircle(int totalHealth, int xpValue)
{
	float angle = DegToRad(GetRandom(0, 360));
	int a = (m_screenCenter.x);
	int b = (m_screenCenter.y);

	int distance = sqrt(pow(a, 2) + pow(b, 2)); //TODO: Cache
	
	Vector2 pos = Vector2((cos(angle) * distance) + m_screenCenter.x, (sin(angle) * distance) + m_screenCenter.y);
	m_pPoolManager->CreateEnemy(totalHealth, xpValue, pos.x, pos.y);
}

