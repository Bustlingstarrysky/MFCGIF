// MFCDlg.h: 头文件
//

#pragma once
#include "第三方代码/gif/PictureEX.h"
#include "第三方代码/gif/MyWay.h"
// CMFCDlg 对话框
class CMFCDlg : public CDialogEx
{
	// 构造
public:
	CMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_MFC_DIALOG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

	//	CPictureEx ceshi;
public:
	//CPictureEX ceshi;
//	CPictureEx ceshi;
	//CPictureEx _gif;
	WE::GIF_OpenCv _GIF;
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnClose();
	afx_msg void OnDestroy();
};
