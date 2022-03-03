// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "main.h"

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];
int perfectPositionGoc = 57;
int perfectPosition = 57;
int startPosition = 5;
int demBpm = 130;
int tocDoBam = 210;
int mucDoPer = 2;
int level = 6;
int perXMax = 5;
bool nenBam = false;
bool nenSpace = true;
auto t1 = high_resolution_clock::now();
auto t2 = high_resolution_clock::now();
bool autoKeyOn = true;
bool autoSpaceOn = true;
bool autoSS = false;
bool waitingForSS = false;
int demPer = 0;

milliseconds ms;
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
Mat notice = imread("btn/notice.png", -1);

Mat screenshot, screenshot2, screenAutoSS;

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

        if (btn == "notice") {
            minval = 0.7;
            maxval = 1;
            threshold = 0.9;
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
            
            if (btn != "sl" && btn != "notice") {
                buttons[maxloc.x] = btn;
            } else if (btn == "sl") {
                lastSpacePosition = maxloc.x;
            } else if (btn == "notice") {
                waitingForSS = maxloc.x;
            }
          
            floodFill(res, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
        }
        else
            break;
    }
    return ref;
}

void QuetBi() {
    return;
    while (true) {
       
        Sleep(1);
    }
}

void stt() {
    std::cout << "ON: " << autoSpaceOn << ". BPM: " << demBpm << ". Per: " << (int)(100 / mucDoPer) << "%. MaxX: " << perXMax << ". Next: " << (perfectPosition - perfectPositionGoc) << ". Auto F1: " << autoSS << endl;
}

void Space() {
   // return;
        //namedWindow("Space", WINDOW_NORMAL);
    while (true) {

        if (!autoSpaceOn) {
            Sleep(1);
            continue;
        }

        screenshot2 = hwnd2mat(gameWindow, 120, 20, 570, 485);
        screenshot2 = FindButton(screenshot2, space, "sl");

        if (lastSpacePosition > 0 && lastSpacePosition < 3) {
            t1 = high_resolution_clock::now();
        }
        if (lastSpacePosition < (perfectPositionGoc + 3) && lastSpacePosition >= perfectPositionGoc) {
            t2 = high_resolution_clock::now();
            ms = duration_cast<milliseconds>(t2 - t1);
           // demBpm = std::max(std::min(176, (int)(750 - ms.count())), 120);
            demBpm = min(220, max(80, (int)(60000 / ms.count() * 1.48)));
            //cout << demBpm << endl;
        }

        // Send space
        int timeNow = (int)std::time(0);
        if (nenSpace && lastSpacePosition > 40 && lastSpacePosition < 75 && timeNow > lastSpaceTime && lastSpacePosition >= perfectPosition) {
            //std::cout << "Space " << startPosition << " < " <<  lastSpacePosition << endl;
            //lastSpacePosition = 0;
            
            char* charArray2 = new char[2];
            charArray2[0] = 's';
            charArray2[1] = '\n';
            arduino.writeSerialPort(charArray2, 2);
            lastSpaceTime = (int)std::time(0);
            nenSpace = false;

            //perfectPosition = perfectPositionGoc - rand() % 3 - 2;
            if ((mucDoPer == 1 || rand() % mucDoPer == 1) && demPer < perXMax) {
                perfectPosition = perfectPositionGoc;
                demPer++;
            }
            else {
                int lechPer = 0;
                while (lechPer == 0) {
                    lechPer = 3 - rand() % 4;
                }
                perfectPosition = perfectPositionGoc + lechPer;
                demPer = 0;
                stt();
            }
            
            //perfectPosition = perfectPositionGoc + 1 - rand() % 2;
           // perfectPosition = perfectPositionGoc;
        }
        Sleep(1);
       //imshow("Space", screenshot2);
        //waitKey(1);
    }
}


void AutoKey() {
   // namedWindow("OpenCV", WINDOW_NORMAL);
    while (true) {
        if (!autoKeyOn) {
            Sleep(1);
            continue;
        }
        int demGiaNgo = 0;
        buttons.clear();
        //screenshot = hwnd2mat(gameWindow, 480, 40, 270, 516);
        screenshot = hwnd2mat(gameWindow, 900, 40, 120, 516);
        screenshot = FindButton(screenshot, one, "1b");
        screenshot = FindButton(screenshot, onered, "1r");
        screenshot = FindButton(screenshot, two, "2b");
        screenshot = FindButton(screenshot, twored, "2r");
        screenshot = FindButton(screenshot, three, "3b");
        screenshot = FindButton(screenshot, threered, "3r");
        screenshot = FindButton(screenshot, four, "4b");
        screenshot = FindButton(screenshot, fourred, "4r");
        screenshot = FindButton(screenshot, six, "6b");
        screenshot = FindButton(screenshot, sixred, "6r");
        screenshot = FindButton(screenshot, seven, "7b");
        screenshot = FindButton(screenshot, sevenred, "7r");
        screenshot = FindButton(screenshot, eight, "8b");
        screenshot = FindButton(screenshot, eightred, "8r");
        screenshot = FindButton(screenshot, nine, "9b");
        screenshot = FindButton(screenshot, ninered, "9r");
        queueButtons = "";
        for (std::map<int, string>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
            queueButtons += it->second + ";";
        }
       
        level = queueButtons.size() / 3;
        if (level > 0) {
            // Dừng lại nhìn đã rồi hẵng bấm bạn ơi
            Sleep(max(20, (rand() % 30 + tocDoBam - demBpm)));
            // std::cout << queueButtons << endl;
            // copy(queueButtons.begin(), queueButtons.end(), charArray);
            nenSpace = false;
            for (int x = 0; x < level; x++) {
                if (x >= level - 1) {
                    nenSpace = true;
                }

                char huongMuiTen = queueButtons[x * 3 + 1];
                char nutBam = queueButtons[x * 3];

                if (huongMuiTen == 'r') {
                    //Sleep(max(20, (rand() % 20 + tocDoBam - demBpm)));
                }

                char* charArray2 = new char[2];
                charArray2[0] = nutBam;
                charArray2[1] = '\n';
                arduino.writeSerialPort(charArray2, 2);


                //int rd = rand() % 30 + 200  - demBpm;
                //int rd = min(60, max(110, (int) (rand() % 30 + 180 - demBpm - queueButtons.size())));
                int rd = min(120 + rand() % 10, max(65 + rand() % 10, (int)(rand() % 20 + 50 + tocDoBam - demBpm - 2 * level)));
                //std::cout << "Toc do bam " << rd << endl;
                Sleep(rd);


                // Bam cham neu 2 nut lien tiep giong nhau
                if (x < level - 2) {
                    int next = x * 2 + 1;
                    if (queueButtons[x] == queueButtons[next]) {
                        Sleep(rand() % 10 + 70 - demBpm / 4);
                    }
                    if ((queueButtons[x] == '2' == queueButtons[next] == '8') || (queueButtons[x] == '8' == queueButtons[next] == '2')) {
                        Sleep(rand() % 10 + 70 - demBpm / 4);
                    }
                }

                // Giả ngố, thi thoảng bấm chậm lại
                int rd2 = rand() % 100;
                if (demGiaNgo < 1 && rd2 > 90 && x < 11 && x > 4) {
                    demGiaNgo++;
                    Sleep(rand() % 20 + 90 - demBpm / 4);
                    //std::cout << "Gia ngo" << endl;
                }
                
                // Thi thoảng miss 1 cái
                //int rd3 = rand() % (550 - demBpm * 2);
                int rd3 = 0;
                if (rd3 == 50) {
                    char* charArray3 = new char[2];
                    charArray3[0] = queueButtons[x];
                    charArray3[1] = '\n';
                    arduino.writeSerialPort(charArray3, 2);
                    //std::cout << "Miss han" << endl;
                }
            }
        }
        Sleep(1);
        // Continue loop screenshot
        //imshow("OpenCV", screenshot);   
        //waitKey(1);
    }
}

void AutoSS() {
    //namedWindow("OpenCV", WINDOW_NORMAL);
    while (true) {
        if (autoSS) {
            waitingForSS = 0;
            screenAutoSS = hwnd2mat(gameWindow, 90, 30, 0, 580);
            screenAutoSS = FindButton(screenAutoSS, notice, "notice");
            if (waitingForSS > 0) {
                char* charArray = new char[2];
                charArray[0] = 'f';
                charArray[1] = '\n';
                arduino.writeSerialPort(charArray, 2);
            }
        }
        Sleep(4000 + rand() % 3 * 1000);
        //imshow("OpenCV", screenAutoSS);
        //waitKey(1);
    }
}

//int WinMain(HINSTANCE hInstance,    HINSTANCE hPrevInstance,    LPSTR     lpCmdLine,    int       nShowCmd)    
int main()
{
    //std::cout << "Starttttttt" << std::endl;
    string port = "\\\\.\\COM5";
    ifstream myfile("port.txt");
    if (myfile.is_open())
    {
        getline(myfile, port);
        myfile.close();
    }
    else {
        //MessageBoxA(NULL, "Cannot find port.txt", "Cannot find port.txt", MB_OK);
        exit(0);
    }

    arduino.Init(port);

    if (arduino.isConnected()) {
        //cout << "Connection made" << endl << endl;
    }
    else {

       // cout << "Error in port name" << endl << endl;
       // cin.get();
        //MessageBoxA(NULL, "Cannot connect to port", "Cannot connect to port", MB_OK);
        return 0;
    }

    //Mat screenshot = imread("lena.jpg");
    gameId = GetGameProcess(L"Audition.exe");
    gameWindow = FindWindowFromProcessId(gameId);
    
    if (gameId == NULL || gameWindow == NULL) {
        //MessageBoxA(NULL, "Cannot find the game", "Cannot find the game", MB_OK);
        gameId = GetGameProcess(L"Aubiz.exe");
        gameWindow = FindWindowFromProcessId(gameId);
        if (gameId == NULL || gameWindow == NULL) {
            exit(0);
        }
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
    //std::thread QuetBiThread(QuetBi);
    std::thread AutoKeyThread(AutoKey);
    std::thread SpaceThread(Space);
    std::thread AutoSSThread(AutoSS);

    // Wating for control keys
    while (arduino.isConnected()) {

        if (GetAsyncKeyState(VK_OEM_PLUS) & 1) {
            perXMax += 1;
            stt();
        }

        if (GetAsyncKeyState(VK_OEM_MINUS) & 1) {
            perXMax -= 1;
            stt();
        }

        if (GetAsyncKeyState(VK_F12) & 1) {
            exit(0);
            ExitProcess(0);
        }

        if (GetAsyncKeyState(VK_F8) & 1) {
            autoSS = !autoSS;
        }


        if (GetAsyncKeyState(VK_F9) & 1) {
            if (mucDoPer == 1) {
                std::cout << "Khong the giam nua. Muc hien tai: " << mucDoPer << std::endl;
            }
            else {
                mucDoPer--;
                stt();
            }
        }

        if (GetAsyncKeyState(VK_F10) & 1) {
            mucDoPer++;
            stt();
        }
        if (GetAsyncKeyState(VK_F11) & 1) {
            autoKeyOn = !autoKeyOn;
            stt();
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