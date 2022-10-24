// COMP710 Les Mcilroy
#ifndef  __ATTACKLISTENER_H__
#define  __ATTACKLISTENER_H__

#include "box2d/b2_world_callbacks.h"
#include <vector>

class b2World;
struct EntityUserData;

class AttackListener : public b2ContactListener
{
public:
	AttackListener();
	virtual ~AttackListener();

protected:
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

private:
	AttackListener(const AttackListener& attackListener);
	AttackListener& operator=(const AttackListener& attackListener);


public:
};


#endif //  __ATTACKLISTENER_H__
