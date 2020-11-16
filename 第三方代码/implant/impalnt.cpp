#include "pch.h"

#include "implant.h"

void WE::MTVOID::IMPlant(int ID, CDialog* MTTHIS) {
	//CRect rect;
	HWND hwnd = AfxGetApp()->m_pMainWnd->m_hWnd;//������
	hwnd = GetDlgItem(hwnd, ID);//id
	CRect rect;
	GetWindowRect(hwnd, &rect);
	ScreenToClient(AfxGetMainWnd()->m_hWnd, LPPOINT(&rect));

	MTTHIS->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
	MTTHIS->ShowWindow(SW_SHOW);
}

void WE::MTVOID::IMPlant(int ID, CDialogEx* Dlg, CDialogEx* MTTHIS) {//�����dlg ��Ĭ��
	CRect rect;
	Dlg->GetDlgItem(ID)->GetWindowRect(&rect);//得到ID的RECT //

	//Sleep(100);
	//Dlg->ScreenToClient(&rect);
	MTTHIS->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
	MTTHIS->ShowWindow(SW_SHOW);
}

void WE::MTVOID::IMPlant_TESHI(int ID, CDialogEx* Dlg, CDialogEx* MTTHS) {
	CRect rect;
	Dlg->GetDlgItem(ID)->GetWindowRect(&rect);//得到ID的RECT //
	CRect MyRect;
	MTTHS->GetClientRect(MyRect);
	//Sleep(100);
	//Dlg->ScreenToClient(&rect);
	MTTHS->MoveWindow(rect.left, rect.top, MyRect.Width(), MyRect.Height());
	MTTHS->ShowWindow(SW_SHOW);
}

void WE::MTVOID::IMPlant(CRect& Rect, CDialogEx* Dlg, CDialogEx* MTTHIS) {
	MTTHIS->MoveWindow(Rect.left, Rect.top, Rect.Width(), Rect.Height());
	MTTHIS->ShowWindow(SW_SHOW);
}