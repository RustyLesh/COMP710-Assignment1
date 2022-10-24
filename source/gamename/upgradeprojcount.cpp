// COMP710 Les Mcilroy

// This include:
#include "upgradeprojcount.h"

// Local includes:
#include "renderer.h"
#include "player.h"
// Library includes:
#include <cassert> 

UpgradeProjCount::UpgradeProjCount()
{ 
 
}

UpgradeProjCount::~UpgradeProjCount()
{

}

void
UpgradeProjCount::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\UpgradeIconExtraProj.png");
}

void
UpgradeProjCount::ApplyUpgrade(Player * player)
{
	player->m_projCount++;

}
