#pragma once

#include<map>
#include<string>
#include <memory>
#ifndef H_DSF_HHH_
#define H_DSF_HHH_
// 规定所有窗口的函数,并且规定哪个给哪个通信 通信窗口 运行窗口 美容
#define PANEL_MAIN_BREAK 1//退出窗口,由控制面板通知主窗口    写了
//
#define SET_摄像机信息_Open 4001
#define SET_摄像机信息_Close 4002
#define SET_图像格式控制_Open 4003
#define SET_图像格式控制_Close 4004
//
//
namespace NN {
#define PANEL_HALCON_OpenCamera 2 // 打开摄像头的消息 //MSG factory 宏定义 // 未定义 ,这个实际上很简单
#define PANEL_HALCON_Picturing 3 // 实时采集图像
#define PANEL_HALCON_ShowPicture 4 // 显示采集的图像
#define PANEL_HALCON_CLOSSCAMERA  5 //关闭摄像头 // 反正规定是规定好了

#define PANEL_HALCON_PICTURETOP 6
#define PANEL_HALCON_PICTUREDOWN 7
#define PANEL_HALCON_PICTURELEFT 8
#define PANEL_HALCON_PICTURERIGHT 9

	//主题可以走消息通知吗,不行,主题消息通知太多,不能作为一个消息来调用
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

	template<typename T, typename ...Args>                 //用什么string
	void MSGfactory(int ID, T func, Args ... args) {
		GetMap().insert(std::map<int, WE::__LL::____FATHER*>::value_type(ID, new __LL::CHILD<T, Args...>(func, args...)));
	}
	void RUNTIMING(int);//工厂把函数放进去,run的时候去查找,那么,需要一个索引,来确保查找没问题//而不是字符串口,并且宏定义,只能用宏,明白吗
}

#endif