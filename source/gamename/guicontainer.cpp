//Comp710 Les Mcilroy
#include "guicontainer.h"

//Local includes
#include "sprite.h"

GUIContainer::GUIContainer()
	:m_isVisable(false)
	,m_isReady(false)
{
}

GUIContainer::~GUIContainer()
{
	for (Sprite * sprite : m_spriteVector)
	{
		delete sprite;
	}
	m_spriteVector.clear();
}

void GUIContainer::Process(float deltaTime, InputSystem & inputSystem)
{

	for (Sprite * sprite : m_spriteVector)
	{
		sprite->Process(deltaTime);
	}
}

void GUIContainer::Draw(Renderer & renderer)
{
	for (Sprite * sprite : m_spriteVector)
	{
		sprite->Draw(renderer);
	}
}

bool GUIContainer::Initialise(Renderer & renderer)
{
	return false;
}

void GUIContainer::AddSprite(Sprite* sprite)
{
	m_spriteVector.push_back(sprite);
}

void GUIContainer::SetVisable(bool setActive)
{
	m_isVisable = setActive;
}

void GUIContainer::SetReady(bool setReady)
{
	m_isReady = setReady;
}

bool
GUIContainer::IsVisable()
{
	return m_isVisable;
}

bool GUIContainer::IsReady()
{
	return m_isReady;
}

float GUIContainer::GetFirstElementHeight()
{
	return m_spriteVector[0]->GetHeight();
}

float GUIContainer::GetFirstElementWidth()
{
	return m_spriteVector[0]->GetWidth();
}
