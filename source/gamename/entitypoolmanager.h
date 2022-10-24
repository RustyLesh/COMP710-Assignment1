#ifndef __ENEMYSPAWNMANAGER_H__
#define __ENEMYSPAWNMANAGER_H__

//Local includes
#include "entity.h"

//Libary includes:
#include <vector>
//Forward declartions:

class Entity;
class Renderer;
class InputSystem;
class b2World;
class Player;
class b2Body;

//Class deccaration:
class EntityPoolManager
{
	//Member Methods:
public:
	EntityPoolManager(Renderer* renderer, b2World* b2world, Player* player);
	~EntityPoolManager();

	bool Initialise();
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);

	void DebugDraw();

	void KillEntity(int entityToKill);
	void Reset();
	void CreateEnemy(int totalHealth, int xpValue, int posX, int posY);
	void CreateBullet(b2Body * body, b2World * world, float angle, EntityType entityType, 
		float speed, float damage, int pierceAmount);

protected:

private:

	//Member data:
public:

protected:
	int m_aliveCount;
	std::vector<Entity*> m_entityPool;
	Renderer* m_pRenderer;
	b2World* m_pB2world;
	Player* m_pPlayer;
};
#endif // !__ENEMYSPAWNMANAGER_H__

