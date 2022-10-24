// COMP710 Les Mcilroy
#ifndef __UPGRADEPROJCOUNT_H__
#define __UPGRADEPROJCOUNT_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeProjCount: public Upgrade
	{
	// Member methods:
public:
	UpgradeProjCount();
	~UpgradeProjCount();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeProjCount(const UpgradeProjCount& upgradeprojcount);
	UpgradeProjCount& operator=(const UpgradeProjCount& upgradeprojcount);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEPROJCOUNT_H__
