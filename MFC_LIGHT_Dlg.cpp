// MFC_LIGHT_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC.h"
#include "MFC_LIGHT_Dlg.h"
#include "afxdialogex.h"
#include "第三方代码/lucency/lucency.h"

// MFC_LIGHT_Dlg 对话框

IMPLEMENT_DYNAMIC(MFC_LIGHT_Dlg, CDialogEx)

MFC_LIGHT_Dlg::MFC_LIGHT_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIGHT_DLG, pParent), _LightIntNum(0) {}

MFC_LIGHT_Dlg::~MFC_LIGHT_Dlg() {}

void MFC_LIGHT_Dlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMLIST, _ComList);
	DDX_Control(pDX, IDC_COMLIGHT, _ComLight);
	DDX_Control(pDX, IDC_RIGHTNESS, _CScroll);
	//	DDX_Control(pDX, IDC_NUM, _LightIntNum);
	DDX_Text(pDX, IDC_NUM, _LightIntNum);
}

BEGIN_MESSAGE_MAP(MFC_LIGHT_Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_FindCom, &MFC_LIGHT_Dlg::OnBnClickedFindcom)
	ON_BN_CLICKED(IDC_OpeningCom, &MFC_LIGHT_Dlg::OnBnClickedOpeningcom)
	ON_BN_CLICKED(IDC_ClosingCom, &MFC_LIGHT_Dlg::OnBnClickedClosingcom)
	ON_BN_CLICKED(IDC_ALLOpening, &MFC_LIGHT_Dlg::OnBnClickedAllopening)
	ON_BN_CLICKED(IDC_RED, &MFC_LIGHT_Dlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_BLUE, &MFC_LIGHT_Dlg::OnBnClickedBlue)
	ON_BN_CLICKED(IDC_ALLClosing, &MFC_LIGHT_Dlg::OnBnClickedAllclosing)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_NUM, &MFC_LIGHT_Dlg::OnEnChangeNum)
	ON_CBN_SELCHANGE(IDC_COMLIGHT, &MFC_LIGHT_Dlg::OnCbnSelchangeComlight)
END_MESSAGE_MAP()

// MFC_LIGHT_Dlg 消息处理程序

BOOL MFC_LIGHT_Dlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	WE::lucency(0, 0, 100, this);

	_CScroll.SetScrollRange(0, 255);
	_CScroll.SetScrollPos(0);

	//_LightNum.LimitText(3);

	_ComLight.ResetContent();
	_ComLight.AddString(L"1");
	_ComLight.AddString(L"2");
	_ComLight.AddString(L"3");
	_ComLight.AddString(L"4");
	_ComLight.AddString(L"红色");
	_ComLight.AddString(L"蓝色");
	_ComLight.AddString(L"全部");

	_ComLight.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void MFC_LIGHT_Dlg::OnPaint() {
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
					   //
	CRect rcGlassArea;
	GetClientRect(&rcGlassArea);
	//dc.FillSolidRect(&rcGlassArea, RGB(134, 243, 102));
	dc.FillSolidRect(&rcGlassArea, RGB(0, 0, 100)); //有什么好不好的拉
}

void MFC_LIGHT_Dlg::OnBnClickedFindcom() {
	// TODO: 在此添加控件通知处理程序代码
			// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	_ComList.ResetContent();
	if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey))//打开串口注册表对应的键值
	{
		int   i = 0;
		TCHAR  RegKeyName[128];
		TCHAR SerialPortName[128];//不管
		DWORD  dwLong, dwSize;
		while (TRUE) {
			dwLong = dwSize = sizeof(RegKeyName);
			if (ERROR_NO_MORE_ITEMS == ::RegEnumValue(hKey, i, RegKeyName, &dwLong, NULL, NULL, reinterpret_cast <PUCHAR>(SerialPortName), &dwSize))//枚举串口
			{
				break;
			}
			_ComList.AddString(SerialPortName);   //SerialPortName就是串口名字
			++i;
		}
		RegCloseKey(hKey);
	}
	_ComList.SetCurSel(0);
}

void MFC_LIGHT_Dlg::OnBnClickedOpeningcom() {
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = _ComList.GetCurSel();
	CString _cstr;
	_ComList.GetLBText(nIndex, _cstr);
	CString ns = _cstr.Mid(3);//Mid设置开始位置，第二参数是个数，默认时为字符串结束。
	int n = _wtoi(ns);//n就是数字了

	if (!_Light.OpenLightCom(n)) {
		AfxMessageBox(L"打开串口失败,请检查");
	}
	GetDlgItem(IDC_OpeningCom)->EnableWindow(FALSE);//变灰
	GetDlgItem(IDC_ClosingCom)->EnableWindow(TRUE);
	GetDlgItem(IDC_ALLOpening)->EnableWindow(TRUE);
	GetDlgItem(IDC_ALLClosing)->EnableWindow(TRUE);
	GetDlgItem(IDC_RED)->EnableWindow(TRUE);
	GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMLIGHT)->EnableWindow(TRUE);
	GetDlgItem(IDC_RIGHTNESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_NUM)->EnableWindow(TRUE);
}

void MFC_LIGHT_Dlg::OnBnClickedClosingcom() {
	// TODO: 在此添加控件通知处理程序代码

	if (!_Light.CloseLightCom()) {
		AfxMessageBox(L"关闭串口失败,请检查");
	}
	GetDlgItem(IDC_OpeningCom)->EnableWindow(TRUE);//变灰
	GetDlgItem(IDC_ClosingCom)->EnableWindow(FALSE);
	GetDlgItem(IDC_ALLOpening)->EnableWindow(FALSE);
	GetDlgItem(IDC_ALLClosing)->EnableWindow(FALSE);
	GetDlgItem(IDC_RED)->EnableWindow(FALSE);
	GetDlgItem(IDC_BLUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMLIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RIGHTNESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_NUM)->EnableWindow(FALSE);
}

void MFC_LIGHT_Dlg::OnBnClickedAllopening() {
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	_Light.LightAllNum(_LightIntNum);
}

void MFC_LIGHT_Dlg::OnBnClickedRed() {
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	_Light.LightChangeNum(2, 0);//
	_Light.LightChangeNum(1, _LightIntNum);
	_Light.LightChangeNum(3, _LightIntNum);
	_Light.LightChangeNum(4, _LightIntNum);
}

void MFC_LIGHT_Dlg::OnBnClickedBlue() {
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	_Light.LightChangeNum(1, 0);
	_Light.LightChangeNum(3, 0);
	_Light.LightChangeNum(4, 0);
	_Light.LightChangeNum(2, _LightIntNum);//没有看到有人在
}

void MFC_LIGHT_Dlg::OnBnClickedAllclosing() {
	// TODO: 在此添加控件通知处理程序代码
	_Light.LightAllNum(0);
}

void MFC_LIGHT_Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UpdateData(TRUE);
	if (pScrollBar == &_CScroll) {
		int iNowPos;
		CString cstr;
		switch (nSBCode) {
		case SB_THUMBTRACK: // 拖动滚动滑块时
			_CScroll.SetScrollPos(nPos);
			_LightIntNum = nPos;

			break;
		case SB_LINELEFT: // 单击滚动条向左的箭头
			iNowPos = _CScroll.GetScrollPos();
			iNowPos -= 1;
			_CScroll.SetScrollPos(iNowPos);
			_LightIntNum = iNowPos;
			break;
		case SB_LINERIGHT: // 单击滚动条向右的箭头
			iNowPos = _CScroll.GetScrollPos();
			iNowPos += 1;
			_CScroll.SetScrollPos(iNowPos);
			_LightIntNum = iNowPos;
			break;
		case SB_PAGELEFT:
			iNowPos = _CScroll.GetScrollPos();
			iNowPos -= 10;
			if (iNowPos < 0) {
				iNowPos = 0;
			}
			_CScroll.SetScrollPos(iNowPos);
			_LightIntNum = iNowPos;
			break;
		case SB_PAGERIGHT:
			iNowPos = _CScroll.GetScrollPos();
			iNowPos += 10;
			if (iNowPos > 255) {
				iNowPos = 255;
			}
			_CScroll.SetScrollPos(iNowPos);
			_LightIntNum = iNowPos;
			;
			break;
		}
	}

	UpdateData(FALSE);
	OnEnChangeNum();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void MFC_LIGHT_Dlg::OnEnChangeNum() {
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	if (_LightIntNum > 255) {
		_LightIntNum = 255;
	}
	if (_LightIntNum < 0) {
		_LightIntNum = 0;
	}
	{
		UpdateData(TRUE);
		_CScroll.SetScrollPos(_LightIntNum);
		UpdateData(FALSE);
	}
	int n = _ComLight.GetCurSel();
	if (n < 4) {
		_Light.LightChangeNum(n + 1, _LightIntNum);
	}
	if (4 == n) {//红色
		_Light.LightChangeNum(2, 0);//蓝色闭嘴
		_Light.LightChangeNum(1, _LightIntNum);
		_Light.LightChangeNum(3, _LightIntNum);
		_Light.LightChangeNum(4, _LightIntNum);
	}
	if (5 == n) {//
		_Light.LightChangeNum(1, 0);
		_Light.LightChangeNum(4, 0);
		_Light.LightChangeNum(3, 0);
		_Light.LightChangeNum(2, _LightIntNum);
	}
	if (6 == n) {
		_Light.LightAllNum(_LightIntNum);
	}
	UpdateData(FALSE);
	// TODO:  在此添加控件通知处理程序代码
}

void MFC_LIGHT_Dlg::OnCbnSelchangeComlight() {
	// TODO: 在此添加控件通知处理程序代码
	OnEnChangeNum();
}

BOOL MFC_LIGHT_Dlg::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)    //回车
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)    //ESC
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}