#pragma once
// COMP710 GP Framework 
#ifndef __PARTICLEEMITTER_H__ 
#define __PARTICLEEMITTER_H__ 

// Library includes: 
#include <vector> 

// Forward declarations:  
class Renderer;
class Sprite;
class Particle;

// Class declaration:  
class ParticleEmitter
{
	// Member methods:  
public:
	ParticleEmitter();
	~ParticleEmitter();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void SetEmitterSettings(int spawnBatchSize,
	float emitRate,
	float maxLifespan,
	float accelerationScalar,
	float r, float g, float b, 
	float minAngle,
	float maxAngle);
	void setScale(float scale);
	void DebugDraw();
	void SetLocation(int x, int y);

protected:

private:
	ParticleEmitter(const ParticleEmitter& particleemitter);
	ParticleEmitter& operator=(const ParticleEmitter& particleemitter);

	void Spawn();
	void Recycle();
	void KillParticle(int particleToKill);

	// Member data:  
public:

protected:
	Sprite* m_pSharedSprite;
	std::vector<Particle*> m_particles;

	float m_fTimeElapsed;

	int m_iAliveCount;
	int m_iSpawnBatchSize;
	float m_fEmitRate;
	float m_fMaxLifespan;
	float m_fAccelerationScalar;
	float m_fColour[3];
	float m_fMinAngle;
	float m_fMaxAngle;
	float m_fX;
	float m_fY;
	float m_scale;
	bool  m_bDrawFromFront;
private:

};

#endif // __PARTICLEEMITTER_H__ 