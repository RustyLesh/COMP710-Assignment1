// COMP710 Les Mcilroy
#ifndef __PLAYER_H__
#define __PLAYER_H__

//Local includes
#include "entity.h"
#include "inputsystem.h"

//Library includes
#include <vector>

// Forward declarations:
class Renderer;
class InputSystem;
class PlayerController;
class Health;
class EntityPoolManager;

// Class declaration:
class Player : public Entity
{
	// Member methods:
public:
	Player(float posX, float posY, b2World* world);
	virtual ~Player();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	void TakeDamage(float amount);
	void KillPlayer();
	void ResetPlayer();
	virtual void OnCollision(EntityUserData* userData);
	virtual void EndCollision(EntityUserData* userData);
	void GainXp();
protected:

private:
	Player(const Player& lowerCaseName);
	Player& operator=(const Player& player);

	void Attack();
	void ProcessPlayerXP();
	void LevelUp();

	// Member data:
public:
	float m_xpMultiplier;
	float m_attackDelay;
	float m_HPRegen;

	Health* m_pHealth;
	PlayerController* m_pPlayerMovement;

	int m_projSpeed;
	int m_projCount;	
	int m_damage;
	int m_defense;
	int m_pierceAmount;

protected:
	int m_xp;
	float m_levelUPThreshold; //TODO: change to scale per level;

	ButtonState m_xboxB;
	b2World* m_pWorld;
	EntityPoolManager* m_pentityPool;

	//NOTE: Attack variables
	float m_attackDelayCounter;
	float m_time;

	float m_iFrameTime;
	float m_iFrameCounter;
	float m_damageToTake;

	int m_level;

	ButtonState m_xboxA;

	bool m_isTouchingEnemy;
	bool m_isAutoShooting;


private:

};

#endif //__PLAYER_H__
