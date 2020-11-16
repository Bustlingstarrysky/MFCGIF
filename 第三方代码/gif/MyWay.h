#pragma once
#ifndef MyWay_h_h_

#define MyWay_h_h_

#include <vector>
#include <opencv2/opencv.hpp>
//#include <atlimage.h>
#include"../drawpicture/DRAW.h"
#include <future>
namespace WE {
	using namespace cv;

	class GIF_OpenCv
	{
	private:

		//CImage image;
		//std::vector<Mat> MatImages;
		std::vector<Mat> Images;
	private:
		std::future<void> TheFuture;
		bool stop;
	public:
		void Load(std::string path);//不用,大小已经改好了
		void Load(std::string path, CRect rect);
		void Run(int ID, int time, CDialogEx* dlg);
		void Stop();
		GIF_OpenCv() = default;
		~GIF_OpenCv();
	private:
		void MatChangeCImage(Mat&, CImage&);
	};
}

#endif
