// COMP710 Les Mcilroy
#ifndef __UPGRADEPROJSPEED_H__
#define __UPGRADEPROJSPEED_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeProjSpeed: public Upgrade
	{
	// Member methods:
public:
	UpgradeProjSpeed();
	~UpgradeProjSpeed();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeProjSpeed(const UpgradeProjSpeed& upgradeprojspeed);
	UpgradeProjSpeed& operator=(const UpgradeProjSpeed& upgradeprojspeed);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEPROJSPEED_H__
