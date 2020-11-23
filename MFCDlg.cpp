// MFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "afxdialogex.h"
#include "第三方代码/drawpicture/DRAW.h"
#include "第三方代码/implant/implant.h"
#include "第三方代码/lucency/lucency.h"
//#include "第三方代码/消息传递/factory.h"
#include "第三方代码/消息传递/RunMessage.hpp"
#include "第三方代码/主题/changetheme.hpp"
#include "第三方代码/主题/TheamName.h"
//#include "第三方代码/消息传递/RunMessage.hpp"
//#include <mmsystem.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_ABOUTBOX
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_CESHI, this->ceshi);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()

// CMFCDlg 对话框

CMFCDlg::CMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CESHI, ceshi);
	//	DDX_Control(pDX, IDC_CESHI, ceshi);
	//DDX_Control(pDX, IDC_GIF, _gif);
}

void CMFCDlg::BREAK(CMFCDlg* dlg) {
	dlg->OnOK();
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//	ON_WM_SHOWWINDOW()
//	ON_WM_TIMER()
//ON_WM_CLOSE()
ON_WM_DESTROY()
//ON_WM_MOVE()
//ON_WM_SHOWWINDOW()
//ON_WM_CAPTURECHANGED()
//ON_WM_MOUSEMOVE()
//ON_WM_LBUTTONDOWN()
//ON_WM_RBUTTONDOWN()
//ON_WM_MOUSEMOVE()
ON_WM_TIMER()
//ON_WM_CLOSE()
//ON_WM_LBUTTONDOWN()
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CMFCDlg 消息处理程序

BOOL CMFCDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化
//
	WE::changelucency(200, this);

	//窗口动画
	//myFlash = new CDlgFlash(this);
	//SetTimer(1, 300, NULL);

	//or you can choose : myFlash=new CDlgFlash(this,9,10);

	//myFlash->SetFlashCreateSpeed(5, 6);

	//myFlash->SetFlashDestroySpeed(5);
	//

	WE::changelucency(230, this);

	//首先,把这一页需要的主题都扔进去
	//选择主题,默认为1
	WE::InsertVectorThemeName();//插入主题,ok

	//WE::SetInsertTheme("主题2");//然后只是告诉他们我们要怎么做,没错 //first是主题名字,主题二,//获取当前主题,获取主题
	WE::THEMEMapInsert<decltype(_GIF.run), WE::MyWayGifControl*, std::string, int, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[0], WE::MyWayGifControl::run, &_GIF, WE::GetThemeNameNum(1)->second.second[0], IDC_GIF, this);
	WE::THEMEMapInsert<decltype(_GIF.run), WE::MyWayGifControl*, std::string, int, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[0], WE::MyWayGifControl::run, &_GIF, WE::GetThemeNameNum(2)->second.second[0], IDC_GIF, this);
	WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[0]]->run();//就是懒;

	//弄完了第一个是0;
	WE::MSGfactory<void(*)(CMFCDlg*)>(PANEL_MAIN_BREAK, BREAK, this);

	_GIFDLG.Create(IDD_HOME_GIF, this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDlg::OnPaint() {
	if (IsIconic()) {
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
	//	WE::Drawpic::DRAWDRAW(IDC_GIF, CString(L"picture/主窗口背景.jpg"), this);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

//void CMFCDlg::OnShowWindow(BOOL bShow, UINT nStatus) {
//	CDialogEx::OnShowWindow(bShow, nStatus);
//
//	//
//
//	// TODO: 在此处添加消息处理程序代码
//}

//void CMFCDlg::OnTimer(UINT_PTR nIDEvent) {
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnTimer(nIDEvent);
//	//定时一次,显示一个
//}

//void CMFCDlg::OnClose() {
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	_GIF.Stop();
//	CDialogEx::OnClose();
//}

void CMFCDlg::OnDestroy() {
	_GIF.Stop();
	Sleep(100);
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CMFCDlg::OnTimer(UINT_PTR nIDEvent) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	myFlash->OnTimer(nIDEvent); //处理窗口动画定时器
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCDlg::OnShowWindow(BOOL bShow, UINT nStatus) {
	CDialogEx::OnShowWindow(bShow, nStatus);
	//
	WE::MTVOID::IMPlant(IDC_SNOW, this, &_GIFDLG);

	// TODO: 在此处添加消息处理程序代码
}