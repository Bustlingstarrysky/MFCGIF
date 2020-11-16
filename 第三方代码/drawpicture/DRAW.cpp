#include "pch.h"
//#include "../pch.h"

#include "DRAW.h"

void WE::Drawpic::DRAWDRAW(int ID, CString& path, CDialog* Dlg) {//�ؼ���
	CImage image;
	image.Load(path);
	CRect rect;
	Dlg->GetDlgItem(ID)->GetClientRect(&rect);
	//Dlg->ScreenToClient(&rect);
	auto picDC = Dlg->GetDlgItem(ID)->GetDC();
	::SetStretchBltMode(picDC->m_hDC, HALFTONE);
	::SetBrushOrgEx(picDC->m_hDC, 0, 0, NULL);
	image.Draw(picDC->m_hDC, rect);
	Dlg->ReleaseDC(picDC);
}

void WE::Drawpic::DRAWDRAWDC(int ID1, int ID2, CString& path, CDialog* Dlg) {//������
	CRect rect_1, rect_2;
	Dlg->GetDlgItem(ID1)->GetWindowRect(&rect_1);
	Dlg->ScreenToClient(&rect_1);
	Dlg->GetDlgItem(ID2)->GetWindowRect(&rect_2);
	Dlg->ScreenToClient(&rect_2);
	CRect rect(rect_1.TopLeft(), rect_2.BottomRight());
	CImage image;
	image.Load(path);
	auto picDC = Dlg->GetDC();
	::SetStretchBltMode(picDC->m_hDC, HALFTONE);
	::SetBrushOrgEx(picDC->m_hDC, 0, 0, NULL);
	image.Draw(picDC->m_hDC, rect);
	Dlg->ReleaseDC(picDC);
}

void WE::Drawpic::DRAWDRAWDC(CRect* rect, CString& path, CDialog* Dlg) {//������
	CImage image;
	image.Load(path);
	auto picDC = Dlg->GetDC();
	::SetStretchBltMode(picDC->m_hDC, HALFTONE);
	::SetBrushOrgEx(picDC->m_hDC, 0, 0, NULL);
	image.Draw(picDC->m_hDC, *rect);
	Dlg->ReleaseDC(picDC);
}

void WE::Drawpic::DRAWDRAWDC(int ID, CString& path, CDialog* Dlg) {
	CImage image;
	image.Load(path);
	CRect rect;
	Dlg->GetDlgItem(ID)->GetWindowRect(&rect);
	Dlg->ScreenToClient(&rect);
	//auto picDC = Dlg->GetDC();
	auto picDC = ::GetDC(Dlg->m_hWnd);
	::SetStretchBltMode(picDC, HALFTONE);
	::SetBrushOrgEx(picDC, 0, 0, NULL);
	image.Draw(picDC, rect);
	::ReleaseDC(Dlg->m_hWnd, picDC);
}

void WE::Drawpic::DRAWDRAW(int ID, CImage& image, CDialog* Dlg) {
	CRect rect;
	Dlg->GetDlgItem(ID)->GetClientRect(&rect);
	//Dlg->ScreenToClient(&rect);
	auto picDC = ::GetDC(Dlg->m_hWnd);
	::SetStretchBltMode(picDC, HALFTONE);
	::SetBrushOrgEx(picDC, 0, 0, NULL);
	image.Draw(picDC, rect);
	::ReleaseDC(Dlg->m_hWnd, picDC);
}