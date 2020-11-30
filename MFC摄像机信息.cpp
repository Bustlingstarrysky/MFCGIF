// MFC摄像机信息.cpp: 实现文件
//

#include "pch.h"
#include "MFC.h"
#include "MFC摄像机信息.h"
#include "afxdialogex.h"
#include "第三方代码/大恒相机/Camera.h"
#include "第三方代码/消息传递/RunMessage.hpp"
#include <tuple>
// MFC摄像机信息 对话框

IMPLEMENT_DYNAMIC(MFC摄像机信息, CDialogEx)

MFC摄像机信息::MFC摄像机信息(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETMSG_Dlg, pParent) {
	//构造函数
}

MFC摄像机信息::~MFC摄像机信息() {
	//IGXFactory::GetInstance().Uninit();
}

void MFC摄像机信息::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}
void MFC摄像机信息::SetTEXT() {
	CString cstr = L"厂商名称: ";//都说了不要,
	cstr += (*CDG)->GetRemoteFeatureControl()->GetStringFeature("DeviceVendorName")->GetValue();
	GetDlgItem(IDC_1)->SetWindowTextW(cstr);
	cstr = L"设备型号: ";
	cstr += (*CDG)->GetRemoteFeatureControl()->GetStringFeature("DeviceModelName")->GetValue();
	GetDlgItem(IDC_2)->SetWindowTextW(cstr);
	cstr = L"设备版本: ";
	cstr += (*CDG)->GetRemoteFeatureControl()->GetStringFeature("DeviceVersion")->GetValue();
	GetDlgItem(IDC_3)->SetWindowTextW(cstr);
	cstr = L"设备固件版本: ";
	cstr += (*CDG)->GetRemoteFeatureControl()->GetStringFeature("DeviceFirmwareVersion")->GetValue();
	GetDlgItem(IDC_4)->SetWindowTextW(cstr);
	cstr = L"设备序列号: ";
	cstr += (*CDG)->GetRemoteFeatureControl()->GetStringFeature("DeviceSerialNumber")->GetValue();
	GetDlgItem(IDC_5)->SetWindowTextW(cstr);
	cstr = L"出厂参数版本: ";
	cstr += (*CDG)->GetRemoteFeatureControl()->GetStringFeature("FactorySettingVersion")->GetValue();
	GetDlgItem(IDC_6)->SetWindowTextW(cstr);
	cstr = L""; //那么,必较简单
	cstr += (*CDG)->GetRemoteFeatureControl()->GetStringFeature("DeviceUserID")->GetValue();
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(cstr);
}

BEGIN_MESSAGE_MAP(MFC摄像机信息, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &MFC摄像机信息::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BREAK, &MFC摄像机信息::OnBnClickedBreak)
END_MESSAGE_MAP()

// MFC摄像机信息 消息处理程序

void MFC摄像机信息::OnEnChangeEdit1() {
	// TODO:  如果该控件是 RICHEDIT 控件，它将不

	//
	CString cstr;
	GetDlgItemTextW(IDC_EDIT1, cstr);
	gxstring str = CW2A(cstr.GetString());
	(*CDG)->GetRemoteFeatureControl()->GetStringFeature("DeviceUserID")->SetValue(str);
	// TODO:  在此添加控件通知处理程序代码
}

BOOL MFC摄像机信息::OnInitDialog() {
	CDialogEx::OnInitDialog();
	// 要关闭的时候用统一处理,
	// TODO:  在此添加额外的初始化
//	WE::RUNTIMING(SET_摄像机信息_Open);
	WE::RUNTIMING(SET_摄像机信息_Open);
	try {
		SetTEXT();
	}
	catch (CGalaxyException& e) {
		WE::MY_MFC_ERROR TRYS;
		TRYS.MyError(e.GetErrorCode());
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL MFC摄像机信息::PreTranslateMessage(MSG* pMsg) {
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

void MFC摄像机信息::OnBnClickedBreak() {
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	WE::RUNTIMING(SET_摄像机信息_Close);
}