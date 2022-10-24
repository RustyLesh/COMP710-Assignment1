// COMP710 Les Mcilroy
#ifndef __SCENEPARTICLEEMITTER_H__
#define __SCENEPARTICLEEMITTER_H__

//Local includes
#include "scene.h"

#include <vector>

// Forward declarations:
class Renderer;
class Sprite;
class ParticleEmitter;

// Class declaration:
class SceneParticleEmitter : public Scene
	{
	// Member methods:
public:
	SceneParticleEmitter();
	virtual ~SceneParticleEmitter();

	virtual bool Initialise(Renderer& renderer, GUIManager& guiManager);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:
	SceneParticleEmitter(const SceneParticleEmitter& lowerCaseName);
	SceneParticleEmitter& operator=(const SceneParticleEmitter& sceneparticleemitter);

	// Member data:
public:

protected:
	ParticleEmitter* m_pParticleEmitter;
private:

};

#endif //__SCENEPARTICLEEMITTER_H__
