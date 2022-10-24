//COMP701 Les Mcilroy

//This include:
#include "entitypoolmanager.h"

//Local includes
#include "entity.h"
#include "enemy.h"
#include "bullet.h"
#include "renderer.h"
#include "box2d/box2d.h"
#include "logmanager.h"
#include "renderer.h"
#include "vector2.h"
#include "sprite.h"

EntityPoolManager::EntityPoolManager(Renderer* renderer, b2World* b2world, Player* player)
	: m_aliveCount(0)
	, m_pRenderer(renderer)
	, m_pB2world(b2world)
	, m_pPlayer(player)
{
}

EntityPoolManager::~EntityPoolManager()
{
	for (int i = 0; i < m_entityPool.size(); i++)
	{
		delete m_entityPool[i];
	}
	m_entityPool.clear();
}

bool
EntityPoolManager::Initialise()
{

	return false;
}

void
EntityPoolManager::Process(float deltaTime, InputSystem& inputSystem)
{
	for (int i = 0; i < m_entityPool.size(); i++)
	{
		if (m_entityPool[i]->IsAlive())
		{
			m_entityPool[i]->Process(deltaTime, inputSystem);
		}
		else if (m_entityPool[i]->m_isMarkedForDeath)
		{
			KillEntity(i);
		}
	}
}

void
EntityPoolManager::Draw(Renderer& renderer)
{
	//for (int i = 0; i < m_aliveCount; i++)
	//{
	//	m_entityPool[i]->Draw(renderer);
	//}
	for (int i = 0; i < m_entityPool.size(); i++)
	{
		if (m_entityPool[i]->IsAlive())
		{
			m_entityPool[i]->Draw(renderer);
		}
	}
}

void
EntityPoolManager::DebugDraw()
{
	ImGui::Text("AliveCounter: %i", m_aliveCount);
}

void
EntityPoolManager::KillEntity(int entityToKill)
{
	if (m_aliveCount > 1)
	{
		//m_entityPool[entityToKill]->m_isMarkedForDeath = false;
		std::swap(m_entityPool[entityToKill], m_entityPool[m_entityPool.size() - 1]);
		m_entityPool[m_aliveCount - 1]->DestroyB2dBody();
		delete m_entityPool[m_aliveCount - 1];
		m_entityPool.pop_back();
		m_aliveCount--;
	}
}

void EntityPoolManager::Reset()
{
	for (int i = 0; i < m_entityPool.size(); i++)
	{
		m_entityPool[i]->DestroyB2dBody();
		delete m_entityPool[i];
	}
	m_entityPool.clear();
	m_aliveCount = 0;

}

void
EntityPoolManager::CreateEnemy(int totalHealth, int xpValue, int posX, int posY)
{
	Enemy* enemy = new Enemy(m_pB2world, m_pPlayer, posX, posY);
	enemy->Initialise(*m_pRenderer, totalHealth, xpValue);
	m_entityPool.push_back(enemy);

	m_aliveCount++;
}

void
EntityPoolManager::CreateBullet(b2Body* body, b2World* world, float angle, EntityType entityType,
	float speed, float damage, int pierceAmount)
{
	Bullet* bullet = new Bullet(body->GetPosition().x, body->GetPosition().y);
	bullet->Initialise(*m_pRenderer, world, angle, entityType, speed, damage, pierceAmount);
	m_entityPool.push_back(bullet);

	m_aliveCount++;
}
