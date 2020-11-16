#include "pch.h"

#include "lucency.h"

void WE::lucency(UINT8 r, UINT8 g, UINT8 b, CDialogEx* dlg) {
	COLORREF maskColor = RGB(r, g, b);   //掩码颜色

	SetWindowLong(dlg->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(dlg->GetSafeHwnd(), GWL_EXSTYLE) | 0x80000);  //设定窗体使用扩展模式
	HINSTANCE hInst = LoadLibrary(L"User32.DLL");

	if (hInst) {
		typedef BOOL(WINAPI* MYFUNC)(HWND, COLORREF, BYTE, DWORD);
		MYFUNC AlphaFunc = NULL;
		AlphaFunc = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (AlphaFunc)AlphaFunc(dlg->GetSafeHwnd(), maskColor, 255, 1);                   //将与掩码颜色相同的窗体部分置为透明
		FreeLibrary(hInst);
	}

	//	_MfcBANTOUMINGDlg.Create(IDD_BANTOUMING_DIALOG, this);
		//_MfcBANTOUMINGDlg.ShowWindow(SW_SHOW);

	//	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void WE::changelucency(UINT8 i, CDialogEx* dlg) {
	SetWindowLong(dlg->m_hWnd, GWL_EXSTYLE, GetWindowLong(dlg->m_hWnd, GWL_EXSTYLE) ^ 0x80000);
	HINSTANCE  hInst = LoadLibrary(L"User32.DLL");
	if (hInst != NULL) {
		typedef BOOL(WINAPI* MYFUNC)(HWND, COLORREF, BYTE, DWORD);

		MYFUNC pFunc = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (pFunc != NULL) {
			pFunc(dlg->m_hWnd, 0, i, 2);//透明度
		}
		FreeLibrary(hInst);
		hInst = NULL;
	}
}