// hookDLL.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

#include <strsafe.h>
#include <string>

using namespace std;
	HWND hWnd;
LRESULT CALLBACK HOOK(int nCode, WPARAM wParam, LPARAM lParam){
	HRESULT hResult;
	HKEY reestr_k;
	LPTSTR Reget = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, 500);
	DWORD RegetSize = 500;
	DWORD RegetPath = sizeof(Reget);
	RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Hook_ker"), 0, KEY_READ | KEY_QUERY_VALUE, &reestr_k);
	RegQueryValueEx(reestr_k, NULL, NULL, NULL, (LPBYTE)Reget, &RegetSize);
	RegCloseKey(reestr_k);

	if (nCode < 0){
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
	char str[80];
	sprintf_s(str, "%d", LOWORD(lParam));
	TCHAR tzTitle[MAX_PATH];
	GetWindowText((HWND)wParam, tzTitle, MAX_PATH);

	HWND hwnd;
	hwnd = GetForegroundWindow();
	GetWindowText(hwnd, tzTitle, 100);

	switch (LOWORD(nCode)){

	case HCBT_SYSCOMMAND:{
		switch (LOWORD(wParam)){

		case SC_CLOSE:{
		//	MessageBox(hWnd, (tzTitle), TEXT("123"), 0);
			if (lstrcmpi(Reget, tzTitle) == 0){
				return 1;
			}
			break;
		}
		}
		break;
	}


	}
	return 0;
}