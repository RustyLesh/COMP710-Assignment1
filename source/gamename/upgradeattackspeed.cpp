// COMP710 Les Mcilroy

// This include:
#include "upgradeattackspeed.h"

// Local includes:
#include "renderer.h"
#include "player.h"

// Library includes:
#include <cassert> 

UpgradeAttackSpeed::UpgradeAttackSpeed()
{ 
 
}

UpgradeAttackSpeed::~UpgradeAttackSpeed()
{

}

void
UpgradeAttackSpeed::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\ArrowUp.png");
}

void
UpgradeAttackSpeed::ApplyUpgrade(Player * player)
{
	player->m_attackDelay -= 0.05;
}
