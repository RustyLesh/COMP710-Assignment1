// COMP710 Les Mcilroy

// This include:
#include "upgradepiercecount.h"

// Local includes:
#include "renderer.h"
#include "player.h"
// Library includes:
#include <cassert> 

UpgradePierceCount::UpgradePierceCount()
{ 
 
}

UpgradePierceCount::~UpgradePierceCount()
{

}

void
UpgradePierceCount::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\Pierce.png");
}

void
UpgradePierceCount::ApplyUpgrade(Player * player)
{
	player->m_pierceAmount++;
}
