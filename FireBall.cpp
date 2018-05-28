#include "FireBall.h"
#include "Player.h"
bool FireBall::init()
{
	player = Player::getInstance();
	initWithFile(".\\FireBall\\FireBall3.png");
	setContentSize(Size(100, 100));
	return true;
}

void FireBall::GoAround()
{
	runAction(RepeatForever::create(RotateBy::create(1.5, 360)));
}
