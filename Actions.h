#pragma once
#include <cocos2d.h>
using namespace cocos2d;
class Actions
{
public:	
	Actions();
	Spawn* MoveLeft;
	Spawn* MoveRight;
	Spawn* MoveUp;
	Spawn* MoveDown;
	void SideStep(Layer * ,EventKeyboard::KeyCode );
	static int GRID_SIZE;
	
private:
	//static Actions instance;
	Sprite * player;
	Sprite * LShade1; Sprite * LShade2; Sprite * LShade3;
	Sprite * RShade1; Sprite * RShade2; Sprite * RShade3;
	Sprite * UShade1; Sprite * UShade2; Sprite * UShade3;
	Sprite * DShade1; Sprite * DShade2; Sprite * DShade3;
		
	SpriteFrame * L1;
	SpriteFrame * L2;
	SpriteFrame * L3;
	SpriteFrame * R1;
	SpriteFrame * R2;
	SpriteFrame * R3;
	SpriteFrame * U1;
	SpriteFrame * U2;
	SpriteFrame * U3;
	SpriteFrame * D1;
	SpriteFrame * D2;
	SpriteFrame * D3;
};

