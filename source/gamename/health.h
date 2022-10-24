// COMP710 Les Mcilroy
#ifndef __HEALTH_H__
#define __HEALTH_H__

class Health
{
	// Member methods:
public:
	Health(int maxHealthPoints);
	~Health();

	void DebugDraw();

	float GetCurrentHealth();
	float GetMaxHealth();

	void ProcessRegen(float deltaTime);
	void SetMaxHealth(float amount);
	void AddRegen(float amount);
	float Damage(float amount);
	void Heal(float amount);

private:

	// Member data
public:

private:
	float m_fCurrentHealth;
	float m_fMaxHealth;
	float m_healthRegen;
};

#endif //__HEALTH_H__