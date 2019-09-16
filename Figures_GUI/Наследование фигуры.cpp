// Наследование фигуры.cpp : Определяет точку входа для приложения.
//


#include "stdafx.h"
#include "Наследование фигуры.h"
#include "Auxiliary_functions.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
CHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
CHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND GlobalWind;
HWND hList;
std::list<std::list<KLoc*>::iterator> figures_to_delete;

int new_angle;//to perform rotation
double explode_coefficient;
std::tuple<int, int> tuple_for_coordinates;

static std::list<KLoc*> figures;
static std::list<KPoint> points;
static std::list<KShape> rectangles;
static std::list<KSquare> squares;
static std::list<KCircle> circles;
static std::list<KTriangle> triangles;
static std::list<Parallelogram> parallelograms;
static std::list<Extraparallelogram> diagparallelograms;
static std::list<ExtraCircle> chord_circles;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    PointCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PointShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PointMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PointShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PointShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PointChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PointDelete(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    RectangleCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleRotate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleExplode(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RectangleDelete(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    SquareCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareRotate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareExplode(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SquareDelete(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    CircleCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CircleShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CircleMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CircleShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CircleShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CircleChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CircleExplode(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CircleDelete(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    TriangleCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleRotate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleExplode(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TriangleDelete(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    ParallelogramCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramRotate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramExplode(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ParallelogramDelete(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    DiagparallelogramCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramChangeColor2(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramRotate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramExplode(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiagparallelogramDelete(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK	ChordCircleCreate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleShowHide(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleMove(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleShiftX(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleShiftY(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleChangeColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleRotate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleExplode(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChordCircleDelete(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    // Инициализация глобальных строк
    LoadStringA(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringA(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEA(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExA(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowA(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); 
   GlobalWind = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case IDM_POINTCREATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_POINT_CREATE), hWnd, PointCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_POINTMOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, PointMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_POINTSHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, PointShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_POINTSHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, PointShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_POINTCHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, PointChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_POINTDELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, PointDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTANGLE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_RECTANGLE), hWnd, RectangleCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTSHOWHIDE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleShowHide);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTMOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTSHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTSHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTCHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTROTATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleRotate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECT_EXPLODE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleExplode);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_RECTDELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, RectangleDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUARE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SQUARE), hWnd, SquareCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUARESHOWHIDE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareShowHide);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUAREMOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUARESHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUARESHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUARECHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUAREROTATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareRotate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUARE_EXPLODE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareExplode);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_SQUAREDELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, SquareDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CIRCLE), hWnd, CircleCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLESHOWHIDE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, CircleShowHide);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLEMOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, CircleMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLESHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, CircleShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLESHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, CircleShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLECHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, CircleChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLE_EXPLODE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, CircleExplode);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CIRCLEDELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, CircleDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_TRIANGLE), hWnd, TriangleCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLESHOWHIDE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleShowHide);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLEMOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLESHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLESHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLECHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLEROTATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleRotate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLE_EXPLODE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleExplode);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_TRIANGLEDELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, TriangleDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_CREATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_PARALLELOGRAM), hWnd, ParallelogramCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_SHOW_HIDE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramShowHide);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_MOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_SHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_SHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_CHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_ROTATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramRotate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_EXPLODE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramExplode);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_PARALLELOGRAM_DELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ParallelogramDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_CREATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_PARALLELOGRAM), hWnd, DiagparallelogramCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_SHOW_HIDE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramShowHide);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_MOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_SHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_SHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_CHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_CHANGECOLOR2:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramChangeColor2);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_ROTATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramRotate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_EXPLODE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramExplode);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_DIAG_PARALLELOGRAM_DELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, DiagparallelogramDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_CREATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHORD_CIRCLE), hWnd, ChordCircleCreate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_SHOWHIDE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleShowHide);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_MOVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleMove);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_SHIFTX:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleShiftX);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_SHIFTY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleShiftY);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_CHANGECOLOR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleChangeColor);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_ROTATE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleRotate);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_EXPLODE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleExplode);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_CHORD_CIRCLE_DELETE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE), hWnd, ChordCircleDelete);
				InvalidateRect(GlobalWind, 0, TRUE);
				break;
			case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			for (auto it = figures.begin(); it != figures.end(); it++)
			{
				if ((*it)->getcolor() == -1)
				{
					const char* classname = typeid(**it).name();
					int x = (*it)->get_x_coord(), y = (*it)->get_y_coord();
					if (strcmp(classname, "class KPoint") == 0)
						points.erase(std::find_if(points.begin(), points.end(), [](KPoint p) {return p.getcolor() == -1; }));
					if (strcmp(classname, "class KShape") == 0)
						rectangles.erase(std::find_if(rectangles.begin(), rectangles.end(), [](KShape p) {return p.getcolor() == -1; }));
					if (strcmp(classname, "class KSquare") == 0)
						squares.erase(std::find_if(squares.begin(), squares.end(), [](KSquare p) {return p.getcolor() == -1; }));
					if (strcmp(classname, "class KCircle") == 0)
						circles.erase(std::find_if(circles.begin(), circles.end(), [](KCircle p) {return p.getcolor() == -1; }));
					if (strcmp(classname, "class KTriangle") == 0)
						triangles.erase(std::find_if(triangles.begin(), triangles.end(), [](KTriangle p) {return p.getcolor() == -1; }));
					if (strcmp(classname, "class Parallelogram") == 0)
						parallelograms.erase(std::find_if(parallelograms.begin(), parallelograms.end(), [](Parallelogram p) {return p.getcolor() == -1; }));
					if (strcmp(classname, "class Extraparallelogram") == 0)
						diagparallelograms.erase(std::find_if(diagparallelograms.begin(), diagparallelograms.end(), [](Extraparallelogram p) {return p.getcolor() == -1; }));
					if (strcmp(classname, "class ExtraCircle") == 0)
						chord_circles.erase(std::find_if(chord_circles.begin(), chord_circles.end(), [](ExtraCircle p) {return p.getcolor() == -1; }));
					figures_to_delete.push_back(it);
					std::string strdeleted("Удаление элемента типа ");
					strdeleted.append(classname).append(" с координатами центра X=").append(std::to_string(x)).append(" Y=").append(
						std::to_string(y)).append(" проведено успешно");
					MessageBox(hWnd, strdeleted.c_str(), 0, MB_OK);
					continue;
				}
				(*it)->Draw(hdc);
			}
			if (!figures_to_delete.empty())
			{
				for (auto it = figures_to_delete.begin(); it != figures_to_delete.end(); it++)
					figures.erase(*it);
				figures_to_delete.clear();
			}
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


//Функции диалоговых окон
INT_PTR CALLBACK MoveWhere(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			tuple_for_coordinates = { -1, -1 };
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDOK:
		{
			UINT xpos, ypos;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			tuple_for_coordinates = { xpos, ypos };
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK ShiftXWhere(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			tuple_for_coordinates = { -1, -1 };
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDOK:
		{
			int xpos;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
			tuple_for_coordinates = { xpos, 0 };
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ShiftYWhere(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			tuple_for_coordinates = { -1, -1 };
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDOK:
		{
			int ypos;
			ypos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
			tuple_for_coordinates = { 0, ypos };
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RotateFigure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			new_angle = -1;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDOK:
		{
			new_angle = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ExplodeFigure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			explode_coefficient = -1;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDOK:
		{
			char explode_coefficient_str[5];
			GetDlgItemText(hDlg, IDC_EDIT1, explode_coefficient_str, 5);
			explode_coefficient = atof(explode_coefficient_str);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}



INT_PTR CALLBACK PointCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			if (LOWORD(wParam) == IDCANCEL)
			{
				MessageBox(GlobalWind, "Точка не была создана", "Внимание", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
			break;
		case IDOK:
		{
			UINT xpos, ypos;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			points.push_front(KPoint(xpos, ypos, 0));
			figures.push_back(&(*(points.begin())));
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK PointMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_points(hList, points);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<KPoint>::iterator point = std::next(points.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					point->ShiftX(x);
					point->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция точки не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK PointShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_points(hList, points);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<KPoint>::iterator point = std::next(points.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1)
				{
					point->ShiftX(x);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция точки не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK PointShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_points(hList, points);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<KPoint>::iterator point = std::next(points.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (y > -1)
				{
					point->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция точки не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK PointChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_points(hList, points);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KPoint>::iterator point = std::next(points.begin(), numb);
				
				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = point->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = point->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp)==FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				point->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK PointDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_points(hList, points);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KPoint>::iterator point = std::next(points.begin(), numb);
				point->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}



INT_PTR CALLBACK RectangleCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(GlobalWind, "Прямоугольник не был создан", "Внимание", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			UINT xpos, ypos, cx, cy, angle;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			cx = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			cy = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			angle = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			try {
				rectangles.push_front(KShape(xpos, ypos, cx, cy, angle, 0));
				figures.push_back(&(*(rectangles.begin())));
			}
			catch (std::exception &ex) {
				std::string cause("Фигура не была создана по причине:\n"); cause.append(ex.what());
				MessageBox(hDlg, cause.c_str(), 0, MB_OK);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK RectangleShowHide(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);
				if (rectangle->getcolor() == hide)
					rectangle->Show();
				else
					rectangle->Hide();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK RectangleMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					rectangle->Move(x, y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция прямоугольника не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RectangleShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1)
				{
					rectangle->ShiftX(x);

				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция прямоугольника не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RectangleShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (y > -1)
				{
					rectangle->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция прямоугольника не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RectangleChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);

				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = rectangle->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = rectangle->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				rectangle->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RectangleRotate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ROTATE), hDlg, RotateFigure);
				try {
					rectangle->Rotate(new_angle);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Вращение не было произведено, т.к одна из точек\n нового прямоугольника находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RectangleExplode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1) return (INT_PTR)FALSE;
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPLODE), hDlg, ExplodeFigure);
				if (explode_coefficient < 0)
				{
					MessageBox(GlobalWind, "Фигура не может быть растянута\nс применением такого коэффициента", "Ошибка", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}				
				try {
					rectangle->Explode(explode_coefficient);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Растяжение не было произведено, т.к одна из точек\n нового прямоугольника находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RectangleDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_rectangles(hList, rectangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KShape>::iterator rectangle = std::next(rectangles.begin(), numb);
				rectangle->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}




INT_PTR CALLBACK SquareCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(GlobalWind, "Квадрат не был создан", "Внимание", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			UINT xpos, ypos, side, angle;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			side = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			angle = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			try{
				squares.push_front(KSquare(xpos, ypos, side, angle, 0));
				figures.push_back(&(*squares.begin()));
			}
			catch (std::exception &ex) {
				std::string cause("Фигура не была создана по причине:\n"); cause.append(ex.what());
				MessageBox(hDlg, cause.c_str(), 0, MB_OK);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareShowHide(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);
				if (square->getcolor() == hide)
					square->Show();
				else
					square->Hide();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					square->Move(x, y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция квадрата не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1)
				{
					square->ShiftX(x);

				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция квадрата не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		int number = 1;
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (y > -1)
				{
					square->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция квадрата не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);

				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = square->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = square->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				square->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareRotate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ROTATE), hDlg, RotateFigure);
				try {
					square->Rotate(new_angle);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Вращение не было произведено, т.к одна из точек\n нового квадрата находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareExplode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1) return (INT_PTR)FALSE;
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPLODE), hDlg, ExplodeFigure);
				if (explode_coefficient < 0)
				{
					MessageBox(GlobalWind, "Фигура не может быть растянута\nс применением такого коэффициента", "Ошибка", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				try {
					square->Explode(explode_coefficient);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Растяжение не было произведено, т.к одна из точек\n нового квадрата находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SquareDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_squares(hList, squares);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KSquare>::iterator square = std::next(squares.begin(), numb);
				square->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}




INT_PTR CALLBACK CircleCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{	
			MessageBox(GlobalWind, "Круг не был создан", "Внимание", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			UINT xpos, ypos, radius;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			radius = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			circles.push_front(KCircle(xpos, ypos, radius, 0));
			figures.push_back(&(*circles.begin()));
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CircleShowHide(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_circles(hList, circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KCircle>::iterator circle = std::next(circles.begin(), numb);
				if (circle->getcolor() == hide)
					circle->Show();
				else
					circle->Hide();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CircleMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_circles(hList, circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<KCircle>::iterator circle = std::next(circles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					circle->Move(x, y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция круга не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CircleShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_circles(hList, circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<KCircle>::iterator circle = std::next(circles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1)
				{
					circle->ShiftX(x);

				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция круга не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CircleShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		int number = 1;
		fill_list_with_circles(hList, circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<KCircle>::iterator circle = std::next(circles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (y > -1)
				{
					circle->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция круга не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CircleChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_circles(hList, circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KCircle>::iterator circle = std::next(circles.begin(), numb);

				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = circle->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = circle->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				circle->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CircleExplode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_circles(hList, circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1) return (INT_PTR)FALSE;
				std::list<KCircle>::iterator circle = std::next(circles.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPLODE), hDlg, ExplodeFigure);
				if (explode_coefficient < 0)
				{
					MessageBox(GlobalWind, "Фигура не может быть растянута\nс применением такого коэффициента", "Ошибка", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				try {
					circle->Explode(explode_coefficient);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Растяжение не было произведено, т.к одна из точек\n нового круга находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK CircleDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_circles(hList, circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KCircle>::iterator circle = std::next(circles.begin(), numb);
				circle->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}



INT_PTR CALLBACK TriangleCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(GlobalWind, "Треугольник не был создан", "Внимание", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			UINT xpos, ypos, bottom, left, right, angle;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			bottom = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			left = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			right = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			angle = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
			try {
				triangles.push_front(KTriangle(xpos, ypos, bottom, left, right, angle, 0));
				figures.push_back(&(*triangles.begin()));
			}
			catch (std::exception &ex) {
				std::string cause("Фигура не была создана по причине:\n"); cause.append(ex.what());
				MessageBox(hDlg, cause.c_str(), 0, MB_OK);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK TriangleShowHide(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);
				if (triangle->getcolor() == hide)
					triangle->Show();
				else
					triangle->Hide();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TriangleMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					triangle->Move(x, y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция треугольника не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TriangleShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1)
				{
					triangle->ShiftX(x);

				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция треугольника не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TriangleShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		int number = 1;
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (y > -1)
				{
					triangle->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция треугольника не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TriangleChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);

				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = triangle->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = triangle->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				triangle->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TriangleRotate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;//при двойном клике не по одному из обьектов
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ROTATE), hDlg, RotateFigure);
				try {
					triangle->Rotate(new_angle);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Вращение не было произведено, т.к одна из точек\n нового треугольника находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TriangleExplode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1) return (INT_PTR)FALSE;
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPLODE), hDlg, ExplodeFigure);
				if (explode_coefficient < 0)
				{
					MessageBox(GlobalWind, "Фигура не может быть растянута\nс применением такого коэффициента", "Ошибка", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				try {
					triangle->Explode(explode_coefficient);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Растяжение не было произведено, т.к одна из точек\n нового треугольника находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TriangleDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_triangles(hList, triangles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<KTriangle>::iterator triangle = std::next(triangles.begin(), numb);
				triangle->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}



INT_PTR CALLBACK ParallelogramCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(GlobalWind, "Параллелограмм не был создан", "Внимание", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			UINT xpos, ypos, bottom, left, angle_btw_sides, angle;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			bottom = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			left = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			angle_btw_sides = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			angle = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
			try {
				parallelograms.push_front(Parallelogram(xpos, ypos, bottom, left, angle_btw_sides, angle));
				figures.push_back(&(*parallelograms.begin()));
			}
			catch (std::exception &ex) {
				std::string cause("Фигура не была создана по причине:\n"); cause.append(ex.what());
				MessageBox(hDlg, cause.c_str(), 0, MB_OK);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK ParallelogramShowHide(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);
				if (Parallelogram->getcolor() == hide)
					Parallelogram->Show();
				else
					Parallelogram->Hide();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ParallelogramMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					Parallelogram->Move(x, y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция паралелограмма не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ParallelogramShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1)
				{
					Parallelogram->ShiftX(x);

				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция параллелограмма не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ParallelogramShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		int number = 1;
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (y > -1)
				{
					Parallelogram->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция параллелограмма не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ParallelogramChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);

				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = Parallelogram->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = Parallelogram->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				Parallelogram->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ParallelogramRotate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;//при двойном клике не по одному из обьектов
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ROTATE), hDlg, RotateFigure);
				try {
					Parallelogram->Rotate(new_angle);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Вращение не было произведено, т.к одна из точек\n нового паралелограмма находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ParallelogramExplode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1) return (INT_PTR)FALSE;
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPLODE), hDlg, ExplodeFigure);
				if (explode_coefficient < 0)
				{
					MessageBox(GlobalWind, "Фигура не может быть растянута\nс применением такого коэффициента", "Ошибка", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				try {
					Parallelogram->Explode(explode_coefficient);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Растяжение не было произведено, т.к одна из точек\n нового параллелограмма находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ParallelogramDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_parallelograms(hList, parallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<Parallelogram>::iterator Parallelogram = std::next(parallelograms.begin(), numb);
				Parallelogram->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK DiagparallelogramCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(GlobalWind, "Параллелограмм не был создан", "Внимание", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			UINT xpos, ypos, bottom, left, angle_btw_sides, angle;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			bottom = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			left = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			angle_btw_sides = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			angle = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
			try {
				diagparallelograms.push_front(Extraparallelogram(xpos, ypos, bottom, left, angle_btw_sides, angle));
				figures.push_back(&(*diagparallelograms.begin()));
			}
			catch (std::exception &ex) {
				std::string cause("Фигура не была создана по причине:\n"); cause.append(ex.what());
				MessageBox(hDlg, cause.c_str(), 0, MB_OK);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK DiagparallelogramShowHide(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);
				if (Diagparallelogram->getcolor() == hide)
					Diagparallelogram->Show();
				else
					Diagparallelogram->Hide();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					Diagparallelogram->Move(x, y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция параллелограмма не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x < Diagparallelogram->get_x_coord())
				{
					Diagparallelogram->ShiftX(x);

				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция параллелограмма не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		int number = 1;
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if(y < Diagparallelogram->get_y_coord())
				{
					Diagparallelogram->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция параллелограмма не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);

				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = Diagparallelogram->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = Diagparallelogram->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				Diagparallelogram->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramChangeColor2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);

				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = Diagparallelogram->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = Diagparallelogram->getcolor2();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				Diagparallelogram->setcolor2(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramRotate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;//при двойном клике не по одному из обьектов
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ROTATE), hDlg, RotateFigure);
				try {
					Diagparallelogram->Rotate(new_angle);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Вращение не было произведено, т.к одна из точек\n нового параллелограмма находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramExplode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1) return (INT_PTR)FALSE;
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPLODE), hDlg, ExplodeFigure);
				if (explode_coefficient < 0)
				{
					MessageBox(GlobalWind, "Фигура не может быть растянута\nс применением такого коэффициента", "Ошибка", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				try {
					Diagparallelogram->Explode(explode_coefficient);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Растяжение не было произведено, т.к одна из точек\n нового параллелограмма находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DiagparallelogramDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_diagparallelograms(hList, diagparallelograms);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<Extraparallelogram>::iterator Diagparallelogram = std::next(diagparallelograms.begin(), numb);
				Diagparallelogram->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ChordCircleCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(GlobalWind, "Круг не был создан", "Внимание", MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			UINT xpos, ypos, radius, distance, angle;
			xpos = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			ypos = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			radius = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			distance = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			angle = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			chord_circles.push_front(ExtraCircle(xpos, ypos, radius, distance, angle));
			figures.push_back(&(*chord_circles.begin()));
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ChordCircleShowHide(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				if (circle->getcolor() == hide)
					circle->Show();
				else
					circle->Hide();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ChordCircleMove(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MOVE_WHERE), hDlg, MoveWhere);
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x > -1 && y > -1)
				{
					circle->Move(x, y);
				}
				else
					MessageBox(hDlg, "Координаты введены неверно, позиция круга не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ChordCircleShiftX(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTX_WHERE), hDlg, ShiftXWhere);
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (x < circle->get_x_coord())
				{
					circle->ShiftX(x);

				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция круга не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ChordCircleShiftY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		int number = 1;
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SHIFTY_WHERE), hDlg, ShiftYWhere);
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				const auto[x, y] = tuple_for_coordinates;
				if (y < circle->get_y_coord())
				{
					circle->ShiftY(y);
				}
				else
					MessageBox(hDlg, "Координата введена неверно, позиция круга не будет изменена", "Warning", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ChordCircleChangeColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				CHOOSECOLOR temp;//заполняет структуру нулями
				static COLORREF acrCustClr[16];
				static DWORD rgbCurrent = circle->getcolor();
				ZeroMemory(&temp, sizeof(temp));
				temp.lStructSize = sizeof(temp);
				temp.hwndOwner = hDlg;
				temp.lpCustColors = (LPDWORD)acrCustClr;
				temp.rgbResult = circle->getcolor();
				temp.Flags = CC_FULLOPEN | CC_RGBINIT;
				if (ChooseColor(&temp) == FALSE)
				{
					MessageBoxA(hDlg, "Ошибка при вводе цвета", "Внимание!!!", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				circle->setcolor(temp.rgbResult);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ChordCircleRotate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;//при двойном клике не по одному из обьектов
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ROTATE), hDlg, RotateFigure);
				try {
					circle->Rotate(new_angle);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Вращение не было произведено, т.к одна из точек\n нового круга находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK ChordCircleExplode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1) return (INT_PTR)FALSE;
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPLODE), hDlg, ExplodeFigure);
				if (explode_coefficient < 0)
				{
					MessageBox(GlobalWind, "Фигура не может быть растянута\nс применением такого коэффициента", "Ошибка", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				try {
					circle->Explode(explode_coefficient);
				}
				catch (std::exception) {
					MessageBox(hDlg, "Растяжение не было произведено, т.к одна из точек\n нового круга находится вне поля", 0, MB_OK);
				}
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK ChordCircleDelete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hList = GetDlgItem(hDlg, IDC_LIST1);
		fill_list_with_chord_circles(hList, chord_circles);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int numb = SendMessage(hList, LB_GETCURSEL, 0, 0);
				if (numb == -1)return (INT_PTR)FALSE;
				std::list<ExtraCircle>::iterator circle = std::next(chord_circles.begin(), numb);
				circle->Delete();
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
	}
	return (INT_PTR)FALSE;
}
