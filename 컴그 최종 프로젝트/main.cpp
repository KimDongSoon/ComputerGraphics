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

// 전역변수
int g_Gear = 0;
bool g_Accel = false;

void main(int argc, char *argv[])
{   //초기화 함수들	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 50);   // 윈도우의 위치지정 
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정
	glutCreateWindow("주차게임");   // 윈도우 생성 (윈도우 이름) 

	g_ScnMgr = new ScnMgr();

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정   
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyUpInput);
	//glutKeyboardFunc(KeyDownBoard);
	glutTimerFunc(TIME, Timer, 1);
	glutReshapeFunc(Reshape);   // 다시 그리기 함수의 지정 
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
	case 'w':				// 일단 엑셀
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

// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // 바탕색을 'black' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 설정된 색으로 전체를 칠하기    

	g_ScnMgr->RenderScene();

	glutPostRedisplay();
	glutSwapBuffers();// 화면에 출력하기
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