#pragma once
#include "Player.h"

class ScnMgr {
	Player* m_Player;		// ÇÏ³ª¸¸ »ý±è

public:
	void RenderScene();

public:
	ScnMgr();
	~ScnMgr();
};