#include "BattleScene.h"
#include "Enemy.h"
#include <fstream>
map<string, string> BattleScene::enemyfile = {
	make_pair("World1",".\\World1\\enemylist.txt")
};

bool BattleScene::init()
{
	this->schedule(SEL_SCHEDULE(BattleScene::enemyMove), 1.0f);
	auto visiablesize = Director::getInstance()->getVisibleSize();
	LoadFromFile(_mapName);
	auto enemyLayer = Layer::create();
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		enemyLayer->addChild((*it));
		(*it)->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	}
	addChild(enemyLayer, 2);

	auto bg1 = Sprite::create(".\\World1\\background1.png");
	auto bg2 = Sprite::create(".\\World1\\background2.png");
	bg1->setContentSize(visiablesize); bg1->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	bg2->setContentSize(visiablesize); bg2->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	addChild(bg1, 1); addChild(bg2, 2);
	return true;
}

Scene * BattleScene::createScene(string mapName)
{
	this->_mapName = mapName;
	return BattleScene::create();
}

void BattleScene::enemyMove(float dt)
{
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		(*it)->seekPlayer();
	}
}

void BattleScene::LoadFromFile(string mapName) {
	ifstream ReadFile(enemyfile[mapName]);
	while (!ReadFile.eof()) {
		string curName;
		getline(ReadFile, curName);
		auto s = Enemy::createEnemy(curName);
		_enemies.push_back(s);
	}
}