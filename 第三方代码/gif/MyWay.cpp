#include "pch.h"
#include "MyWay.h"
#include "assert.h"//��Ϸ����
//#include <afxcontrolbars.h>
#include "../drawpicture/DRAW.h"
void WE::GIF_OpenCv::Load(std::string path) {
	//һ��ʼ��������,���û�취
	VideoCapture capture;
	Mat frame;
	capture.open(path); //��ȡgif�ļ�

WE::CIMAGE_SHOW_CLASS::~CIMAGE_SHOW_CLASS() {}

//先说一下这个方法的实现,//在哪里显示不规它管
void WE::CIMAGE_SHOW_CLASS::RunShow() {
	//我开多线程,这个时候要有一个函数执行
	END = false;
	PAUSE = false;
	BEGIN = true;
	func = std::async(std::launch::async, &CIMAGE_SHOW_CLASS::Async, this);
}
		//CImage image;
		//MatChangeCImage(frame.clone(), image);

void WE::CIMAGE_SHOW_CLASS::Stop() {
	if (BEGIN) {
		END = true;
		BEGIN = false;
		func.get();
		//Sleep(100);
	}
	//���� ����ô��
}

void WE::CIMAGE_SHOW_CLASS::Pause() {
	if (BEGIN) {
		PAUSE = true;
	}
		cv::resize(frame, frame, DST, 0, 0, cv::INTER_CUBIC);
		Images.push_back(frame.clone());
	}//�Լ�ȥ����
	capture.release();
}
void WE::GIF_OpenCv::Run(int ID, int time, CDialogEx* dlg) {
	//�ȼӵ���
	stop = true;

void WE::CIMAGE_SHOW_CLASS::GoOn() {
	if (BEGIN) {
		PAUSE = false;
	}
}
	};

bool WE::CIMAGE_SHOW_CLASS::IsRun() {
	if (BEGIN) {
		return true;
	}
	else {
		return false;
	}
}

void WE::CIMAGE_SHOW_CLASS::Async() {
	while (!END) {
		for (auto& it : SHOWS) {
			it->Show();//执行这个函数,这个函数是什么,我不关心
			Sleep(50);
			while (PAUSE) {
				Sleep(10);
			}
		}
	}
}

void WE::CIMAGE_SHOW_CLASS::add_vector(INSHOW* m_inshow) {
	SHOWS.push_back(std::unique_ptr<INSHOW>(m_inshow));
}

void WE::CIMAGE_SHOW_CLASS::pop_vector() {
	if (!SHOWS.empty()) {
		SHOWS.pop_back();//main是主流程
	}
}

WE::CIMAGE_INSHOW::CIMAGE_INSHOW(std::unique_ptr<CImage>& m_image, int m_nid, CDialogEx* m_dlg) {
	image = std::move(m_image);
	nID = m_nid;
	dlg = m_dlg;
}

void WE::CIMAGE_INSHOW::Show() {
	WE::Drawpic::DRAWDRAWDC(nID, *image, dlg);
}

WE::SHOW_FACTORY_CIMAGE_SHOW_CLASS::SHOW_FACTORY_CIMAGE_SHOW_CLASS(std::string& path, int nID, CDialogEx* dlg) :path(path), nID(nID), dlg(dlg) {};

WE::SHOW_CLASS* WE::SHOW_FACTORY_CIMAGE_SHOW_CLASS::CREATE() {
	cv::VideoCapture capture;
	cv::Mat frame;
	capture.open(path); //读取gif文件
	auto result = new CIMAGE_SHOW_CLASS();
	while (true) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		cv::imwrite("picture/demo.jpg", frame);
		auto image = std::make_unique<CImage>(CImage());
		image->Load(L"picture/demo.jpg");
		auto ptr = new CIMAGE_INSHOW(image, nID, dlg);
		result->add_vector(ptr);
	}//自己去调用
	capture.release();

	return result;
}

void WE::GIF_OpenCv::Load(std::string path, int nID, CDialogEx* dlg) {
	SHOW_FACTORY_CIMAGE_SHOW_CLASS factory(path, nID, dlg);
	_SHOW = factory.CREATE(); //这是一个new ,可以把_SHOW指向
}

void WE::GIF_OpenCv::Run() {
	if (_SHOW != nullptr) {
		_SHOW->RunShow();
	}
			else if (channels == 3) //color
			{
				for (int k = 0; k < 3; ++k) {
					*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
}

void WE::GIF_OpenCv::Stop() {
	if (_SHOW != nullptr) {
		_SHOW->Stop();
	}
}

WE::GIF_OpenCv::GIF_OpenCv() :_SHOW(nullptr) {}

WE::GIF_OpenCv::~GIF_OpenCv() {
	if (_SHOW != nullptr) {
		_SHOW->Stop();
		delete _SHOW;
	}
}