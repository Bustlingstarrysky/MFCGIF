#pragma once

#include<map>
#include<string>
#include <memory>
#ifndef H_DSF_HHH_
#define H_DSF_HHH_
// �涨���д��ڵĺ���,���ҹ涨�ĸ����ĸ�ͨ�� ͨ�Ŵ��� ���д��� ����
#define PANEL_MAIN_BREAK 1//�˳�����,�ɿ������֪ͨ������    д��
//
#define SET_�������Ϣ_Open 4001
#define SET_�������Ϣ_Close 4002
#define SET_ͼ���ʽ����_Open 4003
#define SET_ͼ���ʽ����_Close 4004
//
//
namespace NN {
#define PANEL_HALCON_OpenCamera 2 // ������ͷ����Ϣ //MSG factory �궨�� // δ���� ,���ʵ���Ϻܼ�
#define PANEL_HALCON_Picturing 3 // ʵʱ�ɼ�ͼ��
#define PANEL_HALCON_ShowPicture 4 // ��ʾ�ɼ���ͼ��
#define PANEL_HALCON_CLOSSCAMERA  5 //�ر�����ͷ // �����涨�ǹ涨����

#define PANEL_HALCON_PICTURETOP 6
#define PANEL_HALCON_PICTUREDOWN 7
#define PANEL_HALCON_PICTURELEFT 8
#define PANEL_HALCON_PICTURERIGHT 9

	//�����������Ϣ֪ͨ��,����,������Ϣ֪̫ͨ��,������Ϊһ����Ϣ������
}
namespace WE {
	//	static	std::map<std::string, std::unique_ptr<WE::MY::function>>* prt;

		//	std::map<std::string, std::unique_ptr<WE::MY::function>>* RunFactor::prt = nullptr;
	namespace __LL {
		class ____FATHER
		{
		public:
			virtual void run() = 0;
		};

		template <typename T, typename ...Args>
		class CHILD :public ____FATHER
		{
		public:
			CHILD(T func, Args...args) {
				this->func = func;
				Parme = std::make_tuple(args...);
			};

			virtual void run() override {
				std::apply(func, Parme);
			}
		private:
			T func;
			std::tuple<Args...> Parme;
		};
	}
	std::map<int, std::unique_ptr<WE::__LL::____FATHER>>& GetMap();

	template<typename T, typename ...Args>                 //��ʲôstring
	void MSGfactory(int ID, T func, Args ... args) {
		GetMap().insert(std::map<int, WE::__LL::____FATHER*>::value_type(ID, new __LL::CHILD<T, Args...>(func, args...)));
	}
	void RUNTIMING(int);//�����Ѻ����Ž�ȥ,run��ʱ��ȥ����,��ô,��Ҫһ������,��ȷ������û����//�������ַ�����,���Һ궨��,ֻ���ú�,������
}

#endif