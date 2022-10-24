// COMP710 Les Mcilroy
#ifndef __SCENEDEFEND_H__
#define __SCENEDEFEND_H__

//Local includes
#include "scene.h"
#include "attacklistener.h"
#include "vector2.h"

// Forward declarations:
struct EntityFixtureUserDataType;
class Renderer;
class Player;
class Enemy;
class Sprite;
class b2World;
class Entity;
class EnemyManager;
class GUIManager;

// Class declaration:
class SceneDefend : public Scene
	{
	// Member methods:
public:
	SceneDefend();
	virtual ~SceneDefend();

	virtual bool Initialise(Renderer& renderer, GUIManager& m_pGUIManager);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();
	void ResetScene();
	Player& GetPlayer();

protected:

private:
	SceneDefend(const SceneDefend& lowerCaseName);
	SceneDefend& operator=(const SceneDefend& scenedefend);

	// Member data:
public:
	b2World* m_pWorld;
	float m_timer;

protected:

private:
	Player* m_pPlayer;
	AttackListener* m_attackListenerInstance;
	EnemyManager* m_pEnemyPool;
	Vector2 m_center;

	GUIManager* m_pGUIManager;
};

#endif //__SCENEDEFEND_H__
