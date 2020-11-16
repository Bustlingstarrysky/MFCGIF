#pragma once
#include <map>

#include "ModbusRTU.h"

class Light
{
public:
	Light();
	~Light();

	bool OpenLightCom(unsigned int NumCom, DWORD dwBaud = 38400, BYTE nDataBits = 8, BYTE parity = 0,
		BYTE stopBits = 0);
	bool CloseLightCom();

	bool LightChangeNum(unsigned int Num, unsigned int Lig = 250);
	bool LightAllNum(unsigned int Lig = 250);
	bool LightClose();

private:
	void ByteZest(unsigned int Num = 0);
	bool WriteBool();

	BYTE _byte[8];
};
