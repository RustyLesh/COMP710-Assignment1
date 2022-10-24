//This include
#include "upgradeflatDamage.h"

//Local includes
#include "renderer.h"
#include "player.h"
#include "playercontroller.h"
#include "logmanager.h"

//COMP710 Les Mcilroy

UpgradeFlatDamage::UpgradeFlatDamage()
{
}

UpgradeFlatDamage::~UpgradeFlatDamage()
{
}

void 
UpgradeFlatDamage::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\Damage.png");
}

void 
UpgradeFlatDamage::ApplyUpgrade(Player * player)
{
	player->m_damage += 25;
}
