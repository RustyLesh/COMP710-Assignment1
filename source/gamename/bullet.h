// COMP710 Les Mcilroy
#ifndef __BULLET_H__
#define __BULLET_H__

//Local includes
#include "entity.h"
#include "vector2.h"

#include <vector>
// Forward declarations:
class Renderer;
class b2Vec2;

// Class declaration:
class Bullet : public Entity
	{
	// Member methods:
public:
	Bullet(float posX, float posY);
	Bullet(b2Vec2 location);
	virtual ~Bullet();

	virtual bool Initialise(Renderer& renderer, b2World * b2world, float angle, EntityType entityType, int m_projSpeed, int damage, int pierceAmount);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

	void OnCollision(EntityUserData* userData);

protected:

private:
	Bullet(const Bullet& lowerCaseName);
	Bullet& operator=(const Bullet& bullet);

	// Member data:
public:
	int m_damage;
	int m_pierceAmount; //Number of enemies a bullet can hit before dying //TODO: implement into bullet
	int m_pierceCounter;

	float m_projSpeed;

protected:
	Vector2 m_TopLeftCorner;
	Vector2 m_BotRightCorner;

	int m_boundry;
private:
};

#endif //__BULLET_H__
