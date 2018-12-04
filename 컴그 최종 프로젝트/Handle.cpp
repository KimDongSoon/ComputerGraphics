#include "Handle.h"


GLubyte* pBytes_Handle;
BITMAPINFO *info_Handle;
GLuint textureID_Handle;

GLubyte * LoadDIBitmap_Handle(const char *filename, BITMAPINFO **info);



void Handle::Make_Handle()
{
	glGenTextures(1, &textureID_Handle);
	glBindTexture(GL_TEXTURE_2D, textureID_Handle);
	pBytes_Handle = LoadDIBitmap_Handle("리소스/핸들_알파.bmp", &info_Handle);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pBytes_Handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

}

void Handle::m_Draw_handle(float y)
{

	/*glGenTextures(1, &textureID_Handle);
	glBindTexture(GL_TEXTURE_2D, textureID_Handle);
	pBytes_Handle = LoadDIBitmap_Handle("리소스/핸들_알파.bmp", &info_Handle);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pBytes_Handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);*/

	//m_Rotate_Steering_Handle(m_angle_for_handle);
	//glBegin(GL_LINE_STRIP);
	//for (int m_angle = 0; m_angle < 360; m_angle++)
	//{
	//	glVertex3i(m_x + (cos(m_angle * (PI / 180))* m_r),
	//		m_y + (sin(m_angle * (PI / 180)) * m_r), -200.0);
	//}
	//glEnd();
	//glBegin(GL_TRIANGLES);
	//glVertex3i(m_x, m_y + 20, 0);
	//glVertex3i(m_x - 30, m_y - 10, 0);
	//glVertex3i(m_x + 30, m_y - 10, 0);
	//glEnd();
	//m_angle_for_handle = 0;//0으로 초기화 시켜서 계속해서 회전하지 않도록 함!

	/*glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, textureID_Handle);
		glTranslatef(0.f, 0.f, 0.f);
		glColor4f(1.f, 1.f, 1.f, 0.3f);

		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(m_x-20, m_y+20);

		glTexCoord2f(0.f, 0.f);
		glVertex2f(m_x-20, m_y-20);

		glTexCoord2f(1.f, 0.f);
		glVertex2f(m_x+20, m_x-20);

		glTexCoord2f(1.f, 1.f);
		glVertex2f(m_x+20, m_x+20);

		glEnd();	
	glPopMatrix();*/

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, textureID_Handle);

	// glRotatef
	glTranslatef(m_x, m_y, 0.f);
	glColor4f(1.f, 1.f, 1.f, 0.3f);
	glRotatef(y + 90.f, 0.f, 0.f, 1.f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex2f(- 40, 40);

	glTexCoord2f(0.f, 0.f);
	glVertex2f(- 40, - 40);

	glTexCoord2f(1.f, 0.f);
	glVertex2f(40, -40);

	glTexCoord2f(1.f, 1.f);
	glVertex2f(40, 40);

	glEnd();
	glPopMatrix();
}

void Handle::m_Check_Collision_between_handle_and_Mouse(int x, int y)
{
	float Distance = sqrt(pow(m_x - (x - 400), 2) + pow(m_y - (y - 300), 2));
	if (Distance <= m_r)
	{
		m_chk_collision = true;
	}
	else if (Distance > m_r)
		m_chk_collision = false;
	cout << x << "\t" << y << endl;
}

void Handle::m_Rotate_Steering_Handle(float angle)
{
	m_angle_for_handle = angle;
	if (m_chk_collision)
	{
		//glPushMatrix();
		glRotatef(angle, 0.f, 0.f, 1.f);
		//glPopMatrix();
	}
}



GLubyte * LoadDIBitmap_Handle(const char *filename, BITMAPINFO **info)
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
