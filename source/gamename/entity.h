// COMP710 GP Framework 2022
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Local includes:
#include "vector2.h"
#include "imgui/imgui_impl_sdl.h"
#include "box2d/box2d.h"

#include <string>
#include <vector>
// Forward declarations: 
class Renderer;
class Sprite;
class InputSystem;
class Renderer;
class EntityUserData;
class ParticleEmitter;

enum EntityType
{
	ET_ENTITY,
	ET_PLAYER,
	ET_ENEMY,
	ET_BULLET,
	ET_PLAYER_BULLET,
	ET_ENEMY_BULLET,
};

static const char* entityTypeString[] =
{
	"Entity",
	"Player",
	"Enemy",
	"Bullet",
};

class Entity;
struct EntityUserData
{
	Entity* entity;
};

//Collision Filters
const short CATEGORY_PLAYER = 0x0001;
const short CATEGORY_ENEMY = 0x0002;
const short CATEGORY_BULLET = 0x0004;
const short CATEGORY_PLAYER_BULLET = 0x0008;
const short CATEGORY_ENEMY_BULLET = 0x00016;

const short MASK_PLAYER = CATEGORY_ENEMY;
const short MASK_BULLET = CATEGORY_ENEMY;
const short MASK_ENEMY = CATEGORY_PLAYER | CATEGORY_BULLET;

// Class declaration: 
class Entity
{
	// Member methods: 
public:
	Entity();
	virtual ~Entity();

	virtual bool Initialise(Renderer& renderer, b2World * b2world, EntityType entityType);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void Reinitialise(EntityType entityType, Sprite& sprite);

	void Rotate(float direction);
	bool IsAlive() const;
	void SetDead();
	float GetRadius();
	b2Vec2 GetPosition();
	b2Vec2 GetFacingDirection();
	b2Vec2& GetVelocity();
	b2Vec2 GetWorldCenter();

	virtual EntityType GetEntityType();
	void DestroyB2dBody();
	void ProcessMovement();

	virtual void DebugDraw();
	virtual void OnCollision(EntityUserData* userData);
	virtual void EndCollision(EntityUserData* userData);

	void ChangeColour(float r, float g, float b);

protected:
	void MoveTo(b2Vec2 position);


private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	// Member data: 
public:
	Sprite* m_pSprite;
	b2Vec2 m_velocity;
	Vector2 m_acceleration;
	b2Fixture* m_pFixture;
	int m_collideCounter;
	EntityType m_entityType;

	EntityUserData* m_pUserData;
	float m_movespeed;
	bool m_isMarkedForDeath;
	bool m_bAlive;
	b2Body* m_pBody;
protected:
	b2BodyDef bodyDef;
	Renderer* m_pRenderer;
	std::string m_name;

	Vector2 m_startingPos;

	ParticleEmitter* m_pParticleEmitter;
private:
};
#endif // __ENTITY_H__