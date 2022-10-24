// COMP710 Les Mcilroy

// This include
#include "guimanager.h"

// Local includes:
#include "inputsystem.h"
#include "logmanager.h"
#include "sprite.h"
#include "guicontainer.h"
#include "renderer.h"
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "scenemanager.h"
#include "upgradesmanager.h"
#include "upgrade.h"
#include "player.h"

// Library includes
#include <vector>

GUIManager::GUIManager()
	:m_isPaused(false)
{
}

GUIManager::~GUIManager()
{
	for (GUIContainer * container : m_guiContainers)
	{
		delete container;
	}
	m_guiContainers.clear();

	delete m_pUpgradeManager;
}

void GUIManager::Process(float deltaTime, InputSystem & inputSystem)
{
	for (GUIContainer * container : m_guiContainers)
	{
		if (container->IsVisable())
		{
			container->Process(deltaTime, inputSystem);
		}
	}

	m_pUpgradeManager->Process(inputSystem);
}

void GUIManager::Draw(Renderer & renderer)
{
	for (GUIContainer * container : m_guiContainers)
	{
		if (container->IsVisable())
		{
			container->Draw(renderer);
		}
	}

	//Drawing Upgrade ui While waiting for select
	if (m_pUpgradeManager->m_isUpgrading && m_pUpgradeManager->m_isUpGradesHaveRolled)
	{
		m_GUIInGameUpgradeMenu->Draw(renderer);
		m_isPaused = true;
		m_GUIInGameUpgradeMenu->SetVisable(false);
		m_pUpgradeManager->Draw(renderer);
	}

	//Upgrade selected
	if (m_pUpgradeManager->m_isUpgradeCompleted)
	{
		m_isPaused = false;
		m_pUpgradeManager->m_isUpgradeCompleted = false;
	}
}

bool GUIManager::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;
	m_screenCenter = Vector2(m_pRenderer->GetWidth() / 2, m_pRenderer->GetHeight() / 2);

	//GUI inits

	//--Pause Menu
	m_GUIPauseMenu = new GUIContainer();
	m_GUIPauseMenu->Initialise(renderer);

	//Sprites
	m_GUIPauseMenu->AddSprite(CreateNewSprite("gui\\MainMenu\\mainMenuBG.png", 1, m_screenCenter.x, m_screenCenter.y, 1, 1, 1, 0.5));

	m_guiContainers.push_back(m_GUIPauseMenu);

	//--Main Menu
	m_GUIMainMenu = new GUIContainer();
	m_GUIMainMenu->Initialise(renderer);

	//MenuSprites
	m_GUIMainMenu->AddSprite(CreateNewSprite("gui\\MainMenu\\TitleScreen.png", 1, m_screenCenter.x, m_screenCenter.y, 1, 1, 1, 1));
	m_guiContainers.push_back(m_GUIMainMenu);

	m_GUIMainHowToPlay = new GUIContainer();
	m_GUIMainHowToPlay->Initialise(renderer);
	m_GUIMainHowToPlay->AddSprite(CreateNewSprite("gui\\MainMenu\\HowToPlay.png", 1, m_screenCenter.x, m_screenCenter.y, 1, 1, 1, 1));
	m_guiContainers.push_back(m_GUIMainHowToPlay);
		//How to play


	//--Upgrade Menu
	m_GUIInGameUpgradeMenu = new GUIContainer();
	m_GUIInGameUpgradeMenu->Initialise(renderer);

	//--BG Sprites
	m_GUIInGameUpgradeMenu->AddSprite(CreateNewSprite("gui\\UpgradeMenu\\UpgradeMenuBG.png", 2, m_screenCenter.x, m_screenCenter.y, 1, 1, 1, 1));
	m_upTopLeft = Vector2(m_screenCenter.x - (m_GUIInGameUpgradeMenu->GetFirstElementHeight()) / 2 
		, m_screenCenter.y - (m_GUIInGameUpgradeMenu->GetFirstElementHeight()) / 2);

	m_guiContainers.push_back(m_GUIInGameUpgradeMenu);

	//End Screen
	m_GUIEndScreen = new GUIContainer();
	m_GUIEndScreen->Initialise(renderer);

	m_GUIEndScreen->AddSprite(CreateNewSprite("gui\\MainMenu\\EndScreen.png", 1, m_screenCenter.x, m_screenCenter.y, 1, 1, 1, 1));
	m_guiContainers.push_back(m_GUIEndScreen);

	//Win Screen
	
	m_GUIWinScreen = new GUIContainer();
	m_GUIWinScreen->Initialise(renderer);

	m_GUIWinScreen->AddSprite(CreateNewSprite("gui\\MainMenu\\WinScreen.png", 1, m_screenCenter.x, m_screenCenter.y, 1, 1, 1, 1));
	m_guiContainers.push_back(m_GUIWinScreen);

	//Init upgrades manager
	m_pUpgradeManager = new UpgradesManager();
	m_pUpgradeManager->Initialise(renderer, m_upTopLeft);

	return false;
}

void GUIManager::DebugDraw()
{
	m_pUpgradeManager->DebugDraw();
}

Sprite*
GUIManager::CreateNewSprite(const char * pcFileName, float scale, float posx, float posy, float colourR, float colourG, float colourB, float alpha)
{
	Sprite* newSprite = m_pRenderer->CreateSprite(pcFileName);
	newSprite->SetScale(scale);
	newSprite->SetX(posx);
	newSprite->SetY(posy);
	newSprite->SetRedTint(colourG);
	newSprite->SetGreenTint(colourG);
	newSprite->SetBlueTint(colourB);
	newSprite->SetAlpha(alpha);

	return newSprite;
}

void
GUIManager::LevelPlayer()
{
	m_GUIInGameUpgradeMenu->SetVisable(true);
	m_isPaused = true;
	m_pUpgradeManager->m_isUpgrading = true;
	m_pUpgradeManager->m_isUpgradeToRoll = true;
}

