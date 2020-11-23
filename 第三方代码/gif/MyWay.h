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
		virtual void Show() = 0;//����id,�������
		virtual ~INSHOW() = default;
	};

	class SHOW_CLASS//��ʾ�Ĵ���,���߳�,���߳�,����ʲô��������
	{
	public:
		virtual void RunShow() = 0;//����show Ȼ������show
		virtual void Stop() = 0;
		virtual void Pause() = 0;
		virtual void GoOn() = 0;
		virtual bool IsRun() = 0;
		SHOW_CLASS() = default;
		virtual ~SHOW_CLASS() = default;
	};

	//�ù���������,�ȱ���,������ô��,�涨��һ��ͼƬ
	//���������������Լ����еĶ���,
	class SHOW_FACTORY
	{
	public:
		virtual  SHOW_CLASS* CREATE() = 0;
		virtual ~SHOW_FACTORY() = default;
	};

	class CIMAGE_SHOW_CLASS :public SHOW_CLASS//����һ�������������,Ӧ���ɹ���ȥ����,�ṩ���߲�εĳ���
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
		//�񾭲�,ʲô��ɫ

	//	std::vector<std::unique_ptr<CImage>> Images;
		SHOW_CLASS* _SHOW;
	private:

	public:

		void Load(std::string path, int nID, CDialogEx* dlg);//����,��С�Ѿ��ĺ���
		void Run();
		void Stop();
		GIF_OpenCv();
		~GIF_OpenCv();
	private:
		//	void MatChangeCImage(Mat&, CImage&);
	};//����������������
	//��һ:��ȡͼ��,�洢��vector,����,����,���ǲ���ͼ����ʲô,������һ��vector

	//�����װ,ʹ�ü��˶���,Ȼ�����ȥ�޸�����,ʹ�ö��߳�

	class GIF_Factory_control //�̳�������.�̳�˰? ��run��������
	{
		//ʵ������
	public:

	private:
		GIF_OpenCv* prt;
	};
}

#endif
