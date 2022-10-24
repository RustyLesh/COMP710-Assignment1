// COMP710 Les Mcilroy

// This include:
#include "crate.h"

// Local includes:
#include "renderer.h"
#include "box2d/box2d.h"
#include "sprite.h"
#include "inlinehelpers.h"
// Library includes:
#include <cassert> 

Crate::Crate()
	: m_pSprite(0)
	, m_bAlive(true)
{

}

Crate::~Crate()
{
	delete m_pSprite;
	m_pSprite = 0;
}


bool Crate::Initialise(Renderer & renderer, b2World* b2world)
{
	m_pSprite = renderer.CreateSprite("sprites\\ball.png");
	m_pSprite->SetScale(.5);
	float range = 50;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(renderer.GetWidth() / 2 + GetRandom(-range, +range), renderer.GetHeight() / 2);
	body = b2world->CreateBody(&bodyDef);

	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = m_pSprite->GetWidth() / 2;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = .5f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1;
	m_pFixture = body->CreateFixture(&fixtureDef);


	return false;
}

void
Crate::Process(float deltaTime)
{
	pos = body->GetPosition();
	m_pSprite->SetX(static_cast<int>(pos.x));
	m_pSprite->SetY(static_cast<int>(pos.y));
	m_pSprite->Process(deltaTime);
}

void
Crate::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pSprite->Draw(renderer);
	}
}

void Crate::DebugDraw()
{
	ImGui::InputFloat2("Position", reinterpret_cast<float*>(&pos));
}

void
Crate::Kill()
{
	m_bAlive = false;
}

bool
Crate::IsAlive() const
{
	return m_bAlive;
}
