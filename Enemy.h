#pragma once
#include <cocos2d.h>
#include <string>
#include <map>
using namespace std;
using namespace cocos2d;
class Enemy:public Sprite
{
public:
	virtual bool init();
	static Enemy * createSprite(string name);
	CREATE_FUNC(Enemy);
	void seekPlayer();

private:
	static string _name;//to do
	static map<string, string> _enemypics;
	static Sprite * player;
};

