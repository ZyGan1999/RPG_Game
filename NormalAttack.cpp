#include "NormalAttack.h"
#include "Player.h"
#include<cmath>
Vector<AnimationFrame * > NormalAttack::_animationframe;
bool NormalAttack::_initvector = NormalAttack::initvector();
Rect NormalAttack::CreateAndPlay(int posX, int posY, Scene * s)
{
	auto retsp = Sprite::create();
	double deltaX = posX - Player::getInstance()->getPositionX();
	double deltaY = posY - Player::getInstance()->getPositionY();
	double distance = sqrt(deltaX*deltaX + deltaY * deltaY);
	auto animate = Animate::create(Animation::create(_animationframe, 0.5));
	auto sp = Sprite::create();
	if(distance <= 300){
		sp->setPosition(posX, posY);
	}
	else {
		double r = distance / 300;
		deltaX /= r; deltaY /= r;
		sp->setPosition(Player::getInstance()->getPositionX() + deltaX, Player::getInstance()->getPositionY() + deltaY);
	}
	s->addChild(sp, 6);
	sp->runAction(animate);

	retsp->setPosition(sp->getPositionX(), sp->getPositionY());
	return retsp->getBoundingBox();
}
bool NormalAttack::initvector()
{
	AnimationFrame * a[21];
	a[1] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(0, 0, 192, 192)), 0.1, ValueMap());
	a[2] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(192, 0, 192, 192)), 0.1, ValueMap());
	a[3] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(2 * 192, 0, 192, 192)), 0.1, ValueMap());
	a[4] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(3 * 192, 0, 192, 192)), 0.1, ValueMap());
	a[5] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(4 * 192, 0, 192, 192)), 0.1, ValueMap());
	a[6] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(0, 192, 192, 192)), 0.1, ValueMap());
	a[7] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(192, 192, 192, 192)), 0.1, ValueMap());
	a[8] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(2 * 192, 192, 192, 192)), 0.1, ValueMap());
	a[9] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(3 * 192, 192, 192, 192)), 0.1, ValueMap());
	a[10] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(4 * 192, 192, 192, 192)), 0.1, ValueMap());
	a[11] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(0, 2 * 192, 192, 192)), 0.1, ValueMap());
	a[12] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(192, 2 * 192, 192, 192)), 0.1, ValueMap());
	a[13] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(2 * 192, 2 * 192, 192, 192)), 0.1, ValueMap());
	a[14] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(3 * 192, 2 * 192, 192, 192)), 0.1, ValueMap());
	a[15] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(4 * 192, 2 * 192, 192, 192)), 0.1, ValueMap());
	a[16] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(0, 3 * 192, 192, 192)), 0.1, ValueMap());
	a[17] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(192, 3 * 192, 192, 192)), 0.1, ValueMap());
	a[18] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(2 * 192, 3 * 192, 192, 192)), 0.1, ValueMap());
	a[19] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(3 * 192, 3 * 192, 192, 192)), 0.1, ValueMap());
	a[20] = AnimationFrame::create(SpriteFrame::create(".\\bomb\\NA.png", Rect(4 * 192, 3 * 192, 192, 192)), 0.1, ValueMap());
	
	for (int i = 1; i <= 20; i++) {
		_animationframe.pushBack(a[i]);
	}
	return true;
}
