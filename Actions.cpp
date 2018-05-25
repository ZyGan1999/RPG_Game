#include "Actions.h"
//auto s1 = SpriteFrame::create(".\\player\\player.png", Rect(0, 0, 48, 48));
//auto s2 = SpriteFrame::create(".\\player\\player.png", Rect(0, 1, 48, 48));
//auto s3 = SpriteFrame::create(".\\player\\player.png", Rect(0, 2, 48, 48));
//auto leftsteps = Animation::create();
////leftsteps->addSpriteFrame(s1);
////leftsteps->addSpriteFrame(s2);
////leftsteps->addSpriteFrame(s3);
////leftsteps->setDelayPerUnit(0.1);
//auto leftsteps_animate = Animate::create(leftsteps);
//auto leftmovement = MoveBy::create(0.1, Vec2(-10, 0));
//Spawn* Actions::MoveLeft = Spawn::create(leftsteps_animate, leftmovement);
int Actions::GRID_SIZE = 48;
Actions::Actions() {
	D1 = SpriteFrame::create(".\\player\\player.png", Rect(0, 0, 48, 48));
	D2 = SpriteFrame::create(".\\player\\player.png", Rect(GRID_SIZE,0, 48, 48));
	D3 = SpriteFrame::create(".\\player\\player.png", Rect(2* GRID_SIZE,0, 48, 48));
	L1 = SpriteFrame::create(".\\player\\player.png", Rect(0,GRID_SIZE,  48, 48));
	L2 = SpriteFrame::create(".\\player\\player.png", Rect(GRID_SIZE, GRID_SIZE, 48, 48));
	L3 = SpriteFrame::create(".\\player\\player.png", Rect(2*GRID_SIZE,GRID_SIZE,  48, 48));
	R1 = SpriteFrame::create(".\\player\\player.png", Rect(0,2* GRID_SIZE,  48, 48));
	R2 = SpriteFrame::create(".\\player\\player.png", Rect(GRID_SIZE,2* GRID_SIZE,  48, 48));
	R3 = SpriteFrame::create(".\\player\\player.png", Rect(2* GRID_SIZE,2* GRID_SIZE,  48, 48));
	U1 = SpriteFrame::create(".\\player\\player.png", Rect(0,3* GRID_SIZE,  48, 48));
	U2 = SpriteFrame::create(".\\player\\player.png", Rect(GRID_SIZE,3* GRID_SIZE,  48, 48));
	U3 = SpriteFrame::create(".\\player\\player.png", Rect(2* GRID_SIZE,3* GRID_SIZE,  48, 48));
	//auto s1 = SpriteFrame::create("ball.jpg", Rect(0, 0, 100, 100));
	auto leftsteps = Animation::create();
	leftsteps->addSpriteFrame(L1);
	leftsteps->addSpriteFrame(L2);
	leftsteps->addSpriteFrame(L3);
	leftsteps->addSpriteFrame(L2);
	leftsteps->setDelayPerUnit(0.1);
	auto leftsteps_animate = Animate::create(leftsteps);
	auto leftmovement = MoveBy::create(0.2, Vec2(-3, 0));
	MoveLeft = Spawn::create(leftsteps_animate, leftmovement, NULL);

	auto rightsteps = Animation::create();
	rightsteps->addSpriteFrame(R1); rightsteps->addSpriteFrame(R2);
	rightsteps->addSpriteFrame(R3); rightsteps->addSpriteFrame(R2);
	rightsteps->setDelayPerUnit(0.1);
	auto rightsteps_animate = Animate::create(rightsteps);
	auto rightmovement = MoveBy::create(0.2, Vec2(3, 0));
	MoveRight = Spawn::create(rightsteps_animate, rightmovement, NULL);

	auto upsteps = Animation::create();
	upsteps->addSpriteFrame(U1); upsteps->addSpriteFrame(U2);
	upsteps->addSpriteFrame(U3); upsteps->addSpriteFrame(U2);
	upsteps->setDelayPerUnit(0.1);
	auto upsteps_animate = Animate::create(upsteps);
	auto upmovement = MoveBy::create(0.2, Vec2(0, 3));
	MoveUp = Spawn::create(upsteps_animate, upmovement, NULL);

	auto downsteps = Animation::create();
	downsteps->addSpriteFrame(D1); downsteps->addSpriteFrame(D2);
	downsteps->addSpriteFrame(D3); downsteps->addSpriteFrame(D2);
	downsteps->setDelayPerUnit(0.1);
	auto downsteps_animate = Animate::create(downsteps);
	auto downmovement = MoveBy::create(0.2, Vec2(0, -3));
	MoveDown = Spawn::create(downsteps_animate, downmovement, NULL);
}

Actions& Actions::getInstance()
{
	static Actions instance;
	return instance;
}
