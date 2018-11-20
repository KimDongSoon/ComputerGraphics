#include "Handle.h"

void Handle::m_Draw_handle()
{
	m_Rotate_Steering_Handle(m_angle_for_handle);
	glBegin(GL_LINE_STRIP);
	for (int m_angle = 0; m_angle < 360; m_angle++)
	{
		glVertex3i(m_x + (cos(m_angle * (PI / 180))* m_r),
			m_y + (sin(m_angle * (PI / 180)) * m_r), -200.0);
	}
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3i(m_x, m_y + 20, 0);
	glVertex3i(m_x - 30, m_y - 10, 0);
	glVertex3i(m_x + 30, m_y - 10, 0);
	glEnd();
	m_angle_for_handle = 0;//0���� �ʱ�ȭ ���Ѽ� ����ؼ� ȸ������ �ʵ��� ��!
}

void Handle::m_Check_Collision_between_handle_and_Mouse(int x, int y)
{
	float Distance = sqrt(pow(m_x - (x - 400), 2) + pow(m_y - (y - 300), 2));
	if (Distance <= m_r)
	{
		m_chk_collision = true;
	}
	else if (Distance > m_r)
		m_chk_collision = false;
	cout << x << "\t" << y << endl;
}

void Handle::m_Rotate_Steering_Handle(float angle)
{
	m_angle_for_handle = angle;
	if (m_chk_collision)
	{
		//glPushMatrix();
		glRotatef(angle, 0.f, 0.f, 1.f);
		//glPopMatrix();
	}
}
