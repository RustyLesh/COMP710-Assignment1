// COMP710 Les Mcilroy

// This include:
#include "sceneballgame.h"

// Local includes:
#include "renderer.h"
#include "ball.h"
#include "imgui/imgui_impl_sdl.h"
#include "inputsystem.h"

// Library includes:
#include <cassert> 
#include <cstdlib>

SceneBallGame::SceneBallGame()
	: m_pPlayerBall(0)
{

}

SceneBallGame::~SceneBallGame()
{
	for (Ball* ball : m_pGoodBalls)
	{
		delete ball;
	}
	m_pGoodBalls.clear();

	for (Ball* ball : m_pBadBalls)
	{
		delete ball;
	}
	m_pBadBalls.clear();

	delete m_pPlayerBall;
	m_pPlayerBall = 0;
}

bool
SceneBallGame::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

	m_pPlayerBall = new Ball();
	m_pPlayerBall->Initialise(renderer, PLAYERBALL);
	m_pPlayerBall->RandomiseColour();
	m_pPlayerBall->SetSize(1.0f);

	return true;
}

void
SceneBallGame::Process(float deltaTime, InputSystem& inputSystem)
{
	unsigned int i = 0;
	while (i < m_pGoodBalls.size())
	{
		m_pGoodBalls[i]->Process(deltaTime);
		i++;
	}

	for (int i = 0; i < m_pBadBalls.size(); i++)
	{
		m_pBadBalls[i]->Process(deltaTime);
	}

	m_pPlayerBall->ProcessPlayer(inputSystem);

	CheckCollisions();
}

void
SceneBallGame::Draw(Renderer& renderer)
{
	unsigned int i = 0;
	while (i < m_pGoodBalls.size())
	{
		m_pGoodBalls[i]->Draw(renderer);

		i++;
	}

	for (unsigned int i = 0; i < m_pBadBalls.size(); i++)
	{
		m_pBadBalls[i]->Draw(renderer);
	}

	m_pPlayerBall->Draw(renderer);
}

void
SceneBallGame::DebugDraw()
{
	ImGui::Text("Scene: Bouncing Balls");
	static int editBallNumber = 0;
	m_pPlayerBall->DebugDraw();
	if (ImGui::Button("SpawnGoodBalls"))
	{
		SpawnGoodBalls(10);
	}
	if (ImGui::Button("SpawnBadBalls"))
	{
		SpawnBadBalls(10);
	}
	ImGui::Text("%i", m_pGoodBalls.size());
}

void SceneBallGame::SpawnGoodBalls(int number)
{
	for (int i = 0; i < number; i++)
	{
		Ball* ball = 0;
		ball = new Ball();
		ball->Initialise(*m_pRenderer, GOODBALL);
		m_pGoodBalls.push_back(ball);
		ball->SetColour(0.0f, 1.0f, 0.0f);
	}
}

void SceneBallGame::SpawnBadBalls(int number)
{
	for (int i = 0; i < number; i++)
	{
		Ball* ball = 0;
		ball = new Ball();
		ball->Initialise(*m_pRenderer, BADBALL);
		m_pBadBalls.push_back(ball);
		ball->SetColour(1.0f, 0.0f, 0.0f);
	}
}


void SceneBallGame::CheckCollisions()
{
	for (int i = 0; i < m_pGoodBalls.size(); i++)
	{
		if (BallVsBall(m_pPlayerBall, m_pGoodBalls[i]))
		{
			if (m_pGoodBalls[i]->IsAlive())
			{
				m_pGoodBalls[i]->Kill();
				m_pPlayerBall->Enlarge();
			}
		}
	}

	for (int j = 0; j < m_pBadBalls.size(); j++)
	{
		if (BallVsBall(m_pPlayerBall, m_pBadBalls[j]))
		{
			if (m_pBadBalls[j]->IsAlive())
			{
				m_pBadBalls[j]->Kill();
				m_pPlayerBall->Shrink();
			}
		}
	}
}

bool SceneBallGame::BallVsBall(Ball* p1, Ball* p2)
{
	float x1 = p1->Position().x;
	float y1 = p1->Position().y;

	float x2 = p2->Position().x;
	float y2 = p2->Position().y;

	float r1 = p1->GetRadius();
	float r2 = p2->GetRadius();

	float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) - r1 - r2;

	return (distance <= 0);
}


