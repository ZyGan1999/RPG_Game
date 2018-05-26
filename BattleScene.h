#pragma once
#include <cocos2d.h>
#include <vector>
#include <map>
#include <string>
#include "Enemy.h"
using namespace std;
using namespace cocos2d;
class BattleScene:public Scene
{
public:
	virtual bool init();
	static Scene * createScene(string mapName);
	CREATE_FUNC(BattleScene);
	virtual void enemyMove(float dt);
private:
	static string _mapName;//to do
	vector<Enemy * >_enemies;
	void LoadFromFile(string mapName);
	static map<string, string> enemyfile;
};

