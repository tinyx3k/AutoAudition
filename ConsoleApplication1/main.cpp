// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "main.h"

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];
int perfectPosition = 56;

// change the name of the port with the port name of your computer
// must remember that the backslashes are essential so do not remove them
SerialPort arduino;

DWORD gameId;
HWND gameWindow;
Mat one = imread("btn/1.png", -1);
Mat onered = imread("btn/1d.png", -1);
Mat two = imread("btn/2.png", -1);
Mat twored = imread("btn/2d.png", -1);
Mat three = imread("btn/3.png", -1);
Mat threered = imread("btn/3d.png", -1);
Mat four = imread("btn/4.png", -1);
Mat fourred = imread("btn/4d.png", -1);
Mat six = imread("btn/6.png", -1);
Mat sixred = imread("btn/6d.png", -1);
Mat seven = imread("btn/7.png", -1);
Mat sevenred = imread("btn/7d.png", -1);
Mat eight = imread("btn/8.png", -1);
Mat eightred = imread("btn/8d.png", -1);
Mat nine = imread("btn/9.png", -1);
Mat ninered = imread("btn/9d.png", -1);
Mat space = imread("btn/space.png", -1);
Mat screenshot, screenshot2;

int lastSpacePosition, lastSpaceTime;

std::map<int, string> buttons;
string queueButtons = "";

Mat FindButton(Mat ref, Mat tpl, string btn) {
    Mat gref;
    cvtColor(ref, gref, COLOR_BGRA2BGR);

    Mat res(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
    matchTemplate(gref, tpl, res, TM_CCOEFF_NORMED);
 
    //threshold(res, res, 0.96, 1.0, THRESH_TOZERO);


    while (true)
    {
        double minval, maxval, threshold = 0.96;
        if (btn == "sl") {
            line(ref, cv::Point(perfectPosition, 3), cv::Point(perfectPosition, 17), CV_RGB(255, 0, 0), 2, 8, 0);
            minval = 0.6; 
            maxval = 1;
            threshold = 0.6;
        }
       
       
 
        Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
            if (btn == "1") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(255, 255, 0), 2
                );
            }
            else if (btn == "2") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(255, 255, 255), 2
                );
            }
            else if (btn == "3") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(0, 255, 255), 2
                );
            }
            else if (btn == "4") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(0, 0, 0), 2
                );
            }
            else if (btn == "6") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(125, 255, 0), 2
                );
            }
            else if (btn == "7") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(0, 125, 125), 2
                );
            }
            else if (btn == "8") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(125, 0, 125), 2
                );
            }
            else if (btn == "9") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(100, 178, 230), 2
                );
            }
            else if (btn == "sl") {
                rectangle(
                    ref,
                    maxloc,
                    Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(255, 255, 0), 2
                );
            }
            
            if (btn != "sl") {
                buttons[maxloc.x] = btn;
            }

            if (btn == "sl") {
                lastSpacePosition = maxloc.x;
            }
          
            floodFill(res, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
        }
        else
            break;
    }
    return ref;
}

void Space() {
    namedWindow("Space", WINDOW_NORMAL);
   
    while (true) {
        lastSpacePosition = 0;
        screenshot2 = hwnd2mat(gameWindow, 120, 20, 570, 485);
        screenshot2 = FindButton(screenshot2, space, "sl");
        // Send space
        int timeNow = (int)std::time(0);
        if (lastSpacePosition > 10 && lastSpacePosition < 100 &&  (abs(lastSpacePosition - perfectPosition) < 2 || lastSpacePosition  > perfectPosition) && timeNow > lastSpaceTime) {
            lastSpaceTime = timeNow;
            lastSpacePosition = 0;
            char* charArray2 = new char[3];
            charArray2[0] = 's';
            charArray2[1] = ';';
            charArray2[2] = '\n';
            arduino.writeSerialPort(charArray2, 3);
        }

        imshow("Space", screenshot2);
        waitKey(1);
    }
}

void AutoKey() {
    //namedWindow("OpenCV", WINDOW_NORMAL);
    while (true) {
        buttons.clear();
        screenshot = hwnd2mat(gameWindow, 480, 40, 270, 516);
        screenshot = FindButton(screenshot, one, "1");
        screenshot = FindButton(screenshot, onered, "1");
        screenshot = FindButton(screenshot, two, "2");
        screenshot = FindButton(screenshot, twored, "2");
        screenshot = FindButton(screenshot, three, "3");
        screenshot = FindButton(screenshot, threered, "3");
        screenshot = FindButton(screenshot, four, "4");
        screenshot = FindButton(screenshot, fourred, "4");
        screenshot = FindButton(screenshot, six, "6");
        screenshot = FindButton(screenshot, sixred, "6");
        screenshot = FindButton(screenshot, seven, "7");
        screenshot = FindButton(screenshot, sevenred, "7");
        screenshot = FindButton(screenshot, eight, "8");
        screenshot = FindButton(screenshot, eightred, "8");
        screenshot = FindButton(screenshot, nine, "9");
        screenshot = FindButton(screenshot, ninered, "9");
        queueButtons = "";
        for (std::map<int, string>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
            queueButtons += it->second + ";";
        }
        if (queueButtons.size() > 0) {
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
        }
               
        // Continue loop screenshot
        //imshow("OpenCV", screenshot);   
        waitKey(1);
    }
}


int WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd)
    
//int main()
{
    string port = "\\\\.\\COM6";
    ifstream myfile("port.txt");
    if (myfile.is_open())
    {
        getline(myfile, port);
        myfile.close();
    }
    else {
        MessageBoxA(NULL, "Cannot find port.txt", "Cannot find port.txt", MB_OK);
        exit(0);
    }

    arduino.Init(port);

    if (arduino.isConnected()) {
        cout << "Connection made" << endl << endl;
    }
    else {

       // cout << "Error in port name" << endl << endl;
       // cin.get();
        MessageBoxA(NULL, "Cannot connect to port", "Cannot connect to port", MB_OK);
        return 0;
    }

    //Mat screenshot = imread("lena.jpg");
    gameId = GetGameProcess(L"Audition.exe");
    gameWindow = FindWindowFromProcessId(gameId);
    
    if (gameId == NULL || gameWindow == NULL) {
        MessageBoxA(NULL, "Cannot find the game", "Cannot find the game", MB_OK);
        exit(0);
    }

    // Init buttons Mat
    cvtColor(one, one, COLOR_BGRA2BGR);
    cvtColor(onered, onered, COLOR_BGRA2BGR);
    cvtColor(two, two, COLOR_BGRA2BGR);
    cvtColor(twored, twored, COLOR_BGRA2BGR);
    cvtColor(three, three, COLOR_BGRA2BGR);
    cvtColor(threered, threered, COLOR_BGRA2BGR);
    cvtColor(four, four, COLOR_BGRA2BGR);
    cvtColor(fourred, fourred, COLOR_BGRA2BGR);
    cvtColor(six, six, COLOR_BGRA2BGR);
    cvtColor(sixred, sixred, COLOR_BGRA2BGR);
    cvtColor(seven, seven, COLOR_BGRA2BGR);
    cvtColor(sevenred, sevenred, COLOR_BGRA2BGR);
    cvtColor(eight, eight, COLOR_BGRA2BGR);
    cvtColor(eightred, eightred, COLOR_BGRA2BGR);
    cvtColor(nine, nine, COLOR_BGRA2BGR);
    cvtColor(ninered, ninered, COLOR_BGRA2BGR);
    cvtColor(space, space, COLOR_BGRA2BGR);
    
    // Begin threads
    std::thread AutoKeyThread(AutoKey);
    std::thread SpaceThread(Space);
    

    // Wating for control keys
    while (arduino.isConnected()) {

        if (GetAsyncKeyState(VK_OEM_PLUS) & 1) {
            perfectPosition += 1;
            std::cout << "Perfect position +: " << perfectPosition << std::endl;
        }

        if (GetAsyncKeyState(VK_OEM_MINUS) & 1) {
            perfectPosition -= 1;
            std::cout << "Perfect position -: " << perfectPosition << std::endl;
        }

        if (GetAsyncKeyState(VK_F12)) {
            exit(0);
            ExitProcess(0);
        }
        Sleep(100);
    }
    
    return 0;
}


Mat hwnd2mat(HWND hwnd, int width, int height, int fromX, int fromY)
{
    HDC hwindowDC, hwindowCompatibleDC;

    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER  bi;

    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);
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
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, fromX, fromY, width, height, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
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