#include "World1.h"
#include "Player.h"
#include "Actions.h"
#include <fstream>
#include <algorithm>
string World1::MapFileName = ".\\World1\\MapFile.txt";
int World1::GRID_SIZE = 48;
map<string, Rect> World1::SpriteRect = {
	make_pair("piano",Rect(5 * GRID_SIZE,12 * GRID_SIZE,3 * GRID_SIZE,2 * GRID_SIZE))
};
map<string, int> World1::SpriteTag = {
	make_pair("piano",3)
};
bool World1::init() {
	this->scheduleUpdate();
	auto visiablesize = Director::getInstance()->getVisibleSize();
	auto bg1 = Sprite::create(".\\World1\\background1.png");
	auto bg2 = Sprite::create(".\\World1\\background2.png");
	bg1->setContentSize(visiablesize); bg1->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	bg2->setContentSize(visiablesize); bg2->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	addChild(bg1, 1); addChild(bg2, 2);

	player = Player::getInstance();
	addChild(player, 3);
	player->setPosition(visiablesize.width / 5, visiablesize.height / 2);
	LoadFromFile();
	auto ObjectLayer = Layer::create();
	for (auto it = _objs.begin(); it != _objs.end(); ++it) {
		ObjectLayer->addChild((*it), 4);
	}
	addChild(ObjectLayer,4);

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

void World1::update(float delta) {
	Actions a;
	if (player->getPositionY() > 450) {
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
	if (s != nullptr) {
		switch (s->getTag()) {
		case 1:break;
		case 2: {
			Fix();
			break;
		}
		case 3: {
			if (player->getPositionY() < s->getPositionY()) {
				Fix();
			}
			break;
		}
		case 4: {
			//battle
		}
		}
	}

	if (keys[EventKeyboard::KeyCode::KEY_A])player->runAction(a.MoveLeft),lastDirection = EventKeyboard::KeyCode::KEY_A;
	else if (keys[EventKeyboard::KeyCode::KEY_D])player->runAction(a.MoveRight), lastDirection = EventKeyboard::KeyCode::KEY_D;
	else if (keys[EventKeyboard::KeyCode::KEY_W])player->runAction(a.MoveUp),lastDirection = EventKeyboard::KeyCode::KEY_W;
	else if (keys[EventKeyboard::KeyCode::KEY_S])player->runAction(a.MoveDown),lastDirection = EventKeyboard::KeyCode::KEY_S;
}

Sprite * World1::isCollided()
{
	for (auto it = _objs.begin(); it != _objs.end(); ++it) {
		if (player->getBoundingBox().intersectsRect((*it)->getBoundingBox())) {
			return (*it);
		}
	}
	return nullptr;
}

void World1::Fix()
{
	keys[EventKeyboard::KeyCode::KEY_A] = false;
	keys[EventKeyboard::KeyCode::KEY_S] = false;
	keys[EventKeyboard::KeyCode::KEY_D] = false;
	keys[EventKeyboard::KeyCode::KEY_W] = false;
	switch (lastDirection) {
	case EventKeyboard::KeyCode::KEY_A: {player->runAction(MoveBy::create(0.001, Vec2(1, 0))); break; }
	case EventKeyboard::KeyCode::KEY_D: {player->runAction(MoveBy::create(0.001, Vec2(-1, 0))); break; }
	case EventKeyboard::KeyCode::KEY_W: {player->runAction(MoveBy::create(0.001, Vec2(0, -1))); break; }
	case EventKeyboard::KeyCode::KEY_S: {player->runAction(MoveBy::create(0.001, Vec2(0, 1))); break; }
	}
}

void World1::LoadFromFile() {
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
		auto s = Sprite::create(".\\World1\\objects.png", SpriteRect[curName]);
		s->setTag(SpriteTag[curName]);
		s->setPosition(PosX, PosY);
		_objs.push_back(s);
	}
}