#pragma once
#include <cocos2d.h>
#include <string>
#include <vector>
#include <map>
#include "TalkLayer.h"
using namespace cocos2d;
using namespace std;
class World1:public Scene
{
public:
	CREATE_FUNC(World1);
	virtual bool init();
	static void notTalk() {
		isTalk = false;
	}
private:
	static bool isTalk;
	void Save();
	void update(float delta);
	static int GRID_SIZE;
	void LoadFromFile();
	void LoadFloor();
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

