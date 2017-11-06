#include "stdafx.h"
#include "Robot.h"
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
#define M_PI 3.1416
#define _CRT_SECURE_NO_WARNINGS
#define SERVICE_PORT 10007
using namespace std;
#pragma once


Robot::Robot()
{
	cout << "Robot was created" << endl;
}


Robot::~Robot()
{
	cout << "Robot was destroyed" << endl;
	_getch();
}

int Robot::receiveMess()
{
	return 0;
}

int Robot::sendMess(SOCKET s, int l_power, int r_power, int d_power, sockaddr_in serv_addr, int addrlen)
{
	if (l_power > 100) l_power = 100;
	if (l_power < -100) l_power = -100;
	if (r_power > 100) r_power = 100;
	if (r_power < -100) r_power = -100;
	char control[1024] = { 0 };
	sprintf_s(control, "0xFF 0xFF L%d R%d D%d 0xEE", l_power, r_power, d_power);
	cout << control << "\n";
	return sendto(s, control, strlen(control), 0, (sockaddr*)&serv_addr, addrlen);
}

float Robot::regulator()
{
	return 0;
}

