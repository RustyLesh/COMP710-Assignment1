// COMP710 Les Mcilroy
#ifndef __ENEMY_H__
#define __ENEMY_H__

//Local includes
#include "entity.h"
// Forward declarations:
class Renderer;
class Health;
class Player;

// Class declaration:
class Enemy : public Entity
	{
	// Member methods:
public:
	Enemy(b2World * b2world, Player* player, float x, float y);
	virtual ~Enemy();

	virtual bool Initialise(Renderer& renderer, int totalHealth, int xpValue);
	virtual void Process(float deltaTime, InputSystem &inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void Reinitialise(int totalHealth, float posX, float posY, int xpValue);
	virtual void DebugDraw();

	virtual void TakeDamage(float amount);
	virtual void Die();
	virtual EntityType GetEntityType();
	virtual void OnCollision(EntityUserData* userData);
	virtual void EndCollision(EntityUserData* userData);

protected:

private:
	Enemy(const Enemy& lowerCaseName);
	Enemy& operator=(const Enemy& enemy);

	// Member data:
public:
	bool m_canMove;
	float m_damage;

protected:
	Health* m_pHealth;
	b2World* m_pWorld;
	Player* m_pPlayer;
	float m_movespeed;


private:
};

#endif //__ENEMY_H__
