// COMP710 Les Mcilroy
#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

//Local includes
#include "vector2.h"
#include "scenemanager.h"

//Library includes
#include <vector>

//Foward declarations
class Sprite;
class Renderer;
class InputSystem;
class GUIContainer;
class UpgradesManager;
class Upgrade;
class Player;

//Class declaration
class GUIManager
{
	//Member methods
public:
	GUIManager();
	~GUIManager();

	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	bool Initialise(Renderer& renderer);
	void LevelPlayer();

	Player* m_pPlayer;

	//Upgrade Manager GUI Cords
	Vector2 m_upTopLeft;
	void DebugDraw();
private:
	GUIManager(const GUIManager& lowerCaseName);
	GUIManager& operator=(const GUIManager& scenedefend);

	Sprite* CreateNewSprite(const char * pcFileName, float scale, float posx, float posy, float colourR, float colourG, float colourB, float Alpha);

	//Member data
public:
	//TODO Unspeghetti pausing - Move all pausing functionality into Defend Scene
	bool m_isPaused;

	GUIContainer* m_GUIPauseMenu;
	GUIContainer* m_GUIMainMenu;
	GUIContainer* m_GUIInGameUpgradeMenu;
	GUIContainer* m_GUIMetaUpgradeMenu;
	GUIContainer* m_GUIMainHowToPlay;
	GUIContainer* m_GUIEndScreen;
	GUIContainer* m_GUIWinScreen;

	UpgradesManager* m_pUpgradeManager;

private:
	std::vector<GUIContainer*> m_guiContainers;
	Renderer* m_pRenderer;
	InputSystem* m_inputSystem;
	Vector2 m_screenCenter;


};

#endif // !__GUIMANAGER_H__
