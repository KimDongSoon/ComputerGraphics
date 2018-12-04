#include <stdio.h>
#include <Windows.h>
#include <gl/GLU.h>
#include "ScnMgr.h"
#include "Global.h"

#define carSize 50

GLubyte* pBytes;
BITMAPINFO *info;
GLuint textureID;

//unsigned int textureID;

Handle* handle = new Handle;

void createCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h);
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

ScnMgr::ScnMgr()
{
	m_Player = new Player();
	float x = 0.f, y = 0.f, z = 0.f;		//차의 초기 위치
	m_Player->setCarPosition(x, y, z);

	handle->Make_Handle();

	//g_Handle.m_Draw_handle();

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	pBytes = LoadDIBitmap("리소스/주차장 샘플2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);
}

ScnMgr::~ScnMgr()
{

}

void ScnMgr::RenderScene()
{
	// 바닥
	//glPushMatrix();


	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-400, 0, 800);

	glTexCoord2f(0.f, 0.f);
	glVertex3f(-400, 0, -800);

	glTexCoord2f(1.f, 0.f);
	glVertex3f(400, 0, -800);

	glTexCoord2f(1.f, 1.f);
	glVertex3f(400, 0, 800);
	glEnd();
	//glPopMatrix();

	//glGenTextures(1, &textureID);
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//pBytes = LoadDIBitmap("마세라티 bmp.bmp", &info);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, z, GL_BGR, GL_UNSIGNED_BYTE, pBytes);

	float x , y , z;
	float dX, dY, dZ;
	float move = 0.1f;
	static float angle = 0.1f;
	
//	float tempX = 0.f, tempY = 0.f , tempZ = 0.f;

	m_Player->getCarPosition(&x, &y, &z);
	m_Player->getCarDir(&dX, &dY, &dZ);

	if(g_Accel) {

		if (g_Gear == Drive) {
			//m_Player->getCarDir(&x, &y, &z);
			x -= (move * dX);
			z -= (move * dZ);
		}
		else if (g_Gear == Reverse) {
			x += (move * dX);
			z += (move * dZ);
			//m_Player->getCarDir(&x, &y, &z);
		}

		m_Player->setCarPosition(x, y, z);
		//m_Player->getCarPosition(&x, &y, &z);
	}

	
	glPushMatrix();



	//GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	//glEnable(GL_LIGHTING);
	//glMateriali(GL_FRONT, GL_SHININESS, 64);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specref);

		glColor4f(1.f, 1.f, 0.f, 1.f);
		glTranslated(x,y,z);
		glScalef(2.f, 2.0f, 1.f);		// 삭제해야 될 수도

		if (g_angle) {						// 밑에 Translate 밑에
			//glTranslated(x, y, z);
			//tempX = x;
			//tempY = y;
			//tempZ = z;

			angle += 0.5f;
			cout << "Angle = " << angle << endl;
		}

		float playerAngle = m_Player->GetRotY();
		glRotatef(playerAngle, 0, 1, 0);
		//m_Player->RotationY(angle);

		// 자동차 윗면
		//glutWireCube(carSize);	
		////glBegin(GL_QUADS);
		////glVertex3d()
		////glEnd();

		//glTranslated(0, -50, 0);

		//glPushMatrix();
		//	glColor4f(1.f, 0.f, 1.f, 1.f);
		//	glScalef(1.f, 0.5f, 1.f);
		//	glutWireCube(carSize + 50);
		//glPopMatrix();


		//glPushMatrix();
		//	//glScalef(1.f, 2.f, 1.f);
		//	//glRotatef(45.f, 1.f, 0.f, 0.f);

		//	createCylinder(-30, -30, +30, 10, 10);	// 뒤 오른쪽
		//	createCylinder(-30, -30, -30, 10, 10);	// 뒤 왼쪽

		//	// 회전에 따른 앞바퀴 이동
		//	glPushMatrix();

		//		if (g_angle) {
		//			glRotated(angle, 0, 1, 0);
		//			createCylinder(+30, -30, +30, 10, 10);	// 앞 오른쪽
		//			createCylinder(+30, -30, -30, 10, 10);	// 앞 왼쪽
		//		}
		//		else if (!g_angle) {
		//			createCylinder(+30, -30, +30, 10, 10);	// 앞 오른쪽
		//			createCylinder(+30, -30, -30, 10, 10);	// 앞 왼쪽
		//		}
		//	glPopMatrix();
		//	/*GLUquadricObj *pQuad;
		//	pQuad = gluNewQuadric();

		//	gluCylinder(pQuad, 10.0, 10.0, 30.0, 20, 8);*/
		//glPopMatrix();


		//////////////////////////////////////////////////////////////////////////////////////
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-40.0f, 0.0f, 15.0f);
		glVertex3f(40.0f, 0.0f, 15.0f);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(40.0f, -15.0f, 15.0f);
		glVertex3f(-40.0f, -15.0f, 15.0f);
		glEnd();


		glBegin(GL_POLYGON);					// 뒤 밑
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(40.0f, 0.0f, -15.0f);
		glVertex3f(40.0f, 0.0f, 15.0f);
		glVertex3f(40.0f, -15.0f, 15.0f);
		glVertex3f(40.0f, -15.0f, -15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);				// 앞 밑
		glVertex3f(-40.0f, 0.0f, -15.0f);
		glVertex3f(-40.0f, 0.0f, 15.0f);
		glVertex3f(-40.0f, -15.0f, 15.0f);
		glVertex3f(-40.0f, -15.0f, -15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-40.0f, 0.0f, -15.0f);
		glVertex3f(40.0f, 0.0f, -15.0f);
		glColor3f(1, 1.0, 1.0);
		glVertex3f(40.0f, -15.0f, -15.0f);
		glVertex3f(-40.0f, -15.0f, -15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-40.0f, 0.0f, 15.0f);
		glVertex3f(-40.0f, 0.0f, -15.0f);
		glVertex3f(40.0f, 0.0f, -15.0f);
		glVertex3f(40.0f, 0.0f, 15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-40.0f, -15.0f, 15.0f);
		glVertex3f(-40.0f, -15.0f, -15.0f);
		glVertex3f(40.0f, -15.0f, -15.0f);
		glVertex3f(40.0f, -15.0f, 15.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-20.0f, 0.0f, 15.0f);
		glVertex3f(-10.0f, 10.0f, 15.0f);
		glVertex3f(20.0f, 10.0f, 15.0f);
		glVertex3f(25.0f, 0.0f, 15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-20.0f, 0.0f, -15.0f);
		glVertex3f(-10.0f, 10.0f, -15.0f);
		glVertex3f(20.0f, 10.0f, -15.0f);
		glVertex3f(25.0f, 0.0f, -15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-10.0f, 10.0f, 15.0f);
		glVertex3f(-10.0f, 10.0f, -15.0f);
		glVertex3f(20.0f, 10.0f, -15.0f);
		glVertex3f(20.0f, 10.0f, 15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-10.0f, 10.0f, 15.0f);
		glVertex3f(-20.0f, 0.0f, 15.0f);
		glVertex3f(-20.0f, 0.0f, -15.0f);
		glVertex3f(-10.0f, 10.0f, -15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(20.0f, 10.0f, 15.0f);
		glVertex3f(20.0f, 10.0f, -15.0f);
		glVertex3f(25.0f, 0.0f, -15.0f);
		glVertex3f(25.0f, 0.0f, 15.0f);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-30.0f, -15.0f, 15.0f);
		glVertex3f(-30.0f, -15.0f, -15.0f);
		glVertex3f(30.0f, -15.0f, -15.0f);
		glVertex3f(30.0f, -15.0f, 15.0f);
		glEnd();


		glBegin(GL_3D);
		glColor3f(1, 1, 1);
		glTranslated(-20.0f, -15.0f, 15.0f);
		glutSolidTorus(2, 5, 5, 100);



		glTranslated(0.0f, 0.0f, -30.0f);
		glutSolidTorus(2, 5, 5, 100);
		glTranslated(45.0f, 0.0f, 0.0f);
		glutSolidTorus(2, 5, 5, 100);
		glTranslated(0.0f, 0.0f, 30.0f);
		glutSolidTorus(2, 5, 5, 100);
		glEnd();




		glPushMatrix();
		glColor3f(3.0, 4.0, 5.0);
		//glRotatef(45,0,0,1);
		glScalef(10, 0.3, 3);

		//glutWireCube(-20);


		glPopMatrix();
		//////////////////////////////////////////////////////////////////////////////////////
	glPopMatrix();
	
	
	handle->m_Draw_handle(playerAngle);

}

void ScnMgr::Motion(int x, int y) {

	scnMgr_mouseX = x, scnMgr_mouseY = 300 - y;

	float playerRotY = m_Player->GetRotY();

	m_Player->RotationY(playerRotY + (scnMgr_mouseX - prevX));

	prevX = x;


	cout << scnMgr_mouseX << ", " << scnMgr_mouseY << endl;
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 핚다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 핛당핚다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장핚다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;

}