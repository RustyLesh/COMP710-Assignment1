// COMP710 Les Mcilroy

// This include:
#include "entity.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "logmanager.h"
#include "box2d/box2d.h"
#include "inlinehelpers.h"
#include "particleemitter.h"

// Library includes:
#include <cassert> 
#include <cstdint>

Entity::Entity()
	:m_pSprite(0)
	, m_name("Entity")
	, m_bAlive(true)
	, m_collideCounter(0)
	, m_isMarkedForDeath(false)
{
}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;

	delete m_pUserData;
	m_pUserData = 0;

	delete m_pParticleEmitter;
	m_pParticleEmitter = 0;
}

bool
Entity::Initialise(Renderer& renderer, b2World * b2world, EntityType entityType)
{
	m_collideCounter = 0;
	m_movespeed = 100;
	m_pRenderer = &renderer;
	m_entityType = entityType;

	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->Initialise(renderer);

	//Init user data
	m_pUserData = new EntityUserData;
	m_pUserData->entity = this;

	//Box2d init
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_startingPos.x, m_startingPos.y);
	bodyDef.userData.pointer = (uintptr_t)(m_pUserData);
	m_pBody = b2world->CreateBody(&bodyDef);

	//TODO: Seperate box2d related construction to child class

	//Set body type
	b2CircleShape circleShape;
	circleShape.m_radius = m_pSprite->GetHeight() / 2;

	//Create and set fixtire def
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.1f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = true;
	fixtureDef.userData.pointer = (uintptr_t)(m_pUserData);

	//Set collisition filters
	if (entityType == ET_BULLET)
	{
		fixtureDef.filter.categoryBits = CATEGORY_BULLET;
		fixtureDef.filter.maskBits = MASK_BULLET;
	}
	if (entityType == ET_PLAYER)
	{
		fixtureDef.filter.categoryBits = CATEGORY_PLAYER;
		fixtureDef.filter.maskBits = MASK_PLAYER;
	}

	if (entityType == ET_ENEMY)
	{
		fixtureDef.filter.categoryBits = CATEGORY_ENEMY;
		fixtureDef.filter.maskBits = MASK_ENEMY;
	}
	m_pFixture = m_pBody->CreateFixture(&fixtureDef);

	//Set sprite position
	m_pSprite->SetX(static_cast<int>(m_pBody->GetPosition().x));
	m_pSprite->SetY(static_cast<int>(m_pBody->GetPosition().y));

	return false;
}

void
Entity::Reinitialise(EntityType entityType, Sprite& sprite)
{
	m_collideCounter = 0;
	m_movespeed = 100;
	m_entityType = entityType;
	m_bAlive = true;
	//TODO: Seperate box2d related construction to child class
}

void
Entity::Process(float deltaTime, InputSystem& inputSystem)
{
	//m_pSprite->SetX(static_cast<int>(m_pBody->GetPosition().x));
	//m_pSprite->SetY(static_cast<int>(m_pBody->GetPosition().y));

	m_pSprite->SetX(static_cast<int>(m_pBody->GetPosition().x));
	m_pSprite->SetY(static_cast<int>(m_pBody->GetPosition().y));
	m_pParticleEmitter->Process(deltaTime);
	m_pParticleEmitter->SetLocation(m_pSprite->GetX(), m_pSprite->GetY());
}

void
Entity::Draw(Renderer& renderer)
{
	m_pParticleEmitter->Draw(renderer);
	m_pSprite->Draw(renderer);
}

void
Entity::Rotate(float direction)
{
	m_pSprite->SetAngle(direction);
}

bool 
Entity::IsAlive() const
{
	return m_bAlive;
}

void
Entity::SetDead()
{
	m_bAlive = false;
}

float
Entity::GetRadius()
{
	return m_pSprite->GetHeight() / 2;
}

b2Vec2 Entity::GetPosition()
{
	return m_pBody->GetPosition();
}

b2Vec2 Entity::GetWorldCenter()
{
	return m_pBody->GetWorldCenter();
}

b2Vec2
Entity::GetFacingDirection()
{
	float normal = sqrt(pow(m_velocity.x,2) + pow(m_velocity.y,2));
	b2Vec2 directionVector = {m_velocity.x / normal, m_velocity.y / normal};
	return directionVector;
}

b2Vec2
& Entity::GetVelocity()
{
	return m_velocity;
}

EntityType
Entity::GetEntityType()
{
	return m_entityType;
}

void
Entity::DestroyB2dBody()
{
	m_pBody->GetWorld()->DestroyBody(m_pBody);
}

void
Entity::ProcessMovement()
{
	m_pBody->SetLinearVelocity(m_velocity);
}

void 
Entity::DebugDraw()
{

}

void Entity::OnCollision(EntityUserData* userData)
{
	LogManager::GetInstance().Log("Not implemented");
}

void Entity::EndCollision(EntityUserData * userData)
{

}

void Entity::MoveTo(b2Vec2 position)
{
	float x = position.x - m_pBody->GetWorldCenter().x;
	float y = position.y - m_pBody->GetWorldCenter().y;

	float angle = (atan(x / y));
	float n = sqrt(pow(x, 2) + pow(y, 2));
	m_velocity = b2Vec2((x / n) * m_movespeed, (y / n )* m_movespeed);
}
//m_velocity = b2Vec2(cos(angle) * m_movespeed, -sin(angle) * m_movespeed);orbits around center

void
Entity::ChangeColour(float r, float g, float b)
{
	m_pSprite->SetRedTint(r);
	m_pSprite->SetRedTint(g);
	m_pSprite->SetRedTint(b);
}

