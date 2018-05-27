#pragma once
#include <cocos2d.h>
using namespace cocos2d;

class FireBall:public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(FireBall);
	void GoAround();
private:
	Sprite * player;
	SpriteFrame * fireball_1;
	SpriteFrame * fireball_2;
	SpriteFrame * fireball_3;
};

