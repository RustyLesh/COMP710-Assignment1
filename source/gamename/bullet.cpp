// COMP710 Les Mcilroy

// This include:
#include "bullet.h"

// Local includes:
#include "sprite.h"
#include "logmanager.h"
#include "renderer.h"
#include "inlinehelpers.h"
#include "vector2.h"
#include "particleemitter.h"
// Library includes:
#include <cassert> 

Bullet::Bullet(float posX, float posY)
	: m_projSpeed(500)
	, m_damage(100)
	, m_pierceAmount(1)
	, m_pierceCounter(0)
	, m_boundry(2000)
{
	m_startingPos.x = posX;
	m_startingPos.y = posY;
}

Bullet::~Bullet()
{
}

bool
Bullet::Initialise(Renderer& renderer, b2World * b2world, float angleDegrees, EntityType entityType, int m_projSpeed, int damage, int pierceAmount)
{
	m_pSprite = renderer.CreateSprite("sprites\\bullet.png");

	bodyDef.bullet = true;
	m_damage = damage;
	m_pierceAmount = pierceAmount;

	Entity::Initialise(renderer, b2world, entityType);

	m_pParticleEmitter->SetEmitterSettings(1, 0.05, 2, 10,
		.3 ,.2 ,.2 , 0, 360);

	m_pParticleEmitter->setScale(.65);

	m_pSprite->SetGreenTint(.5);
	m_pSprite->SetBlueTint(.5);
	m_pSprite->SetRedTint(.5);

	float r = DegToRad((angleDegrees + 90));

	m_velocity = b2Vec2((float)cos(r) *m_projSpeed, -(float)sin(r) *m_projSpeed);
	m_TopLeftCorner = Vector2(0, 0);
	m_BotRightCorner = Vector2(renderer.GetWidth(), renderer.GetHeight());
	ProcessMovement();
	m_bAlive = true;

	return false;
}

void
Bullet::Process(float deltaTime, InputSystem& inputSystem)
{
	Entity::Process(deltaTime, inputSystem);
	if (m_pSprite->GetX() < -m_boundry || m_pSprite->GetX() > m_BotRightCorner.x + m_boundry
		|| m_pSprite->GetY() < -m_boundry || m_pSprite->GetY() > m_BotRightCorner.x + m_boundry)
	{
		m_bAlive = false;
		m_isMarkedForDeath = true;
	}

	if (m_pierceCounter >= m_pierceAmount)
	{
		m_bAlive = false;
		m_isMarkedForDeath = true;
	}
}

void
Bullet::Draw(Renderer& renderer)
{
	Entity::Draw(renderer);
}

void Bullet::DebugDraw()
{

}

void
Bullet::OnCollision(EntityUserData* userData)
{
	if (userData->entity->m_entityType == ET_ENEMY)
	{
		m_pierceCounter++;
	}
}
