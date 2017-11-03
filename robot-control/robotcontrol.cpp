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

float x = 0, y = 0;
bool bTerminate = false;

class Robot
{
private:
	// радиус колеса 4 cm
	int w_rad = 4;
	// ширина колесной базы 15 cm
	int r_width = 15;
	// положение левого энкодера
	float l_enc = 0;
	// положение правого энкодера
	float r_enc = 0;
	// запас прочности робота
	float strength = 100;

public:
	void receiveMess()
	{
		cout << "This method in progress";
	}

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
};

int main()
{
	Robot robot;
	_getch();
    return 0;
}