//COMP710 Les Mcilroy

//This include 
#include "upgradesmanager.h"
#include "upgrade.h"
#include "logmanager.h"
#include "inlinehelpers.h"
#include "sprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "scenemanager.h"
#include "imgui/imgui_impl_sdl.h"
//Local includes:

	//Upgrade includes
#include "upgradexpgain.h"
#include "upgradeprojspeed.h"
#include "upgradeprojcount.h"
#include "upgradepiercecount.h"
#include "upgrademovespeed.h"
#include "upgradeflatdamage.h"
#include "upgradeattackspeed.h"
#include "upgrademaxhp.h"
#include "upgradehpregen.h"
#include "upgradedefense.h"


//Library includes
#include <algorithm>

UpgradesManager::UpgradesManager()
	: m_isUpgradeToRoll(false)
	, m_isUpgrading(false)
	, m_isUpGradesHaveRolled(false)
	, m_isUpgradeCompleted(false)
{
}

UpgradesManager::~UpgradesManager()
{
	for (Upgrade* upgrade : m_upgradePool)
	{
		delete upgrade;
	}
	m_upgradePool.clear();

}

void UpgradesManager::Initialise(Renderer& renderer, Vector2 topLeftAnchor)
{
	m_upTopLeft.x = renderer.GetWidth();
	m_upTopLeft.y = renderer.GetHeight();

	//TODO: Create upgrade factory

	//Flat Damage
	UpgradeFlatDamage* upgradeFlatDamage = 0;
	upgradeFlatDamage = new UpgradeFlatDamage();
	upgradeFlatDamage->Initialise(renderer);
	m_upgradePool.push_back(upgradeFlatDamage);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//Attack Speed
	UpgradeAttackSpeed* pgradeAttackSpeed = 0;
	pgradeAttackSpeed = new UpgradeAttackSpeed();
	pgradeAttackSpeed->Initialise(renderer);
	m_upgradePool.push_back(pgradeAttackSpeed);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//XP Fain
	UpgradeXPGain* upgradeXPGain = 0;
	upgradeXPGain = new UpgradeXPGain();
	upgradeXPGain->Initialise(renderer);
	m_upgradePool.push_back(upgradeXPGain);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//Movement Speed
	UpgradeMoveSpeed* upgradeMoveSpeed = 0;
	upgradeMoveSpeed = new UpgradeMoveSpeed();
	upgradeMoveSpeed->Initialise(renderer);
	m_upgradePool.push_back(upgradeMoveSpeed);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//Proj Count
	UpgradeProjCount* upgradeProjCount = 0;
	upgradeProjCount = new UpgradeProjCount();
	upgradeProjCount->Initialise(renderer);
	m_upgradePool.push_back(upgradeProjCount);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//Pierce
	UpgradePierceCount* upgradePierceCount = 0;
	upgradePierceCount = new UpgradePierceCount();
	upgradePierceCount->Initialise(renderer);
	m_upgradePool.push_back(upgradePierceCount);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//Proj Speed
	UpgradeProjSpeed* upgradeProjSpeed = 0;
	upgradeProjSpeed = new UpgradeProjSpeed();
	upgradeProjSpeed->Initialise(renderer);
	m_upgradePool.push_back(upgradeProjSpeed);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//Max HP
	UpgradeMaxHP* upgradeMaxHP = 0;
	upgradeMaxHP = new UpgradeMaxHP();
	upgradeMaxHP->Initialise(renderer);
	m_upgradePool.push_back(upgradeMaxHP);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//HP Regen
	UpgradeHPRegen* upgradeHPRegen = 0;
	upgradeHPRegen = new UpgradeHPRegen();
	upgradeHPRegen->Initialise(renderer);
	m_upgradePool.push_back(upgradeHPRegen);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);

	//Upgrade Defense
	UpgradeDefense* upgradeDefense = 0;
	upgradeDefense = new UpgradeDefense();
	upgradeDefense->Initialise(renderer);
	m_upgradePool.push_back(upgradeDefense);
	m_screenCenter = Vector2(renderer.GetWidth() / 2, renderer.GetHeight() / 2);
}

std::vector<int> UpgradesManager::RollRandomNumbers(int numberOfRolls)
{
	numberOfRolls = Clamp(0, numberOfRolls, m_upgradePool.size());

	std::vector<int> rolls;
	for (int i = 0; i < m_upgradePool.size(); i++)
	{
		rolls.push_back(i);
	}

	std::random_shuffle(rolls.begin(), rolls.end());

	std::vector<int> results;
	for (int i = 0; i < numberOfRolls; i++)
	{
		results.push_back(rolls[i]);
	}

	return results;
}


void UpgradesManager::Process(InputSystem & inputSystem)
{
	if (m_isUpgrading)
	{
		//Roll Upgrade
		if (m_isUpgradeToRoll)
		{
			RollUpgradeOptions(4);

			SetUpgradeIconsPos();

			m_isUpGradesHaveRolled = true;
			m_isUpgradeToRoll = false;
		}

		//Select Upgrade	
		if (m_isUpGradesHaveRolled)
		{
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_Y) == BS_PRESSED)
			{
				m_isUpgrading = false;
				//Roll Upgrade
				//HACK: should be encapsulated somewhre instead of stright calling
				SelectUpgrade(1)->ApplyUpgrade(m_pPlayer);
				m_isUpgradeCompleted = true;
				ClearOptionPool();
			}

			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_X) == BS_PRESSED)
			{
				m_isUpgrading = false;
				//Roll Upgrade
				//HACK: should be encapsulated somewhre instead of stright calling
				SelectUpgrade(2)->ApplyUpgrade(m_pPlayer);
				m_isUpgradeCompleted = true;
				ClearOptionPool();
			}

			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_A) == BS_PRESSED)
			{
				m_isUpgrading = false;
				//Roll Upgrade
				//HACK: should be encapsulated somewhre instead of stright calling
				SelectUpgrade(3)->ApplyUpgrade(m_pPlayer);
				m_isUpgradeCompleted = true;
				ClearOptionPool();
			}

			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_B) == BS_PRESSED)
			{
				m_isUpgrading = false;
				//Roll Upgrade
				//HACK: should be encapsulated somewhre instead of stright calling
				SelectUpgrade(4)->ApplyUpgrade(m_pPlayer);
				m_isUpgradeCompleted = true;
				ClearOptionPool();
			}
		}
	}
}

void UpgradesManager::Draw(Renderer & renderer)
{
	for (Upgrade* upgrade : m_upgradeOptions)
	{
		upgrade->m_pIcon->Draw(renderer);
	}
}

void UpgradesManager::RollUpgradeOptions(int numberOfRolls)
{
	std::vector<int> results = RollRandomNumbers(numberOfRolls);

	for (int roll : results)
	{
		m_upgradeOptions.push_back(m_upgradePool[roll]);
	}
}

void UpgradesManager::ClearOptionPool()
{
	m_upgradeOptions.clear();
}

Upgrade* UpgradesManager::SelectUpgrade(int upgradeSelected)
{
	upgradeSelected = Clamp(0, upgradeSelected, m_upgradeOptions.size());

	return m_upgradeOptions[upgradeSelected - 1];
}

std::vector<Upgrade*> UpgradesManager::GetUpgradeOptions()
{
	return m_upgradeOptions;
}

void UpgradesManager::DebugDraw()
{

}

void UpgradesManager::SetUpgradeIconsPos()
{
	int offset = 500;

	//Hack magic number of 3 cap
	for (int i = 0; i < m_upgradeOptions.size(); i++)
	{
		if ( i == 0)
		{
			m_upgradeOptions[i]->m_pIcon->SetX(m_upTopLeft.x * .5);
			m_upgradeOptions[i]->m_pIcon->SetY(m_upTopLeft.y * .30);
			m_upgradeOptions[i]->m_pIcon->SetAlpha(1);
		}
		if (i == 1)
		{
			m_upgradeOptions[i]->m_pIcon->SetX(m_upTopLeft.x * .36);
			m_upgradeOptions[i]->m_pIcon->SetY(m_upTopLeft.y * .5);
			m_upgradeOptions[i]->m_pIcon->SetAlpha(1);
		}
		if (i == 2)
		{
			m_upgradeOptions[i]->m_pIcon->SetX(m_upTopLeft.x * .5);
			m_upgradeOptions[i]->m_pIcon->SetY(m_upTopLeft.y * .70);
			m_upgradeOptions[i]->m_pIcon->SetAlpha(1);
		}
		if (i == 3)
		{
			m_upgradeOptions[i]->m_pIcon->SetX(m_upTopLeft.x * .64);
			m_upgradeOptions[i]->m_pIcon->SetY(m_upTopLeft.y * .50);
			m_upgradeOptions[i]->m_pIcon->SetAlpha(1);
		}
	}
}



