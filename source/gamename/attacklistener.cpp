// COMP710 Les Mcilroy

#include "attacklistener.h"
#include "box2d/box2d.h"
#include "entity.h"
#include "enemy.h"
#include "logmanager.h"
#include "bullet.h"
#include <cstdint>

AttackListener::AttackListener()
{

}

AttackListener::~AttackListener()
{
}


void AttackListener::BeginContact(b2Contact * contact)
{
	b2BodyUserData fixtureDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	b2BodyUserData fixtureDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	EntityUserData* userDataA = reinterpret_cast<EntityUserData*>(fixtureDataA.pointer);
	EntityUserData* userDataB = reinterpret_cast<EntityUserData*>(fixtureDataB.pointer);

	if (userDataA != NULL && userDataB != NULL)
	{
		if (userDataA->entity->IsAlive() && userDataB->entity->IsAlive())
		{
			if (userDataA->entity->GetEntityType() == ET_ENEMY || userDataB->entity->GetEntityType() == ET_ENEMY)
			{
				if (userDataB->entity->GetEntityType() == ET_BULLET)
				{
					userDataA->entity->OnCollision(userDataB);
					userDataB->entity->OnCollision(userDataA);
				}
			}
			if (userDataA->entity->GetEntityType() == ET_PLAYER)
			{
				userDataB->entity->OnCollision(userDataA);
				userDataA->entity->OnCollision(userDataB);
			}
			if (userDataB->entity->GetEntityType() == ET_PLAYER)
			{
				userDataB->entity->OnCollision(userDataA);
				userDataA->entity->OnCollision(userDataB);
			}
		}

	}
}

void AttackListener::EndContact(b2Contact * contact)
{
	b2BodyUserData fixtureDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	b2BodyUserData fixtureDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	EntityUserData* userDataA = reinterpret_cast<EntityUserData*>(fixtureDataA.pointer);
	EntityUserData* userDataB = reinterpret_cast<EntityUserData*>(fixtureDataB.pointer);

	if (userDataA != NULL && userDataB != NULL)
	{
		if (userDataA->entity->IsAlive() && userDataB->entity->IsAlive())
		{
			if (userDataA->entity->GetEntityType() == ET_ENEMY || userDataB->entity->GetEntityType() == ET_ENEMY)
			{
				if (userDataA->entity->GetEntityType() == ET_PLAYER)
				{
					userDataB->entity->EndCollision(userDataA);
					userDataA->entity->EndCollision(userDataB);
				}
				if (userDataB->entity->GetEntityType() == ET_PLAYER)
				{
					userDataB->entity->EndCollision(userDataA);
					userDataA->entity->EndCollision(userDataB);
				}
			}
		}

	}
}
