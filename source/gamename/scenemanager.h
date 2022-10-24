//COMP710 Les Mcilroy
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <vector>

//Class declaration
class Player;
class Scene;
class Renderer;
class GUIManager;
class InputSystem;
class GUIManager;
class PlayerStats;

enum ScenesEnum
{
	SCENE_SPLASHSCREEN,
	SCENE_MAINMENU,
	SCENE_DEFEND,
	SCENE_EMITTER,
	SCENE_BOX2DTEST,
	SCENE_BALLGAME,
	SCENE_CHECKERBAORDS,

};

enum MainMenuEnum
{
	MAIN_START,
	MAIN_HOWTO,
	MAIN_UPGRADES,
};

class SceneManager
{
	//Member methods
public: 
	static SceneManager& GetInstance();
	static void DestroyInstance();

	void ChangeScene(ScenesEnum NextScene);
	void ResetScene(ScenesEnum sceneEnum);

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);

	void DebugDraw();
	GUIManager* GetGUIManager();
	
	//HACK: Player is global
	Player* m_pPlayer;

private:
	SceneManager();
	~SceneManager();
	SceneManager(const SceneManager& sceneManager);
	SceneManager& operator=(const SceneManager& sceneManager);

	//Main Menu
	void ChangeMainMenu(MainMenuEnum mainMenuEnum);

	//Member data
private:
	GUIManager* m_pGUIManager;
	static SceneManager* sm_pInstance;

	std::vector<Scene*> m_scenes;
	float m_timer;

	MainMenuEnum m_currentMenu;
	ScenesEnum m_currentScene;
	Renderer* m_pRenderer;
	PlayerStats* m_playerStats;
	//NOTE: Debug
	bool m_isSkipToDefendScene;
};

#endif // !__SCENEMANAGER_H__