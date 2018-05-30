#include "Actions.h"
#include "Player.h"
int Actions::GRID_SIZE = 48;
Actions::Actions() {
	player = Player::getInstance();
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

	LShade1 = Sprite::create(".\\player\\shade1.png", Rect(0, GRID_SIZE, 48, 48));
	LShade2 = Sprite::create(".\\player\\shade2.png", Rect(0, GRID_SIZE, 48, 48));
	LShade3 = Sprite::create(".\\player\\shade3.png", Rect(0, GRID_SIZE, 48, 48));
	RShade1 = Sprite::create(".\\player\\shade1.png", Rect(0, 2 * GRID_SIZE, 48, 48));
	RShade2 = Sprite::create(".\\player\\shade2.png", Rect(0, 2 * GRID_SIZE, 48, 48));
	RShade3 = Sprite::create(".\\player\\shade3.png", Rect(0, 2 * GRID_SIZE, 48, 48));
	UShade1 = Sprite::create(".\\player\\shade1.png", Rect(0, 3 * GRID_SIZE, 48, 48));
	UShade2 = Sprite::create(".\\player\\shade2.png", Rect(0, 3 * GRID_SIZE, 48, 48));
	UShade3 = Sprite::create(".\\player\\shade3.png", Rect(0, 3 * GRID_SIZE, 48, 48));
	DShade1 = Sprite::create(".\\player\\shade1.png", Rect(0, 0, 48, 48));
	DShade2 = Sprite::create(".\\player\\shade2.png", Rect(0, 0, 48, 48));
	DShade3 = Sprite::create(".\\player\\shade3.png", Rect(0, 0, 48, 48));
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

void Actions::SideStep(Scene * s, EventKeyboard::KeyCode code)
{
	switch (code) {
	case EventKeyboard::KeyCode::KEY_A:{
		LShade1->setPosition(player->getPositionX(), player->getPositionY());
		LShade2->setPosition(player->getPositionX(), player->getPositionY());
		LShade3->setPosition(player->getPositionX(), player->getPositionY());
		s->addChild(LShade1, player->getLocalZOrder());
		s->addChild(LShade2, player->getLocalZOrder());
		s->addChild(LShade3, player->getLocalZOrder());
		player->runAction(MoveBy::create(0.2, Vec2(-50, 0)));
		LShade1->runAction(MoveBy::create(0.4, Vec2(-50, 0)));
		LShade2->runAction(MoveBy::create(0.6, Vec2(-50, 0)));
		LShade3->runAction(MoveBy::create(0.8, Vec2(-50, 0)));
		auto delayTime = DelayTime::create(1.0f);
		auto DLE = CallFunc::create([this]()
		{
			LShade1->removeFromParentAndCleanup(true);
			LShade2->removeFromParentAndCleanup(true);
			LShade3->removeFromParentAndCleanup(true);
		});
		auto seq1 = Sequence::create(delayTime, DLE, nullptr);
		s->runAction(seq1);
		break;
		}
	case EventKeyboard::KeyCode::KEY_D: {
		RShade1->setPosition(player->getPositionX(), player->getPositionY());
		RShade2->setPosition(player->getPositionX(), player->getPositionY());
		RShade3->setPosition(player->getPositionX(), player->getPositionY());
		s->addChild(RShade1, player->getLocalZOrder());
		s->addChild(RShade2, player->getLocalZOrder());
		s->addChild(RShade3, player->getLocalZOrder());
		player->runAction(MoveBy::create(0.2, Vec2(50, 0)));
		RShade1->runAction(MoveBy::create(0.4, Vec2(50, 0))); RShade1->setPosition(-100, -100);
		RShade2->runAction(MoveBy::create(0.6, Vec2(50, 0))); RShade2->setPosition(-100, -100);
		RShade3->runAction(MoveBy::create(0.8, Vec2(50, 0))); RShade3->setPosition(-100, -100);
		RShade1->removeFromParentAndCleanup(true);
		RShade2->removeFromParentAndCleanup(true);
		RShade3->removeFromParentAndCleanup(true);
		break;
	}
	case EventKeyboard::KeyCode::KEY_W: {
		UShade1->setPosition(player->getPositionX(), player->getPositionY());
		UShade2->setPosition(player->getPositionX(), player->getPositionY());
		UShade3->setPosition(player->getPositionX(), player->getPositionY());
		s->addChild(UShade1, player->getLocalZOrder());
		s->addChild(UShade2, player->getLocalZOrder());
		s->addChild(UShade3, player->getLocalZOrder());
		player->runAction(MoveBy::create(0.2, Vec2(0, 50)));
		UShade1->runAction(MoveBy::create(0.4, Vec2(0, 50)));
		UShade2->runAction(MoveBy::create(0.6, Vec2(0, 50)));
		UShade3->runAction(MoveBy::create(0.8, Vec2(0, 50)));
		auto delayTime = DelayTime::create(1.0f);
		auto DLE = CallFunc::create([this]()
		{
			UShade1->removeFromParentAndCleanup(true);
			UShade2->removeFromParentAndCleanup(true);
			UShade3->removeFromParentAndCleanup(true);
		});
		auto seq1 = Sequence::create(delayTime, DLE, nullptr);
		s->runAction(seq1);
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {
		DShade1->setPosition(player->getPositionX(), player->getPositionY());
		DShade2->setPosition(player->getPositionX(), player->getPositionY());
		DShade3->setPosition(player->getPositionX(), player->getPositionY());
		s->addChild(DShade1, player->getLocalZOrder());
		s->addChild(DShade2, player->getLocalZOrder());
		s->addChild(DShade3, player->getLocalZOrder());
		player->runAction(MoveBy::create(0.2, Vec2(0, -50)));
		DShade1->runAction(MoveBy::create(0.4, Vec2(0, -50)));
		DShade2->runAction(MoveBy::create(0.6, Vec2(0, -50)));
		DShade3->runAction(MoveBy::create(0.8, Vec2(0, -50)));
		auto delayTime = DelayTime::create(1.0f);
		auto DLE = CallFunc::create([this]()
		{
			DShade1->removeFromParentAndCleanup(true);
			DShade2->removeFromParentAndCleanup(true);
			DShade3->removeFromParentAndCleanup(true);
		});
		auto seq1 = Sequence::create(delayTime, DLE, nullptr);
		s->runAction(seq1);
		break;
	}
	}
}

