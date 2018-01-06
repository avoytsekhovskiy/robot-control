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
	// отправка сообщения на сервер
	int sendMess(SOCKET s, int l_power, int r_power, int d_power);
	// регулирование движения робота
	float regulator();

	float* showXY();
	bool bTerminate = false;
	// флаг уничтожения робота
	int dead = 0;

private:
	// радиус колеса 4 cm
	const int wheel_rad = 4;
	// ширина колесной базы 15 cm
	const int wheel_width = 15;
	// положение левого энкодера
	float l_enc = 0;
	// положение правого энкодера
	float r_enc = 0;
	// запас прочности робота
	float strength = 100;
	// флаг нахождения цели
	int sens_target = 0;
	// флаг выполнения цели 1
	int target_one = 0;
	// флаг выполнения цели 2
	int target_two = 0;
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
	// ширина поля
	const float f_width = 300;
	// длина поля 
	const float f_lenght = 300;
	

	// обновление данных о положении робота
	void updatePos(float l_enc, float r_enc)
	{
		// вычисление расстояний, пройденных левым и правым колесами
		float l_dist, r_dist;
		l_dist = (l_enc / 360) * 2 * M_PI * wheel_rad;
		r_dist = (r_enc / 360) * 2 * M_PI * wheel_rad;
		// вычисление пройденного расстояния
		past_dist = (l_dist + r_dist) / 2;
		// вычисления поворота на текущей итерации
		past_ang = (l_dist - r_dist) / wheel_width;
		// вычисление абсолютного угла поворота робота
		abs_ang += past_ang;
		// вычисление текущих координат робота
		x += past_dist * cos(abs_ang);
		y += past_dist * sin(abs_ang);
	}
};

