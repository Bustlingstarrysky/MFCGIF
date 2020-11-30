#pragma once

#ifndef  CAMERA_H_H_H
#define   CAMERA_H_H_H
#include"GalaxyIncludes.h"
#include "ERROR.h"

#include <iostream>
#include<vector>
namespace WE {
	class DAHENG
	{
	public:
		DAHENG();
		~DAHENG();

		//遍历设备ID,通过ID打开摄像头
	};
	void FindCamera(GxIAPICPP::gxdeviceinfo_vector&);
}

#endif
