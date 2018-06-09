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
	static Scene * createScene(string mapName);
	CREATE_FUNC(BattleScene);
	
private:
	void enemyMove(float dt);
	void update(float dt);
	Layer * shadeLayer;
	Layer * enemyLayer;
	PlayerStatus * ps;
	Sprite * player;
	Sprite * PLAYER_HP_RED;
	Sprite * PLAYER_HP_GRAY;
	Sprite * PLAYER_MP_BLUE;
	Sprite * PLAYER_MP_GRAY;
	Sprite * PlayerFace;
	Sprite * FBspic1; Sprite * FBspic2;
	Sprite * SSspic1; Sprite * SSspic2;
	ProgressTimer * FBTimer; ProgressTimer * SSTimer;
	static string mapName;//to do
	vector<Enemy * >_enemies;
	void LoadFromFile(string mapName);
	static map<string, string> enemyfile;
	map<EventKeyboard::KeyCode, bool> keys;
	EventKeyboard::KeyCode lastDirection;
	string PlayerHPStatus;
	LabelTTF * HP_INFO;
	vector<FireBall * > _fireballs;
	vector<FireBall * > _releasedFireBalls;
	void CallFireBall();
	void CallSideStep();
	bool inRange(int x, int inf, int sup) {
		if (x <= sup && x >= inf) {
			return true;
		}
		else return false;
	}
	int FireBallCD;
	int SideStepCD;
	/*LabelTTF * FBCD;
	LabelTTF * SSCD;*/
};

