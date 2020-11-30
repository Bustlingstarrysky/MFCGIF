#pragma once

#include "GalaxyIncludes.h"
#include "第三方代码/大恒相机/Camera.h"
// MFC摄像机信息 对话框

class MFC摄像机信息 : public CDialogEx
{
	DECLARE_DYNAMIC(MFC摄像机信息)

public:
	MFC摄像机信息(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFC摄像机信息();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_SETMSG_Dlg
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//void SetTEXT();
	afx_msg void OnEnChangeEdit1();
	//void set(CGXDevicePointer*);
	void SetTEXT();
	//WE::DAHENG DA;
	//得到信息
	CGXDevicePointer* CDG;//把流给你,然后就可以无法无天了 指针的CDC
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBreak();
};
