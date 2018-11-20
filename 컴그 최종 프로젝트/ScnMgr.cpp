#include "ScnMgr.h"
#include "Global.h"

#define carSize 50


void createCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h);//바퀴그리는 함수.

ScnMgr::ScnMgr()//업데이트 하는 함수
{
	m_Player = new Player();
	float x = 0.f, y = 0.f, z = 0.f;		//차의 초기 위치
	m_Player->setCarPosition(x, y, z);
}

ScnMgr::~ScnMgr()
{
}

void ScnMgr::RenderScene()
{
	float x , y , z;
	float move = 2.f;
	m_Player->getCarPosition(&x, &y, &z);//플레이어 위치를 가져오는것.
	GLdouble eyeX = x , eyeY = y + 50, eyeZ = z + 200;
	GLdouble atX = x, atY = y, atZ = z - 100;
	GLdouble upX = 0.f, upY = 1.f, upZ = 0.f;
	

	if(g_Accel) {

		if (g_Gear == Drive)
			x += move;

		else if (g_Gear == Reverse)
			x -= move;

		m_Player->setCarPosition(x, y, z);
		//m_Player->getCarPosition(&x, &y, &z);
	}

	gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ);

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



