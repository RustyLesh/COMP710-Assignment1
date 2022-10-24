// COMP710 Les Mcilroy

// This include:
#include "upgradexpgain.h"

// Local includes:
#include "renderer.h"
#include "player.h"

// Library includes:
#include <cassert> 

UpgradeXPGain::UpgradeXPGain()
{ 
 
}

UpgradeXPGain::~UpgradeXPGain()
{

}

void
UpgradeXPGain::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\XPPlus.png");
}

void
UpgradeXPGain::ApplyUpgrade(Player * player)
{
	player->m_xpMultiplier += 0.30;
}
