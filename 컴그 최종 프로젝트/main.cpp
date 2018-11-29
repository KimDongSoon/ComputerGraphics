#include <GL/freeglut.h>
#include <iostream>
#include "Global.h"
#include "Player.h"
#include "ScnMgr.h"
#include "Handle.h"

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Timer(int);
GLvoid KeyBoard(unsigned char, int, int);
//void KeyDownInput(unsigned char key, int x, int y);
void KeyUpInput(unsigned char key, int x, int y);
void Motion(int x, int y);
void Mouse(int button, int state, int x, int y);


ScnMgr* g_ScnMgr = NULL;
Handle g_Handle;

// ��������
int g_Gear = 0;
bool g_Accel = false;
bool g_angle = false;

bool chk_left_button = false;
int Handle_x = 0, Handle_y = 0;

void main(int argc, char *argv[])
{   //�ʱ�ȭ �Լ���	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 50);	 // �������� ��ġ���� 
	glutInitWindowSize(800, 600);		 // �������� ũ�� ����
	glEnable(GL_DEPTH_TEST);			 // ���� on
	glutCreateWindow("��������");		 // ������ ���� (������ �̸�) 

	g_ScnMgr = new ScnMgr();

	glutDisplayFunc(drawScene);    // ��� �Լ��� ����   
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyUpInput);
	//glutKeyboardFunc(KeyDownBoard);
	//glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutTimerFunc(100, Timer, 1);
	glutReshapeFunc(Reshape);   // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		g_Gear = Drive;
		break;
	case 'r':
		g_Gear = Reverse;
		break;
	case 'w':				// �ϴ� ����
		g_Accel = true;
		break;
	case 'z':
		g_angle = true;
		break;

	}
}

//void KeyDownInput(unsigned char key, int x, int y)
//{
//	//g_ScnMgr->KeyInput(key, x, y);
//
//	if (key == 'w') {
//		g_Accel = true;
//	}
//
//	
//	//RenderScene();
//}
//

void KeyUpInput(unsigned char key, int x, int y)
{
	//g_ScnMgr->KeyInput(key, x, y);

	if (key == 'w') {
		g_Accel = false;
	}

	if (key == 'z') {
		g_angle = false;
	}


	//RenderScene();
}


GLvoid Timer(int v)
{
	glutTimerFunc(100, Timer, 1);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		chk_left_button = true;
		Handle_x = x, Handle_y = y;
		g_Handle.m_Check_Collision_between_handle_and_Mouse(x, y);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		chk_left_button = false;
	}
}

void Motion(int x, int y)
{
	float angle_of_rotation = 0;
	int cur_x = x;

	if (chk_left_button)
	{
		if (Handle_x > x)
		{
			angle_of_rotation = -(Handle_x - x) / 4;
			g_Handle.m_Rotate_Steering_Handle(angle_of_rotation);
			if (cur_x <= x)
			{
				Handle_x = cur_x;
			}
		}
		else
		{
			angle_of_rotation = -(Handle_x - x) / 4;
			g_Handle.m_Rotate_Steering_Handle(angle_of_rotation);
			if (cur_x >= x)
			{
				Handle_x = cur_x;
			}
		}
		cout << "x : " << x << "\t cur_x :" << cur_x << "\t Handle_x : " << Handle_x << endl;
	}
}
// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);   // �������� 'black' �� ����  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // ������ ������ ��ü�� ĥ�ϱ�    

	g_ScnMgr->RenderScene();

	glutPostRedisplay();
	glutSwapBuffers();// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	gluPerspective(60, 1, 1, 1000);
	glTranslatef(0.f, 0.f, -400.f);
	glRotatef(30.f, 1.f, 0.f, 0.f);
	//glOrtho(-400.f, 400.f, -300.f, 300.f, -400.f, 400.f);

	glMatrixMode(GL_PROJECTION);

	glMatrixMode(GL_MODELVIEW);
}