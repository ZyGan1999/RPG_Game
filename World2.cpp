#include "World2.h"
#include"World1.h"
#include "Player.h"
#include "Actions.h"
#include "BagScene.h"
#include "TalkLayer.h"
#include "BattleScene.h"
#include <fstream>
#include <algorithm>
string World2::MapFileName = ".\\World2\\MapFile.txt";
int World2::GRID_SIZE = 48;
bool World2::isTalk = true;
map<string, Rect> World2::SpriteRect = {
	make_pair("piano",Rect(5 * GRID_SIZE,12 * GRID_SIZE,3 * GRID_SIZE,2 * GRID_SIZE)),
	make_pair("floor",Rect(5 * GRID_SIZE,6 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("wall",Rect(10 * GRID_SIZE,2 * GRID_SIZE,2 * GRID_SIZE,2 * GRID_SIZE)),
	make_pair("shelf",Rect(6 * GRID_SIZE,8 * GRID_SIZE,2 * GRID_SIZE,2 * GRID_SIZE)),
	make_pair("desk1",Rect(0,12 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("desk2",Rect(GRID_SIZE,12 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("can",Rect(9 * GRID_SIZE,9 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("brokencan",Rect(10 * GRID_SIZE,9 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("blackboard",Rect(0,0,3 * GRID_SIZE, 2 * GRID_SIZE)),
	make_pair("pillar",Rect(15 * GRID_SIZE,3 * GRID_SIZE, GRID_SIZE,3 * GRID_SIZE)),
	make_pair("board",Rect(13 * GRID_SIZE,12 * GRID_SIZE,3 * GRID_SIZE,2 * GRID_SIZE))
};
map<string, int> World2::SpriteTag = {
	make_pair("piano",3),
	make_pair("shelf",3),
	make_pair("desk1",2),
	make_pair("desk2",2),
	make_pair("can",4),
	make_pair("brokencan",2),
	make_pair("blackboard",2),
	make_pair("pillar",3),
	make_pair("board",3)
};
map<string, string>World2::SpriteFile = {
	make_pair("piano",".\\World1\\objects1.png"),
	make_pair("shelf",".\\World1\\objects1.png"),
	make_pair("desk1",".\\World1\\objects1.png"),
	make_pair("desk2",".\\World1\\objects1.png"),
	make_pair("can",".\\World1\\objects1.png"),
	make_pair("brokencan",".\\World1\\objects1.png"),
	make_pair("blackboard",".\\World1\\objects2.png"),
	make_pair("pillar",".\\World1\\objects2.png"),
	make_pair("board",".\\World1\\objects2.png")
};
bool World2::init() {
	//LoadFloor();
	isKeyLocked = false;
	auto visiablesize = Director::getInstance()->getVisibleSize();
	talkLayer = TalkLayer::create();
	if(isTalk){
	Soldier = Sprite::create(".\\World2\\Soldier.png");
	sister = Sprite::create(".\\World2\\sister.png", Rect(8 * 64, 5 * 64, 64, 64));
	Soldier->setPosition(visiablesize.width / 2 - 200, visiablesize.height / 2);
	sister->setPosition(Soldier->getPositionX() + 200, Soldier->getPositionY() - 100);
	addChild(Soldier, 3); addChild(sister, 3);
	talkLayer->setTalkLayer(".\\talk\\world2.txt"); isKeyLocked = true;
	}

	move = Sprite::create(".\\World1\\move.png");
	move->setPosition(100, 300);
	addChild(move, 3);
	


	auto bg1 = Sprite::create(".\\World1\\background1.png"); bg1->setContentSize(visiablesize);
	auto bg2 = Sprite::create(".\\World1\\background2.png"); bg2->setContentSize(visiablesize);
	bg1->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	bg2->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	addChild(bg1, 1); addChild(bg2, 2);
	
	
	addChild(talkLayer, 5);
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
		if (code == EventKeyboard::KeyCode::KEY_SPACE) {
			if (talkLayer->getTag() == 0)talkLayer->nextLine();
			if (talkLayer->getTag() == 1) isKeyLocked = false;
		}
		
		if (!isKeyLocked) keys[code] = true;
	};
	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event *e) {
		keys[code] = false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);

	return true;
}
void World2::update(float delta) {
	auto visiablesize = Director::getInstance()->getVisibleSize();
	Actions a;
	if (player->getPositionY() > 650) {
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
			(*s)->removeFromParent();
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
			Director::getInstance()->pushScene(BattleScene::createScene("World1"));
			break;
		}
		}
	}

	if (isTalk) {
		if (player->getBoundingBox().intersectsRect(Soldier->getBoundingBox())) {
			keys[EventKeyboard::KeyCode::KEY_A] = false;
			keys[EventKeyboard::KeyCode::KEY_S] = false;
			keys[EventKeyboard::KeyCode::KEY_D] = false;
			keys[EventKeyboard::KeyCode::KEY_W] = false;
			Soldier->setPosition(-100, -100);
			Soldier->removeFromParent();
			sister->removeFromParent();
			isTalk = false;
			talkLayer->setTalkLayer(".\\talk\\world2-2.txt"); isKeyLocked = true;
			Director::getInstance()->pushScene(BattleScene::createScene("World1"));
			
			
		}
	}

	if (player->getBoundingBox().intersectsRect(move->getBoundingBox())) {
		World1::notTalk();
		World2::notTalk();
		auto w1 = World1::create();
		Director::getInstance()->replaceScene(w1);
	}

	if (keys[EventKeyboard::KeyCode::KEY_A])player->runAction(a.MoveLeft), lastDirection = EventKeyboard::KeyCode::KEY_A;
	if (keys[EventKeyboard::KeyCode::KEY_D])player->runAction(a.MoveRight), lastDirection = EventKeyboard::KeyCode::KEY_D;
	if (keys[EventKeyboard::KeyCode::KEY_W])player->runAction(a.MoveUp), lastDirection = EventKeyboard::KeyCode::KEY_W;
	if (keys[EventKeyboard::KeyCode::KEY_S])player->runAction(a.MoveDown), lastDirection = EventKeyboard::KeyCode::KEY_S;
}

Vector<Sprite * >::iterator World2::isCollided()
{
	auto it = _objs.begin();
	auto pb = player->getBoundingBox();
	pb.setRect(pb.getMinX() + 10, pb.getMidY(), pb.size.width - 20, pb.size.height / 2);
	for (; it != _objs.end(); ++it) {
		if (pb.intersectsRect((*it)->getBoundingBox())) {
			return it;
		}
	}
	return it;
}

void World2::Fix()
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

void World2::LoadFromFile() {
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
void World2::LoadFloor() {
	for (int i = 0; i <= 30; i++) {
		for (int j = 0; j <= 25; j++) {
			auto f = Sprite::create(".\\World1\\floor.png", SpriteRect["floor"]);
			f->setAnchorPoint(Vec2(0, 0));
			f->setPosition(i * GRID_SIZE, j * GRID_SIZE);
			addChild(f, 1);
		}
	}
	for (int i = 0; i <= 15; i++) {
		auto w = Sprite::create(".\\World1\\wall.png", SpriteRect["wall"]);
		w->setAnchorPoint(Vec2(0, 1));
		w->setPosition(2 * i * GRID_SIZE, Director::getInstance()->getVisibleSize().height);
		addChild(w, 2);
	}
}
void World2::Save()
{
	ofstream SaveObj(MapFileName);
	bool flag = false;
	for (auto i = _objs.begin(); i != _objs.end(); ++i) {
		if (flag) SaveObj << endl;
		SaveObj << (*i)->getName() << ' ' << (*i)->getPositionX() << ' ' << (*i)->getPositionY();
		flag = true;
	}
}
