#ifndef __PLAYERSTATS_H__
#define __PLAYERSTATS_H__

//Local includes
#include "player.h"
#include "scenemanager.h"
#include "iniparser.h"

//Library includes
#include <vector>

//Forward declarations
class Player;

class PlayerStats
{
public:
	PlayerStats();
	~PlayerStats();

	//Member methods
	bool Initialise();

	void Save();

private:
	PlayerStats(const PlayerStats& playerStats);
	PlayerStats& operator=(const PlayerStats& playerStats);

	//Member data
public:
	float m_moveSpeed;
	float m_xpGain;
	float m_pierce;

private:

	Player* m_pPlayer;

	IniParser* m_pIniparser;
};

#endif // !__PLAYERSTATS_H__

