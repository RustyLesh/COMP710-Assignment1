#ifndef __ENEMYMANGER_H__
#define __ENEMYMANGER_H__

//Local includes
#include "vector2.h"

//Forward declerations
class EntityPoolManager;
class Renderer;
class InputSystem;
class Player;
class b2World;
//Class delcaration
class EnemyManager
{
	//Member methods:
public:
	EnemyManager();
	~EnemyManager();

	bool Initialise(Renderer& renderer, Player& player, b2World& b2world);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	void DebugDraw();
	void ResetPool();
private:
	void CreateEnemy(int totalHealth, int xpValue, int posX, int posY);
	void SpawnEnemyRandomPositionRange(Vector2 xRange, Vector2 yRange, int totalHealth, int xpValue);
	void SpawnEnemyRandomPositionCircle(int totalHealth, int xpValue);
	// Member data:
public:


private:
	EntityPoolManager* m_pPoolManager;
	Renderer* m_pRenderer;
	b2World * m_pB2world;
	Player* m_pPlayer;

	Vector2 m_screenCenter;

	//Stat Multipliers
	int m_enemyHealthMultiplier;
	int m_enemyDamageMultiplier;
	int m_baseHealth;
	//Enemy Spawning Timers
	float m_spawnDelay;
	float m_spawnDelayCounter;

};
#endif // !__ENEMYMANGER_H__

