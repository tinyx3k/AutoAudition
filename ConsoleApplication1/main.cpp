// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "main.h"
#include <thread>

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

// change the name of the port with the port name of your computer
// must remember that the backslashes are essential so do not remove them
string port = "\\\\.\\COM6";
SerialPort arduino(port);

DWORD gameId;
HWND gameWindow;
Mat len = imread("btn/len.png");
Mat xuong = imread("btn/xuong.png");
Mat trai = imread("btn/trai.png");
Mat phai = imread("btn/phai.png");
Mat dl = imread("btn/dl.png");
Mat dx = imread("btn/dx.png");
Mat dt = imread("btn/dt.png");
Mat dp = imread("btn/dp.png");
Mat img;

std::map<int, string> buttons;
string queueButtons = "";

Mat FindButton(Mat ref, Mat tpl, string btn) {
    Mat gref, gtpl;
    cvtColor(ref, gref, COLOR_RGB2BGRA);
    cvtColor(tpl, gtpl, COLOR_RGB2BGRA);

    Mat res(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
    matchTemplate(gref, gtpl, res, TM_CCOEFF_NORMED);
    threshold(res, res, 0.9, 1., THRESH_TOZERO);

    while (true)
    {
        double minval, maxval, threshold = 0.9;
        Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
            if (btn == "l") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(255, 255, 0), 2
                );
            }
            else if (btn == "r") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(255, 255, 255), 2
                );
            }
            else if (btn == "u") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(0, 255, 255), 2
                );
            }
            else if (btn == "d") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(0, 0, 0), 2
                );
            }
            
            
            buttons[maxloc.x] = btn;
            floodFill(res, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
        }
        else
            break;
    }
    return ref;
}

void Screenshot() {
    namedWindow("OpenCV", WINDOW_NORMAL);
    while (true) {
        buttons.clear();

        img = hwnd2mat(gameWindow);
        img = FindButton(img, len, "u");
        img = FindButton(img, xuong, "d");
        img = FindButton(img, trai, "l");
        img = FindButton(img, phai, "r");
        img = FindButton(img, dl, "d");
        img = FindButton(img, dx, "u");
        img = FindButton(img, dt, "r");
        img = FindButton(img, dp, "l");

        queueButtons = "";

        for (std::map<int, string>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
            queueButtons += it->second + ";";
        }
        char* charArray = new char[queueButtons.size() + 1];
        // copy(queueButtons.begin(), queueButtons.end(), charArray);
        for (int x = 0; x < queueButtons.size(); x++) {
            charArray[x] = queueButtons[x];
        }
        charArray[queueButtons.size()] = '\n';
        arduino.writeSerialPort(charArray, queueButtons.size() + 1);

        while (true) {
            memset(output, 0, MAX_DATA_LENGTH);
            arduino.readSerialPort(output, MAX_DATA_LENGTH);
            string str(output);
            if (str.find(queueButtons) != std::string::npos) {
                queueButtons.clear();
                buttons.clear();
                break;
            }
            Sleep(1);
        }
        // Continue loop img
        imshow("OpenCV", img);   
        waitKey(1);
    }
}


int WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd)
{
    if (arduino.isConnected()) {
        cout << "Connection made" << endl << endl;
    }
    else {
        cout << "Error in port name" << endl << endl;
        cin.get();
        return 0;
    }

    //Mat img = imread("lena.jpg");
    gameId = GetGameProcess(L"Audition.exe");
    gameWindow = FindWindowFromProcessId(gameId);
    img = hwnd2mat(gameWindow);

    std::thread ScreenshotThread(Screenshot);

    


    while (arduino.isConnected()) {
        if (GetAsyncKeyState(VK_F12)) {
            exit(0);
            ExitProcess(0);
        }
        Sleep(100);
    }
    
    return 0;
}


Mat hwnd2mat(HWND hwnd)
{
    HDC hwindowDC, hwindowCompatibleDC;

    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER  bi;

    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom / 10;
    srcwidth = windowsize.right * 0.6;
    height = windowsize.bottom / 10;  //change this to whatever size you want to resize to
    width = windowsize.right * 0.6;

    src.create(height, width, CV_8UC4);

    // create a bitmap
    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, windowsize.right * 0.2, windowsize.bottom * 0.65, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

int GetGameProcess(LPCWSTR name) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    int maxThreadCount = 0;
    int foundGameProcess = 0;
    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (_wcsicmp(name, entry.szExeFile) == 0)
            {
                if (maxThreadCount < entry.cntThreads) {
                    maxThreadCount = entry.cntThreads;
                    foundGameProcess = entry.th32ProcessID;
                }
            }
        }
    }

    CloseHandle(snapshot);
    return foundGameProcess;
}


struct EnumData {
    DWORD dwProcessId;
    HWND hWnd;
};
BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam) {
    // Retrieve storage location for communication data
    EnumData& ed = *(EnumData*)lParam;
    DWORD dwProcessId = 0x0;
    // Query process ID for hWnd
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    // Apply filter - if you want to implement additional restrictions,
    // this is the place to do so.
    GetWindowRect(hWnd, &gameRect);
    if (ed.dwProcessId == dwProcessId && gameRect.right - gameRect.left > 770) {
        // Found a window matching the process ID
        ed.hWnd = hWnd;
        // Report success
        SetLastError(ERROR_SUCCESS);
        // Stop enumeration
        return FALSE;
    }
    // Continue enumeration
    return TRUE;
}
HWND FindWindowFromProcessId(DWORD dwProcessId) {
    EnumData ed = { dwProcessId };
    if (!EnumWindows(EnumProc, (LPARAM)&ed) &&
        (GetLastError() == ERROR_SUCCESS)) {
        return ed.hWnd;
    }
    return NULL;
}