// COMP710 Les Mcilroy
#ifndef __UPGRADEXPGAIN_H__
#define __UPGRADEXPGAIN_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeXPGain: public Upgrade
	{
	// Member methods:
public:
	UpgradeXPGain();
	~UpgradeXPGain();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeXPGain(const UpgradeXPGain& upgradexpgain);
	UpgradeXPGain& operator=(const UpgradeXPGain& upgradexpgain);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEXPGAIN_H__
