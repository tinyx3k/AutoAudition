#pragma once
#include <iostream>
#include <deque>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "Tlhelp32.h";
#include "SerialPort.h"

using namespace std;
using namespace cv;

Mat hwnd2mat(HWND hwnd);
int GetGameProcess(LPCWSTR name);
HWND FindWindowFromProcessId(DWORD dwProcessId);
RECT gameRect;
void Screenshot();
