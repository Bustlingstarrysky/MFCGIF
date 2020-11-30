#include"pch.h"
#include"Camera.h"

#include"ERROR.h"
WE::DAHENG::DAHENG() {
	IGXFactory::GetInstance().Init();
}
//我并不想让他可维护,里面内容太多了
//用我的方法来实现把,一次性把所有的东西全部隐藏,然后每次动用就全部显示,我根本想不到有什么办法能在list里面加控件
//很臭的办法,我不自绘控件,谢谢 , 我只会做映射,没错,我只会做映射,然后把控件显示出来
WE::DAHENG::~DAHENG() {
	IGXFactory::GetInstance().Uninit();;
}

void WE::FindCamera(GxIAPICPP::gxdeviceinfo_vector& vector) {
	//WE::DAHENG ces;
	//IGXFactory::GetInstance().Init();
	IGXFactory::GetInstance().UpdateAllDeviceList(1000, vector);
	//IGXFactory::GetInstance().Uninit();;
	//根据这个返回的值获得所有信息
}