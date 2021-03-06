#pragma once
class PlayerStatus
{
private:
	PlayerStatus(){}
	static int HP;
	static int MP;
	static int HPMax;
	static int MPMax;
	static bool isFBCD;
	static bool isSSCD;
	static bool isBlinking;
	static bool BlinkingFrozen;

	static inline int _min(int a, int b) {
		return a < b ? a : b;
	}
	static inline int _max(int a, int b) {
		return a > b ? a : b;
	}
	static PlayerStatus * instance;
public:
	static PlayerStatus * getInstance();
	static void AddHP(int delta);
	static void SubHP(int delta);
	static void AddMP(int delta);
	static void SubMP(int delta);
	static void AddHPMax(int delta);
	static void AddMPMax(int delta);
	static int getHP() {
		return HP;
	}
	static int getHPMax() {
		return HPMax;
	}
	static int getMP() {
		return MP;
	}
	static int getMPMax() {
		return MPMax;
	}
	static bool isBlinkingFrozen() {
		return BlinkingFrozen;
	}
	static bool isPlayerBlinking() {
		return isBlinking;
	}
	void FreezeBlinking() {
		BlinkingFrozen = true;
	}
	void unFreezeBlinking() {
		BlinkingFrozen = false;
	}
	void setBlinking() {
		isBlinking = true;
	}
	void setUnBlinking() {
		isBlinking = false;
	}
	void setFBCD() {
		isFBCD = true;
	}
	void releaseFBCD() {
		isFBCD = false;
	}
	void setSSCD() {
		isSSCD = true;
	}
	void releaseSSCD() {
		isSSCD = false;
	}
	bool CheckFBCD() {
		return isFBCD;
	}
	bool CheckSSCD() {
		return isSSCD;
	}
	static void releaseAllCD() {
		isFBCD = false;
		isSSCD = false;
	}
};

