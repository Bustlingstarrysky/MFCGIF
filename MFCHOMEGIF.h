#pragma once
#include "第三方代码/gif/MyWay.h"
#include "MFC_PANEL_Dlg.h"
#include "MFC_HALCON_Dlg.h"
//#include "MFCLIGHTDlg.h"
//#include "COCX1.h"
//#include "COCX.h"

#include "MFC_LIGHT_Dlg.h"

// MFCHOMEGIF 对话框

class MFCHOMEGIF : public CDialogEx
{
	DECLARE_DYNAMIC(MFCHOMEGIF)

public:
	MFCHOMEGIF(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFCHOMEGIF();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_HOME_GIF
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()

private:
	WE::GIF_OpenCv _GIF_SNOW;

	MFC_PANEL_Dlg _PALEN;
	MFC_HALCON_Dlg _HALCON;
	MFC_LIGHT_Dlg _Light;

public:
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//COCX _COCX;
	//COCX _MP3OCX;
//	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	static void DRAW(CString, CDialogEx*);
	static void DRAWPIC(int, CString, CDialogEx*);
};
