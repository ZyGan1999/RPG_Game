#pragma once
#include <cocos2d.h>
#include <string>
#include <vector>
#include <map>
using namespace cocos2d;
using namespace std;
class World1:public Scene
{
public:
	CREATE_FUNC(World1);
	virtual bool init();
	void LoadFromFile();
	void update(float delta);
	static int GRID_SIZE;

private:
	vector<Sprite*> _objs;
	static string MapFileName;
	static map<string, Rect> SpriteRect;
	static map<string, int> SpriteTag;
	map<EventKeyboard::KeyCode, bool> keys;
	Sprite *player;
	EventKeyboard::KeyCode lastDirection;
	void Fix();	
	Sprite* isCollided();
};

