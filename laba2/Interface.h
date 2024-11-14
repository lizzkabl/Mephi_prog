#pragma once
#include "BubleSort.h"
#include "ShakerSort.h"
#include "ImprovedSelectionSort.h"
#include "QuickSort.h"
#include "Statistic.h"
#include "Test.h"
#include <Richedit.h>
#include <string>
#include <sstream>
#include <functional>
#include "framework.h"

#define MAX_LOADSTRING 100
#define BUTTON_ADD 1
#define BUTTON_SHOW 2
#define BUTTON_SORT 3
#define BUTTON_SHOW_SORT 4
#define BUTTON_GENERATE 5
#define BUTTON_SORT_SHOW 15
#define COMBO_SORT 7
#define COMBO_SORT_SHOW 16
#define BUTTON_STATISTIC 17

#define EDIT_INPUT 8
#define EDIT_GENERATE 9
#define IDC_SEQUENCE_DISPLAY 10
#define BUTTON_EXIT 12

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ShrdPtr<MutableSequence<int>> sequence(new ListSequenceMutable<int>());


ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ShowSequence(HWND hWnd);
void EnterElements(HWND hWnd);
void Sort(HWND hWnd);
void ShowSort(HWND hWnd);
void StatisticShow(HWND hWnd);


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_LABA23));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LABA23);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    LoadLibrary(TEXT("Msftedit.dll"));
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

        CreateWindow(L"BUTTON", L"Statistic", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 190, 180, 30, hWnd, (HMENU)BUTTON_STATISTIC, hInst, NULL);

        CreateWindow(L"BUTTON", L"Exit", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 230, 180, 30, hWnd, (HMENU)BUTTON_EXIT, hInst, NULL);

        CreateWindow(L"BUTTON", L"Sort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 110, 180, 30, hWnd, (HMENU)BUTTON_SORT, hInst, NULL);

        HWND hComboBox = CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            200, 110, 150, 100, hWnd, (HMENU)COMBO_SORT, hInst, NULL);

        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"Bubble Sort");
        SendMessage(hComboBox, CB_ADDSTRING, 1, (LPARAM)L"Shaker Sort");
        SendMessage(hComboBox, CB_ADDSTRING, 2, (LPARAM)L"Selection(I) Sort");
        SendMessage(hComboBox, CB_ADDSTRING, 3, (LPARAM)L"Quick Sort");
        SendMessage(hComboBox, CB_SETCURSEL, 0, 0);

        CreateWindow(L"BUTTON", L"Show Sort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 150, 180, 30, hWnd, (HMENU)BUTTON_SORT_SHOW, hInst, NULL);

        CreateWindow(MSFTEDIT_CLASS, L"", WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_READONLY,
            375, 150, 300, 200, hWnd, (HMENU)IDC_SEQUENCE_DISPLAY, hInst, NULL); 

        HWND hComboBox2 = CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            200, 150, 150, 100, hWnd, (HMENU)COMBO_SORT_SHOW, hInst, NULL);

        SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)L"Bubble Sort");
        SendMessage(hComboBox2, CB_ADDSTRING, 1, (LPARAM)L"Shaker Sort");
        SendMessage(hComboBox2, CB_ADDSTRING, 2, (LPARAM)L"Selection(I) Sort");
        SendMessage(hComboBox2, CB_ADDSTRING, 3, (LPARAM)L"Quick Sort");
        SendMessage(hComboBox2, CB_SETCURSEL, 0, 0);

        CreateWindow(L"STATIC", L"Input Element:", WS_VISIBLE | WS_CHILD,
            200, 10, 150, 20, hWnd, NULL, hInst, NULL);
        CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            200, 30, 150, 30, hWnd, (HMENU)EDIT_INPUT, hInst, NULL);
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
        case BUTTON_SORT:
            Sort(hWnd);
            break;
        case BUTTON_SORT_SHOW:
            ShowSort(hWnd);
            break;
        case BUTTON_STATISTIC:
            StatisticShow(hWnd);
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

template <typename T>
void VisualizeCurrentState(HWND hWnd, ShrdPtr<MutableSequence<T>> sequence, int currentIndex1 = -1, int currentIndex2 = -1)
{
    HWND hRichEdit = GetDlgItem(hWnd, IDC_SEQUENCE_DISPLAY);
    SendMessage(hRichEdit, WM_SETTEXT, 0, (LPARAM)L"");

    for (int i = 0; i < sequence->GetLength(); i++)
    {
        CHARFORMAT cf;
        ZeroMemory(&cf, sizeof(cf));
        cf.cbSize = sizeof(cf);
        cf.dwMask = CFM_COLOR;

        if (i == currentIndex1)
        {
            cf.crTextColor = RGB(255, 0, 0);  
        }
        else if (i == currentIndex2)
        {
            cf.crTextColor = RGB(0, 255, 0);  
        }
        else
        {
            cf.crTextColor = RGB(0, 0, 255);  
        }

        SendMessage(hRichEdit, EM_SETSEL, -1, -1);
        SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

        std::wstringstream ss;
        ss << sequence->Get(i) << L" ";
        SendMessage(hRichEdit, EM_REPLACESEL, 0, (LPARAM)ss.str().c_str());

        RedrawWindow(hRichEdit, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    }
    SendMessage(hRichEdit, EM_SETSEL, -1, 0); 
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

    bool success = true;
    while (ss >> elem)
    {
        sequence->Append(elem);
    }
    if (!success)
    {
        MessageBox(hWnd, L"incorrect input data. Please enter integer numbers.", L"Error", MB_OK | MB_ICONERROR);
    }
    else
    {
        MessageBox(hWnd, L"Elements are aded.", L"Sucsess", MB_OK);
    }
}

void Sort(HWND hWnd)
{
    HWND hComboBox = GetDlgItem(hWnd, COMBO_SORT);
    int selectedSort = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

    switch (selectedSort)
    {
    case 0:
    {
        BubleSort<int> sort;
        sort.Sort(sequence);
    }
    break;
    case 1:
    {
        ShakerSort<int> sort;
        sort.Sort(sequence);
    }
    break;
    case 2:
    {
        ImprovedSelectionSort<int> sort;
        sort.Sort(sequence);
    }
    break;
    case 3:
    {
        QuickSort<int> sort;
        sort.Sort(sequence);
    }
    break;
    default:
        MessageBox(hWnd, L"Unknown algorithm", L"Erorr", MB_OK | MB_ICONERROR);
        return;
    }

    std::wstringstream ss;
    for (int i = 0; i < sequence->GetLength(); i++) 
    {
        ss << sequence->Get(i) << L" ";
    }
    MessageBox(hWnd, ss.str().c_str(), L"Sequence has been sorted", MB_OK);
}

void ShowSort(HWND hWnd)
{
    HWND hComboBox = GetDlgItem(hWnd, COMBO_SORT_SHOW);
    int selectedSort = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

    switch (selectedSort)
    {
    case 0:
    {
        BubleSort<int> sort;
        sort.ShowSort(sequence, hWnd);
    }
    break;
    case 1:
    {
        ShakerSort<int> sort;
        sort.ShowSort(sequence, hWnd);
    }
    break;
    case 2:
    {
        ImprovedSelectionSort<int> sort;
        sort.ShowSort(sequence, hWnd);
    }
    break;
    case 3:
    {
        QuickSort<int> sort;
        sort.ShowSort(sequence, hWnd);
    }
    break;
    default:
        MessageBox(hWnd, L"Unknown algorithm", L"Erorr", MB_OK | MB_ICONERROR);
        return;
    }
}

void StatisticShow(HWND hWnd)
{
    std::wstringstream ss;
    
    std::wstring errorMessage;
    try
    {
        Statistic<int> stat;
        ss << L"Mean: " << stat.Mean(sequence) << L"\n" << L"Standart Deviation: " << stat.StandartDeviation(sequence) << L"\n" << L"Root Mean Square: " << stat.RootMeanSquare(sequence) << L" ";

        MessageBox(hWnd, ss.str().c_str(), L"Sequence", MB_OK);
    }
    catch (...)
    {
        std::wstringstream errorStream;
        errorStream << L"Failed to calculate "<< L".\n";
        errorMessage += errorStream.str();
        MessageBox(hWnd, errorMessage.c_str(), L"Error", MB_OK);
    }
}

void RunTests() {

    BubbleTestSortingByHeight();
    BubbleTestSortingByFirstName();
    BubbleTestSortingByLastName();
    BubbleTestSortingByBirthYear();
    BubbleTestSortingByWeight();

    ISelectTestSortingByHeight();
    ISelectTestSortingByFirstName();
    ISelectTestSortingByLastName();
    ISelectTestSortingByBirthYear();
    ISelectTestSortingByWeight();


    QuickTestSortingByHeight();
    QuickTestSortingByFirstName();
    QuickTestSortingByLastName();
    QuickTestSortingByBirthYear();
    QuickTestSortingByWeight();


    ShakerTestSortingByHeight();
    ShakerTestSortingByFirstName();
    ShakerTestSortingByLastName();
    ShakerTestSortingByBirthYear();
    ShakerTestSortingByWeight();
}
