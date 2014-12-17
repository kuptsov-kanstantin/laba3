// hookDLL.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

#include <strsafe.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

LRESULT CALLBACK HOOK(int nCode, WPARAM wParam, LPARAM lParam){
	STRSAFE_LPCWSTR szBuf[128];

	STRSAFE_LPWSTR szCode;
	HDC hdc;
	static int c = 0;
	size_t cch;
	size_t * pcch;
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
	switch (LOWORD(lParam)){
	case SW_MINIMIZE:{
						 if (lstrcmpi(Reget, tzTitle) == 0){
							 return 1;
						 }
						 break;
	}
	}
	return 0;
}