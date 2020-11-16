#include "pch.h"
#include "MyWayGifControl.h"

#include <afxdialogex.h>

WE::MyWayGifControl::~MyWayGifControl() {
	if (ptr != nullptr) { //榨干编译器,把编译器的能力运用到极限
		ptr->Stop();
		delete ptr;
		ptr = nullptr;
	}
}

void WE::MyWayGifControl::Stop() {
	if (ptr != nullptr) {
		ptr->Stop();
		delete ptr;
		ptr = nullptr;
	}
}

void WE::MyWayGifControl::run(MyWayGifControl* dlg, std::string& path, int nID, CDialogEx* __dlg) {
	if (dlg->ptr != nullptr) {
		dlg->ptr->Stop();
		delete dlg->ptr;  //完事了,? //使得
		dlg->ptr = nullptr;
	}

	dlg->ptr = new GIF_OpenCv;//兼容一下这个容器
	dlg->ptr->Load(path, nID, __dlg);
	dlg->ptr->Run();
}