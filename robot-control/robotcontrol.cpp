// robotcontrol.cpp: определяет точку входа для консольного приложения.
//


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
#include "Robot.h"
#pragma comment(lib, "ws2_32.lib")
#define M_PI 3.1416
#define _CRT_SECURE_NO_WARNINGS
#define SERVICE_PORT 10007
using namespace std;

// ширина поля
const float f_width = 300;
// длина поля 
const float f_lenght = 300;
// 

bool bTerminate = false;

int main()
{
	Robot robot;
	_getch();
    return 0;
}