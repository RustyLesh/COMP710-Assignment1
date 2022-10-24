// COMP710 Les Mcilroy

// This include:
#include "upgradedefense.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "player.h"

// Library includes:
#include <cassert> 

UpgradeDefense::UpgradeDefense()
{ 
 
}

UpgradeDefense::~UpgradeDefense()
{

}

void
UpgradeDefense::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\ArrowUp.png"); //TODO create a shield sprite
	m_pIcon->SetRedTint(1);
	m_pIcon->SetGreenTint(.2);
	m_pIcon->SetBlueTint(1);
}

void
UpgradeDefense::ApplyUpgrade(Player * player)
{
	player->m_defense += 0.5;
}
