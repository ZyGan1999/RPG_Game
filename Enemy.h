#pragma once
#include <cocos2d.h>
#include <string>
#include <map>
#include "PlayerStatus.h"
using namespace std;
using namespace cocos2d;
class Enemy:public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(Enemy);
	void seekPlayer();
	int getHP() {
		return HP;
	}
	void subHP(int delta) {
		HP -= delta;
	}
private:
	int HP;
	Sprite * player;
	PlayerStatus * ps;
};

