#include "StartScene.h"
#include "BagScene.h"
#include "HelloWorldScene.h"
#include "World1.h"
#include "World3.h"
#include "BattleScene.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
bool StartScene::init() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->setBackgroundMusicVolume(0.1);
	audio->playBackgroundMusic(".\\Music\\poem.wav", 1);
	auto visiablesize = Director::getInstance()->getVisibleSize();
	auto BackGround = Sprite::create(".\\startscene\\Tower1.png");
	BackGround->setContentSize(visiablesize);
	BackGround->setPosition(visiablesize.width / 2, visiablesize.height / 2);

	auto title = Label::createWithTTF("The Siege of Witch", ".\\fonts\\midi.ttf", 140);
	title->setColor(Color3B(208, 32, 144));
	
	auto StartButton = Menu::create(MenuItemImage::create(".\\startscene\\startNormal.png",
		".\\startscene\\startSelected.png", 
		[](Object *obj) {
		Director::getInstance()->replaceScene(World1::create());
		//Director::getInstance()->replaceScene(BattleScene::createScene());
	}), NULL);
	StartButton->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	addChild(StartButton, 2);
	title->setPosition(visiablesize.width / 2, 3 * visiablesize.height / 4);		
	auto titleLayer = Layer::create();
	titleLayer->addChild(title, 2);
	titleLayer->addChild(BackGround, 1);
	addChild(titleLayer);
	
	auto menu = Menu::create(MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [](Object *obj) {
		Director::getInstance()->end();

	}), NULL);
	menu->setPosition(visiablesize.width * 0.9, visiablesize.height / 10);
	titleLayer->addChild(menu, 2);
	/*auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [](EventKeyboard::KeyCode k, Event *e) {
		if (k == EventKeyboard::KeyCode::KEY_B) Director::getInstance()->replaceScene(BagScene::create());
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);*/
	return true;
}
