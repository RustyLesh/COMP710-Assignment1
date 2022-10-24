// COMP710 Les Mcilroy
#ifndef __UPGRADEMAXHP_H__
#define __UPGRADEMAXHP_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeMaxHP: public Upgrade
	{
	// Member methods:
public:
	UpgradeMaxHP();
	~UpgradeMaxHP();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeMaxHP(const UpgradeMaxHP& upgrademaxhp);
	UpgradeMaxHP& operator=(const UpgradeMaxHP& upgrademaxhp);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADEMAXHP_H__
