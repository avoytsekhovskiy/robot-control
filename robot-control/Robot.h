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

// объявления типа матрицы
typedef std::vector<float> matlist;

class Robot
{
public:
	Robot();
	~Robot();
	char* receiveMess(SOCKET s);
	// отправка сообщения на сервер
	int sendMess(SOCKET s, int l_power, int r_power, int d_power);
	// регулирование движения робота
	float* regulator(float tar_x, float tar_y);

	void track();

	float* showXY();
	bool bTerminate = false;
	// флаг уничтожения робота
	int dead = 0;
	//индекс текущей точки миссии
	int idx = 0;
	// матрица с точками миссии
	matlist targets;
	// координаты робота: x - вверх, y - вправо
	float x = 0, y = 0;
	// ширина поля
	const int border = 150;

private:
	// радиус колеса 4 cm
	const int wheel_rad = 4;
	// ширина колесной базы 15 cm
	const int wheel_width = 15;
	// положение левого энкодера
	float l_enc = 0;
	// положение правого энкодера
	float r_enc = 0;
	// положение левого энкодера за прошлые итерации
	float past_l_enc = 0;
	// положение правого энкодера за прошлые итерации
	float past_r_enc = 0;
	// запас прочности робота
	float strength = 100;
	// флаг нахождения цели
	int sens_target = 0;
	// флаг выполнения цели 1
	int target_one = 0;
	// флаг выполнения цели 2
	int target_two = 0;
	// П-коэффициент регулятора
	float kp = 70;
	// И-коэффициент регулятора
	float ki = 0.02;
	
	//
	float past_dist = 0;
	// абсолютный угол поворота робота
	float abs_ang = 0;
	// расстояние, пройденное за предыдущую итерацию
	float rad_dist = 0;
	// угол, на который повернулся робот за предыдущую итерацию
	float past_ang = 0;
		
	
	

	// обновление данных о положении робота
	void updatePos()
	{
		// вычисление расстояний, пройденных левым и правым колесами
		float l_dist, r_dist, dist;
		l_dist = ((l_enc - past_l_enc) / 360) * 2 * M_PI * wheel_rad;
		r_dist = ((r_enc - past_r_enc) / 360) * 2 * M_PI * wheel_rad;
		//l_delta = l_dist - past_l_dist;
		//r_delta = r_dist - past_r_dist;
		// вычисление пройденного расстояния
		rad_dist = (l_dist + r_dist) / 2;
		// вычисления поворота на текущей итерации
		past_ang = (r_dist - l_dist) / wheel_width;
	
		dist = rad_dist;
		
		if (past_ang != 0)
		{
			dist = 2 * (rad_dist / past_ang) * sin(past_ang / 2);
		}
		// вычисление абсолютного угла поворота робота
		abs_ang += past_ang;
		if (abs_ang >= 2 * M_PI)
		{
			abs_ang -= 2 * M_PI;
		}
		if (abs_ang <= -2 * M_PI)
		{
			abs_ang += 2 * M_PI;
		}
		// вычисление текущих координат робота
		x += dist * cos(abs_ang);
		y += dist * sin(abs_ang);
		std::cout << "Current X: " << x << std::endl;
		std::cout << "Current Y: " << y << std::endl;
		std::cout << "Current absolute angle: " << abs_ang << std::endl;
		past_l_enc = l_enc;
		past_r_enc = r_enc;
	}
};

