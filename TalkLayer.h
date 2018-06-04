#pragma once
#include <cocos2d.h>
#include <string>
using namespace std;
using namespace cocos2d;
class TalkLayer:public Layer
{
public:
	void setTalkLayer(string talkfilename);
	void nextLine();
	//TalkLayer * createTalkLayer();
	CREATE_FUNC(TalkLayer);
private:
	void LoadFromFile(string filename);
	void AnalyzeLine(int lineNum);
	//Layer * talklayer;
	string lines[100];
	int curLineNum;
};

