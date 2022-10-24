// COMP710 Les Mcilroy
#ifndef __UPGRADEDEFENSE_H__
#define __UPGRADEDEFENSE_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeDefense: public Upgrade
	{
	// Member methods:
public:
	UpgradeDefense();
	~UpgradeDefense();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeDefense(const UpgradeDefense& upgradedefense);
	UpgradeDefense& operator=(const UpgradeDefense& upgradedefense);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEDEFENSE_H__
