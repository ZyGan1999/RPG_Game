#include "Soldier.h"

string Soldier::SoldierFileName = ".\\Enemy\\Soldier.png";
bool Soldier::init()
{
	return true;
}

Enemy * Soldier::createSoldier()
{
	auto e = Enemy::create();
	e->setName("Soldier");
	e->setHP(100);
	e->initWithFile(SoldierFileName);
	return e;
}
