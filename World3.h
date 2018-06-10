#pragma once
#include <cocos2d.h>
#include <string>
#include <vector>
#include <map>
#include "TalkLayer.h"
using namespace cocos2d;
using namespace std;
class World3 :public Scene
{
public:
	CREATE_FUNC(World3);
	virtual bool init();
private:
	void enemyMove(float delta);
	void update(float delta);
	static int GRID_SIZE;
	void LoadFromFile();
	void LoadFloor();
	void Save();
	Vector<Sprite*> _objs;
	Vector<Sprite*> _enemies;
	static string MapFileName;
	static map<string, Rect> SpriteRect;
	static map<string, int> SpriteTag;
	static map<string, string>SpriteFile;
	map<EventKeyboard::KeyCode, bool> keys;
	Layer * ObjectLayer;
	Layer * EnemyLayer;
	Sprite * player;
	Sprite * move;
	EventKeyboard::KeyCode lastDirection;
	void Fix();
	Vector<Sprite * >::iterator isCollided();
	bool isKeyLocked;
	bool isBattle;
};

