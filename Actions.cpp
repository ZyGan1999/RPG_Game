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

void Actions::SideStep(Layer * s, EventKeyboard::KeyCode code)
{
	switch (code) {
	case EventKeyboard::KeyCode::KEY_A:{
		s->addChild(LShade1, player->getLocalZOrder());
		s->addChild(LShade2, player->getLocalZOrder());
		s->addChild(LShade3, player->getLocalZOrder());
		LShade1->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX() - 70, player->getPositionY());
		LShade2->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX() - 70, player->getPositionY());
		LShade3->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX() - 70, player->getPositionY());
		break;
		}
	case EventKeyboard::KeyCode::KEY_D: {
		s->addChild(RShade1, player->getLocalZOrder());
		s->addChild(RShade2, player->getLocalZOrder());
		s->addChild(RShade3, player->getLocalZOrder());
		RShade1->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX() + 70, player->getPositionY());
		RShade2->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX() + 70, player->getPositionY());
		RShade3->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX() + 70, player->getPositionY());
		break;
	}
	case EventKeyboard::KeyCode::KEY_W: {
		s->addChild(UShade1, player->getLocalZOrder());
		s->addChild(UShade2, player->getLocalZOrder());
		s->addChild(UShade3, player->getLocalZOrder());
		UShade1->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX(), player->getPositionY() + 70);
		UShade2->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX(), player->getPositionY() + 70);
		UShade3->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX(), player->getPositionY() + 70);
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {
		s->addChild(DShade1, player->getLocalZOrder());
		s->addChild(DShade2, player->getLocalZOrder());
		s->addChild(DShade3, player->getLocalZOrder());
		DShade1->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX(), player->getPositionY() - 70);
		DShade2->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX(), player->getPositionY() - 70);
		DShade3->setPosition(player->getPositionX(), player->getPositionY());
		player->setPosition(player->getPositionX(), player->getPositionY() - 70);
		break;
	}
	}
}

