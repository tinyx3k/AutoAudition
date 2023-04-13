#pragma once
#include <iostream>
#include <deque>
#include <windows.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/gpu/gpu.hpp>   
#include "Tlhelp32.h";
#include "SerialPort.h"
#include <ctime>
#include <thread>
#include <fstream>
#include <sstream>
#include <iomanip>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

using namespace std;
using namespace cv;

void sendChat(std::string str, bool sendEnter = true);

Mat hwnd2mat(HWND hwnd, int width, int height, int fromX, int fromY);
int GetGameProcess(LPCWSTR name);
HWND FindWindowFromProcessId(DWORD dwProcessId);
RECT gameRect;
void AutoKey();
