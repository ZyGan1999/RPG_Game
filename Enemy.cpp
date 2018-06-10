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
	int movedistance;
	int flag = 0;
	if (this->getName() == "Soldier") movedistance = 48;
	if (this->getName() == "WindSprite") movedistance = 60,flag = 1;
	int dd = rand() % 100;

	if (!this->getBoundingBox().intersectsRect(player->getBoundingBox())) {
		double deltaX = player->getPositionX() - this->getPositionX();
		double deltaY = player->getPositionY() - this->getPositionY();
		
		double r = sqrt(deltaX * deltaX + deltaY * deltaY) / (movedistance + flag * dd);
		deltaX /= r; deltaY /= r;
		this->runAction(MoveBy::create(1, Vec2(deltaX, deltaY)));
		blood1->runAction(MoveBy::create(1, Vec2(deltaX, deltaY)));
		blood2->runAction(MoveBy::create(1, Vec2(deltaX, deltaY)));
	}
	else {
		int harm;
		if (this->getName() == "Soldier") harm = 7;
		if (this->getName() == "WindSprite") harm = 5;
		ps->SubHP(harm);
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
