// COMP710 Les Mcilroy

// This include:
#include "sceneparticleemitter.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "imgui/imgui_impl_sdl.h"
#include "particleemitter.h"

// Library includes:
#include <cassert> 

SceneParticleEmitter::SceneParticleEmitter()
	:m_pParticleEmitter(0)
{
}

SceneParticleEmitter::~SceneParticleEmitter()
{
	delete m_pParticleEmitter;
	m_pParticleEmitter = 0;
}


bool 
SceneParticleEmitter::Initialise(Renderer & renderer, GUIManager & guiManager)
{
	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->Initialise(renderer);

	return false;
}

void
SceneParticleEmitter::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pParticleEmitter->Process(deltaTime);
}

void
SceneParticleEmitter::Draw(Renderer& renderer)
{
	m_pParticleEmitter->Draw(renderer);
}

void SceneParticleEmitter::DebugDraw()
{
	ImGui::Text("Scene: ParticleEmitterTest");
	m_pParticleEmitter->DebugDraw();
}

