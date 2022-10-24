//COMP710 Les Mcilroy
#ifndef __UPGRADE_DAMAGE_H__
#define __UPGRADE_DAMAGE_H__
#include "upgrade.h"

class UpgradeFlatDamage : public Upgrade
{
	//Member Methods
public:
	UpgradeFlatDamage();
	virtual ~UpgradeFlatDamage();

	// Inherited via Upgrade
	virtual void Initialise(Renderer & renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

	UpgradeFlatDamage(const UpgradeFlatDamage& upgradeFlatDamage);
	UpgradeFlatDamage& operator=(const UpgradeFlatDamage& upgradeFlatDamage);
};

#endif // !__UPGRADE_DAMAGE_H__

