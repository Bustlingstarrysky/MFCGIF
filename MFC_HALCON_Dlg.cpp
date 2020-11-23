// MFC_HALCON_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC.h"
#include "MFC_HALCON_Dlg.h"
#include "afxdialogex.h"
#include"HalconCpp.h"
#include "第三方代码/消息传递/RunMessage.hpp"
// MFC_HALCON_Dlg 对话框

IMPLEMENT_DYNAMIC(MFC_HALCON_Dlg, CDialogEx)

MFC_HALCON_Dlg::MFC_HALCON_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HALCON_Dialog, pParent) {
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
}

MFC_HALCON_Dlg::~MFC_HALCON_Dlg() {}

void MFC_HALCON_Dlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MFC_HALCON_Dlg, CDialogEx)
	ON_WM_SIZE()
	//ON_EN_CHANGE(IDC_NUM, &MFC_HALCON_Dlg::OnEnChangeNum)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// MFC_HALCON_Dlg 消息处理程序

BOOL MFC_HALCON_Dlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	//是不是写一个对话框,直接在对话框调节大小,直接调用api实习那

	// TODO:  在此添加额外的初始化
	//添加这一个虚函数

	// Local control variables

	HalconCpp::HTuple m_ImageWidth, m_ImageHeight;//假设故障的问题,然后去实现

	CWnd* pWnd = GetDlgItem(IDC_HALCON_PIC);
	pWnd->GetWindowRect(&rect);
	//MoveWindow(rect.left, rect.top, 1500 / 2, 1200 / 2); //大小怎么还是不对
	OpenWindow(0, 0, rect.Width(), rect.Width(), (Hlong)pWnd->m_hWnd, "", "", &hv_WindowHandle);// 窗口溢出,那就不用implant
	HalconCpp::HDevWindowStack::Push(hv_WindowHandle);//最上层,并且不透明,可以选择采集图像 然后不就可以集成吗
	HalconCpp::SetPart(hv_WindowHandle, 0, 0, rect.Width(), rect.Width());//
//
	//
	_THREAD = nullptr;
	JUDEG = false;
	//
	WE::MSGfactory<void(*)(MFC_HALCON_Dlg*), MFC_HALCON_Dlg*>(PANEL_HALCON_OpenCamera, OpenCamara, this);//
	WE::MSGfactory<void(*)(MFC_HALCON_Dlg*), MFC_HALCON_Dlg*>(PANEL_HALCON_CLOSSCAMERA, CloseCramara, this);
	WE::MSGfactory<void(*)(MFC_HALCON_Dlg*), MFC_HALCON_Dlg*>(PANEL_HALCON_Picturing, PICTURING, this);//一直采集
	WE::MSGfactory<void(*)(MFC_HALCON_Dlg*), MFC_HALCON_Dlg*>(PANEL_HALCON_ShowPicture, RUNPICTRUE, this);//显示一个 //用自己的办法采集图像,然后给halcon 传递常说
	return TRUE;
}

void MFC_HALCON_Dlg::OnSize(UINT nType, int cx, int cy) {
	CDialogEx::OnSize(nType, cx, cy);
	_RESIZE;
	// TODO: 在此处添加消息处理程序代码
}
void MFC_HALCON_Dlg::OpenCamara(MFC_HALCON_Dlg* Dlg) {
	//打开之后必须关闭
	try {
		HalconCpp::HDevWindowStack::Push(Dlg->hv_WindowHandle);
		HalconCpp::OpenFramegrabber("GigEVision2", 0, 0, 0, 0, 0, 0, "progressive", -1, "default",
			-1, "false", "default", "00214901b3b4_DahengImaging_MER13230GM", 0, -1, &(Dlg->hv_AcqHandle));
		// 这个就是静态函数  要改就是在这里改了
	}
	catch (...) {
		AfxMessageBox(L"发生异常,请检查摄像头时候已经打开或者有没有连接");
	}
}

void MFC_HALCON_Dlg::CloseCramara(MFC_HALCON_Dlg* Dlg) {
	if (Dlg->_THREAD != nullptr) {
		Dlg->JUDEG = false;
		Dlg->_THREAD->join();
		delete Dlg->_THREAD;
		Dlg->_THREAD = nullptr;
	}

	HalconCpp::CloseFramegrabber(Dlg->hv_AcqHandle);
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::HDevWindowStack::Pop();// ok ,接下来就是实时采集了,
}

void MFC_HALCON_Dlg::PICTURING(MFC_HALCON_Dlg* Dlg) {
	auto func = [](MFC_HALCON_Dlg* Dlg) {
		GrabImageStart(Dlg->hv_AcqHandle, -1);//摄像头句柄打开,但是我行关闭呢 //打开句柄  //把指针传递给你
		//应该给一个true if true 就继续
		while (Dlg->JUDEG) {
			try {
				GrabImageAsync(&Dlg->ho_Image, Dlg->hv_AcqHandle, -1);//就算是这样,也得开多线程

				if (HalconCpp::HDevWindowStack::IsOpen()) {
					HalconCpp::ZoomImageSize(Dlg->ho_Image, &Dlg->ho_Image, Dlg->rect.Width(), Dlg->rect.Width(), "nearest_neighbor");//只能说写是写好了基本工具
					//1292
					;//964
					DispObj(Dlg->ho_Image, HalconCpp::HDevWindowStack::GetActive());  //一直采集,直到摄像头关闭???
				}
			}
			catch (...) {
				AfxMessageBox(L"异常");
			}
		}
	};

	if (Dlg->_THREAD == nullptr) {
		Dlg->JUDEG = true;
		Dlg->_THREAD = new std::thread(func, Dlg);//启动了
	}
	else {
		Dlg->JUDEG = false;
		Dlg->_THREAD->join();
		delete Dlg->_THREAD;
		Dlg->_THREAD = nullptr;
		Dlg->JUDEG = true;
		Dlg->_THREAD = new std::thread(func, Dlg);//启动了
		//就行了,ok 下一个
	}

	//然后就是启动异步了
}

void MFC_HALCON_Dlg::RUNPICTRUE(MFC_HALCON_Dlg* Dlg) {
	if (Dlg->_THREAD != nullptr) {
		Dlg->JUDEG = false;
		Dlg->_THREAD->join();
		delete Dlg->_THREAD;
		Dlg->_THREAD = nullptr;
	}
	else {
		AfxMessageBox(L"摄像头每开采集");
		return;
	}

	//采集一帧 作为决定

	if (HalconCpp::HDevWindowStack::IsOpen()) {
		GrabImageAsync(&Dlg->ho_Image, Dlg->hv_AcqHandle, -1);//就算是这样,也得开多线程

		HalconCpp::ZoomImageSize(Dlg->ho_Image, &Dlg->ho_Image, Dlg->rect.Width(), Dlg->rect.Width(), "nearest_neighbor");
		DispObj(Dlg->ho_Image, HalconCpp::HDevWindowStack::GetActive());  //一直采集,直到摄像头关闭???
	}
}

//打开摄像头,但是不做显示,打开摄像头,做显示
//突然发现有问题了,打开摄像头是在一个窗口做的 //异步显示还是同步显示  如何显示,写一个halcon打开摄像头函数? //开始异步采集图像,并且显示到窗口,那难度有点大
// 异步是写在哪里,怎么写,实现异步
// 头疼的地方来

void MFC_HALCON_Dlg::OnClose() {
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	RUNPICTRUE(this);
	CDialogEx::OnClose();
}

BOOL MFC_HALCON_Dlg::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)    //回车
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)    //ESC
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}