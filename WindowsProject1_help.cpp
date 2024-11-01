#include "framework.h"
#include "WindowsProject1_help.h"
#include "LinkedList.h"
#include "test.h"
#include <string>
#include <sstream>

#define MAX_LOADSTRING 100
#define BUTTON_ADD 1
#define BUTTON_SHOW 2
#define BUTTON_ADD_END 3
#define BUTTON_ADD_AT 4
#define BUTTON_ADD_BEGIN 5
#define BUTTON_SUBSEQ 6
#define BUTTON_EXIT 7

#define EDIT_INPUT 8
#define EDIT_POSITION1 9
#define EDIT_INPUT_BEG 10
#define EDIT_POSITION2 11
#define EDIT_SUBSEQ_POS1 12
#define EDIT_SUBSEQ_POS2 13
#define EDIT_SUBSEQ_ELEM 14


HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ShrdPtr<LinkedList<int>> sequence(new LinkedList<int>());

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ShowSequence(HWND hWnd);
void EnterElements(HWND hWnd);
void EnterElementsAtBegining(HWND hWnd);
void EnterElementsAtPosition(HWND hWnd);
void ShowSubSeq(HWND hWnd);
void RunTests();



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    try
    {
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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1HELP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1HELP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        CreateWindow(L"BUTTON", L"Add Element", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 30, 180, 30, hWnd, (HMENU)BUTTON_ADD, hInst, NULL);
        CreateWindow(L"BUTTON", L"Show Sequence", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 70, 180, 30, hWnd, (HMENU)BUTTON_SHOW, hInst, NULL);
        CreateWindow(L"BUTTON", L"Add Element at beginning", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 120, 180, 30, hWnd, (HMENU)BUTTON_ADD_BEGIN, hInst, NULL);
        CreateWindow(L"BUTTON", L"Add Element at position", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 170, 180, 30, hWnd, (HMENU)BUTTON_ADD_AT, hInst, NULL);
        CreateWindow(L"BUTTON", L"Show subsequence", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 220, 180, 30, hWnd, (HMENU)BUTTON_SUBSEQ, hInst, NULL);
        CreateWindow(L"BUTTON", L"Exit Program", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 270, 180, 30, hWnd, (HMENU)BUTTON_EXIT, hInst, NULL);

        CreateWindow(L"STATIC", L"Input Element:", WS_VISIBLE | WS_CHILD,
            200, 10, 150, 20, hWnd, NULL, hInst, NULL);
        CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            200, 30, 150, 30, hWnd, (HMENU)EDIT_INPUT, hInst, NULL);

        CreateWindow(L"STATIC", L"Input Element:", WS_VISIBLE | WS_CHILD,
            200, 100, 150, 20, hWnd, NULL, hInst, NULL);
        CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            200, 120, 150, 30, hWnd, (HMENU)EDIT_INPUT_BEG, hInst, NULL);

        CreateWindow(L"STATIC", L"Element:", WS_VISIBLE | WS_CHILD,
            200, 150, 150, 20, hWnd, NULL, hInst, NULL);
        CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            200, 170, 150, 30, hWnd, (HMENU)EDIT_POSITION1, hInst, NULL);

        CreateWindow(L"STATIC", L"Position:", WS_VISIBLE | WS_CHILD,
            360, 150, 150, 20, hWnd, NULL, hInst, NULL);
        CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            360, 170, 150, 30, hWnd, (HMENU)EDIT_POSITION2, hInst, NULL);

        CreateWindow(L"STATIC", L"Start Position:", WS_VISIBLE | WS_CHILD,
            200, 200, 150, 20, hWnd, NULL, hInst, NULL);
        CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            360, 220, 150, 30, hWnd, (HMENU)EDIT_SUBSEQ_POS1, hInst, NULL);

        CreateWindow(L"STATIC", L"End Position:", WS_VISIBLE | WS_CHILD,
            360, 200, 150, 20, hWnd, NULL, hInst, NULL);
        CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            200, 220, 150, 30, hWnd, (HMENU)EDIT_SUBSEQ_POS2, hInst, NULL);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case BUTTON_ADD:
            EnterElements(hWnd);
            break;
        case BUTTON_SHOW:
            ShowSequence(hWnd);
            break;
        break;
        case BUTTON_ADD_AT:
        {
            EnterElementsAtPosition(hWnd);
        }
        break;
        case BUTTON_ADD_BEGIN:
        {
            EnterElementsAtBegining(hWnd);
        }
        break;
        case BUTTON_SUBSEQ:
        {
            ShowSubSeq(hWnd);
        }
        break;
        case BUTTON_EXIT:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam); 
        }
        return 0;  
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void ShowSequence(HWND hWnd)
{
    std::wstringstream ss;
    for (int i = 0; i < sequence->GetLength(); i++)
    {
        ss << sequence->Get(i) << L" ";
    }
    MessageBox(hWnd, ss.str().c_str(), L"Sequence", MB_OK);
}

void EnterElements(HWND hWnd)
{
    wchar_t buffer[256];
    GetWindowText(GetDlgItem(hWnd, EDIT_INPUT), buffer, 256);
    std::wstring input(buffer);
    std::wistringstream ss(input);
    int elem;
    while (ss >> elem)
    {
        sequence->Append(elem);
    }
    MessageBox(hWnd, L"Elements added.", L"Success", MB_OK);
}

void EnterElementsAtBegining(HWND hWnd)
{
    wchar_t buffer[256];
    GetWindowText(GetDlgItem(hWnd, EDIT_INPUT_BEG), buffer, 256); 
    std::wstring input(buffer);
    std::wistringstream ss(input);

    int elem;
    while (ss >> elem)
    {
        sequence->Prepend(elem);
    }
    MessageBox(hWnd, L"Elements added at the beginning.", L"Success", MB_OK);
}

void EnterElementsAtPosition(HWND hWnd)
{
    wchar_t bufferElem[256];
    wchar_t bufferPos[256];

    GetWindowText(GetDlgItem(hWnd, EDIT_POSITION1), bufferElem, 256);
    GetWindowText(GetDlgItem(hWnd, EDIT_POSITION2), bufferPos, 256);

    std::wistringstream ssElem(bufferElem);
    std::wistringstream ssPos(bufferPos);

    int elem, pos;
    bool success = false;
    std::wstring errorMessage;

    while (ssElem >> elem && ssPos >> pos)
    {
        try
        {
            sequence->InsertAt(elem, pos);
            success = true;
        }
        catch (...)
        {
            std::wstringstream errorStream;
            errorStream << L"Failed to add element " << elem << L" at position " << pos << L".\n";
            errorMessage += errorStream.str();
        }
    }

    if (success)
    {
        MessageBox(hWnd, L"Elements added at the specified positions.", L"Success", MB_OK);
    }
    if (!errorMessage.empty())
    {
        MessageBox(hWnd, errorMessage.c_str(), L"Error", MB_OK);
    }
}

void ShowSubSeq(HWND hWnd)
{
    wchar_t buffer1[256];
    GetWindowText(GetDlgItem(hWnd, EDIT_SUBSEQ_POS1), buffer1, 256);
    int pos2 = std::wcstol(buffer1, nullptr, 10);

    wchar_t buffer2[256];
    GetWindowText(GetDlgItem(hWnd, EDIT_SUBSEQ_POS2), buffer2, 256);
    int pos1 = std::wcstol(buffer2, nullptr, 10);
    try
    {
        std::wstringstream ss;
        ShrdPtr<LinkedList<int>> subsequence = sequence->GetSubList(pos1, pos2);
        for (int i = 0; i < subsequence->GetLength(); i++)
        {
            ss << subsequence->Get(i) << L" ";
        }
        MessageBox(hWnd, ss.str().c_str(), L"Subsequence", MB_OK);
    }
    catch (...)
    {
        MessageBox(hWnd, L"Invalid positions.", L"Error", MB_OK);
    }
}

void RunTests()
{  
    Test1_OfListSequenceMutable();
    Test2_OfListSequenceMutable();
    Test3_OfListSequenceMutable();
    Test4_OfListSequenceMutable();
    Test5_OfListSequnceMutable();
    Test1_OfLinkedList();
    Test2_OfLinkedList();
    Test3_OfLinkedList();
    Test4_OfLinkedList();
}

