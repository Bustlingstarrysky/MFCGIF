#pragma once
#ifndef ERROR_R_R_R_
#define ERROR_R_R_R_

#define MY_ERROR__0 "成功"
#define MY_ERROR__1 "不期望发生错误"
#define MY_ERROR__2 "找不到TL库"
#define MY_ERROR__3 "找不到设备"
#define MY_ERROR__4 "当前设备为掉线设备"
#define MY_ERROR__5 "无效参数"

#define MY_ERROR__6 "无效句柄"
#define MY_ERROR__7 "无效的接口调用"
#define MY_ERROR__8 "功能当前不可访问或设备访问错误"
#define MY_ERROR__9 "用户buffer不足"
#define MY_ERROR__10 "Feature类型错误,比如用IntFeature操作浮点功能"
#define MY_ERROR__11 "写入值越界"

#define MY_ERROR__12 "不支持的功能"
#define MY_ERROR__13 "没有调用初始化接口"
#define MY_ERROR__14 "超时错误"

#define MY_ERROR__ "非错误码里面的错误"
//接管所有的错误处理,直接宏定义也好,不是宏也好,反正就是接管
//接管错误

#define MY_ERROR_TRY(_1)\
	try{  \
	  _1();\
	} \
	catch (CGalaxyException& e)\
	{\
	WE::MY_MFC_ERROR TRY;	\
	TRY.MyError(e.GetErrorCode()); \
	\
};\//这样就行了

namespace WE {
	class MY_ERROR
	{
	public:
		virtual void MyError(int i) = 0;
	};
	class MY_MFC_ERROR : public MY_ERROR
	{
	public:
		virtual void MyError(int i) override;
	};
}

#endif
