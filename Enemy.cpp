#include "Enemy.h"
#include "Player.h"
#include <cmath>
map<string, string> Enemy::_enemypics = {
	make_pair("","")
};
Sprite * Enemy::player = Player::getInstance();

bool Enemy::init()
{
	return true;
}

Sprite * Enemy::createSprite(string name)
{
	return Sprite::create(_enemypics[name]);
}

void Enemy::seekPlayer()
{
	if (!this->getBoundingBox().intersectsRect(player->getBoundingBox())) {
		double deltaX = player->getPositionX() - this->getPositionX();
		double deltaY = player->getPositionY() - this->getPositionY();
		
		double r = sqrt(deltaX*deltaX + deltaY * deltaY) / 48;
		deltaX *= r; deltaY *= r;
		this->runAction(MoveBy::create(1, Vec2(deltaX, deltaY)));
	}
}
