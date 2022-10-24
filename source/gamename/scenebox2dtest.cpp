// COMP710 Les Mcilroy

// This include:
#include "scenebox2dtest.h"

// Local includes:
#include "renderer.h"
#include "box2d/box2d.h"
#include "crate.h"
#include "imgui/imgui_impl_sdl.h"
#include "sprite.h"
#include "vector2.h"

// Library includes:
#include <cassert> 

SceneBox2dTest::SceneBox2dTest()
{

}

SceneBox2dTest::~SceneBox2dTest()
{
	delete world;
	world = 0;

	for (Crate* crate : m_pCrates)
	{
		delete crate;
	}

	m_pCrates.clear();

	delete m_pGroundMark;
	m_pGroundMark = 0;
}

bool
SceneBox2dTest::Initialise(Renderer & renderer, GUIManager & guiManager)
{
	m_pRenderer = &renderer;

	InitialiseGizmos();

	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);

	b2BodyDef groundBodyDef;

	Vector2 groundCenter(renderer.GetWidth()*.75, renderer.GetHeight()*.75f);
	groundBodyDef.position.Set(groundCenter.x, groundCenter.y);


	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;

	groundBox.SetAsBox(renderer.GetWidth(), 1.0f); // Size of ground box

	groundBody->CreateFixture(&groundBox, 0.0f);

	m_pGroundMark->SetX(groundCenter.x);
	m_pGroundMark->SetY(groundCenter.y);

	return true;
}

void
SceneBox2dTest::Process(float deltaTime, InputSystem& inputSystem)
{
	world->Step(deltaTime, 6, 2);
	for (Crate* crate : m_pCrates)
	{
		crate->Process(deltaTime);
	}
}

void
SceneBox2dTest::Draw(Renderer& renderer)
{
	for (Crate* crate : m_pCrates)
	{
		crate->Draw(renderer);
	}

	if (m_bgizmoVisable)
	{
		DrawGizmos();
	}
}

void
SceneBox2dTest::DebugDraw()
{
	ImGui::Text("Scene: Box2d Test");

	static int editCrateNumber = 0;
	ImGui::Text("%i", m_pCrates.size());
	if (ImGui::Button("SpawnCrate"))
	{
		spawnCrate();
	}

	if (ImGui::Button("Toggle Gizmo"))
	{
		ToggleGroundCenterGizmo();
	}
}


void
SceneBox2dTest::ToggleGroundCenterGizmo()
{
	m_bgizmoVisable = !m_bgizmoVisable;
}

void
SceneBox2dTest::DrawGizmos()
{
	m_pGroundMark->Draw(*m_pRenderer);
}

void 
SceneBox2dTest::InitialiseGizmos()
{
	m_pGroundMark = m_pRenderer->CreateSprite("sprites\\ball.png");
}

void
SceneBox2dTest::spawnCrate()
{
	Crate* crate = 0;
	crate = new Crate();
	crate->Initialise(*m_pRenderer, world);
	m_pCrates.push_back(crate);
}
