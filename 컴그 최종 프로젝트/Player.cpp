#include "Player.h"

void Player::setCarPosition(float x, float y, float z)
{
	carX = x;
	carY = y;		// 필요 x
	carZ = z;
}

void Player::getCarPosition(float * x, float * y, float * z)
{
	*x = carX;
	*y = carY;		// 필요 x
	*z = carZ;
}

void Player::setCarDir(float x, float y, float z)
{
	dirX = x;
	dirY = y;		// 필요 x
	dirZ = z;
}

void Player::getCarDir(float * x, float * y, float * z)
{
	*x = dirX;
	*y = dirY;		// 필요 x
	*z = dirZ;
}

void Player::RotationY(float y)
{
	RotY = y;
	float radians = (y * 3.1415f) / 180.f;

	dirX = (cos(radians) * 1) + sin(radians) * 0;		// x y z 바꿔줘야 댐!	y는 계속 0!
	dirY = 0;
	dirZ = (-sin(radians) * 1) + cos(radians) * 0;
}

void Player::Update()
{
	carX = 0.f;
	carY = 0.f;
	carZ = 0.f;
}

void createCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h)		// 바퀴
{
	/* function createCyliner()
	원기둥의 중심 x,y,z좌표, 반지름, 높이를 받아 원기둥을 생성하는 함수(+z방향으로 원에서 늘어남)
	centerx : 원기둥 원의 중심 x좌표
	centery : 원기둥 원의 중심 y좌표
	centerz : 원기둥 원의 중심 z좌표
	radius : 원기둥의 반지름
	h : 원기둥의 높이
	*/
	GLfloat x, y, angle;

	glBegin(GL_TRIANGLE_FAN);           //원기둥의 윗면
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor3f(1, 0, 0);
	glVertex3f(centerx, centery, centerz);

	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius * sin(angle);
		y = centery + radius * cos(angle);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(x, y, centerz);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);            //원기둥의 옆면
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius * sin(angle);
		y = centery + radius * cos(angle);
		glNormal3f(sin(angle), cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);           //원기둥의 밑면
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(centerx, centery, centerz + h);
	for (angle = (2.0f*GL_PI); angle > 0.0f; angle -= (GL_PI / 8.0f))
	{
		x = centerx + radius * sin(angle);
		y = centery + radius * cos(angle);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();
}

