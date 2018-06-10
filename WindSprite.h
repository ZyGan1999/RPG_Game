#pragma once
#include <cocos2d.h>
#include <string>
#include "Enemy.h"
using namespace cocos2d;
using namespace std;
class WindSprite:public Enemy
{
public:
	virtual bool init();
	CREATE_FUNC(WindSprite);
	static Enemy * createWindSprite();
private:
	static string WindSpriteFileName;
};

