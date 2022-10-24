// COMP710 Les Mcilroy
#ifndef __UPGRADE_MOVESPEED_H__
#define __UPGRADE_MOVESPEED_H__

//Local includes
#include "upgrade.h" 

// Forward declarations:

// Class declaration:
class UpgradeMoveSpeed : public Upgrade
	{
	// Member methods:
public:
	UpgradeMoveSpeed();
	~UpgradeMoveSpeed();

	virtual void Initialise(Renderer& renderer) override;
	virtual void ApplyUpgrade(Player* player) override;

protected:

private:
	UpgradeMoveSpeed(const UpgradeMoveSpeed& upgrademovespeed);
	UpgradeMoveSpeed& operator=(const UpgradeMoveSpeed& upgrademovespeed);

	// Member data:
public:

protected:

private:

};

#endif //__UPGRADE_MOVESPEED_H__
