// COMP710 Les Mcilroy

// This include:
#include "upgradehpregen.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "player.h"
// Library includes:
#include <cassert> 

UpgradeHPRegen::UpgradeHPRegen()
{ 
 
}

UpgradeHPRegen::~UpgradeHPRegen()
{

}

void
UpgradeHPRegen::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\XPPlus.png");
	m_pIcon->SetRedTint(0);
	m_pIcon->SetBlueTint(0);
	m_pIcon->SetGreenTint(1);
}

void
UpgradeHPRegen::ApplyUpgrade(Player * player)
{
	player->m_HPRegen += 0.06;
}
