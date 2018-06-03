#pragma once
#include<cocos2d.h>
using namespace cocos2d;
class NormalAttack
{
public:
	static Rect CreateAndPlay(int posX, int posY, Scene * s);
private:
	static Vector<AnimationFrame * > _animationframe;
	static bool _initvector;
	static bool initvector();
};

