#pragma once
#include "Enemy.h"
#include <cocos2d.h>
#include <string>
using namespace std;
using namespace cocos2d;
class Soldier:public Enemy
{
public:
	virtual bool init();
	static Enemy * createSoldier();
	CREATE_FUNC(Soldier);
private:
	static string SoldierFileName;
};

