#include "StartScene.h"
#include "BagScene.h"
#include "HelloWorldScene.h"
#include "World1.h"
#include "BattleScene.h"
bool StartScene::init() {
	auto visiablesize = Director::getInstance()->getVisibleSize();
	auto BackGround = Sprite::create(".\\startscene\\Tower1.png");
	BackGround->setContentSize(visiablesize);
	BackGround->setPosition(visiablesize.width / 2, visiablesize.height / 2);

	auto label_welcome = Label::createWithTTF("The Siege of Witch", ".\\fonts\\midi.ttf", 140);
	label_welcome->setColor(Color3B(208, 32, 144));
	
	auto StartButton = Menu::create(MenuItemImage::create(".\\startscene\\startNormal.png",
		".\\startscene\\startSelected.png", 
		[](Object *obj) {
		Director::getInstance()->replaceScene(BattleScene::createScene("World1"));
	}), NULL);
	StartButton->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	addChild(StartButton, 2);
	label_welcome->setPosition(visiablesize.width / 2, 3 * visiablesize.height / 4);		
	auto layer_welcome = Layer::create();
	layer_welcome->addChild(label_welcome, 2);
	layer_welcome->addChild(BackGround, 1);
	addChild(layer_welcome);
	
	auto menu = Menu::create(MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [](Object *obj) {
		Director::getInstance()->end();

	}), NULL);
	menu->setPosition(visiablesize.width * 0.9, visiablesize.height / 10);
	layer_welcome->addChild(menu, 2);
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [](EventKeyboard::KeyCode k, Event *e) {
		if (k == EventKeyboard::KeyCode::KEY_B) Director::getInstance()->replaceScene(BagScene::create());
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);
	return true;
}
