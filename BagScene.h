#pragma once
#include<cocos2d.h>
#include<string>
#include<vector>
#include<map>

using namespace std;
using namespace cocos2d;
class BagScene:public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(BagScene);
	void LoadItemsFromFile();
	static string bag_file_name;
	static string resourcename;
	static int GRID_SIZE;//一格代表多少像素
	void saveBag();
private:
	static map<string, Rect> location;
	vector<Sprite*> _items;
	//Layer* BagItemLayer;
};

