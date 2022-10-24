// COMP710 Les Mcilroy

// This include:
#include "upgrademovespeed.h"

// Local includes:
#include "renderer.h"
#include "player.h"
#include "playercontroller.h"

// Library includes:
#include <cassert> 

UpgradeMoveSpeed::UpgradeMoveSpeed()
{
}

UpgradeMoveSpeed::~UpgradeMoveSpeed()
{
}

void
UpgradeMoveSpeed::Initialise(Renderer & renderer)
{
	m_pIcon = renderer.CreateSprite("gui\\UpgradeMenu\\Boot.png");
}

void
UpgradeMoveSpeed::ApplyUpgrade(Player * player)
{
	player->m_pPlayerMovement->m_movemetSpeed += 0.002;
}
