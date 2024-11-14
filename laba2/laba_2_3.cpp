#include "C:\Users\user\source\repos\WindowsProject1_help\WindowsProject1_help.h"
#include "C:\Users\user\source\repos\WindowsProject1_help\LinkedList.h"
#include "Test.h"
#include "Interface.h"
#include <sstream>
#include <functional>
#include "framework.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    try
    {
        RunTests();
        MessageBox(NULL, L"All test are correct.", L"Test Notification", MB_OK);
    }
    catch (const std::out_of_range& e)
    {
        MessageBox(NULL, L"Something wrong with tests", L"Test Notification", MB_OK);
        PostQuitMessage(0);
    }
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1HELP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1HELP));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}