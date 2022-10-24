// COMP710 Les Mcilroy

// This include:
#include "upgrademaxhp.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "player.h"
#include "health.h"

// Library includes:
#include <cassert> 

UpgradeMaxHP::UpgradeMaxHP()
{ 
 
}

UpgradeMaxHP::~UpgradeMaxHP()
{

}

void
UpgradeMaxHP::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\ArrowUp.png");
	m_pIcon->SetRedTint(1);
	m_pIcon->SetGreenTint(0.1);
	m_pIcon->SetBlueTint(0);
}

void
UpgradeMaxHP::ApplyUpgrade(Player * player)
{
	player->m_pHealth->SetMaxHealth(player->m_pHealth->GetMaxHealth() + 1);
}
