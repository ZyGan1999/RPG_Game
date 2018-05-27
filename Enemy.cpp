#include "Enemy.h"
#include "Player.h"
#include "PlayerStatus.h"
#include <cmath>
bool Enemy::init()
{
	player = Player::getInstance();
	ps = PlayerStatus::getInstance();
	return true;
}


void Enemy::seekPlayer()
{

	if (!this->getBoundingBox().intersectsRect(player->getBoundingBox())) {
		double deltaX = player->getPositionX() - this->getPositionX();
		double deltaY = player->getPositionY() - this->getPositionY();
		
		double r = sqrt(deltaX * deltaX + deltaY * deltaY) / 48;
		deltaX /= r; deltaY /= r;
		this->runAction(MoveBy::create(1, Vec2(deltaX, deltaY)));
	}
	else {
		ps->SubHP(7);
		if(!ps->isBlinkingFrozen()){
			ps->setBlinking();
			ps->FreezeBlinking();
			player->runAction(Blink::create(1, 5));
			auto delayTime1 = DelayTime::create(1.0f);
			auto UB = CallFunc::create([this]() 
			{
				ps->setUnBlinking();
			});
			auto seq1 = Sequence::create(delayTime1, UB, nullptr);
			this->runAction(seq1);

			auto delayTime2 = DelayTime::create(3.0f);
			auto UF = CallFunc::create([this]()
			{
				ps->unFreezeBlinking();
			});
			auto seq2 = Sequence::create(delayTime2, UF, nullptr);
			this->runAction(seq2);
		}

	}
}
