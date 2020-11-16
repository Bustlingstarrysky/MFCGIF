#pragma once

#ifndef DRAWDRAW_H_
#define DRAWDRAW_H_

namespace WE {
	namespace Drawpic {
		void DRAWDRAW(int ID, CString& path, CDialog* Dlg);
		void DRAWDRAWDC(int ID1, int ID2, CString& path, CDialog* Dlg);
		void DRAWDRAWDC(CRect* rect, CString& path, CDialog* Dlg);
		void DRAWDRAWDC(int ID, CString& path, CDialog* Dlg);
		void DRAWDRAWDC(int ID, CImage& image, CDialogEx* Dlg);
		void DRAWDRAW(int ID, CImage& path, CDialog* Dlg);

		//void DRAWDRAW(int ID, HWND hwnd, CString& path);
	}
}

#endif
