#include "BagScene.h"
#include "StartScene.h"
#include "PlayerStatus.h"
#include "Player.h"
#include<fstream>
string BagScene::bag_file_name = ".\\bagobject\\bag.txt";
string BagScene::resourcename = ".\\bagobject\\resource.png";
int BagScene::GRID_SIZE = 48;
map<string, Rect> BagScene::location = {
	make_pair("tea",Rect(9 * GRID_SIZE,9 * GRID_SIZE,GRID_SIZE,GRID_SIZE)),
	make_pair("bread",Rect(11 * GRID_SIZE,7 * GRID_SIZE,GRID_SIZE,GRID_SIZE))
};

void BagScene::LoadItemsFromFile() {
	ifstream ReadBag(bag_file_name);
	while (!ReadBag.eof()) {
		string curName;
		getline(ReadBag, curName);
		auto s = Sprite::create(resourcename, location[curName]);
		s->setName(curName);
		_items.push_back(s);
	}
}

bool BagScene::init() {
	LoadItemsFromFile();
	auto visiablesize = Director::getInstance()->getVisibleSize();
	int row = 0; int col = 0;
	Size objectsize(visiablesize.height / 6, visiablesize.height / 6);
	for (auto i = _items.begin(); i != _items.end(); ++i) {
		(*i)->setContentSize(objectsize);
		//(*i)->setAnchorPoint(Vec2(0, 1));
		(*i)->setPosition(col*objectsize.width + 0.5*objectsize.width, visiablesize.height - row * objectsize.height - 0.5*objectsize.height);
		addChild((*i));
		//BagItemLayer->addChild((*i));
		if (col == 8) col = 0, row++;
		else col++;
	}
	auto backNormal = Sprite::create("back.png"); backNormal->setContentSize(objectsize);
	auto backSelected = Sprite::create("back.png"); backSelected->setContentSize(objectsize / 1.5);
	auto menu = Menu::create(MenuItemSprite::create(backNormal,backSelected, [](Object *obj) {
		Director::getInstance()->popScene();
	}), NULL);
	/*auto menu = Menu::create(MenuItemImage::create("back.png", "back.png", [](Object *obj) {
		Director::getInstance()->replaceScene(StartScene::create());
	}), NULL);*/
	menu->setPosition(visiablesize.width / 10, visiablesize.height / 10);
	addChild(menu);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *t, Event *e) {
		for (auto i = _items.begin(); i != _items.end(); ++i) {
			if ((*i)->getBoundingBox().containsPoint(t->getLocation())) {
				(*i)->setAnchorPoint(Vec2(0.5, 0.5));
				(*i)->runAction(ScaleBy::create(0.1, 0.8));
				break;
			}
		}
		return true;
	};
	listener->onTouchCancelled = [&](Touch *t, Event *e) {
		for (auto i = _items.begin(); i != _items.end(); ++i) {
			if ((*i)->getBoundingBox().containsPoint(t->getLocation())) {
				(*i)->setAnchorPoint(Vec2(0.5, 0.5));
				(*i)->runAction(ScaleBy::create(0.1, 1.25));
				break;
			}
		}
	};
	listener->onTouchEnded = [&](Touch *t, Event *e) {
		for (auto i = _items.begin(); i != _items.end(); ++i) {
			if ((*i)->getBoundingBox().containsPoint(t->getLocation())) {
				if ((*i)->getName() == "tea") {
					PlayerStatus::getInstance()->AddMP(7);
				}
				if ((*i)->getName() == "bread") {
					PlayerStatus::getInstance()->AddHP(7);
				}
				(*i)->removeFromParent();
				_items.erase(i);
				saveBag();
				Director::getInstance()->replaceScene(create());
				break;
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	auto ps = PlayerStatus::getInstance();
	string PlayerHPStatus = to_string(ps->getHP()) + " / " + to_string(ps->getHPMax());
	string PlayerMPStatus = to_string(ps->getMP()) + " / " + to_string(ps->getMPMax());
	auto HP_INFO = LabelTTF::create(PlayerHPStatus, "Courier", 36); HP_INFO->setColor(Color3B(255, 0, 0));
	auto MP_INFO = LabelTTF::create(PlayerMPStatus, "Courier", 36); MP_INFO->setColor(Color3B(0, 0, 255));
	HP_INFO->setPosition(visiablesize.width * 0.8, visiablesize.height / 5);
	MP_INFO->setPosition(visiablesize.width * 0.8, visiablesize.height / 6);
	addChild(HP_INFO); addChild(MP_INFO);

	return true;
}

void BagScene::saveBag() {
	ofstream SaveBag(bag_file_name, ios::ate);
	bool flag = false;
	for (auto i = _items.begin(); i != _items.end(); ++i) {
		if (flag) SaveBag << endl;
		SaveBag << (*i)->getName();
		flag = true;
	}
}