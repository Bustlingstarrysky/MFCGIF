#pragma once

// MFC_HALCON_Dlg 对话框
#include <thread>

#include "第三方代码/risize/riseze.h"
#include"HalconCpp.h"

class MFC_HALCON_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_HALCON_Dlg)

public:
	MFC_HALCON_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFC_HALCON_Dlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_HALCON_Dialog
	};
#endif
	_RESIZEOLD;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	HalconCpp::HObject  ho_Image;
	HalconCpp::HTuple  hv_WindowHandle;//句柄
	HalconCpp::HTuple  hv_AcqHandle;;//句柄

	std::thread* _THREAD;
	bool JUDEG;
	CRect rect;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	static void OpenCamara(MFC_HALCON_Dlg*);
	static void CloseCramara(MFC_HALCON_Dlg*);
	static void PICTURING(MFC_HALCON_Dlg*);
	static void RUNPICTRUE(MFC_HALCON_Dlg*);

	//afx_msg void OnEnChangeNum();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
