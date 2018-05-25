#pragma once
#include<cocos2d.h>
using namespace std;
using namespace cocos2d;
class Player
{
private:
	Player();
	static Sprite* instance;
public:
	static Sprite * getInstance();
	static int GRID_SIZE;
};

