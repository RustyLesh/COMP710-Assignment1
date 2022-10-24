#include "scenemainmenu.h"

#include "guicontainer.h"
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "scenemanager.h"

SceneMainMenu::SceneMainMenu()
{
}

SceneMainMenu::~SceneMainMenu()
{
}

bool SceneMainMenu::Initialise(Renderer& renderer, GUIManager& guiManager)
{
	m_pGUIManager = &guiManager;
	return false;
}

void SceneMainMenu::Process(float deltaTime, InputSystem & inputSystem)
{

}

void SceneMainMenu::Draw(Renderer & renderer)
{
}

void SceneMainMenu::DebugDraw()
{

}
