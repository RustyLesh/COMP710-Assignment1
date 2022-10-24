// COMP710 Les Mcilroy

// This include:
#include "enemy.h"

// Local includes:
#include "renderer.h"
#include "logmanager.h"
#include "health.h"
#include "sprite.h"
#include "player.h"
#include "bullet.h"
#include "particleemitter.h"

// Library includes:
#include <cassert> 
#include <string>

Enemy::Enemy(b2World * b2world, Player* player, float x, float y)
	: m_pHealth(0)
	, m_canMove(true)
	, m_damage(1)
{
	m_pWorld = b2world;
	m_pPlayer = player;
	m_startingPos.x = x;
	m_startingPos.y = y;
}

Enemy::~Enemy()
{
	delete m_pHealth;
	m_pHealth = 0;
}

bool
Enemy::Initialise(Renderer& renderer, int totalHealth, int xpValue)
{
	m_pSprite = renderer.CreateSprite("sprites\\ball.png");
	m_name = "Enemy";

	Entity::Initialise(renderer, m_pWorld, ET_ENEMY);

	m_pSprite->SetRedTint(1);
	m_pSprite->SetGreenTint(0.1);
	m_pSprite->SetBlueTint(0.1);

	m_pParticleEmitter->SetEmitterSettings(1, 0.1, .2, 10,
		.5, .5, .5, 0, 360);

	m_pParticleEmitter->setScale(0.9);

	m_pHealth = new Health(totalHealth);
	m_bAlive = true;
	return false;
}

void
Enemy::Reinitialise(int totalHealth, float posX, float posY, int xpValue)
{
	m_pBody->SetTransform(b2Vec2(posX, posY), 0);

	Entity::Reinitialise(ET_ENEMY, *m_pSprite);



	m_name = "Enemy";

	m_pHealth->SetMaxHealth(totalHealth);
}

void
Enemy::Process(float deltaTime, InputSystem &inputSystem)
{
	Entity::Process(deltaTime, inputSystem);
	MoveTo(m_pPlayer->GetPosition());

	if (m_canMove)
	{
		ProcessMovement();
	}
}

void
Enemy::Draw(Renderer& renderer)
{
	Entity::Draw(renderer);
}

void Enemy::DebugDraw()
{
	ImGui::Text(m_name.c_str());
	ImGui::Text("HP: %f", m_pHealth->GetCurrentHealth());
	ImGui::Text("Collide Counter: %i", m_collideCounter);

}

void Enemy::TakeDamage(float amount)
{
	if (m_pHealth->Damage(amount) <= 0)
	{
		Die();
	}
}

void Enemy::Die()
{
	//std::string log = m_name + " died";
	//LogManager::GetInstance().Log(log.c_str());
	m_pPlayer->GainXp();
	m_bAlive = false;
	m_isMarkedForDeath = true;
}

EntityType
Enemy::GetEntityType()
{
	return ET_ENEMY;
}

void
Enemy::OnCollision(EntityUserData* userData)
{
	if (userData->entity->GetEntityType() == ET_BULLET && userData->entity->IsAlive())
	{
		TakeDamage(reinterpret_cast<Bullet*>(userData->entity)->m_damage);
	}
}

void Enemy::EndCollision(EntityUserData * userData)
{
	LogManager::GetInstance().Log("ENEMYSiTS");
}
