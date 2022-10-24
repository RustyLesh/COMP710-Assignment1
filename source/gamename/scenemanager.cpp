//COMP710 Les Mcilroy

//This include
#include "scenemanager.h"

//Local includes
#include "logmanager.h"
#include "imgui/imgui_impl_sdl.h"
#include "scene.h"
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "guimanager.h"
#include "guicontainer.h"
#include "upgradesmanager.h"
#include "game.h"
#include "player.h"
#include "playerstats.h"

// Scene includes
#include "scenecheckerboards.h"
#include "scenebouncingballs.h"
#include "scenesplashaut.h"
#include "sceneballgame.h"
#include "scenebox2dtest.h"
#include "sceneparticleemitter.h"
#include "scenedefend.h"
#include "scenemainmenu.h"

class Player;

//Static Members
SceneManager* SceneManager::sm_pInstance = 0;

SceneManager::SceneManager()
	:m_currentScene(SCENE_BOX2DTEST)
	, m_currentMenu(MAIN_START)
	, m_isSkipToDefendScene(false)
	, m_timer(0)
{
}

SceneManager::~SceneManager()
{
	delete m_pGUIManager;
	m_pGUIManager = 0;

	for (Scene* scene : m_scenes)
	{
		delete scene;
	}
	m_scenes.clear();


}

SceneManager &
SceneManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new SceneManager();
	}

	return (*sm_pInstance);
}

void SceneManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void SceneManager::ChangeMainMenu(MainMenuEnum mainMenuEnum)
{
	switch (m_currentMenu)
	{
	case MAIN_START:
		m_pGUIManager->m_GUIMainMenu->SetVisable(false);
		break;
	case MAIN_HOWTO:
		m_pGUIManager->m_GUIMainHowToPlay->SetVisable(false);
		break;
	case MAIN_UPGRADES:

		break;
	default:
		break;
	}

	m_currentMenu = mainMenuEnum;

	switch (m_currentMenu)
	{
	case MAIN_START:
		m_pGUIManager->m_GUIMainMenu->SetVisable(true);
		break;
	case MAIN_HOWTO:
		m_pGUIManager->m_GUIMainHowToPlay->SetVisable(true);
		break;
	case MAIN_UPGRADES:

		break;
	default:
		break;
	}
}

void SceneManager::ChangeScene(ScenesEnum NextScene)
{
	switch (m_currentScene)
	{
	case SCENE_SPLASHSCREEN:

		break;

	case SCENE_MAINMENU:
		m_pGUIManager->m_GUIMainMenu->SetReady(false);
		m_pGUIManager->m_GUIMainHowToPlay->SetReady(false);
		m_pGUIManager->m_GUIMainMenu->SetVisable(false);

		break;

	case SCENE_DEFEND:
		m_pGUIManager->m_GUIInGameUpgradeMenu->SetReady(false);
		m_pGUIManager->m_GUIPauseMenu->SetVisable(false);

		m_pGUIManager->m_GUIPauseMenu->SetReady(false);
		m_pGUIManager->m_GUIPauseMenu->SetVisable(false);

		m_pGUIManager->m_isPaused = false;
		m_pGUIManager->m_GUIEndScreen->SetReady(false);
		m_pGUIManager->m_GUIEndScreen->SetVisable(false);

		m_pGUIManager->m_GUIWinScreen->SetReady(false);
		m_pGUIManager->m_GUIWinScreen->SetVisable(false);
		m_timer = 0;
		break;

	default:

		break;
	}

	m_currentScene = NextScene;

	switch (m_currentScene)
	{
	case SCENE_SPLASHSCREEN:

		break;
	case SCENE_MAINMENU:
		m_pGUIManager->m_GUIMainMenu->SetReady(true);
		m_pGUIManager->m_GUIMainMenu->SetVisable(true);
		m_pGUIManager->m_GUIMainHowToPlay->SetReady(true);
		ChangeMainMenu(MAIN_START);

		break;
	case SCENE_DEFEND:
		m_pGUIManager->m_GUIInGameUpgradeMenu->SetReady(true);
		m_pGUIManager->m_GUIPauseMenu->SetReady(true);
		m_pGUIManager->m_GUIEndScreen->SetReady(true);
		m_pGUIManager->m_GUIWinScreen->SetReady(true);

		break;
	default:
		break;
	}
}

void SceneManager::ResetScene(ScenesEnum sceneEnum)
{
	dynamic_cast<SceneDefend*>(m_scenes[sceneEnum])->ResetScene();
}

bool SceneManager::Initialise(Renderer & renderer)
{
	m_pRenderer = &renderer;

	m_pGUIManager = new GUIManager();
	m_pGUIManager->Initialise(*m_pRenderer);

	//Scenes

	Scene* pScene2 = 0;
	pScene2 = new SceneSplashAut;
	pScene2->Initialise(*m_pRenderer, *m_pGUIManager);
	m_scenes.push_back(pScene2);

	Scene* pScene6 = 0;
	pScene6 = new SceneMainMenu;
	pScene6->Initialise(*m_pRenderer, *m_pGUIManager);
	m_scenes.push_back(pScene6);

	Scene* pScene5 = 0;
	pScene5 = new SceneDefend;
	pScene5->Initialise(*m_pRenderer, *m_pGUIManager);
	m_scenes.push_back(pScene5);

	Scene* pSceneP = 0;
	pSceneP = new SceneParticleEmitter;
	pSceneP->Initialise(*m_pRenderer, *m_pGUIManager);
	m_scenes.push_back(pSceneP);

	Scene* pScene7 = 0;
	pScene7 = new SceneBox2dTest;
	pScene7->Initialise(*m_pRenderer, *m_pGUIManager);
	m_scenes.push_back(pScene7);

	m_pPlayer = &dynamic_cast<SceneDefend*>(pScene5)->GetPlayer();

	m_pGUIManager->m_pPlayer = m_pPlayer;
	m_pGUIManager->m_pUpgradeManager->m_pPlayer = m_pPlayer;

	ChangeScene(m_currentScene);
	return true;
}

void SceneManager::Process(float deltaTime, InputSystem & inputSystem)
{
	m_scenes[m_currentScene]->Process(deltaTime, inputSystem);

	m_pGUIManager->Process(deltaTime, inputSystem);

	if (!m_pGUIManager->m_isPaused && m_currentScene == SCENE_DEFEND)
	{
		m_timer += deltaTime;
	}
	switch (m_currentScene)
	{
	case SCENE_SPLASHSCREEN:
		if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_A) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)
		{
			ChangeScene(SCENE_MAINMENU);
		}
		break;
	case SCENE_MAINMENU:

		switch (m_currentMenu)
		{
		case MAIN_START:
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_B) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED)
			{
				Game::GetInstance().Quit();
			}
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_Y) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_RETURN) == BS_PRESSED)
			{
				ChangeMainMenu(MAIN_HOWTO);
			}
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_A) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)
			{
				ChangeScene(SCENE_DEFEND);
			}
			break;
		case MAIN_HOWTO:
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_B) == BS_PRESSED)
			{
				ChangeMainMenu(MAIN_START);
			}
			break;
		case MAIN_UPGRADES:
			break;
		default:
			break;
		}
		break;

	case SCENE_DEFEND:

		//Escape or Start pauses - Pauses processes
		//TODO: Should extract pasuing out into its own method/variable so that it stays paused when specific ui's are visable
		if (inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED ||
			inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_START) == BS_PRESSED)
		{
			if (m_pGUIManager->m_GUIPauseMenu->IsReady())
			{
				if (!m_pGUIManager->m_GUIInGameUpgradeMenu->IsVisable())
				{
					m_pGUIManager->m_isPaused = !m_pGUIManager->m_isPaused;
				}
				m_pGUIManager->m_GUIPauseMenu->SetVisable(!m_pGUIManager->m_GUIPauseMenu->IsVisable());
			}
		}
		if (m_pGUIManager->m_isPaused && inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_BACK) == BS_PRESSED && m_pGUIManager->m_GUIPauseMenu->IsVisable() && !m_pGUIManager->m_GUIInGameUpgradeMenu->IsVisable() || inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED)
		{
			ChangeScene(SCENE_MAINMENU);
			ResetScene(SCENE_DEFEND);
			m_pPlayer->ResetPlayer();
		}

		if (!m_pPlayer->IsAlive())
		{
			m_pGUIManager->m_isPaused = true;
			m_pGUIManager->m_GUIEndScreen->SetVisable(true);
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_A) == BS_PRESSED)
			{
				ChangeScene(SCENE_MAINMENU);
				ResetScene(SCENE_DEFEND);
				m_pPlayer->ResetPlayer();
			}
		}

		if (m_timer > 120)
		{
			m_pGUIManager->m_isPaused = true;
			m_pGUIManager->m_GUIWinScreen->SetVisable(true);
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_A) == BS_PRESSED)
			{
				ChangeScene(SCENE_MAINMENU);
				ResetScene(SCENE_DEFEND);
				m_pPlayer->ResetPlayer();
			}
		}

		//DEBUG INPUT - Should normaly be called automaically on player level.
		//if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_BACK) == BS_PRESSED)
		//{
		//	m_pGUIManager->m_GUIInGameUpgradeMenu->SetVisable(!m_pGUIManager->m_GUIInGameUpgradeMenu->IsVisable());

		//	if(!m_pGUIManager->m_GUIPauseMenu->IsVisable())
		//	{
		//		m_pGUIManager->m_isPaused = !m_pGUIManager->m_isPaused;
		//	}
		//}

		break;

	default:
		break;
	}

	//NOTE: Debugging input

	//if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_B) == BS_PRESSED)
	//{
	//	ChangeScene(SCENE_MAINMENU);
	//}

}

void SceneManager::Draw(Renderer & renderer)
{
	m_scenes[m_currentScene]->Draw(renderer);
	m_pGUIManager->Draw(renderer);
}

void SceneManager::DebugDraw()
{
	ImGui::Text("Scene Timer %f", m_timer);

	//ImGui::SliderInt("Active scene", (int*)m_currentScene, 0, m_scenes.size() - 1, "%i");
	m_scenes[m_currentScene]->DebugDraw();


	if (m_pGUIManager->m_isPaused)
		ImGui::Text("Paused");
	else
		ImGui::Text("Playing");

	m_pGUIManager->DebugDraw();
}

GUIManager *
SceneManager::GetGUIManager()
{
	return m_pGUIManager;
}



