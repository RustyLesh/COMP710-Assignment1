// COMP710 Les Mcilroy
#ifndef __UPGRADEHPREGEN_H__
#define __UPGRADEHPREGEN_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeHPRegen: public Upgrade
	{
	// Member methods:
public:
	UpgradeHPRegen();
	~UpgradeHPRegen();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeHPRegen(const UpgradeHPRegen& upgradehpregen);
	UpgradeHPRegen& operator=(const UpgradeHPRegen& upgradehpregen);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEHPREGEN_H__
