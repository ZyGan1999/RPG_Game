#include "GameOverScene.h"
#include "StartScene.h"
bool GameOverScene::init()
{
	auto visiablesize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create(".\\GameOver\\GameOver.png");
	bg->setContentSize(visiablesize);
	bg->setPosition(visiablesize.width / 2, visiablesize.height / 2);
	auto s1 = Sprite::create(".\\GameOver\\RestartNormal.png"); s1->setContentSize(Size(100, 100));
	auto s2 = Sprite::create(".\\GameOver\\RestartSelected.png"); s2->setContentSize(Size(100, 100));
	auto ReStart = Menu::create(MenuItemSprite::create(s1,s2,
		[](Object *obj) {
		Director::getInstance()->replaceScene(StartScene::create());
	}), NULL);
	ReStart->setPosition(visiablesize.width / 2, visiablesize.height / 4);
	addChild(bg, 1);
	addChild(ReStart, 2);
	return true;
}
