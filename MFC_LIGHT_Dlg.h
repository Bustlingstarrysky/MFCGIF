#pragma once
#include "第三方代码/modbus/Light.h"

// MFC_LIGHT_Dlg 对话框

class MFC_LIGHT_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_LIGHT_Dlg)

public:
	MFC_LIGHT_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFC_LIGHT_Dlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_LIGHT_DLG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedFindcom();
	afx_msg void OnBnClickedOpeningcom();
	afx_msg void OnBnClickedClosingcom();
	afx_msg void OnBnClickedAllopening();
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedBlue();
	afx_msg void OnBnClickedAllclosing();
	CComboBox _ComList;
	Light _Light;
	CComboBox _ComLight;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar _CScroll;
	//int _LightIntNum;
	int _LightIntNum;
	afx_msg void OnEnChangeNum();
	afx_msg void OnCbnSelchangeComlight();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
