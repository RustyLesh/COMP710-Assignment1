// COMP710 Les Mcilroy

// This include
#include "scenedefend.h"

// Local includes
#include "sprite.h"
#include "imgui/imgui_impl_sdl.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"
#include "box2d/box2d.h"
#include "logmanager.h"
#include "attacklistener.h"
#include "enemymanager.h"
#include "xboxcontroller.h"
#include "guimanager.h"
#include "guicontainer.h"

// Library includes
#include <cassert> 
#include <vector>

SceneDefend::SceneDefend()
	: m_pPlayer(0)
	, m_timer(0)
{
}

SceneDefend::~SceneDefend()
{
	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_pWorld;
	m_pWorld = 0;

	delete m_pEnemyPool;
	m_pEnemyPool = 0;
}

bool
SceneDefend::Initialise(Renderer& renderer, GUIManager& guiManager)
{
	b2Vec2 gravity(0.0f, 0.0f);//Init b2world
	m_pWorld = new b2World(gravity);
	m_center = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);
	//init b2world ground
	b2BodyDef groundBodyDef;

	Vector2 groundCenter(renderer.GetWidth()*.75, renderer.GetHeight()*.75f);
	groundBodyDef.position.Set(groundCenter.x, groundCenter.y);

	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;

	groundBox.SetAsBox(renderer.GetWidth(), 1.0f); // Size of ground box

	groundBody->CreateFixture(&groundBox, 0.0f);

	m_attackListenerInstance = new AttackListener();
	m_pWorld->SetContactListener(m_attackListenerInstance);

	m_pPlayer = new Player(renderer.GetWidth() / 2, renderer.GetHeight() / 2, m_pWorld);
	m_pPlayer->Initialise(renderer);

	m_pEnemyPool = new EnemyManager();
	m_pEnemyPool->Initialise(renderer, *m_pPlayer, *m_pWorld);

	m_pGUIManager = &guiManager;

	return false;
}

void
SceneDefend::Process(float deltaTime, InputSystem& inputSystem)
{
	if (m_pGUIManager->m_isPaused)
	{
		deltaTime = 0;
	}

	m_timer += deltaTime;
	m_pWorld->Step(deltaTime, 8, 2);
	m_pPlayer->Process(deltaTime, inputSystem);
	m_pEnemyPool->Process(deltaTime, inputSystem);
}

void
SceneDefend::Draw(Renderer& renderer)
{
	m_pEnemyPool->Draw(renderer);
	m_pPlayer->Draw(renderer);
}

void SceneDefend::DebugDraw()
{
	ImGui::Text("Scene: Defend");
	ImGui::Text("Timer %f", m_timer);
	m_pPlayer->DebugDraw();
	m_pEnemyPool->DebugDraw();
}

void SceneDefend::ResetScene()
{
	m_pPlayer->m_pBody->SetTransform(b2Vec2(m_center.x, m_center.y), 0);

	m_pEnemyPool->ResetPool();
}

Player & SceneDefend::GetPlayer()
{
	return *m_pPlayer;
}
