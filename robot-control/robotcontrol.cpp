// robotcontrol.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <iostream>
#include <Winsock.h>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <cmath>
#include <vector>
#include <fstream>
#include "Robot.h"
#pragma comment(lib, "ws2_32.lib")
#define M_PI 3.1416
#define _CRT_SECURE_NO_WARNINGS

#define SERVICE_PORT 10007
using namespace std;

bool bTerminate = false;

int main()
{
	Robot robot;
	SOCKET s;
	sockaddr_in serv_addr;
	WSADATA wsadata;
	char sName[128];
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	// ��������� ����� ������� ������
	gethostname(sName, sizeof(sName));
	printf("\nClient host: %s\n", sName);
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		fprintf(stderr, "Can't create socket\n");
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	// ��������� ������ �� ���� ��������� ������� �����������, � ��������� localhost
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// �������������� ������� ����
	serv_addr.sin_port = htons((u_short)SERVICE_PORT);
	// �����������
	while (connect(s, (sockaddr*)&serv_addr, sizeof(serv_addr)) == INVALID_SOCKET)
	{
		fprintf(stderr, "Can't connect\n");
	}
	send(s, "Begin", strlen("Begin"), 0);
	char sReceiveBuffer[1024] = { 0 };
	robot.receiveMess(s);
	ofstream dots;
	dots.open("dots.txt");
	float* coord;
	float* speed;
	while (!robot.bTerminate)
	{
		char sReceiveBuffer[1024] = { 0 };
		_getch();
		speed = robot.regulator(25, 35);
		robot.sendMess(s, speed[1], speed[0], 0);
		robot.receiveMess(s);
		
		coord = robot.showXY();

		dots << coord[0] << " " << coord[1] << std::endl;
		if (robot.dead == 1)
		{
			break;
		};
	}
	dots.close();
	_getch();
    return 0;
}