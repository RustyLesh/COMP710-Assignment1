// COMP710 Les Mcilroy
#ifndef __UPGRADEATTACKSPEED_H__
#define __UPGRADEATTACKSPEED_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeAttackSpeed: public Upgrade
	{
	// Member methods:
public:
	UpgradeAttackSpeed();
	~UpgradeAttackSpeed();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeAttackSpeed(const UpgradeAttackSpeed& upgradeattackspeed);
	UpgradeAttackSpeed& operator=(const UpgradeAttackSpeed& upgradeattackspeed);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEATTACKSPEED_H__
