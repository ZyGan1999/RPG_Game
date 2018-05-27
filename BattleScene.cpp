#include "BattleScene.h"
#include "Enemy.h"
#include "Soldier.h"
#include "Actions.h"
#include "PlayerStatus.h"
#include <fstream>
string BattleScene::mapName = "World1";
map<string, string> BattleScene::enemyfile = {
	make_pair("World1",".\\World1\\enemylist.txt")
};

bool BattleScene::init()
{
	ps = PlayerStatus::getInstance();
	player = Player::getInstance();
	this->scheduleUpdate();
	schedule(schedule_selector(BattleScene::enemyMove), 1.0f);
	auto visiablesize = Director::getInstance()->getVisibleSize();
	player->setPosition(visiablesize.width / 5, visiablesize.height / 5);
	addChild(player, 3);
	LoadFromFile(mapName);
	auto enemyLayer = Layer::create();
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		enemyLayer->addChild((*it));
		(*it)->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	}
	addChild(enemyLayer, 4);

	auto bg1 = Sprite::create(".\\World1\\background1.png");
	auto bg2 = Sprite::create(".\\World1\\background2.png");
	bg1->setContentSize(visiablesize); bg1->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	bg2->setContentSize(visiablesize); bg2->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	addChild(bg1, 1); addChild(bg2, 2);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event *e) {
		keys[code] = true;
	};
	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event *e) {
		keys[code] = false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);


	return true;
}

Scene * BattleScene::createScene()
{
	return BattleScene::create();
}

void BattleScene::enemyMove(float dt)
{
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		(*it)->seekPlayer();
	}
}

void BattleScene::update(float dt)
{
	auto visiablesize = Director::getInstance()->getVisibleSize();
	PlayerHPStatus = to_string(ps->getHP()) + " / " + to_string(ps->getHPMax());
	HP_INFO = LabelTTF::create(PlayerHPStatus, "Courier", 36); HP_INFO->setColor(Color3B(255, 0, 0));
	HP_INFO->setPosition(visiablesize.width * 0.8, visiablesize.height / 5);
	HP_INFO->removeFromParent();
	addChild(HP_INFO, 6);
	Actions a;
	if (keys[EventKeyboard::KeyCode::KEY_A])player->runAction(a.MoveLeft), lastDirection = EventKeyboard::KeyCode::KEY_A;
	if (keys[EventKeyboard::KeyCode::KEY_D])player->runAction(a.MoveRight), lastDirection = EventKeyboard::KeyCode::KEY_D;
	if (keys[EventKeyboard::KeyCode::KEY_W])player->runAction(a.MoveUp), lastDirection = EventKeyboard::KeyCode::KEY_W;
	if (keys[EventKeyboard::KeyCode::KEY_S])player->runAction(a.MoveDown), lastDirection = EventKeyboard::KeyCode::KEY_S;
}

void BattleScene::LoadFromFile(string mapName) {
	ifstream ReadFile(enemyfile[mapName]);
	while (!ReadFile.eof()) {
		string curName;
		getline(ReadFile, curName);
		if (curName == "Soldier") {
			auto s = Soldier::createSoldier();
			_enemies.push_back(s);
		}
	}
}