#pragma once
#include <array>
//#include"CMFC_SET_Dlg.h"
#include"MFC_SET_DLG.h"
// MFC_PANEL_Dlg 对话框

class MFC_PANEL_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_PANEL_Dlg)
public:
	MFC_PANEL_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFC_PANEL_Dlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_PANEL_Dlg
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	static void DRAWPIC(int, CString, CDialogEx*);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

	std::array<CRect, 4> RectArray;
	static void MYHIDE(MFC_PANEL_Dlg*);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CComboBox _ComTheme;

	MFC_SET_DLG  _cmfcsetdlg;
	afx_msg void OnCbnSelchangeComtheme();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBreak();
	afx_msg void OnBnClickedOpencamara();
	afx_msg void OnBnClickedClosecamrar();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCamapic();
	afx_msg void OnBnClickedMypicture();
	afx_msg void OnBnClickedCmrset();
};
