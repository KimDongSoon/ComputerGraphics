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

// 전역변수
int g_Gear = 0;
bool g_Accel = false;
bool g_angle = false;

bool chk_left_button = false;
int Handle_x = 0, Handle_y = 0;

void main(int argc, char *argv[])
{   //초기화 함수들	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 50);	 // 윈도우의 위치지정 
	glutInitWindowSize(800, 600);		 // 윈도우의 크기 지정
	glEnable(GL_DEPTH_TEST);			 // 조명 on
	glutCreateWindow("주차게임");		 // 윈도우 생성 (윈도우 이름) 

	g_ScnMgr = new ScnMgr();

	glutDisplayFunc(drawScene);    // 출력 함수의 지정   
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyUpInput);
	//glutKeyboardFunc(KeyDownBoard);
	//glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutTimerFunc(100, Timer, 1);
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
// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);   // 바탕색을 'black' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 설정된 색으로 전체를 칠하기    

	g_ScnMgr->RenderScene();

	glutPostRedisplay();
	glutSwapBuffers();// 화면에 출력하기
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