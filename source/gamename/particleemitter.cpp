// COMP710 Les Mcilroy

// This include:
#include "particleemitter.h"

// Local includes:
#include "renderer.h"
#include "particle.h"
#include "imgui/imgui_impl_sdl.h"
// Library includes:
#include <cassert> 
#include <tgmath.h>
#include <cstdlib>

ParticleEmitter::ParticleEmitter()  //TODO: able ti random more varaibles
	: m_pSharedSprite(0)
	, m_iSpawnBatchSize(1)
	, m_fTimeElapsed(0)
	, m_fMaxLifespan(3)
	, m_fEmitRate(1)
	, m_fAccelerationScalar(10)
	, m_fMinAngle(0)
	, m_fMaxAngle(6.33)
	, m_fX(0)
	, m_fY(0)
	, m_bDrawFromFront(false)
	, m_fColour{ 0 }//TODO: Add lerping for colour
	, m_iAliveCount(0)
	, m_scale(0)
{

}

ParticleEmitter::~ParticleEmitter()
{
	for (Particle *particle : m_particles)
	{
		delete particle;
	}
	m_particles.clear();

	delete m_pSharedSprite;
	m_pSharedSprite = 0;
}

bool
ParticleEmitter::Initialise(Renderer& renderer)
{
	m_pSharedSprite = renderer.CreateSprite("sprites\\ball.png");
	m_fX = renderer.GetWidth() / 2;
	m_fY = renderer.GetHeight() / 2;
	return true;
}

void
ParticleEmitter::Process(float deltaTime)
{
	m_fTimeElapsed += deltaTime;
	if (m_fTimeElapsed > m_fEmitRate)
	{
		Spawn();
		m_fTimeElapsed = 0;
	}

	for (int i = 0; i < m_iAliveCount; i++)
	{
		m_particles[i]->Process(deltaTime);
		if (!m_particles[i]->m_bAlive)
		{
			KillParticle(i);
		}
	}
}

void
ParticleEmitter::Draw(Renderer& renderer)
{
	if (m_bDrawFromFront)
	{
		for (Particle *particle : m_particles)
		{
			particle->Draw(renderer);
		}
	}
	else
	{
		for (int i = m_particles.size() - 1; i >= 0; i--)
		{
			m_particles[i]->Draw(renderer);
		}
	}
}

void ParticleEmitter::SetEmitterSettings(int spawnBatchSize, float emitRate, float maxLifespan, float accelerationScalar, float r, float g, float b, float minAngle, float maxAngle)
{

	m_iSpawnBatchSize = spawnBatchSize;
	m_fEmitRate = emitRate;
	m_fMaxLifespan = maxLifespan;
	m_fAccelerationScalar = accelerationScalar;
	m_fColour[0] = r;
	m_fColour[1] = g;
	m_fColour[2] = b;
	m_fMinAngle = minAngle;
	m_fMaxAngle = maxAngle;

}

void ParticleEmitter::setScale(float scale)
{
	m_scale = scale;
}

void ParticleEmitter::Spawn() //Creates or Recycles a particle
{
	for (int i = 0; i < m_iSpawnBatchSize; i++)
	{
		if (m_iAliveCount < m_particles.size())
		{
			Recycle();
		}
		else
		{
			Particle* particle = 0;
			particle = new Particle();
			particle->Initialise(*m_pSharedSprite);
			particle->m_fMaxLifespan = m_fMaxLifespan;
			particle->m_position.x = m_fX;
			particle->m_position.y = m_fY;
			particle->m_bAlive = true;

			particle->m_fColour[0] = m_fColour[0];
			particle->m_fColour[1] = m_fColour[1];
			particle->m_fColour[2] = m_fColour[2];

			particle->SetStartScale(m_scale);

			if (m_fMinAngle > m_fMaxAngle)
			{
				m_fMinAngle = m_fMaxAngle;
			}

			float r = ((m_fMinAngle + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_fMaxAngle - m_fMinAngle)))) - 90) * (M_PI / 180);
			//Convert degree to rad and rotoate 90degrees anti clockwise.

			particle->m_acceleration = Vector2((float)cos(r) *m_fAccelerationScalar, (float)sin(r) *m_fAccelerationScalar);

			m_particles.push_back(particle);
		}

		m_iAliveCount++;
	}
}

void ParticleEmitter::Recycle() //Assigns a dead particle with starting values.
{
	m_particles[m_iAliveCount]->Initialise(*m_pSharedSprite);
	m_particles[m_iAliveCount]->m_fMaxLifespan = m_fMaxLifespan;
	m_particles[m_iAliveCount]->m_position.x = m_fX;
	m_particles[m_iAliveCount]->m_position.y = m_fY;
	m_particles[m_iAliveCount]->m_bAlive = true;
	m_particles[m_iAliveCount]->m_fColour[0] = m_fColour[0];
	m_particles[m_iAliveCount]->m_fColour[1] = m_fColour[1];
	m_particles[m_iAliveCount]->m_fColour[2] = m_fColour[2];
	m_particles[m_iAliveCount]->m_fCurrentAge = 0;
	m_particles[m_iAliveCount]->m_velocity = Vector2();
	m_particles[m_iAliveCount]->SetStartScale(m_scale);

	if (m_fMinAngle > m_fMaxAngle)
	{
		m_fMinAngle = m_fMaxAngle;
	}

	float r = ((m_fMinAngle + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_fMaxAngle - m_fMinAngle)))) - 90) * (M_PI / 180);
	//Convert degree to rad and rotoate 90degrees anti clockwise.

	m_particles[m_iAliveCount]->m_acceleration = Vector2((float)cos(r) *m_fAccelerationScalar, (float)sin(r) *m_fAccelerationScalar);
}

void ParticleEmitter::KillParticle(int particleToKill)
{
	if (m_iAliveCount > 1)
	{
		std::swap(m_particles[m_iAliveCount - 1], m_particles[particleToKill]);
		m_iAliveCount--;
	}
}

void ParticleEmitter::SetLocation(int x, int y)
{
	m_fX = x;
	m_fY = y;
}

void ParticleEmitter::DebugDraw()
{
	ImGui::Text("Scene: particles");
	ImGui::Text("Particles: %i", m_particles.size());
	ImGui::SliderInt("Batch Size ", &m_iSpawnBatchSize, 0, 100, "%d");
	ImGui::SliderFloat("Imit Rate ", &m_fEmitRate, 0, 10, "%f");
	ImGui::SliderFloat("Acc Scaler ", &m_fAccelerationScalar, -1000, 1000, "%f");
	ImGui::SliderFloat("Ming Angle ", &m_fMinAngle, -180.0f, 360.0f, "%f");
	ImGui::SliderFloat("Max Angle ", &m_fMaxAngle, -180.0f, 360.0f, "%f");
	ImGui::Checkbox("Draw from front? ", &m_bDrawFromFront);

	float colour[3];
	colour[0] = m_fColour[0];
	colour[1] = m_fColour[1];
	colour[2] = m_fColour[2];
	ImGui::ColorEdit3("Ball colour", colour);

	m_fColour[0] = colour[0];
	m_fColour[1] = colour[1];
	m_fColour[2] = colour[2];
}
