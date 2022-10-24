//Comp710 Les Mcilroy
#ifndef __UPGRADE_H__
#define __UPGRADE_H__

#include <string>
class Sprite;
class Renderer;
class Player;

class Upgrade
{
	//Local members
public:
	Upgrade();
	virtual ~Upgrade();

	virtual void Initialise(Renderer& renderer) = 0;
	virtual void ApplyUpgrade(Player* player) = 0;

	std::string m_upgradeName;
	Sprite* m_pIcon; //TODO: Encapsulate
protected:
	//Local data
};

#endif // !__UPGRADE_H__

