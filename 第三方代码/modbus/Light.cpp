#include "pch.h"
#include "Light.h"

Light::Light() {
	ByteZest();
}

Light::~Light() {
	LightClose();
	RTUCloseCom();
}

bool Light::OpenLightCom(unsigned int NumCom, DWORD dwBaud, BYTE nDataBits, BYTE parity,
	BYTE stopBits) {
	if (!RTUOpenCom(NumCom, 38400, nDataBits, parity, stopBits)) {
		return false;
	}
	return true;
}

bool Light::CloseLightCom() {
	RTUCloseCom();
	return true;
}

bool Light::LightChangeNum(unsigned int Num, unsigned  int Lig) {
	unsigned long _Num = (Num * 2 - 1);
	if (_Num > UINT_MAX) {
		return false;
	}
	_byte[_Num] = Lig;//无语了,都
	return WriteBool();//我觉得有必要弄一个vpn,为什么,信息收集能力
}

bool Light::LightAllNum(unsigned Lig) {
	ByteZest();
	_byte[1] = Lig;
	_byte[3] = Lig;
	_byte[5] = Lig;
	_byte[7] = Lig;
	return WriteBool();
}

bool Light::LightClose() {
	ByteZest();
	return WriteBool();
}

void Light::ByteZest(unsigned int Num) {
	for (unsigned char& i : _byte) {
		i = Num;//i个锤子i啊,就这样当作把
	}
}

bool Light::WriteBool() {
	if (!RTUWriteMultipleRegisters(20, 1, 4, _byte)) {
		return false;
	}
	return true;
}