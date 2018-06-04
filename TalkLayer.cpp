#include "TalkLayer.h"
#include <fstream>

void TalkLayer::setTalkLayer(string talkfilename)
{
	memset(lines, 0, sizeof(string));
	curLineNum = 1;
	LoadFromFile(talkfilename);
	AnalyzeLine(curLineNum);
	//return talklayer;
}

void TalkLayer::nextLine()
{
	this->removeAllChildren();
	AnalyzeLine(++curLineNum);
}

void TalkLayer::LoadFromFile(string filename)
{
	ifstream ReadTalk(filename);
	int i = 1;
	while (!ReadTalk.eof()) {
		getline(ReadTalk, lines[i++]);
	}
}

void TalkLayer::AnalyzeLine(int lineNum)
{
	auto visiablesize = Director::getInstance()->getVisibleSize();
	switch (lines[lineNum][0]) {
	case 'p': {
		auto cg = Sprite::create(".\\CG\\PlayerCG.png");
		cg->setScale(0.5);
		//position
		cg->setPosition(visiablesize.width / 5, visiablesize.height / 2 - 50);
		this->addChild(cg, 1);
		string word = "";
		for (int i = 2; i < lines[lineNum].length(); i++) {
			word += lines[lineNum][i];
		}
		auto WordLabel = LabelTTF::create(word, "Courier", 36);
		//position
		WordLabel->setPosition(visiablesize.width * 0.7, visiablesize.height / 5);
		this->addChild(WordLabel, 3);
		auto talkbox = Sprite::create(".\\talk\\wordbox.png");
		talkbox->setPosition(visiablesize.width *0.7, visiablesize.height / 5);
		talkbox->setScale(0.4);
		this->addChild(talkbox, 2);
		break;
	}
	case 'e': {
		//Talk Over
		this->setTag(1);
		this->removeAllChildren();
		break;
	}
	}
	
}
