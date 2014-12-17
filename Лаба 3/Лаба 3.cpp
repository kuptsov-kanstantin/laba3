// Лаба 3.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Лаба 3.h"

#define MAX_LOADSTRING 100
/*
#if defined _M_X64
#pragma comment(lib, "hookDLL.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "hookDLL.x86.lib")
#endif
*/
// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

HHOOK g_hHook = NULL; //A handle to a hook. 
HMODULE g_hHookLib; //дескриптор на файл библиотеки
HOOKPROC g_hHookCbt = NULL; //дескриптор функции, перегруж. из библиотеки


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (g_hHookLib = LoadLibrary(L"hookDLL.dll")){
		g_hHookCbt = (HOOKPROC)GetProcAddress(g_hHookLib, "HOOK");
	}/*else{
		MessageBox(NULL, L"Не могу найти хук!", L"Ошибка", MB_ICONERROR);
		return 0;
	}*/

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow)){
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3));




	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
HWND  hwndMain;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   hwndMain = hWnd;
   if (!hWnd){
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

VOID CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime){

}
void kkkk(){
	HWINEVENTHOOK g;
//	WinEvents d;
	WINEVENTPROC vl;
	//WinEventProc();
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//


/****************************************************************
Процедура ловушки WH_CBT
****************************************************************/
#define NUMHOOKS 7

// Глобальные переменные

typedef struct _MYHOOKDATA{
	int nType;
	HOOKPROC hkprc;
	HHOOK hhook;
} MYHOOKDATA;

MYHOOKDATA myhookdata[NUMHOOKS];
enum {
	ID_LABEL = 1, ID_ONE, ID_TWO, ID_THREE, ID_FOUR
};
HWND  one, two, three, four;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message){		
	case WM_CREATE:{
					   one = CreateWindow(L"Button", L"Включение хука", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 140, 150, 150, 25, hWnd, (HMENU)ID_ONE, hInst, 0);
					   two = CreateWindow(L"Button", L"Выключение хука", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 140 + 150 + 5, 150, 150, 25, hWnd, (HMENU)ID_TWO, hInst, 0);
					   break; 
	}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case ID_ONE:{
						if (g_hHook == NULL){
							g_hHook = SetWindowsHookEx(WH_CBT, g_hHookCbt, g_hHookLib, 0);
							if (g_hHook == NULL){
								MessageBox(hWnd, TEXT("ОШИБКА!"), TEXT("HOOK"), 0);
							}
							else{
								MessageBox(hWnd, TEXT("Hook Start"), TEXT("HOOK"), 0);
							}

						}
						break; 
		}	
		case ID_TWO:{
						if (g_hHook != NULL){
							UnhookWindowsHookEx(g_hHook);
							g_hHook = NULL;
							MessageBox(hWnd, TEXT("Hook Stop"), TEXT("HOOK"), 0);
						}
						break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	UNREFERENCED_PARAMETER(lParam);
	switch (message){
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL){
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
