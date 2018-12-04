#include "Player.h"

void Player::setCarPosition(float x, float y, float z)
{
	carX = x;
	carY = y;		// �ʿ� x
	carZ = z;
}

void Player::getCarPosition(float * x, float * y, float * z)
{
	*x = carX;
	*y = carY;		// �ʿ� x
	*z = carZ;
}

void Player::setCarDir(float x, float y, float z)
{
	dirX = x;
	dirY = y;		// �ʿ� x
	dirZ = z;
}

void Player::getCarDir(float * x, float * y, float * z)
{
	*x = dirX;
	*y = dirY;		// �ʿ� x
	*z = dirZ;
}

void Player::RotationY(float y)
{
	RotY = y;
	float radians = (y * 3.1415f) / 180.f;

	dirX = (cos(radians) * 1) + sin(radians) * 0;		// x y z �ٲ���� ��!	y�� ��� 0!
	dirY = 0;
	dirZ = (-sin(radians) * 1) + cos(radians) * 0;
}

void Player::Update()
{
	carX = 0.f;
	carY = 0.f;
	carZ = 0.f;
}

void createCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h)		// ����
{
	/* function createCyliner()
	������� �߽� x,y,z��ǥ, ������, ���̸� �޾� ������� �����ϴ� �Լ�(+z�������� ������ �þ)
	centerx : ����� ���� �߽� x��ǥ
	centery : ����� ���� �߽� y��ǥ
	centerz : ����� ���� �߽� z��ǥ
	radius : ������� ������
	h : ������� ����
	*/
	GLfloat x, y, angle;

	glBegin(GL_TRIANGLE_FAN);           //������� ����
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

	glBegin(GL_QUAD_STRIP);            //������� ����
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius * sin(angle);
		y = centery + radius * cos(angle);
		glNormal3f(sin(angle), cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);           //������� �ظ�
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

