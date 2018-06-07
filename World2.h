#pragma once
#include <cocos2d.h>
#include <string>
#include <vector>
#include <map>
#include "TalkLayer.h"
using namespace cocos2d;
using namespace std;
class World2:public Scene
{
public:
	CREATE_FUNC(World2);
	virtual bool init();
	static void notTalk() {
		isTalk = false;
	}
private:
	void update(float delta);
	Sprite * Soldier;
	Sprite * sister;
	static bool isTalk;
	static int GRID_SIZE;
	void LoadFromFile();
	void LoadFloor();
	void Save();
	Vector<Sprite*> _objs;
	static string MapFileName;
	static map<string, Rect> SpriteRect;
	static map<string, int> SpriteTag;
	static map<string, string>SpriteFile;
	map<EventKeyboard::KeyCode, bool> keys;
	Layer * ObjectLayer;
	Sprite * player;
	Sprite * move;
	EventKeyboard::KeyCode lastDirection;
	void Fix();
	Vector<Sprite * >::iterator isCollided();
	TalkLayer * talkLayer;
	bool isKeyLocked;
};

