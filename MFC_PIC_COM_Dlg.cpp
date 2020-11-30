// MFC_PIC_COM_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC.h"
#include "MFC_PIC_COM_Dlg.h"
#include "afxdialogex.h"

#include "第三方代码/消息传递/RunMessage.hpp"
// MFC_PIC_COM_Dlg 对话框

IMPLEMENT_DYNAMIC(MFC_PIC_COM_Dlg, CDialogEx)

MFC_PIC_COM_Dlg::MFC_PIC_COM_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PICTURECOM_Dlg, pParent) {}

MFC_PIC_COM_Dlg::~MFC_PIC_COM_Dlg() {}

void MFC_PIC_COM_Dlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PixelFormat, _PixelFormat);
	DDX_Control(pDX, IDC_TestPattern, _TestPattern);
	DDX_Control(pDX, IDC_PixelSize, _PixelSize);
}

BEGIN_MESSAGE_MAP(MFC_PIC_COM_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BREAK, &MFC_PIC_COM_Dlg::OnBnClickedBreak)
	ON_EN_CHANGE(IDC_Width, &MFC_PIC_COM_Dlg::OnEnChangeWidth)
	ON_EN_CHANGE(IDC_Height, &MFC_PIC_COM_Dlg::OnEnChangeHeight)
	ON_CBN_SELCHANGE(IDC_PixelFormat, &MFC_PIC_COM_Dlg::OnCbnSelchangePixelformat)
	ON_CBN_SELCHANGE(IDC_PixelSize, &MFC_PIC_COM_Dlg::OnCbnSelchangePixelsize)
	ON_CBN_SELCHANGE(IDC_TestPattern, &MFC_PIC_COM_Dlg::OnCbnSelchangeTestpattern)
END_MESSAGE_MAP()

// MFC_PIC_COM_Dlg 消息处理程序

BOOL MFC_PIC_COM_Dlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	WE::RUNTIMING(SET_图像格式控制_Open);
	// TODO:  在此添加额外的初始化

	SetTEXT();//这个弄好了,就剩下接下来的了,对吧
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL MFC_PIC_COM_Dlg::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)// 屏蔽esc键
	{
		return TRUE;// 不作任何操作
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)// 屏蔽enter键
	{
		return TRUE;// 不作任何处理
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void MFC_PIC_COM_Dlg::OnBnClickedBreak() {
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	WE::RUNTIMING(SET_图像格式控制_Close);//运行这个函数
}

void MFC_PIC_COM_Dlg::SetTEXT() {
	CString cstr;
	cstr.Format(L"%d", (*CDG)->GetRemoteFeatureControl()->GetIntFeature("SensorWidth")->GetValue());
	GetDlgItem(IDC_SensorWidth)->SetWindowTextW(cstr);

	cstr.Format(L"%d", (*CDG)->GetRemoteFeatureControl()->GetIntFeature("SensorHeight")->GetValue());
	GetDlgItem(IDC_SensorHeight)->SetWindowTextW(cstr);

	cstr.Format(L"%d", (*CDG)->GetRemoteFeatureControl()->GetIntFeature("WidthMax")->GetValue());
	GetDlgItem(IDC_WidthMax)->SetWindowTextW(cstr);

	cstr.Format(L"%d", (*CDG)->GetRemoteFeatureControl()->GetIntFeature("HeightMax")->GetValue());
	GetDlgItem(IDC_HeightMax)->SetWindowTextW(cstr);

	cstr.Format(L"%d", (*CDG)->GetRemoteFeatureControl()->GetIntFeature("Width")->GetValue());
	GetDlgItem(IDC_Width)->SetWindowTextW(cstr);

	cstr.Format(L"%d", (*CDG)->GetRemoteFeatureControl()->GetIntFeature("Height")->GetValue());
	GetDlgItem(IDC_Height)->SetWindowTextW(cstr);

	CString c;
	c = (*CDG)->GetRemoteFeatureControl()->GetEnumFeature("PixelFormat")->GetValue();
	_PixelFormat.AddString(c);
	_PixelFormat.SetCurSel(0);

	c = (*CDG)->GetRemoteFeatureControl()->GetEnumFeature("PixelSize")->GetValue();
	_PixelSize.AddString(c);
	_PixelSize.SetCurSel(0);

	c = (*CDG)->GetRemoteFeatureControl()->GetEnumFeature("TestPattern")->GetValue();
	_TestPattern.AddString(c);
	_TestPattern.SetCurSel(0);

	for (auto& i : (*CDG)->GetRemoteFeatureControl()->GetEnumFeature("PixelFormat")->GetEnumEntryList()) {
		CString cs;
		cs = i;
		_PixelFormat.AddString(cs);
	}

	//NEXT
	for (auto& i : (*CDG)->GetRemoteFeatureControl()->GetEnumFeature("PixelSize")->GetEnumEntryList()) {
		CString cs;
		cs = i;
		_PixelSize.AddString(cs);
	}
	for (auto& i : (*CDG)->GetRemoteFeatureControl()->GetEnumFeature("TestPattern")->GetEnumEntryList()) {
		CString cs;
		cs = i;
		_TestPattern.AddString(cs);
	}
}

void MFC_PIC_COM_Dlg::OnEnChangeWidth() {
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	//获取自己的数值
	int i = GetDlgItemInt(IDC_Width);

	if (i > (*CDG)->GetRemoteFeatureControl()->GetIntFeature("WidthMax")->GetValue()) {
		SetDlgItemInt(IDC_Width, (*CDG)->GetRemoteFeatureControl()->GetIntFeature("WidthMax")->GetValue());
		return;
	}
	(*CDG)->GetRemoteFeatureControl()->GetIntFeature("Width")->SetValue(i);
	// TODO:  在此添加控件通知处理程序代码
}

void MFC_PIC_COM_Dlg::OnEnChangeHeight() {
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	int i = GetDlgItemInt(IDC_Height);

	if (i > (*CDG)->GetRemoteFeatureControl()->GetIntFeature("HeightMax")->GetValue()) {
		SetDlgItemInt(IDC_Height, (*CDG)->GetRemoteFeatureControl()->GetIntFeature("HeightMax")->GetValue());
		return;
	}

	(*CDG)->GetRemoteFeatureControl()->GetIntFeature("Height")->SetValue(i);

	// TODO:  在此添加控件通知处理程序代码
}

void MFC_PIC_COM_Dlg::OnCbnSelchangePixelformat() {
	// TODO: 在此添加控件通知处理程序代码
	//获取cstring
	//_PixelFormat.GetCount(0);
	//
	CString cstr;
	GetDlgItem(IDC_PixelFormat)->GetWindowText(cstr);  //获得组合框中的选中内容
	std::string str;
	str = CT2A(cstr);

	try {
		(*CDG)->GetRemoteFeatureControl()->GetEnumFeature("PixelFormat")->SetValue(str.c_str());
	}
	catch (CGalaxyException& e) {
		WE::MY_MFC_ERROR TTRY;
		TTRY.MyError(e.GetErrorCode());
	}
}

void MFC_PIC_COM_Dlg::OnCbnSelchangePixelsize() {
	// TODO: 在此添加控件通知处理程序代码
	CString cstr;
	GetDlgItem(IDC_PixelSize)->GetWindowText(cstr);  //获得组合框中的选中内容
	std::string str;
	str = CT2A(cstr);

	try {
		(*CDG)->GetRemoteFeatureControl()->GetEnumFeature("PixelSize")->SetValue(str.c_str());
	}
	catch (CGalaxyException& e) {
		WE::MY_MFC_ERROR TTRY;
		TTRY.MyError(e.GetErrorCode());
	}
}

void MFC_PIC_COM_Dlg::OnCbnSelchangeTestpattern() {
	// TODO: 在此添加控件通知处理程序代码
	CString cstr;
	GetDlgItem(IDC_TestPattern)->GetWindowText(cstr);  //获得组合框中的选中内容
	std::string str;
	str = CT2A(cstr);

	try {
		(*CDG)->GetRemoteFeatureControl()->GetEnumFeature("TestPattern")->SetValue(str.c_str()); // 配音 扎
	}
	catch (CGalaxyException& e) {
		WE::MY_MFC_ERROR TTRY;
		TTRY.MyError(e.GetErrorCode());
	}
}