#pragma once

#include <gl/freeglut.h>
#include <math.h>

#define GL_PI 3.1415f

class Player {
	float carX = 0.f;			// player 차의 정가운데
	float carY = 0.f;
	float carZ = 0.f;

	float left_FrontWheel = 0.f;
	float right_FrontWheel = 0.f;


public:
	void setCarPosition(float x, float y, float z);
	void getCarPosition(float* x, float* y, float* z);

	void setAcc(float x);

	void createCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h);


	void Update();
};