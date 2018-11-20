#include <GL/freeglut.h>
#include <iostream>
#include "Global.h"
#include "Player.h"
#include "ScnMgr.h"
#include "handle.h"

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Timer(int);
GLvoid KeyBoard(unsigned char, int, int);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
void KeyDownInput(unsigned char key, int x, int y);
void KeyUpInput(unsigned char key, int x, int y);

ScnMgr* g_ScnMgr = NULL;

// ��������
int g_Gear = 0;
bool g_Accel = false;

void main(int argc, char *argv[])
{   //�ʱ�ȭ �Լ���	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 50);   // �������� ��ġ���� 
	glutInitWindowSize(800, 600);    // �������� ũ�� ����
	glutCreateWindow("��������");   // ������ ���� (������ �̸�) 

	g_ScnMgr = new ScnMgr();

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����   
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyUpInput);
	//glutKeyboardFunc(KeyDownBoard);
	glutTimerFunc(TIME, Timer, 1);
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

	
	//RenderScene();
}


GLvoid Timer(int value)
{
	glutTimerFunc(TIME, Timer, 1);
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // �������� 'black' �� ����  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // ������ ������ ��ü�� ĥ�ϱ�    

	g_ScnMgr->RenderScene();

	glutPostRedisplay();
	glutSwapBuffers();// ȭ�鿡 ����ϱ�
}
GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		;
	}
}
GLvoid Motion(int x, int y)
{

}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.f, 800/800, 1.0f, 1000.0f);
	glTranslatef(0.f, 0.f, -400.f);
	//glRotatef(50, 0.f, 1.f, 0.f);
	//glOrtho(-400.f, 400.f, -300.f, 300.f, -400.f, 400.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}