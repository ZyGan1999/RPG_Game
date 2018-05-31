#include "BattleScene.h"
#include "Enemy.h"
#include "Soldier.h"
#include "Actions.h"
#include "PlayerStatus.h"
#include "GameOverScene.h"
#include <fstream>
string BattleScene::mapName = "World1";
map<string, string> BattleScene::enemyfile = {
	make_pair("World1",".\\World1\\enemylist.txt")
};

bool BattleScene::init()
{
	FireBallCD = 0;
	SideStepCD = 0;
	FBCD = LabelTTF::create(to_string(FireBallCD / 60), "Courier", 36);
	SSCD = LabelTTF::create(to_string(SideStepCD / 60), "Courier", 36);
	addChild(FBCD, 8); addChild(SSCD, 8);
	shadeLayer = Layer::create();
	addChild(shadeLayer, 4);
	enemyLayer = Layer::create();
	ps = PlayerStatus::getInstance();
	player = Player::getInstance();
	this->scheduleUpdate();
	schedule(schedule_selector(BattleScene::enemyMove), 1.0f);
	auto visiablesize = Director::getInstance()->getVisibleSize();
	player->setPosition(visiablesize.width / 5, visiablesize.height / 5);
	addChild(player, 3);
	LoadFromFile(mapName);
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		enemyLayer->addChild((*it));
		(*it)->setPosition(visiablesize.width / 2, visiablesize.height / 2);
		(*it)->setBlood(enemyLayer);
	}
	addChild(enemyLayer, 4);

	auto bg1 = Sprite::create(".\\World1\\background1.png");
	auto bg2 = Sprite::create(".\\World1\\background2.png");
	bg1->setContentSize(visiablesize); bg1->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	bg2->setContentSize(visiablesize); bg2->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	addChild(bg1, 1); addChild(bg2, 2);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event *e) {
		if (code == EventKeyboard::KeyCode::KEY_R) {
			if (!ps->CheckFBCD())CallFireBall();
			return;
		}
		else if (code == EventKeyboard::KeyCode::KEY_SPACE) {
			if (!ps->CheckSSCD())CallSideStep();
			return;
		}
		keys[code] = true;
	};
	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event *e) {
		keys[code] = false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);

	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = [this](Touch *t, Event *e) {
		if (!_fireballs.empty()) {
			auto f = &_fireballs[0];
			_releasedFireBalls.push_back((*f));
			(*f)->setAnchorPoint(Vec2(0.5, 0.5));
			(*f)->runAction(MoveBy::create(2, 10 * Vec2(t->getLocation().x - player->getPositionX(), t->getLocation().y - player->getPositionY())));
			_fireballs.erase(_fireballs.begin());
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchlistener, this);
	PlayerHPStatus = to_string(ps->getHP()) + " / " + to_string(ps->getHPMax());
	HP_INFO = LabelTTF::create(PlayerHPStatus, "Courier", 36); HP_INFO->setColor(Color3B(255, 0, 0));
	HP_INFO->setPosition(visiablesize.width * 0.8, visiablesize.height / 5);

	addChild(HP_INFO, 8);
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
	if (FireBallCD != 0) {
		FireBallCD--;
		if (FireBallCD == 0) {
			ps->releaseFBCD();
		}
	}
	if (SideStepCD != 0) {
		SideStepCD--;
		if (SideStepCD == 0) {
			ps->releaseSSCD();
		}
	}
	Actions a;
	if (keys[EventKeyboard::KeyCode::KEY_A])player->runAction(a.MoveLeft), lastDirection = EventKeyboard::KeyCode::KEY_A;
	if (keys[EventKeyboard::KeyCode::KEY_D])player->runAction(a.MoveRight), lastDirection = EventKeyboard::KeyCode::KEY_D;
	if (keys[EventKeyboard::KeyCode::KEY_W])player->runAction(a.MoveUp), lastDirection = EventKeyboard::KeyCode::KEY_W;
	if (keys[EventKeyboard::KeyCode::KEY_S])player->runAction(a.MoveDown), lastDirection = EventKeyboard::KeyCode::KEY_S;
	if (ps->getHP() == 0) Director::getInstance()->replaceScene(GameOverScene::create());
	if (player->getPositionX() < 50) player->setPositionX(50);
	if (player->getPositionX() > 974) player->setPositionX(974);
	if (player->getPositionY() < 50) player->setPositionY(50);
	if (player->getPositionY() > 450) player->setPositionY(450);
	for (auto e = _enemies.begin(); e != _enemies.end(); ++e) {
		(*e)->removeBlood();
		(*e)->updateHP();
		(*e)->setBlood(enemyLayer);
	}
	auto visiablesize = Director::getInstance()->getVisibleSize();
	HP_INFO->removeFromParent();
	PlayerHPStatus = to_string(ps->getHP()) + " / " + to_string(ps->getHPMax());
	HP_INFO = LabelTTF::create(PlayerHPStatus, "Courier", 36); HP_INFO->setColor(Color3B(255, 0, 0));
	HP_INFO->setPosition(visiablesize.width * 0.8, visiablesize.height / 5);
	addChild(HP_INFO, 6);

	FBCD->removeFromParent();
	FBCD = LabelTTF::create(to_string(FireBallCD + 60 / 60), "Courier", 36); FBCD->setColor(Color3B(0, 255, 255));
	addChild(FBCD, 8); FBCD->setPosition(HP_INFO->getPositionX(), HP_INFO->getPositionY() + 100);
	SSCD->removeFromParent();
	SSCD = LabelTTF::create(to_string(SideStepCD + 60 / 60), "Courier", 36); SSCD->setColor(Color3B(255, 255, 0));
	addChild(SSCD, 8); SSCD->setPosition(HP_INFO->getPositionX(), HP_INFO->getPositionY() + 200);

	if (!_fireballs.empty())
		for (auto it = _fireballs.begin(); it != _fireballs.end(); ) {
			(*it)->setPosition(player->getPositionX(), player->getPositionY());
			++it;
		}
	if (!_releasedFireBalls.empty()) {
		for (auto it = _releasedFireBalls.begin(); it != _releasedFireBalls.end();) {
			if (!inRange((*it)->getPositionX(), 0, 1024) || !inRange((*it)->getPositionY(), 0, 768)) {
				(*it)->removeFromParentAndCleanup(true);
				it = _releasedFireBalls.erase(it);
				continue;
			}
			else {
				for (auto e = _enemies.begin(); e != _enemies.end(); ++e) {
					if ((*it)->getBoundingBox().intersectsRect((*e)->getBoundingBox())) {
						(*e)->subHP(1);
					}
				}++it;
			}
			
		}
	}

		for (auto it = _enemies.begin(); it != _enemies.end(); ) {
			if ((*it)->getHP() <= 0) {
				(*it)->removeBlood();
				(*it)->removeFromParent();
				it = _enemies.erase(it);
			}
			else ++it;
		}
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

void BattleScene::CallFireBall()
{
	FireBallCD = 600;
	ps->setFBCD();
	auto f1 = FireBall::create(); f1->setAnchorPoint(Vec2(0.5, -0.7)); f1->setTag(0);
	auto f2 = FireBall::create(); f2->setAnchorPoint(Vec2(1.7, 0.5)); f2->setTag(0);
	auto f3 = FireBall::create(); f3->setAnchorPoint(Vec2(0.5, 1.7)); f3->setTag(0);
	auto f4 = FireBall::create(); f4->setAnchorPoint(Vec2(-0.7, 0.5)); f4->setTag(0);
	_fireballs.push_back(f1); _fireballs.push_back(f2); _fireballs.push_back(f3); _fireballs.push_back(f4);
	f1->setPosition(player->getPositionX(), player->getPositionY()); addChild(f1, 7);f1->GoAround();
	f2->setPosition(player->getPositionX(), player->getPositionY()); addChild(f2, 7);f2->GoAround();
	f3->setPosition(player->getPositionX(), player->getPositionY()); addChild(f3, 7);f3->GoAround();
	f4->setPosition(player->getPositionX(), player->getPositionY()); addChild(f4, 7);f4->GoAround();
}

void BattleScene::CallSideStep()
{
	SideStepCD = 120;
	ps->setSSCD();
	Actions a;
	a.SideStep(shadeLayer, lastDirection);

	auto delayTime = DelayTime::create(0.5f);
	auto DLE = CallFunc::create([this]()
	{
		shadeLayer->removeAllChildren();
	});
	auto seq1 = Sequence::create(delayTime, DLE, nullptr);
	this->runAction(seq1);
}
