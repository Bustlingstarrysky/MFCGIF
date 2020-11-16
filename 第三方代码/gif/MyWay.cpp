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

	Images.clear();//��д�쳣
	while (true) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		//CImage image;
		//MatChangeCImage(frame.clone(), image);

		Images.push_back(frame.clone());
	}//�Լ�ȥ����
	capture.release();
}

void WE::GIF_OpenCv::Load(std::string path, CRect rect) {
	//һ��ʼ��������,���û�취
	VideoCapture capture;
	Mat frame;
	capture.open(path); //��ȡgif�ļ�
	cv::Size DST(rect.Width(), rect.Height());
	Images.clear();//��д�쳣
	while (true) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		cv::resize(frame, frame, DST, 0, 0, cv::INTER_CUBIC);
		Images.push_back(frame.clone());
	}//�Լ�ȥ����
	capture.release();
}
void WE::GIF_OpenCv::Run(int ID, int time, CDialogEx* dlg) {
	//�ȼӵ���
	stop = true;

	//lambal;f
	auto func = [](bool* stop, int ID, int time, CDialogEx* dlg, std::vector<Mat>* images)mutable ->void {
		//	dlg->GetDlgItem(ID);

		while (*stop) {
			int i = 0;
			for (auto& it : (*images)) {
				cv::imwrite("picture/demo.jpg", it);
				WE::Drawpic::DRAWDRAW(ID, CString(L"picture/demo.jpg"), dlg);
				//	if (!(*stop)) {
				//		return;
				//	}//�Ҿ�
				Sleep(10);
			}
		}
	};

	TheFuture = std::async(func, &stop, ID, time, dlg, &Images);
}

void WE::GIF_OpenCv::Stop() {
	stop = false;

	TheFuture.get();
	//Sleep(1000);

	//TheFuture = nullptr;
}

WE::GIF_OpenCv::~GIF_OpenCv() {
	if (stop == true) {
		Stop();
	}
}

void WE::GIF_OpenCv::MatChangeCImage(Mat& mat, CImage& cImage) {
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy(); //clear
	cImage.Create(width,
		height, //positive: left-bottom-up   or negative: left-top-down
		8 * channels); //numbers of bits per pixel

	//copy values
	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); //A pointer to the bitmap buffer

	//The pitch is the distance, in bytes. represent the beginning of
	// one bitmap line and the beginning of the next bitmap line
	int step = cImage.GetPitch();

	for (int i = 0; i < height; ++i) {
		ps = (mat.ptr<uchar>(i));
		for (int j = 0; j < width; ++j) {
			if (channels == 1) //gray
			{
				*(pimg + i * step + j) = ps[j];
			}
			else if (channels == 3) //color
			{
				for (int k = 0; k < 3; ++k) {
					*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
				}
			}
		}
	}
}