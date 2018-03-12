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
// объявления типа матрицы
//typedef std::vector< std::vector< std::vector<int> > > matX;

int main()
{
	Robot robot;
	robot.track();
	SOCKET s;
	sockaddr_in serv_addr;
	WSADATA wsadata;
	char sName[128];
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	// ��������� ����� ������� ������
	gethostname(sName, sizeof(sName));
	printf("\nClient host: %s\n", sName);
	int tcp_or_udp = 1;
	std::cout << "Enter 0 for UDP or 1 for TCP" << std::endl;
	std::cin >> tcp_or_udp;
	if (tcp_or_udp > 0) {
		if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
			fprintf(stderr, "Can't create socket\n");
			exit(1);
		}
	}
	else {
		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
			fprintf(stderr, "Can't create socket\n");
			exit(1);
		}
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	// ��������� ������ �� ���� ��������� ������� �����������, � ��������� localhost
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// �������������� ������� ����
	serv_addr.sin_port = htons((u_short)SERVICE_PORT);
	// �����������
	while (connect(s, (sockaddr*)&serv_addr, sizeof(serv_addr)) == INVALID_SOCKET) {
		fprintf(stderr, "Can't connect\n");
	}
	send(s, "Begin", strlen("Begin"), 0);
	char sReceiveBuffer[1024] = { 0 };
	robot.receiveMess(s);
	ofstream dots;
	dots.open("dots.txt");
	float* coord;
	float* speed;
	int X, Y;
	bool debug = false;
	while (!robot.bTerminate) {
		char sReceiveBuffer[1024] = { 0 };
		//_getch();
		if (debug && robot.target_one == 0) {
			X = 95;
			Y = -50;
		} else if (robot.target_one > 0) {
			X = 0;
			Y = 0;
		} else {
			X = robot.targets[robot.idx + 1];
			Y = robot.targets[robot.idx];
		}
		std::cout << "-------------------------" << std::endl;
		std::cout << "TARGET X: " << X << std::endl;
		std::cout << "TARGET Y: " << Y << std::endl;
		std::cout << "IDX: " << robot.idx / 2 << std::endl;
		if (robot.sens_target > 0 && robot.target_one == 0) {
			std::cout << "I found point!" << std::endl;
			std::cout << "It's true! Stop!!!" << std::endl;
			robot.sendMess(s, 0, 0, 20);
			robot.receiveMess(s);
			std::cout << robot.target_one << std::endl;
			if (robot.target_one > 0) {
				std::cout << "Target 1 was completed" << std::endl;
			}
			_getch();
		} else if (robot.target_two > 0) {
			std::cout << "cake is a lie" << std::endl;
			_getch();
			return 0;
		} else {
			speed = robot.regulator(X, Y);
			robot.sendMess(s, speed[0], speed[1], 0);
			robot.receiveMess(s);
			coord = robot.showXY();
			dots << coord[0] << " " << coord[1] << std::endl;
			if (robot.dead == 1) break;
			float pif = sqrt(pow(robot.targets[robot.idx + 1] - robot.x, 2) + pow(robot.targets[robot.idx] - robot.y, 2));
			std::cout << "PIF: " << pif << std::endl;
			if (robot.idx < robot.targets.size()) {
				if (sqrt(pow(robot.targets[robot.idx + 1] - robot.x, 2) + pow(robot.targets[robot.idx] - robot.y, 2)) < 2) robot.idx += 2;
			} else {
				std::cout << "That's all" << std::endl;
				break;
			}
		}
	}
	dots.close();
	_getch();
	return 0;
}