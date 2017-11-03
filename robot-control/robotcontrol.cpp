// robotcontrol.cpp: определяет точку входа для консольного приложения.
//

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h"
#include <iostream>
#include <Winsock2.h>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <cmath>
#include <vector>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
#define SERVICE_PORT 10007
using namespace std;

// ширина поля
const float f_width = 300;
// длина поля 
const float f_lenght = 300;
// 

bool bTerminate = false;

class Robot
{
private:
	// радиус колеса 4 cm
	int wheel_rad = 4;
	// ширина колесной базы 15 cm
	int wheel_width = 15;
	// положение левого энкодера
	float l_enc = 0;
	// положение правого энкодера
	float r_enc = 0;
	// запас прочности робота
	float strength = 100;
	// П-коэффициент регулятора
	float kp = 5;
	// И-коэффициент регулятора
	float ki = 0.02;
	// координаты робота: x - вверх, y - вправо
	float x = 0, y = 0;
	// абсолютный угол поворота робота
	float abs_ang = 0;
	// расстояние, пройденное за предыдущую итерацию
	float past_dist = 0;
	// угол, на который повернулся робот за предыдущую итерацию
	float past_ang = 0;

	// обновление данных о положении робота
	void updatePos(float l_enc, float r_enc)
	{
		float l_dist, r_dist;
		l_dist = (l_enc * 360) * 2 * M_PI * wheel_rad;
		r_dist = (r_enc * 360) * 2 * M_PI * wheel_rad;

		past_dist = (l_dist + r_dist) / 2;
		past_ang = (l_dist - r_dist) / wheel_width;
		abs_ang += past_ang;
		x += past_dist * cos(abs_ang);
		y += past_dist * sin(abs_ang);
	}
	
public:
	// прием сообщения с сервера
	void receiveMess()
	{
		cout << "This method in progress";
	}

	// отправка сообщения на сервер
	int sendMess(SOCKET s, int l_power, int r_power, int d_power, sockaddr_in serv_addr, int addrlen)
	{
		if (l_power > 100) l_power = 100;
		if (l_power < -100) l_power = -100;
		if (r_power > 100) r_power = 100;
		if (r_power < -100) r_power = -100;
		char control[1024] = { 0 };
		sprintf(control, "0xFF 0xFF L%d R%d D%d 0xEE", l_power, r_power, d_power);
		cout << control << "\n";
		return sendto(s, control, strlen(control), 0, (sockaddr*)&serv_addr, addrlen);
	}

	// регулирование движения робота
	float regulator()
	{
		return 0;
	}
};

int main()
{
	Robot robot;
	_getch();
    return 0;
}