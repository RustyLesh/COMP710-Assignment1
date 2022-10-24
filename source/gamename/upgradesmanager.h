#ifndef __UPGRADESMANAGER_H__
#define __UPGRADESMANAGER_H__

#include "vector2.h"

//Library includes
#include <vector>

//Forward declarations
class Player;
class Upgrade;
class InputSystem;
class Renderer;

class UpgradesManager
{
	//Member methods
public:
	UpgradesManager();
	~UpgradesManager();

	void Initialise(Renderer& renderer, Vector2 topLeftAnchor);
	void Process(InputSystem & inputSystem);
	void Draw(Renderer& renderer);

	void RollUpgradeOptions(int numberOfRolls);
	void ClearOptionPool();
	Upgrade* SelectUpgrade(int upgradeSelected);
	std::vector<Upgrade*> GetUpgradeOptions();

	void DebugDraw();
	//Member data
private:
	void SetUpgradeIconsPos();
	std::vector<int> RollRandomNumbers(int numberOfRolls);

private:
public:
	Player* m_pPlayer;
	bool m_isUpgrading;//TODO State machine for upgrades
	bool m_isUpgradeToRoll;
	bool m_isUpGradesHaveRolled;
	bool m_isUpgradeCompleted;

private:
	std::vector<Upgrade*> m_upgradePool;
	std::vector<Upgrade*> m_upgradeOptions;

	int upgradesGained;

	Vector2 m_screenCenter;
	Vector2 m_upTopLeft;
};

#endif // !__UPGRADESMANAGER_H__

