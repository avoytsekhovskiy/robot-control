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

class Robot
{
public:
	Robot();
	~Robot();
	char* receiveMess(SOCKET s);
	// �������� ��������� �� ������
	int sendMess(SOCKET s, int l_power, int r_power, int d_power);
	// ������������� �������� ������
	float regulator();

private:
	// ������ ������ 4 cm
	int wheel_rad = 4;
	// ������ �������� ���� 15 cm
	int wheel_width = 15;
	// ��������� ������ ��������
	float l_enc = 0;
	// ��������� ������� ��������
	float r_enc = 0;
	// ����� ��������� ������
	float strength = 100;
	// �-����������� ����������
	float kp = 5;
	// �-����������� ����������
	float ki = 0.02;
	// ���������� ������: x - �����, y - ������
	float x = 0, y = 0;
	// ���������� ���� �������� ������
	float abs_ang = 0;
	// ����������, ���������� �� ���������� ��������
	float past_dist = 0;
	// ����, �� ������� ���������� ����� �� ���������� ��������
	float past_ang = 0;
	//
	

	// ���������� ������ � ��������� ������
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
	bool bTerminate = false;

};

