#include "pch.h"
#include "MyWayGifControl.h"

#include <afxdialogex.h>

WE::MyWayGifControl::~MyWayGifControl() {
	if (ptr != nullptr) { //ե�ɱ�����,�ѱ��������������õ�����
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
		delete dlg->ptr;  //������,? //ʹ��
		dlg->ptr = nullptr;
	}

	dlg->ptr = new GIF_OpenCv;//����һ���������
	dlg->ptr->Load(path, nID, __dlg);
	dlg->ptr->Run();
}