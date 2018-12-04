#pragma once

#include <gl/freeglut.h>
#include <iostream>
#include <math.h>
using namespace std;

#define PI 3.1415927

class Handle
{
private:
	int m_x = 0, m_y = 0, m_z = 0;
	int m_r = 100, m_angle = 0;
	float m_angle_for_handle = 0.f;
	bool m_chk_collision = false;

public:

	void Make_Handle();
	void m_Draw_handle(float y);
	void m_Check_Collision_between_handle_and_Mouse(int x, int y);
	void m_Rotate_Steering_Handle(float angle);
};

