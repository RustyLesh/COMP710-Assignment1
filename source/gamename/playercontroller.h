// COMP710 Les Mcilroy
#ifndef __PLAYERMOVEMENT_H__
#define __PLAYERMOVEMENT_H__

//Local includes
#include "vector2.h"
#include "inputsystem.h"

// Forward declarations:
class Renderer;
class InputSystem;
class Vector2;
class Player;

// Class declaration:
class PlayerController
{
	// Member methods:
public:
	PlayerController();
	~PlayerController();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem, Player& player);

	void DebugDraw();
protected:

private:
	PlayerController(const PlayerController& lowerCaseName);
	PlayerController& operator=(const PlayerController& playermovement);

	// Member data:
public:
	float speedMultiplier;
	float m_deadZoneX;
	float m_deadZoneY;
	float m_movemetSpeed;

protected:

private:
	Vector2 m_xboxLeftStick;
	Vector2 m_xboxRightStick;
	ButtonState m_xboxA;

};

#endif //__PLAYERMOVEMENT_H__
