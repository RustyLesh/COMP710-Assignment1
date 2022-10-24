// COMP710 Les Mcilroy
#ifndef __CRATE_H__
#define __CRATE_H__

//Local includes
#include "box2d/box2d.h"
#include "imgui/imgui_impl_sdl.h"
// Forward declarations:
class Renderer;
class InputSystem;
class Sprite;
class Vector2;

// Class declaration:
class Crate
	{
	// Member methods:
public:
	Crate();
	~Crate();

	bool Initialise(Renderer& renderer, b2World* b2world);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	virtual void DebugDraw();

	void Kill();
	bool IsAlive() const;
protected:

private:
	Crate(const Crate& lowerCaseName);
	Crate& operator=(const Crate& crate);
	b2Vec2 pos;

	// Member data:
public:
	b2Fixture* m_pFixture;

protected:
	Sprite* m_pSprite;
	bool m_bAlive;
	b2Body* body;
private:
};

#endif //__CRATE_H__
