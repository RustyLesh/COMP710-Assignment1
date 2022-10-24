// COMP710 GP Framework 2022
#ifndef __BALL_H__
#define __BALL_H__
// Local includes:
#include "vector2.h"

// Forward declarations: 
class Renderer;
class Sprite;
class InputSystem;

enum BallType
{
	GOODBALL,
	BADBALL,
	PLAYERBALL,
	RANDOMBALL,
};

// Class declaration: 
class Ball
{
	// Member methods: 
public:
	Ball();
	~Ball();
	bool Initialise(Renderer& renderer, BallType _ballType);
	void Process(float deltaTime);
	void ProcessPlayer(InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	void RandomiseColour();
	void RandomiseSize();
	void SetSize(float scale);
	Vector2& Position();

	virtual void DebugDraw();

	void SetPlayerPosition(Vector2 position);

	void SetColour(float r, float g, float b);

	void Shrink();
	void Enlarge();
	float GetRadius();
	void Kill();
	bool IsAlive() const;
	BallType GetBallType()const;

protected:
	void ComputeBounds(int width, int height);
	BallType ballType;

private:
	Ball(const Ball& ball);
	Ball& operator=(const Ball& ball);
	// Member data: 
public:
	Vector2 m_position;

protected:
	Vector2 m_velocity;
	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
	Sprite* m_pSprite;
	bool m_bAlive;
	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;

private:
	float sizeChangeScaler = 0.1f;
};
#endif // __BALL_H__
