// ModbusRTU.cpp : ���� DLL Ӧ�ó������ڵ㡣
//
#include "pch.h"
#include "ModbusRTU.h"

BOOL RTUOpenCom(int nPort, DWORD dwBaud, BYTE nDataBits, BYTE parity,
	BYTE stopBits) {
	if (gModbus != NULL) {
		return gModbus->OpenCom(nPort, dwBaud, nDataBits, parity, stopBits);
	}
	else {
		gModbus = new CModbus();
		return gModbus->OpenCom(nPort, dwBaud, nDataBits, parity, stopBits);
	}
}
void RTUCloseCom() {
	if (gModbus != NULL) {
		gModbus->CloseCom();
		gModbus = NULL;
	}
}

WORD RTUReadCoils(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf) {
	if (gModbus != NULL) {
		return gModbus->ReadCoils(nSlaveAddress, nUnitAddress, nUnitCount, pReturnBuf);
	}
	else {
		return FALSE;
	}
}
WORD RTUReadDiscreteInputs(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf) {
	if (gModbus != NULL) {
		return gModbus->ReadDiscreteInputs(nSlaveAddress, nUnitAddress, nUnitCount, pReturnBuf);
	}
	else {
		return FALSE;
	}
}
WORD RTUReadHoldingRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf) {
	if (gModbus != NULL) {
		Sleep(10);
		return gModbus->ReadHoldingRegisters(nSlaveAddress, nRegAddress, nRegCount, pReturnBuf);
	}
	else {
		return FALSE;
	}
}
WORD RTUReadInputRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf) {
	if (gModbus != NULL) {
		return gModbus->ReadInputRegisters(nSlaveAddress, nRegAddress, nRegCount, pReturnBuf);
	}
	else {
		return FALSE;
	}
}
WORD RTUWriteSingleCoil(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue) {
	if (gModbus != NULL) {
		return gModbus->WriteSingleCoil(nSlaveAddress, nRegAddress, nUnitValue);
	}
	else {
		return FALSE;
	}
}
WORD RTUWriteSingleRegister(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue) {
	if (gModbus != NULL) {
		return gModbus->WriteSingleRegister(nSlaveAddress, nRegAddress, nUnitValue);
	}
	else {
		return FALSE;
	}
}
WORD RTUWriteMultipleCoils(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf) {
	if (gModbus != NULL) {
		return gModbus->WriteMultipleCoils(nSlaveAddress, nRegAddress, nUnitCount, pWriteBuf);
	}
	else {
		return FALSE;
	}
}
WORD RTUWriteMultipleRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf) {
	if (gModbus != NULL) {
		Sleep(30);
		return gModbus->WriteMultipleRegisters(nSlaveAddress, nRegAddress, nUnitCount, pWriteBuf);
	}
	else {
		return FALSE;
	}
}