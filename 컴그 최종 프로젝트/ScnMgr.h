#pragma once
#include "Player.h"

class ScnMgr {
	Player* m_Player;		// ÇÏ³ª¸¸ »ý±è

public:
	void RenderScene();

	void Motion(int, int);

	int& GetPrevX() { return prevX; }

private:
	int prevX = 0, prevY = 0;

	int scnMgr_mouseX = 0, scnMgr_mouseY = 0;


public:
	ScnMgr();
	~ScnMgr();
};