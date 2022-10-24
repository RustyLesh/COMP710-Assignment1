// COMP710 Les Mcilroy

//This include:
#include "health.h"

//Local includes
#include "inlinehelpers.h"
#include "logmanager.h"

Health::Health(int maxHealthPoints)
	:m_fMaxHealth(maxHealthPoints)
	, m_fCurrentHealth(maxHealthPoints)
	, m_healthRegen(0)
{
}

Health::~Health()
{
}

void Health::DebugDraw()
{
}

float Health::GetCurrentHealth()
{
	return m_fCurrentHealth;
}

float Health::GetMaxHealth()
{
	return m_fMaxHealth;
}

//Returns curent health after damage, ammount must be > 0
float Health::Damage(float amount)
{
	if (amount > 0)
	{
		return(m_fCurrentHealth = Clamp(0, m_fCurrentHealth - amount, m_fMaxHealth));
	}
	else
	{
		LogManager::GetInstance().Log("Tried to deal <= 0 damage");
		return m_fCurrentHealth;
	}


}

//Increase health value, amount must be > 0
void Health::Heal(float amount)
{
	if (amount > 0)
	{
		m_fCurrentHealth = Clamp(0, m_fCurrentHealth + amount, m_fMaxHealth);
	}
	else
	{
		LogManager::GetInstance().Log("Tried to heal for < 0 health");
	}
}

void Health::ProcessRegen(float deltaTime)
{
	if (m_fCurrentHealth <= m_fMaxHealth)
	{
		m_fCurrentHealth = Clamp(0, (m_fCurrentHealth + (m_healthRegen * deltaTime)), m_fMaxHealth);
	}

}

void Health::SetMaxHealth(float amount)
{
	if (amount > 0)
	{
		m_fMaxHealth = amount;
	}
	else
	{
		LogManager::GetInstance().Log("Tried to set max health <= 0");
	}
}

void Health::AddRegen(float amount)
{
	m_healthRegen += amount;
}


