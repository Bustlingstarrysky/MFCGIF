// MFCDlg.h: 头文件
//

#pragma once
#include "第三方代码/gif/PictureEX.h"
#include "第三方代码/gif/MyWay.h"
#include "第三方代码/gif/MyWayGifControl.h"
// CMFCDlg 对话框
#include "第三方代码/implant/implant.h"
#include "MFCHOMEGIF.h"
#include "第三方代码/mp3/AudioClip.h"
#include "第三方代码/主题/changetheme.hpp"
#include "thread"
//#include "第三方代码/窗口动画/CDlgFlash.h"
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

	static void BREAK(CMFCDlg*);

	// 实现
protected:
	HICON m_hIcon;
	MFCHOMEGIF _GIFDLG;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

	//	CPictureEx ceshi;
public:
	//CPictureEX ceshi;
	WE::MyWayGifControl _GIF;

	afx_msg void OnDestroy();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
