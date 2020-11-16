#pragma once
#include "Modbus.h"

BOOL RTUOpenCom(int nPort, DWORD dwBaud = 9600, BYTE nDataBits = 8, BYTE parity = 0,
	BYTE stopBits = 0);
void RTUCloseCom();

#define MODBUS_SUCCESS						0x0000		// SUCCESS
#define MODBUS_EXCEPTION					0x8000		// EXCEPTION
#define MODBUS_EXCEPTION_CODE_01			0x0001
#define MODBUS_EXCEPTION_CODE_02			0x0002
#define MODBUS_EXCEPTION_CODE_03			0x0003
#define MODBUS_EXCEPTION_CODE_04			0x0004
#define MODBUS_ERROR_CRC					0x4001		// ERROR
#define MODBUS_ERROR_ADDRESS				0x4002
#define MODBUS_ERROR_FUNCTION_CODE			0x4003
#define MODBUS_ERROR_DATA					0x4004
#define MODBUS_ERROR_RESPONSE_COUNT			0x4005
#define MODBUS_ERROR_WRITE_TIME_OUT			0x4006
#define MODBUS_ERROR_RESPONSE_TIME_OUT		0x4007
#define MODBUS_ERROR_RESERVED_FUNCTION		0x4008
#define MODBUS_ILLEGAL_DEVICE_ADDRESS		0x2001		// ILLEGAL
#define MODBUS_ILLEGAL_FUNCTION_CODE		0x2002
#define MODBUS_ILLEGAL_REQUEST_COUNT		0x2003
#define MODBUS_ILLEGAL_PARAMETER			0x2004

WORD RTUReadCoils(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf);
WORD RTUReadDiscreteInputs(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf);
WORD RTUReadHoldingRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf);
WORD RTUReadInputRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf);
WORD RTUWriteSingleCoil(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue);
WORD RTUWriteMultipleCoils(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf);
WORD RTUWriteSingleRegister(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue);
WORD RTUWriteMultipleRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf);
