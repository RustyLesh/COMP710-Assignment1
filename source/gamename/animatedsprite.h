// COMP710 GP Framework 2022
#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

// Local includes:
#include "sprite.h"

// Forward declarations: 
class Renderer;
class VertexArray;

// Class declaration: 
class AnimatedSprite : public Sprite
{
	// Member methods: 
public:
	AnimatedSprite();
	~AnimatedSprite();
	bool Initialise(Texture& texture);
	void SetupFrames(int fixedFrameWidth, int fixedFrameHeight);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void SetLooping(bool loop);
	void Animate();
	bool IsAnimating() const;
	void Restart();
	void SetFrameDuration(float seconds);
	int GetWidth() const;
	int GetHeight() const;
	void DebugDraw();
protected:
private:
	AnimatedSprite(const AnimatedSprite& animatedsprite);
	AnimatedSprite& operator=(const AnimatedSprite& animatedsprite);
	// Member data: 
public:
protected:
	VertexArray* m_pVertexData;
	int m_iFrameWidth;
	int m_iFrameHeight;
	int m_iCurrentFrame;
	int m_iTotalFrames;
	float m_fTimeElapsed;
	float m_frameDuration;
	float m_totalTime;
	bool m_bAnimating;
	bool m_bLooping;
private:
};
#endif // __ANIMATEDSPRITE_H__
