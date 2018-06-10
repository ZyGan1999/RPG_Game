#include "World3.h"
#include "World2.h"
#include "Player.h"
#include "Actions.h"
#include "BagScene.h"
#include "TalkLayer.h"
#include "BattleScene.h"
#include "SimpleAudioEngine.h"
#include <fstream>
#include <algorithm>
using namespace CocosDenshion;
string World3::MapFileName = ".\\World3\\MapFile.txt";
int World3::GRID_SIZE = 48;
map<string, Rect> World3::SpriteRect = {
	make_pair("can",Rect(9 * GRID_SIZE,9 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("brokencan",Rect(10 * GRID_SIZE,9 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("pillar",Rect(4 * GRID_SIZE,9 * GRID_SIZE, GRID_SIZE,2 * GRID_SIZE)),
	make_pair("grass",Rect(0,0,2 * GRID_SIZE,2 * GRID_SIZE)),
	make_pair("fence",Rect(13 * GRID_SIZE,0,GRID_SIZE,GRID_SIZE)),
	make_pair("pool",Rect(0,GRID_SIZE,2 * GRID_SIZE,2 * GRID_SIZE)),
	make_pair("bare",Rect(2 * GRID_SIZE,GRID_SIZE,2 * GRID_SIZE,2 * GRID_SIZE)),
	make_pair("statue",Rect(10 * GRID_SIZE,10 * GRID_SIZE,GRID_SIZE,2 * GRID_SIZE)),
	make_pair("fountain",Rect(0,2 * GRID_SIZE,3 * GRID_SIZE,2 * GRID_SIZE)),
	make_pair("flower",Rect(4 * GRID_SIZE,4 * GRID_SIZE,3 * GRID_SIZE,GRID_SIZE)),
	make_pair("dustbin",Rect(14 * GRID_SIZE,0,2 * GRID_SIZE,GRID_SIZE)),
	make_pair("light",Rect(5 * GRID_SIZE,10 * GRID_SIZE,GRID_SIZE,2 * GRID_SIZE)),
	make_pair("road",Rect(5 * GRID_SIZE,0,GRID_SIZE,2 * GRID_SIZE))
};
map<string, int> World3::SpriteTag = {
	make_pair("can",4),
	make_pair("brokencan",2),
	make_pair("pillar",3),
	make_pair("fence",3),
	make_pair("pool",2),
	make_pair("bare",1),
	make_pair("statue",3),
	make_pair("fountain",2),
	make_pair("flower",2),
	make_pair("dustbin",2),
	make_pair("light",3)
};
map<string, string>World3::SpriteFile = {
	make_pair("can",".\\World1\\objects1.png"),
	make_pair("brokencan",".\\World1\\objects1.png"),
	make_pair("pillar",".\\World3\\world3-2.png"),
	make_pair("fence",".\\World3\\grass.png"),
	make_pair("pool",".\\World3\\world3.png"),
	make_pair("bare",".\\World3\\grass.png"),
	make_pair("statue",".\\World1\\objects2.png"),
	make_pair("fountain",".\\World3\\world3-2.png"),
	make_pair("flower",".\\World3\\world3-2.png"),
	make_pair("dustbin",".\\World3\\world3-3.png"),
	make_pair("light",".\\World3\\world3-3.png")
};
bool World3::init() {
	schedule(schedule_selector(World3::enemyMove), 1.0f);
	LoadFloor();
	EnemyLayer = Layer::create();
	isKeyLocked = false;
	auto visiablesize = Director::getInstance()->getVisibleSize();
	move = Sprite::create(".\\World1\\move.png");
	move->setPosition(100, 300);
	addChild(move, 3);
	isBattle = true;
	for (int i = 0; i < 5; i++) {
		auto s = Sprite::create(".\\Enemy\\Windspirit.png");
		s->setContentSize(Size(50, 50));
		s->setPosition(i * 50 + 200, 600);
		_enemies.pushBack(s);
		EnemyLayer->addChild(s);
	}
	addChild(EnemyLayer, 5);

	this->scheduleUpdate();

	player = Player::getInstance();
	addChild(player, 3);
	player->setPosition(visiablesize.width * 0.8, visiablesize.height / 2);
	LoadFromFile();
	ObjectLayer = Layer::create();
	for (auto it = _objs.begin(); it != _objs.end(); ++it) {
		ObjectLayer->addChild((*it), 4);
	}
	addChild(ObjectLayer, 4);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event *e) {
		if (code == EventKeyboard::KeyCode::KEY_B) Director::getInstance()->pushScene(BagScene::create());
		keys[code] = true;
	};
	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event *e) {
		keys[code] = false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);

	return true;
}
void World3::update(float delta) {
	auto visiablesize = Director::getInstance()->getVisibleSize();
	Actions a;
	if (player->getPositionY() > 718) {
		keys[EventKeyboard::KeyCode::KEY_W] = false;
	}
	if (player->getPositionY() < 50) {
		keys[EventKeyboard::KeyCode::KEY_S] = false;
	}
	if (player->getPositionX() < 50) {
		keys[EventKeyboard::KeyCode::KEY_A] = false;
	}
	if (player->getPositionX() > 974) {
		keys[EventKeyboard::KeyCode::KEY_D] = false;
	}
	auto s = isCollided();
	if (s != _objs.end()) {
		switch ((*s)->getTag()) {
		case 1:break;
		case 2: {
			Fix();
			break;
		}
		case 3: {
			if (player->getPositionY() < (*s)->getPositionY()) {
				Fix();
			}
			break;
		}
		case 4: {
			auto bs = Sprite::create(SpriteFile["brokencan"], SpriteRect["brokencan"]);
			bs->setTag(2);
			bs->setPosition((*s)->getPositionX(), (*s)->getPositionY());
			ObjectLayer->addChild(bs);
			_objs.pushBack(bs);
			(*s)->removeFromParentAndCleanup(true);
			_objs.eraseObject(*s);
			int breadNum; int teaNum;
			breadNum = rand() % 5; breadNum++;
			teaNum = rand() % 5; teaNum++;
			ofstream GetItemToBag(".\\bagobject\\bag.txt", ios::app);
			for (int i = 0; i < breadNum; i++) {
				GetItemToBag << endl << "bread";
			}
			for (int i = 0; i < teaNum; i++) {
				GetItemToBag << endl << "tea";
			}
			auto getBread = LabelTTF::create("Get Bread * " + to_string(breadNum), "Courier", 36);
			auto getTea = LabelTTF::create("Get Tea * " + to_string(teaNum), "Courier", 36);
			getBread->setColor(Color3B(255, 0, 0)); getTea->setColor(Color3B(0, 0, 255));
			addChild(getBread, 10); addChild(getTea, 10);
			getBread->setPosition(visiablesize.width / 2, 300);
			getTea->setPosition(visiablesize.width / 2, 350);
			//this->runAction(Sequence::create(DelayTime::create(1.0f), [getBread,getTea]() {getBread->removeFromParent(); getTea->removeFromParent(); }, nullptr));
			/*getBread->runAction(MoveBy::create(5, Vec2(0, 1000)));
			getTea->runAction(MoveBy::create(5, Vec2(0, 1000)));*/
			auto delayTime1 = DelayTime::create(2.0f);
			auto GET = CallFunc::create([getBread, getTea]()
			{
				getBread->removeFromParent();
				getTea->removeFromParent();
			});
			auto seq1 = Sequence::create(delayTime1, GET, nullptr);
			this->runAction(seq1);
			break;
		}
		case 5: {
			(*s)->removeFromParent();
			_objs.eraseObject(*s);
			Director::getInstance()->pushScene(BattleScene::createScene());
			break;
		}
		}
	}


	if (player->getBoundingBox().intersectsRect(move->getBoundingBox())) {
		//World1::notTalk();
		World2::notTalk();
		auto w2 = World2::create();
		Director::getInstance()->replaceScene(w2);
	}
	if(isBattle)
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		if ((*it)->getPositionX() < 50) (*it)->setPositionX(50);
		if ((*it)->getPositionX() > 974) (*it)->setPositionX(974);
		if ((*it)->getPositionY() < 50) (*it)->setPositionY(50);
		if ((*it)->getPositionY() > 718) (*it)->setPositionY(718);
		if ((*it)->getBoundingBox().intersectsRect(player->getBoundingBox())) {
			isBattle = false;
			EnemyLayer->removeAllChildrenWithCleanup(true);
			keys[EventKeyboard::KeyCode::KEY_A] = false;
			keys[EventKeyboard::KeyCode::KEY_S] = false;
			keys[EventKeyboard::KeyCode::KEY_D] = false;
			keys[EventKeyboard::KeyCode::KEY_W] = false;
			SimpleAudioEngine::getInstance()->playBackgroundMusic(".\\Music\\Lighting.wav", 1);
			PlayerStatus::releaseAllCD();
			BattleScene::setBattleScene("World3");
			Director::getInstance()->pushScene(BattleScene::createScene());
		}
		
	}

	if (keys[EventKeyboard::KeyCode::KEY_A])player->runAction(a.MoveLeft), lastDirection = EventKeyboard::KeyCode::KEY_A;
	if (keys[EventKeyboard::KeyCode::KEY_D])player->runAction(a.MoveRight), lastDirection = EventKeyboard::KeyCode::KEY_D;
	if (keys[EventKeyboard::KeyCode::KEY_W])player->runAction(a.MoveUp), lastDirection = EventKeyboard::KeyCode::KEY_W;
	if (keys[EventKeyboard::KeyCode::KEY_S])player->runAction(a.MoveDown), lastDirection = EventKeyboard::KeyCode::KEY_S;
}

Vector<Sprite * >::iterator World3::isCollided()
{
	auto it = _objs.begin();
	auto pb = player->getBoundingBox();
	//pb.setRect(pb.getMinX() + 10, pb.getMidY(), pb.size.width - 20, pb.size.height / 2);
	for (; it != _objs.end(); ++it) {
		if (pb.intersectsRect((*it)->getBoundingBox())) {
			return it;
		}
	}
	return it;
}

void World3::Fix()
{
	keys[EventKeyboard::KeyCode::KEY_A] = false;
	keys[EventKeyboard::KeyCode::KEY_S] = false;
	keys[EventKeyboard::KeyCode::KEY_D] = false;
	keys[EventKeyboard::KeyCode::KEY_W] = false;
	switch (lastDirection) {
	case EventKeyboard::KeyCode::KEY_A: {player->setPosition(player->getPositionX() + 5, player->getPositionY()); break; }
	case EventKeyboard::KeyCode::KEY_D: {player->setPosition(player->getPositionX() - 5, player->getPositionY()); break; }
	case EventKeyboard::KeyCode::KEY_W: {player->setPosition(player->getPositionX(), player->getPositionY() - 5); break; }
	case EventKeyboard::KeyCode::KEY_S: {player->setPosition(player->getPositionX(), player->getPositionY() + 5); break; }
	}
}

void World3::LoadFromFile() {
	ifstream ReadMap(MapFileName);
	while (!ReadMap.eof()) {
		string curLine;
		getline(ReadMap, curLine);
		string curName = ""; string X = ""; string Y = "";
		int i = 0;
		for (; curLine[i] != ' '; i++) {
			curName += curLine[i];
		}
		for (i++; curLine[i] != ' '; i++) {
			X += curLine[i];
		}
		for (i++; i < curLine.length(); i++) {
			Y += curLine[i];
		}
		int PosX = atoi(X.c_str()); int PosY = atoi(Y.c_str());
		auto s = Sprite::create(SpriteFile[curName], SpriteRect[curName]);
		s->setTag(SpriteTag[curName]);
		s->setName(curName);
		s->setPosition(PosX, PosY);
		_objs.pushBack(s);
	}
}
void World3::LoadFloor() {
	for (int i = 0; i <= 15; i++) {
		for (int j = 0; j <= 10; j++) {
			auto f = Sprite::create(".\\World3\\grass.png", SpriteRect["grass"]);
			f->setAnchorPoint(Vec2(0, 0));
			f->setPosition(i * 2 * GRID_SIZE, j * 2 * GRID_SIZE);
			addChild(f, 1);
		}
	}
	for (int i = 0; i <= 30; i++) {
		auto w = Sprite::create(".\\World3\\floor.png", SpriteRect["road"]);
		w->setAnchorPoint(Vec2(0, 1));
		w->setPosition(i * GRID_SIZE, 350);
		addChild(w, 2);
	}
}
void World3::Save()
{
	ofstream SaveObj(MapFileName);
	bool flag = false;
	for (auto i = _objs.begin(); i != _objs.end(); ++i) {
		if (flag) SaveObj << endl;
		SaveObj << (*i)->getName() << ' ' << (*i)->getPositionX() << ' ' << (*i)->getPositionY();
		flag = true;
	}
}

void World3::enemyMove(float delta) {
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		int direction = rand() % 4; direction++;
		switch (direction) {
		case 1: {
			(*it)->runAction(MoveBy::create(1, Vec2(-100, 0)));
			break;
		}
		case 2: {
			(*it)->runAction(MoveBy::create(1, Vec2(100, 0)));
			break;
		}
		case 3: {
			(*it)->runAction(MoveBy::create(1, Vec2(0, 100)));
			break;
		}
		case 4: {
			(*it)->runAction(MoveBy::create(1, Vec2(0, -100)));
			break;
		}
		}
	}
}