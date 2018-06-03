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
	void setHP(int hp) {
		HP = hp;
		HPMax = hp;
	}
	double getHP() {
		return HP;
	}
	void subHP(double delta) {
		HP -= delta;
	}
	void updateHP() {
		blood1 = Sprite::create(".\\Enemy\\blood1.png", Rect(0, 0, (HP / HPMax) * 150, 10));
		blood2 = Sprite::create(".\\Enemy\\blood2.png");
	}
	void setBlood(Layer * l) {
		blood1->setAnchorPoint(Vec2(0, 0.5));
		blood2->setAnchorPoint(Vec2(0, 0.5));
		blood1->setPosition(this->getPositionX() - 75, this->getPositionY() + 70);
		blood2->setPosition(this->getPositionX() - 75, this->getPositionY() + 70);
		l->addChild(blood1, 2);
		l->addChild(blood2, 1);
	}
	void removeBlood() {
		blood1->removeFromParentAndCleanup(true);
		blood2->removeFromParentAndCleanup(true);
	}
private:
	Sprite * blood1;
	Sprite * blood2;
	double HP;
	double HPMax;
	Sprite * player;
	PlayerStatus * ps;
};

