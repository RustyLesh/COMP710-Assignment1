// COMP710 GP Framework 2022

// This include:
#include "game.h"

//Local includes;
#include "imgui/imgui_impl_sdl.h"
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "guimanager.h"
#include "renderer.h"
#include "logmanager.h"
#include "scenemanager.h"

// Library includes:
#include <cstdlib>
#include <ctime>

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pRenderer(0)
	, m_bLooping(true)
	, m_bPauseSimulation(false)
{

}

Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;

	delete m_pInputSystem;
	m_pInputSystem = 0;
}

void
Game::Quit()
{
	m_bLooping = false;
}

bool
Game::Initialise()
{
	srand(time(NULL));

	int bbWidth = 1920;
	int bbHeight = 1080;

	//Initialise Renderer
	m_pRenderer = new Renderer();
	if (!m_pRenderer->Initialise(true, bbWidth, bbHeight)) //Full Screen //TODO create a setting for full screen, save it in INI
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}

	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();

	m_iLastTime = SDL_GetPerformanceCounter();

	m_pRenderer->SetClearColour(20, 20, 0);

	m_pInputSystem = new InputSystem();
	m_pInputSystem->Initialise();

	//Initialise Scene Manager
	m_pSceneManager = &SceneManager::GetInstance();

	if (!m_pSceneManager->Initialise(*m_pRenderer))
	{
		LogManager::GetInstance().Log("Scene Manager failed to initialise!");
		return false;
	}

	return true;
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	// TODO: Process input here!
	m_pInputSystem->ProcessInput();

	if (m_bLooping)
	{
		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_iLastTime = current;

		m_fExecutionTime += deltaTime;

		Process(deltaTime);

#ifdef USE_LAG
		m_fLag += deltaTime;

		int innerLag = 0;

		while (m_fLag >= stepSize)
		{
			Process(stepSize);

			m_fLag -= stepSize;

			++m_iUpdateCount;
			++innerLag;
	}
#endif //USE_LAG

		Draw(*m_pRenderer);
}

	return m_bLooping;
}

void
Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);
	m_pSceneManager->Process(deltaTime, *m_pInputSystem);
}

void
Game::Draw(Renderer& renderer)
{
	++m_iFrameCount;

	renderer.Clear();

	m_pSceneManager->Draw(renderer);

	DebugDraw();

	renderer.Present();
}

void
Game::ProcessFrameCounting(float deltaTime)
{
	// Count total simulation time elapsed:
	m_fElapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_fElapsedSeconds > 1.0f)
	{
		m_fElapsedSeconds -= 1.0f;
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}
}

void
Game::DebugDraw()
{
	if (m_bShowDebugWindow)
	{
		bool open = true;
		ImGui::Begin("Debug Window", &open, ImGuiWindowFlags_MenuBar);
		ImGui::Text("COMP710 GP Framework (%s)", "2022, S2");
		if (ImGui::Button("Quit"))
		{
			Quit();
		}

		m_pSceneManager->DebugDraw();

		ImGui::Separator();
		LogManager::GetInstance().DebugDraw();

		ImGui::End();
	}
}

void
Game::ToggleDebugWindow()
{
	m_bShowDebugWindow = !m_bShowDebugWindow;
	m_pInputSystem->ShowMouseCursor(m_bShowDebugWindow);
}



