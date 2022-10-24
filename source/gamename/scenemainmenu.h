//Comp710 Les Mcilroy
#ifndef __SCENEMAINMENU_H__
#define __SCENEMAINMENU_H__

//Local includes
#include "scene.h"

//Forward declarations
class Renderer;
class GUIManager;

//Class declaration
class SceneMainMenu : public Scene
{
	//Member meathods
public:
	SceneMainMenu();
	virtual ~SceneMainMenu();

	virtual bool Initialise(Renderer& renderer, GUIManager& m_pGUIManager);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

private:
	SceneMainMenu(const SceneMainMenu& sceneMainMenu);
	SceneMainMenu& operator=(const SceneMainMenu& sceneMainMenu);

	//MemberData
public:

private:
	GUIManager* m_pGUIManager;

};

#endif // !__SCENEMAINMENU_H__
