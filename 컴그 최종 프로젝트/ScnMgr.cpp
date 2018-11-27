#include "ScnMgr.h"
#include "Global.h"

#define carSize 50


void createCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h);

ScnMgr::ScnMgr()
{
	m_Player = new Player();
	float x = 0.f, y = 0.f, z = 0.f;		//차의 초기 위치
	m_Player->setCarPosition(x, y, z);

	g_Handle.m_Draw_handle();
}

ScnMgr::~ScnMgr()
{
}

void ScnMgr::RenderScene()
{
	float x , y , z;
	float move = 0.1f;

	

	m_Player->getCarPosition(&x, &y, &z);

	if(g_Accel) {

		if (g_Gear == Drive)
			x += move;

		else if (g_Gear == Reverse)
			x -= move;

		m_Player->setCarPosition(x, y, z);
		//m_Player->getCarPosition(&x, &y, &z);
	}


	if (g_angle)						// 밑에 Translate 밑에
		g_angle += 0.0002f;
	glRotatef(g_angle, 0, 1, 0);

	glPushMatrix();
	glColor4f(1.f, 0.f, 0.f, 1.f);
		glTranslated(x,y,z);
		glScalef(1.f, 0.5f, 1.f);		// 삭제해야 될 수도
		glutWireCube(carSize);

		glTranslated(0, -50, 0);

		glPushMatrix();
			glScalef(1.f, 0.5f, 1.f);
			glutWireCube(carSize + 50);
		glPopMatrix();


		glPushMatrix();
			//glScalef(1.f, 2.f, 1.f);
			//glRotatef(45.f, 1.f, 0.f, 0.f);

			createCylinder(-30, -30, +30, 10, 10);	
			createCylinder(-30, -30, -30, 10, 10);
			createCylinder(+30, -30, +30, 10, 10);
			createCylinder(+30, -30, -30, 10, 10);

			/*GLUquadricObj *pQuad;
			pQuad = gluNewQuadric();

			gluCylinder(pQuad, 10.0, 10.0, 30.0, 20, 8);*/
		glPopMatrix();
	glPopMatrix();
}



