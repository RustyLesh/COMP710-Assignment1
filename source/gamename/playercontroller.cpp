// COMP710 Les Mcilroy

// This include:
#include "playercontroller.h"

// Local includes:
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "entity.h"
#include "vector2.h"
#include "logmanager.h"
#include "renderer.h"
#include "imgui/imgui_impl_sdl.h"
#include "player.h"
#include "inlinehelpers.h"

// Library includes:
#include <cassert> 

PlayerController::PlayerController()
	:m_movemetSpeed(0.01)
	, m_deadZoneX(2500)
	, m_deadZoneY(2500)
{

}

PlayerController::~PlayerController()
{

}

bool
PlayerController::Initialise(Renderer& renderer)
{
	return false;
}

void
PlayerController::Process(float deltaTime, InputSystem& inputSystem, Player& player)
{
	if (deltaTime <= 0)
	{
		return;
	}

	m_xboxLeftStick = inputSystem.GetController(0)->GetLeftStick();
	m_xboxRightStick = inputSystem.GetController(0)->GetRightStick();

	//Left analogue stick - Movement
	if (abs(m_xboxLeftStick.x) > m_deadZoneX)
	{
		player.m_velocity.x = (m_xboxLeftStick.x - m_deadZoneX) * m_movemetSpeed;
	}
	else
	{
		player.m_velocity.x = 0;
	}
	if (abs(m_xboxLeftStick.y) > m_deadZoneY)
	{
		player.m_velocity.y = (m_xboxLeftStick.y - m_deadZoneY) * m_movemetSpeed;
	}
	else
	{
		player.m_velocity.y = 0;
	}

	//TODO: Lerp roation to slow it down , (non instant rotation)

	//Right Analogue stick - Aim, Rotation
	if (abs(m_xboxRightStick.x) > m_deadZoneX || abs(m_xboxRightStick.y) > m_deadZoneY)
	{
		float r = RadToDeg(atan(m_xboxRightStick.x / m_xboxRightStick.y));

		if (m_xboxRightStick.x > 0 && m_xboxRightStick.y > 0)
		{
			player.Rotate(r + 180);
		}
		else if (m_xboxRightStick.x < 0 && m_xboxRightStick.y > 0)
		{
			player.Rotate(r - 180);
		}

		else if (m_xboxRightStick.x < 0 && m_xboxRightStick.y < 0)
		{
			player.Rotate(r - 360);
		}

		else if (m_xboxRightStick.x > 0 && m_xboxRightStick.y < 0)
		{
			player.Rotate(r);
		}
	}
}

void PlayerController::DebugDraw()
{
	ImGui::Text("PlayerController");
	ImGui::Text("Speed: %f", m_movemetSpeed);
}

