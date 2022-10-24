// COMP710 Les Mcilroy
#ifndef __SCENESPLASHAUT_H__
#define __SCENESPLASHAUT_H__

//Local includes
#include "scene.h"

// Forward declarations:
class Renderer;
class Sprite;

// Class declaration:
class SceneSplashAut : public Scene
{
	// Member methods:
public:
	SceneSplashAut();
	virtual ~SceneSplashAut();

	virtual bool Initialise(Renderer& renderer, GUIManager& m_pGUIManager);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

protected:

private:
	SceneSplashAut(const SceneSplashAut& lowerCaseName);
	SceneSplashAut& operator=(const SceneSplashAut& scenesplashaut);

	// Member data:
public:

protected:
	Sprite* m_pLogoSplash;
	float m_scale;
	float m_spriteAlpha;
	float m_alphaChangeSpeed;
	float m_delay;
	float m_delayCounter;

	bool m_isToFade;
	float m_stickCounter;
	float m_blackCounter;
private:

};

#endif //__SCENESPLASHAUT_H__
