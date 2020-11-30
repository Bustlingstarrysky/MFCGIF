// MFC_PANEL_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC.h"
#include "MFC_PANEL_Dlg.h"
#include "afxdialogex.h"
#include "第三方代码/drawpicture/DRAW.h"
#include "第三方代码/lucency/lucency.h"
//#include "第三方代码/消息传递/factory.h"
#include <functional>

#include "第三方代码/主题/changetheme.hpp"
#include "第三方代码/主题/TheamName.h"
#include "第三方代码/消息传递/RunMessage.hpp"
//#include "第三方代码/消息传递/RunMessage.hpp"
// MFC_PANEL_Dlg 对话框
//extern  std::map<std::string, std::unique_ptr<WE::MY::function>> TABLE; // 我受够了静态变量跟一个傻狗一样
IMPLEMENT_DYNAMIC(MFC_PANEL_Dlg, CDialogEx)

MFC_PANEL_Dlg::MFC_PANEL_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PANEL_DIG, pParent) {
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
}
//把图片改变的函数进行包装就行了,其他一概不管,对,就这样
MFC_PANEL_Dlg::~MFC_PANEL_Dlg() {}

void MFC_PANEL_Dlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMTHEME, _ComTheme);
}

void MFC_PANEL_Dlg::DRAWPIC(int ID, CString str, CDialogEx* Dlg) {
	WE::Drawpic::DRAWDRAW(ID, str, Dlg);
}

BEGIN_MESSAGE_MAP(MFC_PANEL_Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMTHEME, &MFC_PANEL_Dlg::OnCbnSelchangeComtheme)
	ON_BN_CLICKED(IDC_BREAK, &MFC_PANEL_Dlg::OnBnClickedBreak)
	ON_BN_CLICKED(IDC_OpenCamara, &MFC_PANEL_Dlg::OnBnClickedOpencamara)
	ON_BN_CLICKED(IDC_CLOSECAMRAR, &MFC_PANEL_Dlg::OnBnClickedClosecamrar)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CAMAPIC, &MFC_PANEL_Dlg::OnBnClickedCamapic)
	ON_BN_CLICKED(IDC_MYPICTURE, &MFC_PANEL_Dlg::OnBnClickedMypicture)
	ON_BN_CLICKED(IDC_CMRSET, &MFC_PANEL_Dlg::OnBnClickedCmrset)
END_MESSAGE_MAP()

// MFC_PANEL_Dlg 消息处理程序

void MFC_PANEL_Dlg::OnPaint() {
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用
	CDialogEx::OnPaint();

	//SetDialogBkColor(RGB(0, 0, 255), RGB(255, 0, 0));
	CRect rcGlassArea;
	GetClientRect(&rcGlassArea);
	//dc.FillSolidRect(&rcGlassArea, RGB(134, 243, 102));
	dc.FillSolidRect(&rcGlassArea, RGB(0, 0, 100)); //有什么好不好的拉

	WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[2]]->run();//就是懒;
	WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[3]]->run();//就是懒;
	WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[4]]->run();//就是懒;
	WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[5]]->run();//就是懒;

//箭头不用换,但是未来有调用的过程,首先,是一个异步的gif 既然是异步的gif 那就使用呗 // 可以通知重绘,但是有必要吗 每一个都是,难道是双异步??? 搞锤子啊
}

BOOL MFC_PANEL_Dlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//WE::RunFactor::factory<decltype(ShowWindow),>(ShowWindow,this);//把控制面板函数传递进去;
//	WE::factory<void(*)(MFC_PANEL_Dlg*), MFC_PANEL_Dlg*>("控制面板隐藏", HideLLL, this);

	WE::lucency(0, 0, 100, this); //透明完成,接下来就是用做控件
	//WE::factory("控制面板消息隐藏", MYHIDE, this);//隐藏,不好意思,我不写

	auto func = [](int ID, CRect& rect, CDialogEx* Dlg)mutable ->void {
		Dlg->GetDlgItem(ID)->GetWindowRect(&rect);
		Dlg->ScreenToClient(&rect);
	};
	//std::array<CRect, 4> RectArray;
	RectArray[0] = CRect();
	RectArray[1] = CRect();
	RectArray[2] = CRect();
	RectArray[3] = CRect();

	func(IDC_TOP, RectArray[0], this);
	func(IDC_LEFT, RectArray[1], this);
	func(IDC_RIGHT, RectArray[2], this);
	func(IDC_DOWN, RectArray[3], this);

	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[2], DRAWPIC, IDC_TOP, CString(WE::GetThemeNameNum(1)->second.second[2].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[2], DRAWPIC, IDC_TOP, CString(WE::GetThemeNameNum(2)->second.second[2].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[3], DRAWPIC, IDC_DOWN, CString(WE::GetThemeNameNum(1)->second.second[3].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[3], DRAWPIC, IDC_DOWN, CString(WE::GetThemeNameNum(2)->second.second[3].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[4], DRAWPIC, IDC_LEFT, CString(WE::GetThemeNameNum(1)->second.second[4].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[4], DRAWPIC, IDC_LEFT, CString(WE::GetThemeNameNum(2)->second.second[4].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[5], DRAWPIC, IDC_RIGHT, CString(WE::GetThemeNameNum(1)->second.second[5].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[5], DRAWPIC, IDC_RIGHT, CString(WE::GetThemeNameNum(2)->second.second[5].c_str()), this);

	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[6], DRAWPIC, IDC_TOP, CString(WE::GetThemeNameNum(1)->second.second[6].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[6], DRAWPIC, IDC_TOP, CString(WE::GetThemeNameNum(2)->second.second[6].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[7], DRAWPIC, IDC_DOWN, CString(WE::GetThemeNameNum(1)->second.second[7].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[7], DRAWPIC, IDC_DOWN, CString(WE::GetThemeNameNum(2)->second.second[7].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[8], DRAWPIC, IDC_LEFT, CString(WE::GetThemeNameNum(1)->second.second[8].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[8], DRAWPIC, IDC_LEFT, CString(WE::GetThemeNameNum(2)->second.second[8].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(1)->first, WE::GetThemeNameNum(1)->second.first[9], DRAWPIC, IDC_RIGHT, CString(WE::GetThemeNameNum(1)->second.second[9].c_str()), this);
	WE::THEMEMapInsert<decltype(DRAWPIC), int, CString, CDialogEx*>(WE::GetThemeNameNum(2)->first, WE::GetThemeNameNum(2)->second.first[9], DRAWPIC, IDC_RIGHT, CString(WE::GetThemeNameNum(2)->second.second[9].c_str()), this);

	_ComTheme.AddString(L"主题1");
	_ComTheme.AddString(L"主题2");
	_ComTheme.SetCurSel(0);

	_cmfcsetdlg.Create(IDD_SET_DLG, this);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void MFC_PANEL_Dlg::MYHIDE(MFC_PANEL_Dlg* Dlg) {
	Dlg->ShowWindow(SW_HIDE);
}

void MFC_PANEL_Dlg::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//逻辑不对
	CDialogEx::OnMouseMove(nFlags, point);

	auto function = [](CRect& rect, CPoint& point, int i, int j)mutable ->void {
		if (rect.PtInRect(point)) {
			WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[j]]->run();//就是懒;
		}
		else {
			WE::GetTheme(WE::GetThemeName()->first)[WE::GetThemeName()->second.first[i]]->run();//就是懒;
		}
	}; //也就是说,这里需要插入8个函数 但是为了同理,省得map乱七八糟 ,所以只能这样了
	//如果鼠标不在里面

	function(RectArray[0], point, 2, 6);
	function(RectArray[3], point, 3, 7);
	function(RectArray[1], point, 4, 8);
	function(RectArray[2], point, 5, 9);
}

void MFC_PANEL_Dlg::OnCbnSelchangeComtheme() {
	// TODO: 在此添加控件通知处理程序代码
	unsigned int i = _ComTheme.GetCurSel();

	if (WE::GetThemeNameNum(i + 1) == WE::GetThemeName()) {
		return;
	}
	else {
		WE::ChangeNumTheme(i + 1);
	}
}

BOOL MFC_PANEL_Dlg::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)    //回车
		return TRUE; //拿不到板子
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)    //ESC //
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void MFC_PANEL_Dlg::OnBnClickedBreak() {
	// TODO: 在此添加控件通知处理程序代码
	WE::RUNTIMING(PANEL_MAIN_BREAK);

	//调用father的onok
}

void MFC_PANEL_Dlg::OnBnClickedOpencamara() {
	// TODO: 在此添加控件通知处理程序代码
	WE::RUNTIMING(PANEL_HALCON_OpenCamera); //放大缩小,放大时放大,缩小是缩小
}

void MFC_PANEL_Dlg::OnBnClickedClosecamrar() {
	// TODO: 在此添加控件通知处理程序代码
	WE::RUNTIMING(PANEL_HALCON_CLOSSCAMERA);
}

void MFC_PANEL_Dlg::OnClose() {
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}

void MFC_PANEL_Dlg::OnBnClickedCamapic() {
	// TODO: 在此添加控件通知处理程序代码
	WE::RUNTIMING(PANEL_HALCON_Picturing);
}

void MFC_PANEL_Dlg::OnBnClickedMypicture() {
	// TODO: 在此添加控件通知处理程序代码
	WE::RUNTIMING(PANEL_HALCON_ShowPicture);
}

void MFC_PANEL_Dlg::OnBnClickedCmrset() {
	// TODO: 在此添加控件通知处理程序代码
	_cmfcsetdlg.ShowWindow(SW_SHOW); //对啊,为什么窗口显示无反应//不知道
}