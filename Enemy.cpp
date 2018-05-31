#include "Enemy.h"
#include "Player.h"
#include "PlayerStatus.h"
#include <cmath>
bool Enemy::init()
{	
	HP = 50; HPMax = 50;
	blood1 = Sprite::create(".\\Enemy\\blood1.png", Rect(0, 0, (HP / HPMax) * 150, 10));
	blood2 = Sprite::create(".\\Enemy\\blood2.png");
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
		blood1->runAction(MoveBy::create(1, Vec2(deltaX, deltaY)));
		blood2->runAction(MoveBy::create(1, Vec2(deltaX, deltaY)));
	}
	else {
		ps->SubHP(7);
		if(!ps->isPlayerBlinking()){
			ps->setBlinking();
			//ps->FreezeBlinking();
			player->runAction(Blink::create(1, 5));
			auto delayTime1 = DelayTime::create(1.0f);
			auto UB = CallFunc::create([this]() 
			{
				ps->setUnBlinking();
			});
			auto seq1 = Sequence::create(delayTime1, UB, nullptr);
			this->runAction(seq1);
		}

	}
}
