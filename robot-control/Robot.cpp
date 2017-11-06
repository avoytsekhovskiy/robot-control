#include "stdafx.h"
#include "Robot.h"
#include <iostream>
#include <Winsock.h>
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

char* Robot::receiveMess(SOCKET s)
{
	char sReceiveBuffer[1024] = { 0 };
	// �������� � ������������ ������ �� �������
	int nReaded = recv(s, sReceiveBuffer, sizeof(sReceiveBuffer) - 1, 0);
	// � ������ ������ (��������, ������������ �������) �������
	if (nReaded <= 0) return 0;
	// �� �������� ����� ����, ������� ����� �������������� 
	// �������� ����������� 0 ��� ASCII ������ 
	sReceiveBuffer[nReaded] = 0;
	// ����������� ������� �������� �����
	for (char* pPtr = sReceiveBuffer; *pPtr != 0; pPtr++)
	{
		if (*pPtr == '\n' || *pPtr == '\r')
		{
			*pPtr = 0;
			break;
		}
	}
	cout << "-------------------------\n";
	cout << "Receive:" << endl;
	cout << sReceiveBuffer << "\n";
	return sReceiveBuffer;
}

int Robot::sendMess(SOCKET s, int l_power, int r_power, int d_power)
{
	if (l_power > 100) l_power = 100;
	if (l_power < -100) l_power = -100;
	if (r_power > 100) r_power = 100;
	if (r_power < -100) r_power = -100;
	char control[1024] = { 0 };
	sprintf_s(control, "0xFF 0xFF L%d R%d D%d 0xEE", l_power, r_power, d_power);
	cout << "-------------------------\n";
	cout << "Send:" << endl;
	cout << control << "\n";
	return send(s, control, strlen(control), 0);
}

float Robot::regulator()
{
	return 0;
}

