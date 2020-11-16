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
	_byte[_Num] = Lig;//溢出就直接截断
	return WriteBool();
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
	for (int i = 0; i < 8; ++i) {
		_byte[i] = Num;
	}
}

bool Light::WriteBool() {
	if (!RTUWriteMultipleRegisters(20, 1, 4, _byte)) {
		return false;
	}
	return true;
}