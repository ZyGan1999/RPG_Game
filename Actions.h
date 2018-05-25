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
	static Actions& getInstance();
	static int GRID_SIZE;
	
private:
	//static Actions instance;

		
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

