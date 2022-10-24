// COMP710 Les Mcilroy
#ifndef __SCENEBOX2DTEST_H__
#define __SCENEBOX2DTEST_H__

//Local includes
#include "scene.h"
#include <vector>

// Forward declarations:
class Renderer;
class Sprite;
class b2World;
class Crate;
class b2Body;

// Class declaration:
class SceneBox2dTest : public Scene
	{
	// Member methods:
public:
	SceneBox2dTest();
	virtual ~SceneBox2dTest();

	virtual bool Initialise(Renderer & renderer, GUIManager & guiManager) override;
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();


	void spawnCrate();
protected:

private:
	SceneBox2dTest(const SceneBox2dTest& lowerCaseName);
	SceneBox2dTest& operator=(const SceneBox2dTest& scenebox2dtest);

	void ToggleGroundCenterGizmo();
	void DrawGizmos();
	void InitialiseGizmos();

	// Member data:
public:
	b2World* world;
	
protected:

	std::vector<Crate*> m_pCrates;

private:
	Renderer* m_pRenderer;
	Sprite* m_pGroundMark; //Creates the sprite at the center of the ground.
	bool m_bgizmoVisable;
	// Inherited via Scene
	//Togles gizmos
};

#endif //__SCENEBOX2DTEST_H__
