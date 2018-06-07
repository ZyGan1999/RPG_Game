#include "TalkLayer.h"
#include <fstream>

void TalkLayer::setTalkLayer(string talkfilename)
{
	this->setTag(0);
	memset(lines, 0, sizeof(string));
	//for (int i = 1; i <= 100; i++) {
	//	lines[i] = "";
	//}
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
			//if ((i - 1) % 7 == 0) word += '\n';
			word += lines[lineNum][i];
		}
		auto WordLabel = LabelTTF::create(string_To_UTF8(word), "Courier", 16);
		//position
		WordLabel->setPosition(visiablesize.width * 0.7, visiablesize.height / 5);
		this->addChild(WordLabel, 3);
		auto talkbox = Sprite::create(".\\talk\\wordbox.png");
		talkbox->setPosition(visiablesize.width *0.7, visiablesize.height / 5);
		talkbox->setScale(0.4);
		this->addChild(talkbox, 2);
		break;
	}
	case 's': {
		auto cg = Sprite::create(".\\CG\\sisterCG.png");
		cg->setScale(0.5);
		//position
		cg->setPosition(visiablesize.width / 5, visiablesize.height / 2 - 50);
		this->addChild(cg, 1);
		string word = "";
		for (int i = 2; i < lines[lineNum].length(); i++) {
			//if ((i - 1) % 7 == 0) word += '\n';
			word += lines[lineNum][i];
		}
		auto WordLabel = LabelTTF::create(string_To_UTF8(word), "Courier", 16);
		//position
		WordLabel->setPosition(visiablesize.width * 0.7, visiablesize.height / 5);
		this->addChild(WordLabel, 3);
		auto talkbox = Sprite::create(".\\talk\\wordbox.png");
		talkbox->setPosition(visiablesize.width *0.7, visiablesize.height / 5);
		talkbox->setScale(0.4);
		this->addChild(talkbox, 2);
		break;
	}
	case 'l': {
		auto cg = Sprite::create(".\\CG\\Soldier.png");
		cg->setScale(2);
		//position
		cg->setPosition(visiablesize.width / 5, visiablesize.height / 2 - 50);
		this->addChild(cg, 1);
		string word = "";
		for (int i = 2; i < lines[lineNum].length(); i++) {
			//if ((i - 1) % 7 == 0) word += '\n';
			word += lines[lineNum][i];
		}
		auto WordLabel = LabelTTF::create(string_To_UTF8(word), "Courier", 16);
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

std::string TalkLayer::string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}