#pragma once

#include"MyWay.h"
//����������ҵ�ԭ��
namespace WE {
	class MyWayGifControl
	{
	private:
		GIF_OpenCv* ptr;//��ʽ������ָ��

	public:

		MyWayGifControl() = default;//��Ĭ�ϵ�
		~MyWayGifControl();//delete prt������,������������������
	//����һ�����������,��������gif
		void Stop();
	public:
		static void run(MyWayGifControl* dlg, std::string& path, int nID, CDialogEx* __dlg);
	};
}
