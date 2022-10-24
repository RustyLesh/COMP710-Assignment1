// COMP710 Les Mcilroy

// This include:
#include "player.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "logmanager.h"
#include "playercontroller.h"
#include "health.h"
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "box2d/box2d.h"
#include "bullet.h"
#include "scenemanager.h"
#include "guimanager.h"
#include "inlinehelpers.h"
#include "entitypoolmanager.h"
#include "enemy.h"
#include "particleemitter.h"

// Library includes:
#include <cassert> 
#include <vector>
#include <string>

Player::Player(float posX, float posY, b2World* world)
	: m_pPlayerMovement(0)
	, m_pHealth(0)
	, m_xp(0)
	, m_isAutoShooting(true)
	, m_levelUPThreshold(1)
	, m_level(0)
	, m_xpMultiplier(1)
	, m_iFrameTime(1)
	, m_iFrameCounter(1)
	, m_isTouchingEnemy(false)
	, m_damageToTake(0)

	//NOTE: Attack variables
	, m_projSpeed(300)
	, m_projCount(1)
	, m_attackDelay(1)
	, m_attackDelayCounter(0)
	, m_damage(50)
	, m_defense(0)
	, m_HPRegen(0.01)
	, m_pierceAmount(1)

{
	m_startingPos.x = posX;
	m_startingPos.y = posY;
	m_pWorld = world;
}

Player::~Player()
{
	delete m_pPlayerMovement;
	m_pPlayerMovement = 0;

	delete m_pHealth;
	m_pHealth = 0;

	delete m_pentityPool;
	m_pentityPool = 0;
}

bool
Player::Initialise(Renderer& renderer)
{
	m_pSprite = renderer.CreateSprite("sprites\\ship.png");

	m_pentityPool = new EntityPoolManager(&renderer, m_pWorld, this);

	Entity::Initialise(renderer, m_pWorld, ET_PLAYER);

	m_pParticleEmitter->SetEmitterSettings(1, 0.1, 2, 50,
		.1, .1, .1, 135, 225);

	m_pParticleEmitter->setScale(0.6);

	m_levelUPThreshold = pow(m_level + 1 / 0.79f, 2.04f) + 3.4;

	m_pSprite->SetGreenTint(1.0);

	m_pPlayerMovement = new PlayerController();
	m_pPlayerMovement->Initialise(renderer);

	m_pHealth = new Health(10);
	m_pHealth->AddRegen(m_HPRegen);

	m_name = "Player";

	m_bAlive = true;

	return false;
}

void
Player::Process(float deltaTime, InputSystem& inputSystem)
{
	m_xboxA = inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_A);

	m_attackDelayCounter += deltaTime;
	m_iFrameCounter += deltaTime;
	m_pHealth->ProcessRegen(deltaTime);
	m_pentityPool->Process(deltaTime, inputSystem);


	Entity::Process(deltaTime, inputSystem);

	m_pPlayerMovement->Process(deltaTime, inputSystem, *this);
	ProcessMovement();

	m_pSprite->SetX(static_cast<int>(m_pBody->GetPosition().x));
	m_pSprite->SetY(static_cast<int>(m_pBody->GetPosition().y));


	if (m_isTouchingEnemy)
	{
		TakeDamage(m_damageToTake);
	}

	if (m_iFrameCounter < m_iFrameTime)
	{
		m_pSprite->SetRedTint(1);
		m_pSprite->SetGreenTint(0.1);
		m_pSprite->SetBlueTint(1);
	}
	else
	{
		m_pSprite->SetRedTint(1);
		m_pSprite->SetGreenTint(1);
		m_pSprite->SetBlueTint(1);
	}

	//NOTE: Attack variables
	if (m_xboxA == BS_PRESSED || m_isAutoShooting)
	{
		if (m_attackDelayCounter > m_attackDelay)
		{
			Attack();
			m_attackDelayCounter = 0;
		}
	}

	ProcessPlayerXP(); //TODO only procces on XP change
}

void
Player::Draw(Renderer& renderer)
{
	m_pentityPool->Draw(renderer);

	Entity::Draw(renderer);
}

void
Player::DebugDraw()
{
	m_pPlayerMovement->DebugDraw();

	ImGui::Text("----------------------------------");
	ImGui::Text(m_name.c_str());
	ImGui::Text("HP: %f", m_pHealth->GetCurrentHealth());
	ImGui::Text("Player Level: %i", m_level);
	ImGui::Text("Experience points : %i", m_xp);
	ImGui::Text("Next level: %f", m_levelUPThreshold);
	ImGui::Text("I Frame Counter: %f", m_iFrameCounter);

	//ImGui::Text("Posx %f", m_pBody->GetPosition().x);
	//ImGui::Text("Posy %f", m_pBody->GetPosition().y);

	//ImGui::Text("Entity Pool Size: %i", m_pEntityPool.size());
	//ImGui::Text("Player Radius: %f", GetRadius());
	//ImGui::Text("Sprite Width: %f", m_pSprite->GetWidth());
	//ImGui::Text("Sprite Scale: %f", m_pSprite->GetScale());

	m_pentityPool->DebugDraw();
	ImGui::Text("----------------------------------");
}

//Applies damage to the player, then kills the player if health falls bellow 0
void
Player::TakeDamage(float amount)
{
	if (m_iFrameCounter > m_iFrameTime)
	{
		amount = Clamp(0, amount - m_defense, FLT_MAX);

		if (m_pHealth->Damage(amount) <= 0)
		{
			KillPlayer();
		}
		LogManager::GetInstance().Log("Hurts");
		m_iFrameCounter = 0;
	}
}

void
Player::KillPlayer()
{
	LogManager::GetInstance().Log("Player Died");
	m_bAlive = false;
}

void
Player::Attack()
{
	//TODO Recycle Bullet
	//NOTE: Attack variables

	int angle = m_pSprite->GetAngle();
	int angleOffset = 10;

	for (int i = 0; i < m_projCount; ++i)
	{
		if (i >= 1)
		{
			if (i % 2 == 0)
			{
				angle = (m_pSprite->GetAngle() + (i * angleOffset));
			}
			else
			{
				angle = (m_pSprite->GetAngle() - (i * angleOffset));
			}
		}
		m_pentityPool->CreateBullet(m_pBody, m_pWorld, angle, ET_BULLET, m_projSpeed, m_damage, m_pierceAmount);
	}

}

void Player::ProcessPlayerXP()
{
	if (m_xp > m_levelUPThreshold)
	{
		LevelUp();
		int x = m_level + 1;
		m_levelUPThreshold = pow(x / 0.79f, 2.04f) + 3.4;
	}	
}

void
Player::GainXp()
{
	m_xp += m_xpMultiplier;
}

void
Player::OnCollision(EntityUserData* userData)
{
	if (userData->entity->GetEntityType() == ET_ENEMY && userData->entity->IsAlive())
	{
		m_damageToTake = reinterpret_cast<Enemy*>(userData->entity)->m_damage;
		m_isTouchingEnemy = true;
	}
}

void Player::EndCollision(EntityUserData * userData)
{
	m_isTouchingEnemy = false;
	m_damageToTake = 0;
}

void
Player::LevelUp()
{
	SceneManager::GetInstance().GetGUIManager()->LevelPlayer();
	m_level++;
}

void
Player::ResetPlayer()
{
	m_projSpeed = 300;
	m_projCount = 1;
	m_attackDelay = 1;
	m_attackDelayCounter = 0;
	m_damage = 50;
	m_defense = 0;
	m_HPRegen = 0.01;
	m_pierceAmount=1;
	m_isTouchingEnemy = false;
	m_pSprite->SetAngle(0);
	m_pHealth->Heal(9999);
	m_pPlayerMovement->m_movemetSpeed = 0.01;
	m_bAlive = true;
}