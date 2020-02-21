// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "main.h"
#include <thread>

// keymap: https://github.com/dorianj/CoRD/blob/master/Resources/keymap.txt
enum ScanCode
{
    SCANCODE_X = 0x2D,
    SCANCODE_Y = 0x15,
    SCANCODE_ESC = 0x01,
   
    SCANCODE_LEFT = 0x4b,
    SCANCODE_RIGHT = 0x4d,
    SCANCODE_UP = 0x48,
    SCANCODE_DOWN = 0x50,
    
    /*
    SCANCODE_LEFT = 0x14,
    SCANCODE_RIGHT = 0x19,
    SCANCODE_UP = 0x26,
    SCANCODE_DOWN = 0x1F,
    */
};
bool autoKeyDone = false;
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

InterceptionContext context;
InterceptionDevice device;
InterceptionKeyStroke stroke;
std::map<int, ScanCode> buttons;
std::vector<ScanCode> queueButtons;

Mat FindButton(Mat ref, Mat tpl, ScanCode btn) {
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
            
            rectangle(
                ref,
                maxloc,
                Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                CV_RGB(0, 255, 0), 2
            );
            
            buttons[maxloc.x] = btn;
            floodFill(res, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
        }
        else
            break;
    }
    return ref;
}

void Screenshot() {
    namedWindow("clone", WINDOW_NORMAL);

    while (true) {
    buttons.clear();
    
    img = hwnd2mat(gameWindow);
    /*
    img = FindButton(img, len, "len");
    img = FindButton(img, xuong, "xuong");
    img = FindButton(img, trai, "trai");
    img = FindButton(img, phai, "phai");
    img = FindButton(img, dl, "xuong");
    img = FindButton(img, dx, "len");
    img = FindButton(img, dt, "phai");
    img = FindButton(img, dp, "trai");
    */

    img = FindButton(img, len, SCANCODE_UP);
    img = FindButton(img, xuong, SCANCODE_DOWN);
    img = FindButton(img, trai, SCANCODE_LEFT);
    img = FindButton(img, phai, SCANCODE_RIGHT);
    img = FindButton(img, dl, SCANCODE_DOWN);
    img = FindButton(img, dx, SCANCODE_UP);
    img = FindButton(img, dt, SCANCODE_RIGHT);
    img = FindButton(img, dp, SCANCODE_LEFT);
    queueButtons.clear();
    for (std::map<int, ScanCode>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
        queueButtons.push_back(it->second);
           
    }
    autoKeyDone = false;
    imshow("clone", img);
    waitKey(1);
   
   }
}

void Autokey() {
    int countButtons = 0;
    while (interception_receive(context, device = interception_wait(context), (InterceptionStroke*)&stroke, 1) > 0)
    {
        interception_send(context, device, (InterceptionStroke*)&stroke, 1);
        if (autoKeyDone == false && stroke.code == SCANCODE_X) {
            for (int i = 0; i < queueButtons.size(); i++) {
                stroke.code = queueButtons[i];
                std::cout << queueButtons[i] << " ";
                interception_send(context, device, (InterceptionStroke*)&stroke, 1);
            }
            std::cout << " Done" << std::endl;
            autoKeyDone = true;
        }
    }
       
    
   // interception_destroy_context(context);
}

int main()
{
    context = interception_create_context();
    interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);

    //Mat img = imread("lena.jpg");
    gameId = GetGameProcess(L"Audition.exe");
    gameWindow = FindWindowFromProcessId(gameId);
    img = hwnd2mat(gameWindow);

    std::thread ScreenshotThread(Screenshot);

    std::thread AutokeyThread(Autokey);

    while (true) {
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