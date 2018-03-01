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

// ���������� ���� �������
typedef std::vector<float> matlist;

class Robot
{
public:
	Robot();
	~Robot();
	char* receiveMess(SOCKET s);
	// �������� ��������� �� ������
	int sendMess(SOCKET s, int l_power, int r_power, int d_power);
	// ������������� �������� ������
	float* regulator(float tar_x, float tar_y);

	void track();

	float* showXY();
	bool bTerminate = false;
	// ���� ����������� ������
	int dead = 0;
	//������ ������� ����� ������
	int idx = 0;
	// ������� � ������� ������
	matlist targets;
	// ���������� ������: x - �����, y - ������
	float x = 0, y = 0;
	// ������ ����
	const int border = 150;

private:
	// ������ ������ 4 cm
	const int wheel_rad = 4;
	// ������ �������� ���� 15 cm
	const int wheel_width = 15;
	// ��������� ������ ��������
	float l_enc = 0;
	// ��������� ������� ��������
	float r_enc = 0;
	// ��������� ������ �������� �� ������� ��������
	float past_l_enc = 0;
	// ��������� ������� �������� �� ������� ��������
	float past_r_enc = 0;
	// ����� ��������� ������
	float strength = 100;
	// ���� ���������� ����
	int sens_target = 0;
	// ���� ���������� ���� 1
	int target_one = 0;
	// ���� ���������� ���� 2
	int target_two = 0;
	// �-����������� ����������
	float kp = 70;
	// �-����������� ����������
	float ki = 0.02;
	
	//
	float past_dist = 0;
	// ���������� ���� �������� ������
	float abs_ang = 0;
	// ����������, ���������� �� ���������� ��������
	float rad_dist = 0;
	// ����, �� ������� ���������� ����� �� ���������� ��������
	float past_ang = 0;
		
	
	

	// ���������� ������ � ��������� ������
	void updatePos()
	{
		// ���������� ����������, ���������� ����� � ������ ��������
		float l_dist, r_dist, dist;
		l_dist = ((l_enc - past_l_enc) / 360) * 2 * M_PI * wheel_rad;
		r_dist = ((r_enc - past_r_enc) / 360) * 2 * M_PI * wheel_rad;
		//l_delta = l_dist - past_l_dist;
		//r_delta = r_dist - past_r_dist;
		// ���������� ����������� ����������
		rad_dist = (l_dist + r_dist) / 2;
		// ���������� �������� �� ������� ��������
		past_ang = (r_dist - l_dist) / wheel_width;
	
		dist = rad_dist;
		
		if (past_ang != 0)
		{
			dist = 2 * (rad_dist / past_ang) * sin(past_ang / 2);
		}
		// ���������� ����������� ���� �������� ������
		abs_ang += past_ang;
		if (abs_ang >= 2 * M_PI)
		{
			abs_ang -= 2 * M_PI;
		}
		if (abs_ang <= -2 * M_PI)
		{
			abs_ang += 2 * M_PI;
		}
		// ���������� ������� ��������� ������
		x += dist * cos(abs_ang);
		y += dist * sin(abs_ang);
		std::cout << "Current X: " << x << std::endl;
		std::cout << "Current Y: " << y << std::endl;
		std::cout << "Current absolute angle: " << abs_ang << std::endl;
		past_l_enc = l_enc;
		past_r_enc = r_enc;
	}
};

