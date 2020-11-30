// MFC_SET_DLG.cpp: 实现文件
//

#include "pch.h"
#include "MFC.h"
#include "MFC_SET_DLG.h"
#include "afxdialogex.h"
#include "第三方代码/消息传递/RunMessage.hpp"

// MFC_SET_DLG 对话框

IMPLEMENT_DYNAMIC(MFC_SET_DLG, CDialogEx)

MFC_SET_DLG::MFC_SET_DLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_DLG, pParent) {
	_MFC摄像机信息 = nullptr;
}//通过大量的图片获取信息并不现实,通过信息预测未来并不现实,所有,通过收集信息取卖,非常有前途

MFC_SET_DLG::~MFC_SET_DLG() {}

void MFC_SET_DLG::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GETID, _ComList);
}

BEGIN_MESSAGE_MAP(MFC_SET_DLG, CDialogEx)
	ON_BN_CLICKED(IDC_FIND, &MFC_SET_DLG::OnBnClickedFind)
	ON_BN_CLICKED(IDC_SETMSG, &MFC_SET_DLG::OnBnClickedSetmsg)
	//	ON_BN_CLICKED(IDC_OPENCAMERA, &MFC_SET_DLG::OnBnClickedOpencamera)
	ON_BN_CLICKED(IDC_SETING, &MFC_SET_DLG::OnBnClickedSeting)
	//	ON_BN_CLICKED(IDC_BUTTON1, &MFC_SET_DLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BREAK, &MFC_SET_DLG::OnBnClickedBreak)
	//	ON_BN_CLICKED(IDC_BUTTON6, &MFC_SET_DLG::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_PICCOM, &MFC_SET_DLG::OnBnClickedPiccom)
END_MESSAGE_MAP()

// MFC_SET_DLG 消息处理程序

void MFC_SET_DLG::OnBnClickedFind() {
	// TODO: 在此添加控件通知处理程序代码
	IGXFactory::GetInstance().Init();
	vectorDeviceInfo.clear();
	_ComList.ResetContent();
	try {// 点子是
		WE::FindCamera(vectorDeviceInfo);
	}
	catch (CGalaxyException& e) {
		WE::MY_MFC_ERROR TRYS;
		TRYS.MyError(e.GetErrorCode()); //没道理啊,初始化后 //明年体
	}

	if (vectorDeviceInfo.empty()) {
		return;
	}
	for (auto& i : vectorDeviceInfo) {
		_ComList.AddString(i.GetModelName().w_str());//这样就实现了遍历所有,接下来呢//你们真是在扯犊子
	}
	_ComList.SetCurSel(0);
	IGXFactory::GetInstance().Uninit(); //把它关了,吗
}

void MFC_SET_DLG::OnBnClickedSetmsg() {
	// TODO: 在此添加控件通知处理程序代码
	//因为涉及到自身的一些乱七八糟的引述
	_MFC摄像机信息 = new MFC摄像机信息(); // 等于指针
	// 这个只是包装,关键还是运行
	WE::MSGfactory<void(*)(MFC_SET_DLG*, MFC摄像机信息*), MFC_SET_DLG*, MFC摄像机信息*>(SET_摄像机信息_Open, OpenCamera_SXJXX, this, _MFC摄像机信息);
	WE::MSGfactory<void(*)(MFC_SET_DLG*, MFC摄像机信息*), MFC_SET_DLG*, MFC摄像机信息*>(SET_摄像机信息_Close, CloseCamera_SXJXX, this, _MFC摄像机信息);
	_MFC摄像机信息->Create(IDD_SETMSG_Dlg, this);//创建对话框,然后显示
	_MFC摄像机信息->ShowWindow(SW_SHOW);//去做
}

BOOL MFC_SET_DLG::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void MFC_SET_DLG::OpenCamera_SXJXX(MFC_SET_DLG* TTHE, MFC摄像机信息* Dlg) {
	//假设这个时候已经初始化了,也就是说
	TTHE->OpeningCamera();
	Dlg->CDG = &TTHE->ObjDevicePtr; // 把指针给它,
}

void MFC_SET_DLG::CloseCamera_SXJXX(MFC_SET_DLG* TTHE, MFC摄像机信息* Dlg) {
	TTHE->CloseCamera();//把它关闭了
	delete Dlg;
	TTHE->_MFC摄像机信息 = nullptr;
	IGXFactory::GetInstance().Uninit();
}

void MFC_SET_DLG::OpenCamera_PICCOM(MFC_SET_DLG* TTHE, MFC_PIC_COM_Dlg* Dlg) {
	TTHE->OpeningCamera();
	Dlg->CDG = &TTHE->ObjDevicePtr; // 把指针给它,
}

void MFC_SET_DLG::CloseCamera_PICCOM(MFC_SET_DLG* TTHE, MFC_PIC_COM_Dlg* Dlg) {
	TTHE->CloseCamera();//把它关闭了
	delete Dlg;
	TTHE->_MFC摄像机信息 = nullptr;
	IGXFactory::GetInstance().Uninit();
}

void MFC_SET_DLG::OpeningCamera() {
	// 我们重新搞,对吧
	IGXFactory::GetInstance().Init();
	try {
		//就是打开了
		vectorDeviceInfo.clear();
		WE::FindCamera(vectorDeviceInfo);
		GxIAPICPP::gxstring strSN = vectorDeviceInfo[_ComList.GetCurSel()].GetUserID();
		ObjDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(
			vectorDeviceInfo[_ComList.GetCurSel()].GetSN(),
			GX_ACCESS_EXCLUSIVE);
		//AfxMessageBox(L"成功");//我发现我最大的问题是,下周一二,把所有的窗口实现,要说极限的化 把所有接口全部弄出来,然后就是
		ObjStreamPtr = ObjDevicePtr->OpenStream(0);//或许这就是数据类型把
	}
	catch (CGalaxyException& e) {
		WE::MY_MFC_ERROR TRYS;
		TRYS.MyError(e.GetErrorCode());
	}
}

void MFC_SET_DLG::CloseCamera() {
	ObjStreamPtr->Close();
	ObjDevicePtr->Close();// 对吧,没错把 //我把任何一个指针传递进来,然后delete掉就行了
}

void MFC_SET_DLG::OnBnClickedSeting() {
	// TODO: 在此添加控件通知处理程序代码
}

BOOL MFC_SET_DLG::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)// 屏蔽esc键
	{
		return TRUE;// 不作任何操作
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)// 屏蔽enter键
	{
		return TRUE;// 不作任何处理
	}
	//屏蔽掉了
	return CDialogEx::PreTranslateMessage(pMsg);
}

//void MFC_SET_DLG::OnBnClickedButton1() {
//	// TODO: 在此添加控件通知处理程序代码
//}

void MFC_SET_DLG::OnBnClickedBreak() {
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

//void MFC_SET_DLG::OnBnClickedButton6() {
//	// TODO: 在此添加控件通知处理程序代码
//}

void MFC_SET_DLG::OnBnClickedPiccom() {
	// TODO: 在此添加控件通知处理程序代码
	//一切按照流程来,根据计算
	_MFCPICCOM = new MFC_PIC_COM_Dlg();//
	WE::MSGfactory<void(*)(MFC_SET_DLG*, MFC_PIC_COM_Dlg*), MFC_SET_DLG*, MFC_PIC_COM_Dlg*>(SET_图像格式控制_Open, OpenCamera_PICCOM, this, _MFCPICCOM);
	WE::MSGfactory<void(*)(MFC_SET_DLG*, MFC_PIC_COM_Dlg*), MFC_SET_DLG*, MFC_PIC_COM_Dlg*>(SET_图像格式控制_Close, CloseCamera_PICCOM, this, _MFCPICCOM);
	_MFCPICCOM->Create(IDD_PICTURECOM_Dlg, this);
	_MFCPICCOM->ShowWindow(SW_SHOW);
}