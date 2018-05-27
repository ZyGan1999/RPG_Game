#pragma once
#include <cocos2d.h>
#include <vector>
#include <map>
#include <string>
#include "Enemy.h"
#include "Player.h"
#include "FireBall.h"
using namespace std;
using namespace cocos2d;
class BattleScene:public Scene
{
public:
	virtual bool init();
	static Scene * createScene();
	CREATE_FUNC(BattleScene);
	void enemyMove(float dt);
	void update(float dt);
private:
	PlayerStatus * ps;
	Sprite * player;
	static string mapName;//to do
	vector<Enemy * >_enemies;
	void LoadFromFile(string mapName);
	static map<string, string> enemyfile;
	map<EventKeyboard::KeyCode, bool> keys;
	EventKeyboard::KeyCode lastDirection;
	string PlayerHPStatus;
	LabelTTF * HP_INFO;
	vector<FireBall * > _fireballs;
	void CallFireBall();
};

