#include "Player.h"
int Player::GRID_SIZE = 48;
Sprite* Player::instance = Sprite::create(".\\player\\player.png", Rect(0, 1, GRID_SIZE, GRID_SIZE));
Sprite * Player::getInstance()
{
	if (instance == nullptr) {
		instance = Sprite::create(".\\player\\player.png", Rect(0, 1, GRID_SIZE, GRID_SIZE));
	}
	return instance;
}


//bool Player::init()
//{
//	auto s1 = SpriteFrame::create(".\\player\\player.png", Rect(0, 0, GRID_SIZE, GRID_SIZE));
//	auto s2 = SpriteFrame::create(".\\player\\player.png", Rect(0, 1, GRID_SIZE, GRID_SIZE));
//	auto s3 = SpriteFrame::create(".\\player\\player.png", Rect(0, 2, GRID_SIZE, GRID_SIZE));
//	auto leftsteps = Animation::create();
//	leftsteps->addSpriteFrame(s1);
//	leftsteps->addSpriteFrame(s2);
//	leftsteps->addSpriteFrame(s3);
//	leftsteps->setDelayPerUnit(0.1);
//	auto leftsteps_animate = Animate::create(leftsteps);
//	auto leftmovement = MoveBy::create(0.1, Vec2(-10, 0));
//	moveleft = Spawn::create(leftsteps_animate, leftmovement);
//
//	return true;
//}
