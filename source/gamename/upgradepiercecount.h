// COMP710 Les Mcilroy
#ifndef __UPGRADEPIERCECOUNT_H__
#define __UPGRADEPIERCECOUNT_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradePierceCount: public Upgrade
	{
	// Member methods:
public:
	UpgradePierceCount();
	~UpgradePierceCount();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradePierceCount(const UpgradePierceCount& upgradepiercecount);
	UpgradePierceCount& operator=(const UpgradePierceCount& upgradepiercecount);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEPIERCECOUNT_H__
