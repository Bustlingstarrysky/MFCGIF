#pragma once
#include "第三方代码/大恒相机/Camera.h"
#include "MFC摄像机信息.h"
#include"MFC_PIC_COM_Dlg.h"
// MFC_SET_DLG 对话框

class MFC_SET_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_SET_DLG)

public:
	MFC_SET_DLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFC_SET_DLG();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_SET_DLG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	GxIAPICPP::gxdeviceinfo_vector vectorDeviceInfo;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFind();
	CComboBox _ComList;
	afx_msg void OnBnClickedSetmsg();

	MFC摄像机信息* _MFC摄像机信息;
	MFC_PIC_COM_Dlg* _MFCPICCOM;

	//	void SetTEXT();
	CGXDevicePointer ObjDevicePtr;// 把这个给它就行了
	CGXStreamPointer ObjStreamPtr;

	//给的是流,流打开了

	//WE::DAHENG daheng;
	virtual BOOL OnInitDialog();
	// 通知父窗口打开摄像机,同时,可以
	static void OpenCamera_SXJXX(MFC_SET_DLG*, MFC摄像机信息*);
	static void CloseCamera_SXJXX(MFC_SET_DLG*, MFC摄像机信息*);
	static void OpenCamera_PICCOM(MFC_SET_DLG*, MFC_PIC_COM_Dlg*);
	static void CloseCamera_PICCOM(MFC_SET_DLG*, MFC_PIC_COM_Dlg*);
	void OpeningCamera();
	void CloseCamera();
	afx_msg void OnBnClickedSeting();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBreak();
	//	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedPiccom();
};
