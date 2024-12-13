#include "framework.h"
#include "DirectedGraph.h"
#include "Vertex.h"
#include "ArraySequenceMutable.h"
#include "Test.h"


HINSTANCE hInst;
bool colorGraphMode = false;
ArraySequenceMutable<ArraySequenceMutable<int>> mstEdges;
DirectedGraph<int> graph;
const int BUTTON_ADD_VERTEX = 1;
const int BUTTON_ADD_EDGE = 2;
const int BUTTON_DRAW_GRAPH = 3;
const int BUTTON_SHORT_DIST = 8;
const int INPUT_FROM_VERTEX = 4;
const int INPUT_TO_VERTEX = 5;
const int INPUT_WEIGHT = 6;
const int INPUT_FROM = 9;
const int INPUT_TO = 10;
const int BUTTON_COLOR_GRAPH = 7;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawGraph(HDC hdc, RECT rect);
void ClearGraph(HDC hdc, RECT rect);
void ColorGraph(HDC hdc, RECT rect);
void GetShortDistance(int from, int to);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
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
    hInst = hInstance;

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"GraphApp";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"GraphApp",
        L"Graph Visualizer",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND buttonAddVertex, buttonAddEdge, buttonDrawGraph, buttonColorGraph, buttonShortDis, buttonDrawMST;
    static HWND editFromVertex, editToVertex, editWeight, editTo, editFrom;

    switch (uMsg)
    {
    case WM_CREATE:

        buttonAddVertex = CreateWindow(L"BUTTON", L"Add Vertex",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 10, 100, 30, hwnd, (HMENU)BUTTON_ADD_VERTEX, hInst, nullptr);

        buttonShortDis = CreateWindow(L"BUTTON", L"Short Dist",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 170, 100, 30, hwnd, (HMENU)BUTTON_SHORT_DIST, hInst, nullptr);

        buttonAddEdge = CreateWindow(L"BUTTON", L"Add Edge",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 50, 100, 30, hwnd, (HMENU)BUTTON_ADD_EDGE, hInst, nullptr);

        buttonColorGraph = CreateWindow(L"BUTTON", L"Color Graph",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 130, 100, 30, hwnd, (HMENU)BUTTON_COLOR_GRAPH, hInst, nullptr);

        editFromVertex = CreateWindow(L"EDIT", L"",
            WS_BORDER | WS_CHILD | WS_VISIBLE,
            120, 50, 50, 20, hwnd, (HMENU)INPUT_FROM_VERTEX, hInst, nullptr);

        editToVertex = CreateWindow(L"EDIT", L"",
            WS_BORDER | WS_CHILD | WS_VISIBLE,
            180, 50, 50, 20, hwnd, (HMENU)INPUT_TO_VERTEX, hInst, nullptr);

        editWeight = CreateWindow(L"EDIT", L"0",
            WS_BORDER | WS_CHILD | WS_VISIBLE,
            240, 50, 50, 20, hwnd, (HMENU)INPUT_WEIGHT, hInst, nullptr);

        editFrom = CreateWindow(L"EDIT", L"",
            WS_BORDER | WS_CHILD | WS_VISIBLE,
            120, 170, 50, 20, hwnd, (HMENU)INPUT_FROM, hInst, nullptr);
        editTo = CreateWindow(L"EDIT", L"",
            WS_BORDER | WS_CHILD | WS_VISIBLE,
            180, 170, 50, 20, hwnd, (HMENU)INPUT_TO, hInst, nullptr);

        buttonDrawGraph = CreateWindow(L"BUTTON", L"Draw Graph",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 90, 100, 30, hwnd, (HMENU)BUTTON_DRAW_GRAPH, hInst, nullptr);

        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case BUTTON_ADD_VERTEX:
            graph.AddVertex();
            break;

        case BUTTON_ADD_EDGE:
        {
            wchar_t buffer[10];
            int fromId, toId, weight;

            GetWindowText(editFromVertex, buffer, 10);
            if (swscanf_s(buffer, L"%d", &fromId) != 1 || fromId <= 0) 
            {
                MessageBox(hwnd, L"Invalid input for 'From Vertex'. Please enter a positive integer.", L"Input Error", MB_OK | MB_ICONERROR);
                break;
            }

            GetWindowText(editToVertex, buffer, 10);
            if (swscanf_s(buffer, L"%d", &toId) != 1 || toId <= 0) 
            {
                MessageBox(hwnd, L"Invalid input for 'To Vertex'. Please enter a positive integer.", L"Input Error", MB_OK | MB_ICONERROR);
                break;
            }

            GetWindowText(editWeight, buffer, 10);
            if (swscanf_s(buffer, L"%d", &weight) != 1 || weight < 0) {
                MessageBox(hwnd, L"Invalid input for 'Weight'. Please enter a non-negative integer.", L"Input Error", MB_OK | MB_ICONERROR);
                break;
            }

            try {
                graph.AddEdge(fromId, toId, weight);
            }
            catch (...) 
            {
                MessageBoxA(hwnd,"something wrong", "Error", MB_OK | MB_ICONERROR);
            }
            break;
        }

        case BUTTON_SHORT_DIST:
        {
            wchar_t buffer[10];
            int fromId, toId;

            GetWindowText(editFrom, buffer, 10);
            if (swscanf_s(buffer, L"%d", &fromId) != 1 || fromId <= 0) {
                MessageBox(hwnd, L"Invalid input for 'From Vertex'. Please enter a positive integer.", L"Input Error", MB_OK | MB_ICONERROR);
                break;
            }

            GetWindowText(editTo, buffer, 10);
            if (swscanf_s(buffer, L"%d", &toId) != 1 || toId <= 0) {
                MessageBox(hwnd, L"Invalid input for 'To Vertex'. Please enter a positive integer.", L"Input Error", MB_OK | MB_ICONERROR);
                break;
            }

            try {
                auto result = graph.FindShortestPath(fromId, toId);
                int distance = result.first;
                const std::vector<int>& path = result.second;

                if (distance == -1) {
                    MessageBox(hwnd, L"No path found between these vertices", L"Error", MB_OK | MB_ICONERROR);
                }
                else {
                    wchar_t resultMessage[500];
                    swprintf(resultMessage, 500, L"Shortest distance: %d\nPath: ", distance);

                    for (size_t i = 0; i < path.size(); ++i) {
                        if (i > 0) swprintf(resultMessage + wcslen(resultMessage), 500 - wcslen(resultMessage), L" -> ");
                        swprintf(resultMessage + wcslen(resultMessage), 500 - wcslen(resultMessage), L"%d", path[i]);
                    }

                    MessageBox(hwnd, resultMessage, L"Result", MB_OK | MB_ICONINFORMATION);
                }
            }
            catch (const std::exception& e) {
                MessageBoxA(hwnd, e.what(), "Error", MB_OK | MB_ICONERROR);
            }
            break;
        }




        case BUTTON_DRAW_GRAPH:
            colorGraphMode = false;
            InvalidateRect(hwnd, nullptr, TRUE);
            break;

        case BUTTON_COLOR_GRAPH:
            colorGraphMode = true;
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);

        ClearGraph(hdc, rect);

        if (colorGraphMode)
        {
            ColorGraph(hdc, rect);
        }
        else
        {
            DrawGraph(hdc, rect);
        }

        EndPaint(hwnd, &ps);
    }
    break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void ClearGraph(HDC hdc, RECT rect)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));  
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);
}

void DrawGraph(HDC hdc, RECT rect)
{
    int radius = 20;
    int centerX = (rect.right - rect.left) / 2;
    int centerY = (rect.bottom - rect.top) / 2;
    int circleRadius = min(rect.right - rect.left, rect.bottom - rect.top) / 3;
    int vertexCount = graph.GetVertexCount();

    if (vertexCount == 0)
        return;

    std::vector<std::pair<int, int>> vertexPositions(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        double angle = i * 2 * 3.141592653589793 / vertexCount;
        int x = centerX + static_cast<int>(circleRadius * cos(angle));
        int y = centerY + static_cast<int>(circleRadius * sin(angle));

        vertexPositions[i] = { x, y };

        COLORREF colorRef = RGB(255, 255, 255); 


        HBRUSH hBrush = CreateSolidBrush(colorRef);
        SelectObject(hdc, hBrush);
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
        DeleteObject(hBrush);

        wchar_t id[10];
        swprintf_s(id, 10, L"%d", i + 1);
        TextOut(hdc, x - 5, y - 5, id, wcslen(id));
    }

    for (int i = 0; i < vertexCount; ++i)
    {
        Vertex<int>* vertex = graph.GetVertex(i + 1);
        const DictionaryOnSequence<int, int>& outgoings = vertex->GetOutgoings();

        for (int j = 0; j < outgoings.GetCount(); ++j)
        {
            int toId = outgoings.GetKeyAtIndex(j);
            int fromX = vertexPositions[i].first;
            int fromY = vertexPositions[i].second;
            int toX = vertexPositions[toId - 1].first;
            int toY = vertexPositions[toId - 1].second;

            MoveToEx(hdc, fromX, fromY, nullptr);
            LineTo(hdc, toX, toY);

            int arrowSize = 10;
            double angle = atan2(toY - fromY, toX - fromX);
            int arrowX1 = toX - static_cast<int>(arrowSize * cos(angle - 3.141592653589793 / 6));
            int arrowY1 = toY - static_cast<int>(arrowSize * sin(angle - 3.141592653589793 / 6));
            int arrowX2 = toX - static_cast<int>(arrowSize * cos(angle + 3.141592653589793 / 6));
            int arrowY2 = toY - static_cast<int>(arrowSize * sin(angle + 3.141592653589793 / 6));

            MoveToEx(hdc, toX, toY, nullptr);
            LineTo(hdc, arrowX1, arrowY1);
            MoveToEx(hdc, toX, toY, nullptr);
            LineTo(hdc, arrowX2, arrowY2);

            wchar_t weightLabel[10];
            swprintf_s(weightLabel, 10, L"%d", outgoings.Get(toId));
            TextOut(hdc, (fromX + toX) / 2, (fromY + toY) / 2, weightLabel, wcslen(weightLabel));
        }
    }
}

void ColorGraph(HDC hdc, RECT rect)
{
    graph.ColorGraph();
    int radius = 20;
    int centerX = (rect.right - rect.left) / 2;
    int centerY = (rect.bottom - rect.top) / 2;
    int circleRadius = min(rect.right - rect.left, rect.bottom - rect.top) / 3;
    int vertexCount = graph.GetVertexCount();
    graph.ColorGraph();
    if (vertexCount == 0)
        return;

    std::vector<std::pair<int, int>> vertexPositions(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        double angle = i * 2 * 3.141592653589793 / vertexCount;
        int x = centerX + static_cast<int>(circleRadius * cos(angle));
        int y = centerY + static_cast<int>(circleRadius * sin(angle));

        vertexPositions[i] = { x, y };


        Vertex<int>* vertex = graph.GetVertex(i + 1);
        int color = vertex->GetColor();


        COLORREF colorRef = RGB(255, 255, 255);  
        if (color == 0)
            colorRef = RGB(255, 0, 0); 
        else if (color == 1)
            colorRef = RGB(0, 255, 0);
        else if (color == 2)
            colorRef = RGB(0, 0, 255); 
        else if (color == 3)
            colorRef = RGB(255, 255, 0);
        else if (color == 4)
            colorRef = RGB(255, 165, 0);
        else if (color == 5)
            colorRef = RGB(255, 0, 255);

        HBRUSH hBrush = CreateSolidBrush(colorRef);
        SelectObject(hdc, hBrush);
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
        DeleteObject(hBrush);

        wchar_t id[10];
        swprintf_s(id, 10, L"%d", i + 1);
        TextOut(hdc, x - 5, y - 5, id, wcslen(id));
    }

    for (int i = 0; i < vertexCount; ++i)
    {
        Vertex<int>* vertex = graph.GetVertex(i + 1);
        const DictionaryOnSequence<int, int>& outgoings = vertex->GetOutgoings();

        for (int j = 0; j < outgoings.GetCount(); ++j)
        {
            int toId = outgoings.GetKeyAtIndex(j);
            int fromX = vertexPositions[i].first;
            int fromY = vertexPositions[i].second;
            int toX = vertexPositions[toId - 1].first;
            int toY = vertexPositions[toId - 1].second;

            MoveToEx(hdc, fromX, fromY, nullptr);
            LineTo(hdc, toX, toY);

            int arrowSize = 10;
            double angle = atan2(toY - fromY, toX - fromX);
            int arrowX1 = toX - static_cast<int>(arrowSize * cos(angle - 3.141592653589793 / 6));
            int arrowY1 = toY - static_cast<int>(arrowSize * sin(angle - 3.141592653589793 / 6));
            int arrowX2 = toX - static_cast<int>(arrowSize * cos(angle + 3.141592653589793 / 6));
            int arrowY2 = toY - static_cast<int>(arrowSize * sin(angle + 3.141592653589793 / 6));

            MoveToEx(hdc, toX, toY, nullptr);
            LineTo(hdc, arrowX1, arrowY1);
            MoveToEx(hdc, toX, toY, nullptr);
            LineTo(hdc, arrowX2, arrowY2);

            wchar_t weightLabel[10];
            swprintf_s(weightLabel, 10, L"%d", outgoings.Get(toId));
            TextOut(hdc, (fromX + toX) / 2, (fromY + toY) / 2, weightLabel, wcslen(weightLabel));
        }
    }
}

