#pragma once
#ifndef MyWay_h_h_

#define MyWay_h_h_

#include <vector>
#include <opencv2/opencv.hpp>
//#include <atlimage.h>
#include"../drawpicture/DRAW.h"
#include <future>
namespace WE {
	//using namespace cv;

	class INSHOW
	{
	public:
		INSHOW() = default;
		virtual void Show() = 0;//不用id,这个东西
		virtual ~INSHOW() = default;
	};

	class SHOW_CLASS//显示的次数,多线程,单线程,或者什么乱起八糟的
	{
	public:
		virtual void RunShow() = 0;//运行show 然后运行show
		virtual void Stop() = 0;
		virtual void Pause() = 0;
		virtual void GoOn() = 0;
		virtual bool IsRun() = 0;
		SHOW_CLASS() = default;
		virtual ~SHOW_CLASS() = default;
	};

	//用工厂来处理,先别处理,容器怎么办,规定给一个图片
	//工厂创造出这个类以及所有的东西,
	class SHOW_FACTORY
	{
	public:
		virtual  SHOW_CLASS* CREATE() = 0;
		virtual ~SHOW_FACTORY() = default;
	};

	class CIMAGE_SHOW_CLASS :public SHOW_CLASS//这是一个工厂给你的类,应该由工厂去调用,提供更高层次的抽象
	{
	public:
		CIMAGE_SHOW_CLASS() = default;
		~CIMAGE_SHOW_CLASS();
		virtual void RunShow()override;
		virtual void Stop()override;
		virtual void Pause() override;
		virtual void GoOn() override;
		virtual bool IsRun()override;
		virtual void Async();

		void add_vector(INSHOW*);
		void pop_vector();
	protected:
		std::vector<std::unique_ptr<INSHOW>> SHOWS;
		bool PAUSE = false;
		bool END = true;
		bool BEGIN = false;
		std::future<void> func;
	};

	class CIMAGE_INSHOW :public INSHOW
	{
	public:
		//CIMAGE_INSHOW(CImage*);
		CIMAGE_INSHOW(std::unique_ptr<CImage>&, int, CDialogEx*);
		~CIMAGE_INSHOW() = default;
		virtual void Show() override;

	private:
		std::unique_ptr<CImage> image;
		int nID;
		CDialogEx* dlg;
	};
	class SHOW_FACTORY_CIMAGE_SHOW_CLASS :public SHOW_FACTORY
	{
	public:
		SHOW_FACTORY_CIMAGE_SHOW_CLASS(std::string& path, int nID, CDialogEx* dlg);
		virtual SHOW_CLASS* CREATE() override;
		~SHOW_FACTORY_CIMAGE_SHOW_CLASS() = default;
	private:
		std::string path;
		int nID;
		CDialogEx* dlg;
	};

	class GIF_OpenCv
	{
	private:
		//神经病,什么乐色

	//	std::vector<std::unique_ptr<CImage>> Images;
		SHOW_CLASS* _SHOW;
	private:

	public:

		void Load(std::string path, int nID, CDialogEx* dlg);//不用,大小已经改好了
		void Run();
		void Stop();
		GIF_OpenCv();
		~GIF_OpenCv();
	private:
		//	void MatChangeCImage(Mat&, CImage&);
	};//这个代码有三个层次
	//第一:读取图像,存储进vector,所以,所以,我们不管图像是什么,它就是一个vector

	//主题封装,使用极端定义,然后可以去修改主题,使用多线程

	class GIF_Factory_control //继承它干嘛.继承税? 把run都给割了
	{
		//实现了吗
	public:

	private:
		GIF_OpenCv* prt;
	};
}

#endif
