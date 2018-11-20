#pragma once
//extern 전역변수는 해당 cpp에서만 쓸수 있음.
//extern int 
#define Drive 1			// 기어 D
#define Reverse 2		// 기어 R
#define TIME 100		// 타이머 시간 : 100ms

extern int g_Gear;			// 기어

extern bool g_Accel;	// 엑셀이 안눌렸을때

extern GLdouble eyeX, eyeY, eyeZ; //카메라 eye 파라미터
extern GLdouble atX, atY, atZ; // 카메라 at 파라미터
extern GLdouble upX, upY, upZ; // 카메라 up 파라미터