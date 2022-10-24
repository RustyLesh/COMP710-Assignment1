// COMP710 Les Mcilroy

// This include:
#include "upgradeprojspeed.h"

// Local includes:
#include "renderer.h"
#include "player.h"
// Library includes:
#include <cassert> 

UpgradeProjSpeed::UpgradeProjSpeed()
{ 
 
}

UpgradeProjSpeed::~UpgradeProjSpeed()
{

}

void
UpgradeProjSpeed::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\ProjSpeed.png");
}

void
UpgradeProjSpeed::ApplyUpgrade(Player * player)
{
	player->m_projSpeed += 150;
}
