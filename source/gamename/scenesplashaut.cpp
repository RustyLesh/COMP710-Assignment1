// COMP710 Les Mcilroy

// This include:
#include "scenesplashaut.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "imgui/imgui_impl_sdl.h"
#include "guimanager.h"
// Library includes:
#include <cassert> 

SceneSplashAut::SceneSplashAut()
	: m_pLogoSplash(0),
	m_spriteAlpha(0),
	m_alphaChangeSpeed(0.4),
	m_scale(0.8),
	m_delay(1.5),
	m_delayCounter(0),
	m_isToFade(false),
	m_stickCounter(0),
	m_blackCounter(0)
{
}

SceneSplashAut::~SceneSplashAut()
{
	delete m_pLogoSplash;
	m_pLogoSplash = 0;
}

bool
SceneSplashAut::Initialise(Renderer& renderer, GUIManager& m_pGUIManager)
{
	m_pLogoSplash = renderer.CreateSprite("gui\\SplashScreen.png");
	m_pLogoSplash->SetAlpha(m_spriteAlpha);
	m_pLogoSplash->SetX(renderer.GetWidth() / 2);
	m_pLogoSplash->SetY(renderer.GetHeight() / 2);
	m_pLogoSplash->SetScale(1);
	return false;
}

void
SceneSplashAut::Process(float deltaTime, InputSystem& inputSystem)
{
	m_delayCounter += deltaTime;

	if (m_delayCounter > m_delay && m_spriteAlpha <= 1 && !m_isToFade) //Stops the alpha from going past 1
	{
		m_spriteAlpha += m_alphaChangeSpeed * deltaTime;
		m_pLogoSplash->SetAlpha(m_spriteAlpha);
	}
	else if (m_isToFade && m_spriteAlpha >= 0 && m_stickCounter > 3)
	{
		m_spriteAlpha -= m_alphaChangeSpeed * deltaTime;
		m_pLogoSplash->SetAlpha(m_spriteAlpha);
	}

	if (m_spriteAlpha >= 1)
	{
		m_isToFade = true;
		m_stickCounter += deltaTime;
	}

	if(m_spriteAlpha <= 0 && m_stickCounter > 3)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_MAINMENU);
	}
}

void
SceneSplashAut::Draw(Renderer& renderer)
{
	m_pLogoSplash->Draw(renderer);
}

void
SceneSplashAut::DebugDraw()
{
	ImGui::Text("Alpha %f", m_spriteAlpha);
}
