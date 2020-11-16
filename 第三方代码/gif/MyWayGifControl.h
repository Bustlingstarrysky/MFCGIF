#pragma once

#include"MyWay.h"
//有命名域混乱的原因
namespace WE {
	class MyWayGifControl
	{
	private:
		GIF_OpenCv* ptr;//方式用智能指针

	public:

		MyWayGifControl() = default;//用默认的
		~MyWayGifControl();//delete prt就行了,调用析构是它的事情
	//这是一个主题管理器,用来控制gif
		void Stop();
	public:
		static void run(MyWayGifControl* dlg, std::string& path, int nID, CDialogEx* __dlg);
	};
}
