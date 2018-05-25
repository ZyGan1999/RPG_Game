#include "PlayerStatus.h"
PlayerStatus * PlayerStatus::instance = new PlayerStatus;
int PlayerStatus::HP = 10;
int PlayerStatus::MP = 10;
int PlayerStatus::HPMax = 100;
int PlayerStatus::MPMax = 100;
PlayerStatus * PlayerStatus::getInstance()
{
	if (instance == nullptr) instance = new PlayerStatus;
	return instance;
}

void PlayerStatus::AddHP(int delta)
{
	HP += delta;
	HP = _min(HP, HPMax);
}

void PlayerStatus::SubHP(int delta)
{
	HP -= delta;
	HP = _max(HP, 0);
}

void PlayerStatus::AddMP(int delta)
{
	MP += delta;
	MP = _min(MP, MPMax);
}

void PlayerStatus::SubMP(int delta)
{
	MP -= delta;
	MP = _max(MP, 0);
}

void PlayerStatus::AddHPMax(int delta)
{
	HPMax += delta;
}

void PlayerStatus::AddMPMax(int delta)
{
	MPMax += delta;
}