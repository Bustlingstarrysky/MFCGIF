// MFCHOMEGIF.cpp: 实现文件
//

#include "pch.h"
#include "MFC.h"
#include "MFCHOMEGIF.h"
#include "afxdialogex.h"
#include "第三方代码/lucency/lucency.h"
#include "第三方代码/implant/implant.h"
#include "第三方代码/主题/changetheme.hpp"
#include "第三方代码/主题/TheamName.h"
#include "MFC_LIGHT_Dlg.h"
//#include "MFC_PANEL_Dlg.h"

#include "HalconCpp.h"

using namespace HalconCpp;
// MFCHOMEGIF 对话框

IMPLEMENT_DYNAMIC(MFCHOMEGIF, CDialogEx)

MFCHOMEGIF::MFCHOMEGIF(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOME_GIF, pParent) {}

MFCHOMEGIF::~MFCHOMEGIF() {}

void MFCHOMEGIF::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_OCX, _COCX);
//	DDX_Control(pDX, IDC_OCX, _MP3OCX);
}

BOOL MFCHOMEGIF::OnInitDialog() {
	CDialogEx::OnInitDialog();

	WE::changelucency(150, this);
	WE::THEMEMapInsert<decltype(DRAW), CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[1], DRAW, CString(WE::GetThemeNameNum(1)->second.second[1].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAW), CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[1], DRAW, CString(WE::GetThemeNameNum(2)->second.second[1].c_str()), this);

	//明天要做的事情
	//把灯光接口集成在这里,拿到工具模板,进行测试
	//图像基本滤镜处理
	//直接代码一直

	///
	_PALEN.Create(IDD_PANEL_DIG, this);
	_HALCON.Create(IDD_HALCON_Dialog, this);
	_Light.Create(IDD_LIGHT_DLG, this);
	//这是我的做法,明白吗

	return TRUE;
}

BEGIN_MESSAGE_MAP(MFCHOMEGIF, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//	ON_BN_CLICKED(IDC_BUTTON1, &MFCHOMEGIF::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// MFCHOMEGIF 消息处理程序

void MFCHOMEGIF::OnDestroy() {
	//_GIF_SNOW.Stop();
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void MFCHOMEGIF::DRAW(CString str, CDialogEx* DLg) {
	CRect rect;   //
	DLg->GetClientRect(rect);  //rect不对进
	WE::Drawpic::DRAWDRAWDC(&rect, str, DLg);//这个是背景窗口的,要用包装函数
}

void MFCHOMEGIF::DRAWPIC(int ID, CString str, CDialogEx* Dlg) {
	WE::Drawpic::DRAWDRAW(ID, str, Dlg);//有多少个主题就建造多少个vector,
}

void MFCHOMEGIF::OnPaint() {
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用
					   //

	//WE::THEMEMapInsert("");//写一个vector 然后把vector扔进去,不就行了,之后用vector指针管理

	WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[1]]->run();//就是懒;
}

//void MFCHOMEGIF::OnBnClickedButton1() {
//	// TODO: 在此添加控件通知处理程序代码
//	AfxMessageBox(L"测试成功");
//	}

BOOL MFCHOMEGIF::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)    //回车
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)    //ESC
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void MFCHOMEGIF::OnClose() {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//::SendMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	CDialogEx::OnClose();
}

void MFCHOMEGIF::OnShowWindow(BOOL bShow, UINT nStatus) {
	CDialogEx::OnShowWindow(bShow, nStatus);
	WE::MTVOID::IMPlant(IDC_PANEL, this, &_PALEN);
	WE::MTVOID::IMPlant(IDC_CAMERA, this, &_HALCON);
	WE::MTVOID::IMPlant(IDC_LIGHT, this, &_Light);
	//_PALEN.ShowWindow(SW_SHOW);
	// TODO: 在此处添加消息处理程序代码
}