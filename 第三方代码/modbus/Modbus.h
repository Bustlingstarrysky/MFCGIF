
#pragma once

#include "SerialPort.h"

// Define Modbus Constant
#define MAX_MODBUS_DATA_LENGTH				252
#define MAX_MODBUS_RTU_FRAME_LENGTH			256
#define MAX_MODBUS_ASCII_FRAME_LENGTH		513
#define MAX_MODBUS_RETRY_TIMES				3
#define MODBUS_RESPONSE_TIME_OUT			200		// Response time-out: 0.1s
#define MODBUS_TURNAROUND_TIME_OUT			200			// Trnaround time-out: 200ms
// Define Modbus function code
#define MODBUS_READ_COILS					0x01
#define MODBUS_READ_DISCRETE_INPUTS			0x02
#define MODBUS_READ_HOLDING_REGISTERS		0x03
#define MODBUS_READ_INPUT_REGISTERS			0x04
#define MODBUS_WRITE_SINGLE_COIL			0x05
#define MODBUS_WRITE_SINGLE_REGISTER		0x06
#define MODBUS_WRITE_MULTIPLE_COILS			0x0F
#define MODBUS_WRITE_MULTIPLE_REGISTERS		0x10
// Define error code
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

// ---- CModbus class ----
class CModbus : public CSerialPort
{
public:
	
	CModbus();
	~CModbus();

	BOOL OpenCom(int nPort, DWORD dwBaud = 9600, BYTE nDataBits = 8, BYTE parity = 0, BYTE stopBits = 0);
	void CloseCom();
	inline int GetResponseTimeOut() { return m_nResponseTimeOut; }
	inline void SetResponseTimeOut(int nTimeOut) { m_nResponseTimeOut = nTimeOut; }
	WORD ReadHoldingRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf);
	WORD ReadInputRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf);
	WORD WriteSingleCoil(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue);
	WORD WriteSingleRegister(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue);
	WORD WriteMultipleCoils(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf);
	WORD WriteMultipleRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf);
	WORD ReadCoils(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf);
	WORD ReadDiscreteInputs(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf);

private:
	WORD ReadRegisters(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf);
	WORD CRC16Calculate(BYTE* pMsg, WORD nDataLen);
	WORD CRC16Table(BYTE* pMsg, WORD nDataLen);
	WORD CRC16(BYTE* pMsg, WORD nDataLen, BOOL bTable = TRUE);
	WORD WriteSingleUint(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nRegAddress, WORD nUnitValue);
	WORD WriteMultipleUnits(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf);
	WORD ReadMultipleUnits(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf);
	//限制线程
	HANDLE				m_hThread;
	static DWORD WINAPI ThreadProc(LPVOID lpParam);

protected:
	BYTE* m_pSendBuf;			// Request buffer
	BYTE* m_pReceiveBuf;		// Response buffer
	DWORD m_nResponseTimeOut;		// Response time out
	
};

extern CModbus* gModbus;
