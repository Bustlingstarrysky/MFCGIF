#include "pch.h"
#include "ERROR.h"

void WE::MY_MFC_ERROR::MyError(int i) {
	switch (i) {
	case 0: AfxMessageBox(TEXT(MY_ERROR__0), MB_OK); break;
	case -1: AfxMessageBox(TEXT(MY_ERROR__1), MB_OK); break;
	case -2: AfxMessageBox(TEXT(MY_ERROR__), MB_OK); break;
	case -3: AfxMessageBox(TEXT(MY_ERROR__3), MB_OK); break;
	case -4: AfxMessageBox(TEXT(MY_ERROR__4), MB_OK); break;
	case -5: AfxMessageBox(TEXT(MY_ERROR__5), MB_OK); break;
	case -6: AfxMessageBox(TEXT(MY_ERROR__6), MB_OK); break;
	case -7: AfxMessageBox(TEXT(MY_ERROR__7), MB_OK); break;
	case -8: AfxMessageBox(TEXT(MY_ERROR__8), MB_OK); break;
	case -9: AfxMessageBox(TEXT(MY_ERROR__9), MB_OK); break;
	case -10: AfxMessageBox(TEXT(MY_ERROR__10), MB_OK); break;
	case -11: AfxMessageBox(TEXT(MY_ERROR__11), MB_OK); break;
	case -12: AfxMessageBox(TEXT(MY_ERROR__12), MB_OK); break;
	case -13: AfxMessageBox(TEXT(MY_ERROR__13), MB_OK); break;
	case -14: AfxMessageBox(TEXT(MY_ERROR__14), MB_OK); break;
	default:AfxMessageBox(TEXT(MY_ERROR__), MB_OK); break;
	}
	//нчак,
}