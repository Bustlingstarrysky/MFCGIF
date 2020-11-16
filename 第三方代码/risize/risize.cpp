#include "pch.h"
#include "../../pch.h"

#include "riseze.h"

void WE::resize(CDialogEx* dlg, POINT* Old) {//也就是说需要保留
	float fsp[2];
	POINT Newp;
	CRect recta;
	dlg->GetClientRect(&recta);
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / Old->x;
	fsp[1] = (float)Newp.y / Old->y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint;
	CPoint OldBRPoint, BRPoint;
	HWND  hwndChild = ::GetWindow(dlg->m_hWnd, GW_CHILD);
	while (hwndChild) {
		woc = ::GetDlgCtrlID(hwndChild);
		dlg->GetDlgItem(woc)->GetWindowRect(Rect);
		dlg->ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x * fsp[0]);
		TLPoint.y = long(OldTLPoint.y * fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x * fsp[0]);
		BRPoint.y = long(OldBRPoint.y * fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		dlg->GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	Old->x = Newp.x;
	Old->y = Newp.y;
}

void WE::Oldpoint(CDialogEx* Dlg, POINT* Old) {
	CRect rect;
	Dlg->GetClientRect(&rect);//取客户区大小
	Old->x = rect.right - rect.left;
	Old->y = rect.bottom - rect.top;// 又不丑，不丑把，又很抽 实现了初始
}