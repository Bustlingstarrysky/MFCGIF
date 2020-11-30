#pragma once
#include "第三方代码/大恒相机/Camera.h"

// MFC_PIC_COM_Dlg 对话框

class MFC_PIC_COM_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_PIC_COM_Dlg)

public:
	MFC_PIC_COM_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFC_PIC_COM_Dlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_PICTURECOM_Dlg
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBreak();	//子类要给父类通信,

	//这样不久做出来了

	CGXDevicePointer* CDG;//把流给你,然后就可以无法无天了 指针的CDC

	void SetTEXT();

	CComboBox _PixelFormat;
	CComboBox _TestPattern;
	CComboBox _PixelSize;
	afx_msg void OnEnChangeWidth();
	afx_msg void OnEnChangeHeight();
	afx_msg void OnCbnSelchangePixelformat();
	afx_msg void OnCbnSelchangePixelsize();
	afx_msg void OnCbnSelchangeTestpattern();
};
