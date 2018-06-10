#include "WindSprite.h"
string WindSprite::WindSpriteFileName = ".\\Enemy\\Windspirit.png";
bool WindSprite::init()
{
	return true;
}

Enemy * WindSprite::createWindSprite()
{
	auto e = Enemy::create();
	e->setName("WindSprite");
	e->setHP(50);
	e->initWithFile(WindSpriteFileName);
	return e;
}
