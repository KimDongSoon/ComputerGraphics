#pragma once
#include "Player.h"

class ScnMgr {
	Player* m_Player;		// �ϳ��� ����

public:
	void RenderScene();

public:
	ScnMgr();
	~ScnMgr();
};