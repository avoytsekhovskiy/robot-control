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
#pragma comment(lib, "ws2_32.lib")
#define M_PI 3.1416
#define _CRT_SECURE_NO_WARNINGS
#define SERVICE_PORT 10007 
#pragma once

// объявления типа матрицы
typedef std::vector<float> matlist;

class RobotTr {
public:
	RobotTr();
	~RobotTr();
	char* receiveMess(SOCKET s);
	// отправка сообщения на сервер
	int sendMess(SOCKET s, int l_power, int r_power, int d_power);
	// регулирование движения робота
	float* regulator(float tar_x, float tar_y);
	bool bTerminate = false;
	// флаг уничтожения робота
	int dead = 0;
	//индекс текущей точки миссии
	int idx = 0;
	// матрица с точками миссии
	matlist targets;
	// координаты робота: x - вверх, y - вправо
	float x = 0, y = 0;
	float prev_x = 0, prev_y = 0;
	// ширина поля
	const int border = 150;
	// радиус колеса 4 cm
	const int wheel_rad = 4;
	// ширина колесной базы 15 cm
	const int wheel_width = 15;
	// запас прочности робота
	float strength = 100;
	// П-коэффициент регулятора
	float kp = 10;
	// И-коэффициент регулятора
	float ki = 0.02;
	int target_one = 0;
	int target_two = 0;
	int target_three = 0;
	//
	float past_dist = 0;
	// абсолютный угол поворота робота
	float abs_ang = 0;
	// расстояние, пройденное за предыдущую итерацию
	float rad_dist = 0;
	// угол, на который повернулся робот за предыдущую итерацию
	float past_ang = 0;

	float station_1 = 0;
	float station_2 = 0;
	float station_3 = 0;
	float station_4 = 0;
	float beakon = 0;
	float ex_robot = 0;
	float ex_beacon = 0;
	float base = 0;

	bool first = true;

	void updatePos()
	{
		prev_x = x;
		prev_y = y;
		float sscale = 400.0 / 44100.0;
		if (station_1 >= 1 && station_4 >= 1) x = (1 / station_1 - 1 / station_4) / sscale;
		if (station_3 >= 1 && station_2 >= 1) x = (1 / station_3 - 1 / station_2) / sscale;
		if (station_1 >= 1 && station_3 >= 1) y = (1 / station_1 - 1 / station_3) / sscale;
		if (station_4 >= 1 && station_2 >= 1) y = (1 / station_4 - 1 / station_2) / sscale;
		float delta_x = x - prev_x;
		float delta_y = y - prev_y;
		abs_ang = atan2(delta_y, delta_x);
		if (abs_ang >= 2 * M_PI) abs_ang -= 2 * M_PI;
		if (abs_ang <= -2 * M_PI) abs_ang += 2 * M_PI;
		std::cout << "Current X: " << x << std::endl;
		std::cout << "Current Y: " << y << std::endl;
		std::cout << "Current absolute angle: " << abs_ang << std::endl;
	}
};