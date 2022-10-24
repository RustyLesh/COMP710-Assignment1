// COMP710 Les Mcilroy

// This include:
#include "scene.h"

// Local includes:
#include "renderer.h"
#include "guimanager.h"

// Library includes:
#include <cassert> 

Scene::Scene()
{ 
 
}

Scene::~Scene()
{

}

bool
Scene::Initialise(Renderer& renderer, GUIManager& guiManager)
{
	return false;
}

void
Scene::Process(float deltaTime, InputSystem& inputSystem)
{
	assert(0);
}

void
Scene::Draw(Renderer& renderer)
{
	assert(0);
}
