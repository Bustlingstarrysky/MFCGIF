#include "pch.h"

#include "Modbus.h"
#define  myTimeOut 7200  //2h

// Table of CRC values for high–order byte
static BYTE auchCRCHi[] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40
};
// Table of CRC values for low–order byte
static BYTE auchCRCLo[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
	0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
	0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
	0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
	0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
	0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
	0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
	0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
	0x40
};
CModbus* gModbus = NULL;
// ---- CModbus class ----
CModbus::CModbus()

	: m_pSendBuf(NULL)
	, m_pReceiveBuf(NULL)
	, m_nResponseTimeOut(MODBUS_RESPONSE_TIME_OUT) {
	gModbus = this;
}

CModbus::~CModbus() {
	Close();
}

DWORD WINAPI CModbus::ThreadProc(LPVOID lpParam) {
	DWORD dCounter = 0;

	while (1) {
		dCounter++;
		if (dCounter > myTimeOut)// Time out
		{
			gModbus->CloseCom();
		}
		Sleep(1000);
	}
	return 0;
}
BOOL CModbus::OpenCom(int nPort, DWORD dwBaud, BYTE nDataBits, BYTE parity, BYTE stopBits) {
	// Close Modbus port if it's opened
	//Close();
	// Allocate buffer

	m_pSendBuf = new BYTE[MAX_MODBUS_RTU_FRAME_LENGTH];
	m_pReceiveBuf = new BYTE[MAX_MODBUS_RTU_FRAME_LENGTH];
	//    m_hThread = CreateThread(NULL, 0, ThreadProc, this, 0, 0);
	return CSerialPort::Open(nPort, dwBaud, nDataBits, parity, stopBits);
}

void CModbus::CloseCom() {
	if (m_pSendBuf != NULL) {
		delete[] m_pSendBuf;
		m_pSendBuf = NULL;
	}
	if (m_pReceiveBuf != NULL) {
		delete[] m_pReceiveBuf;
		m_pReceiveBuf = NULL;
	}
	CSerialPort::Close();
}

WORD CModbus::CRC16Calculate(BYTE* pMsg, WORD nDataLen) {
	WORD nCarryFlag;
	WORD nTempCRC = 0xFFFF;
	for (int i = 0; i < nDataLen; i++) {
		nTempCRC ^= pMsg[i];
		for (int j = 0; j < 8; j++) {
			nCarryFlag = nTempCRC & 0x0001;
			nTempCRC >>= 1;
			if (nCarryFlag) nTempCRC ^= 0xA001;
		}
	}
	// swap higher and lower bytes of CRC
	nTempCRC = (nTempCRC >> 8) | (nTempCRC << 8);

	return nTempCRC;
}

WORD CModbus::CRC16Table(BYTE* pMsg, WORD nDataLen) {
	BYTE nCRCHi = 0xFF;		// high byte of CRC initialized
	BYTE nCRCLo = 0xFF;		// low byte of CRC initialized
	WORD nIndex;			// will index into CRC lookup table
	while (nDataLen--)		// pass through message buffer
	{
		nIndex = nCRCLo ^ *pMsg++;		// calculate the CRC
		nCRCLo = nCRCHi ^ auchCRCHi[nIndex];
		nCRCHi = auchCRCLo[nIndex];
	}
	// swap higher and lower bytes of CRC
	return (nCRCLo << 8 | nCRCHi);
}

WORD CModbus::CRC16(BYTE* pMsg, WORD nDataLen, BOOL bTable) {
	if (bTable)
		return CRC16Table(pMsg, nDataLen);
	else
		return CRC16Calculate(pMsg, nDataLen);
}

// Buffer size >= nRegCount * 2
WORD CModbus::ReadRegisters(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf) {
	// Modbus address rule -- 0: Broadcasr address, 1-247: Slave individual address, 248-255: Reserved
	if ((nSlaveAddress < 1) || (nSlaveAddress > 247))
		return MODBUS_ILLEGAL_DEVICE_ADDRESS;
	// This function is only called by modbus function code: MODBUS_READ_HOLDING_REGISTERS or MODBUS_READ_INPUT_REGISTERS
	if ((nFunctionCode != MODBUS_READ_HOLDING_REGISTERS) && (nFunctionCode != MODBUS_READ_INPUT_REGISTERS))
		return MODBUS_ILLEGAL_FUNCTION_CODE;
	// Quantity of registers: 1 to 125(0X7D)
	if ((nRegCount < 1) || (nRegCount > 125))
		return MODBUS_ILLEGAL_REQUEST_COUNT;

	// Send request message frame
	m_pSendBuf[0] = nSlaveAddress;			// Slave device address
	m_pSendBuf[1] = nFunctionCode;			// Function code
	m_pSendBuf[2] = nRegAddress >> 8;		// Starting address Hi
	m_pSendBuf[3] = nRegAddress & 0x00FF;	// Starting addresss Lo
	m_pSendBuf[4] = nRegCount >> 8;			// No. of registers Hi
	m_pSendBuf[5] = nRegCount & 0x00FF;		// No. of registers Lo
	WORD nCRC = CRC16(m_pSendBuf, 6);		// Generate CRC and swap it's higher and lower bytes
	m_pSendBuf[6] = nCRC >> 8;				// CRC Hi
	m_pSendBuf[7] = nCRC & 0x00FF;			// CRC Lo
	Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);	// Discard all characters from the output and input buffer
	if (Write(m_pSendBuf, 8) != 8)			// Send request message frame
		return MODBUS_ERROR_WRITE_TIME_OUT;
	// Get slave response message frame
	DWORD dwStartTime = GetTickCount();
	DWORD dwResponseTime;
	WORD nReceivedBytes = 0;
	WORD nRequiredBytes = 5 + nRegCount * 2;
	while (nReceivedBytes < nRequiredBytes) {
		nReceivedBytes += (WORD)Read(m_pReceiveBuf + nReceivedBytes, nRequiredBytes - nReceivedBytes);
		dwResponseTime = GetTickCount() - dwStartTime;
		if (dwResponseTime > m_nResponseTimeOut)		// Time out
		{
			if (nReceivedBytes == 5)			// If the count of receive bytes equals exception message length
			{
				nCRC = CRC16(m_pReceiveBuf, nReceivedBytes - 2);			// CRC ok
				if ((m_pReceiveBuf[nReceivedBytes - 2] == (nCRC >> 8)) && (m_pReceiveBuf[nReceivedBytes - 1] == (nCRC & 0x00FF)))
					if (m_pReceiveBuf[0] == m_pSendBuf[0])					// Slave device address ok
						if (m_pReceiveBuf[1] == (m_pSendBuf[1] | 0x80))		// Exception: (Function code | 0x80)
							return MODBUS_EXCEPTION | m_pReceiveBuf[2];		// Return the exception code
			}
			return MODBUS_ERROR_RESPONSE_TIME_OUT;
		}
	}

	// Decode response message
	nCRC = CRC16(m_pReceiveBuf, nRequiredBytes - 2);	// CRC error
	if ((m_pReceiveBuf[nRequiredBytes - 2] != (nCRC >> 8)) || (m_pReceiveBuf[nRequiredBytes - 1] != (nCRC & 0x00FF)))
		return MODBUS_ERROR_CRC;
	if (m_pReceiveBuf[0] != m_pSendBuf[0])				// Slave device address error
		return MODBUS_ERROR_ADDRESS;
	if (m_pReceiveBuf[1] != m_pSendBuf[1])			// Function code error
	{
		return MODBUS_ERROR_FUNCTION_CODE;
	}
	if (m_pReceiveBuf[2] != nRegCount * 2)
		return MODBUS_ERROR_RESPONSE_COUNT;
	memcpy(pReturnBuf, m_pReceiveBuf + 3, nRegCount * 2);

	//	// Send request message frame
	//	m_pSendBuf[0] = nSlaveAddress;			// Slave device address
	//	m_pSendBuf[1] = 0x40;			        // yaskawa code
	//	m_pSendBuf[2] = 0x00;			        // Function code Hi
	//	m_pSendBuf[3] = nFunctionCode;			// Function code Lo
	//	m_pSendBuf[4] =	nRegAddress >> 8;		// Starting address Hi
	//	m_pSendBuf[5] = nRegAddress & 0x00FF;	// Starting addresss Lo
	//	m_pSendBuf[6] = nRegCount >> 8;			// No. of registers Hi
	//	m_pSendBuf[7] = nRegCount & 0x00FF;		// No. of registers Lo
	//	WORD nCRC = CRC16(m_pSendBuf, 8);		// Generate CRC and swap it's higher and lower bytes
	//	m_pSendBuf[8] = nCRC >> 8;				// CRC Hi
	//	m_pSendBuf[9] = nCRC & 0x00FF;			// CRC Lo
	//	Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);	// Discard all characters from the output and input buffer
	//	if(Write(m_pSendBuf, 10) != 10)			// Send request message frame
	//		return MODBUS_ERROR_WRITE_TIME_OUT;
	//
	//	// Get slave response message frame
	//	DWORD dwStartTime = GetTickCount();
	//	DWORD dwResponseTime;
	//	WORD nReceivedBytes = 0;
	//	WORD nRequiredBytes = 8 + nRegCount * 2;
	//	while(nReceivedBytes < nRequiredBytes)
	//	{
	//		nReceivedBytes += (WORD)Read(m_pReceiveBuf + nReceivedBytes, nRequiredBytes - nReceivedBytes);
	//		dwResponseTime = GetTickCount() - dwStartTime;
	//		if(dwResponseTime > m_nResponseTimeOut)		// Time out
	//		{
	//			if(nReceivedBytes == 8)			// If the count of receive bytes equals exception message length
	//			{
	//				nCRC = CRC16(m_pReceiveBuf, nReceivedBytes - 2);			// CRC ok
	//				if((m_pReceiveBuf[nReceivedBytes - 2] == (nCRC >> 8)) && (m_pReceiveBuf[nReceivedBytes - 1] == (nCRC & 0x00FF)))
	//					if(m_pReceiveBuf[0] == m_pSendBuf[0])					// Slave device address ok
	//						if(m_pReceiveBuf[1] == (m_pSendBuf[1] | 0x80))		// Exception: (Function code | 0x80)
	//							return MODBUS_EXCEPTION | m_pReceiveBuf[2];		// Return the exception code
	//			}
	//			return MODBUS_ERROR_RESPONSE_TIME_OUT;
	//		}
	//	}
	//
	//	// Decode response message
	//	nCRC = CRC16(m_pReceiveBuf, nRequiredBytes - 2);	// CRC error
	//	if((m_pReceiveBuf[nRequiredBytes - 2] != (nCRC >> 8)) || (m_pReceiveBuf[nRequiredBytes - 1] != (nCRC & 0x00FF)))
	//		return MODBUS_ERROR_CRC;
	//	if(m_pReceiveBuf[0] != m_pSendBuf[0])				// Slave device address error
	//		return MODBUS_ERROR_ADDRESS;
	//	if(m_pReceiveBuf[1] != m_pSendBuf[1])				//
	//		return MODBUS_ERROR_ADDRESS;
	//	if(m_pReceiveBuf[2] != m_pSendBuf[2])			// Function code error
	//	{
	//		return MODBUS_ERROR_FUNCTION_CODE;
	//	}
	//	if(m_pReceiveBuf[3] != m_pSendBuf[3])			// Function code error
	//	{
	//		return MODBUS_ERROR_FUNCTION_CODE;
	//	}
	//	int reccount = 0;
	//	reccount |=  ((int)m_pReceiveBuf[4])<<8;
	//	reccount |=  (int)m_pReceiveBuf[5];
	//	if(reccount != nRegCount * 2)
	//		return MODBUS_ERROR_RESPONSE_COUNT;
	//	memcpy(pReturnBuf, m_pReceiveBuf + 6, nRegCount * 2);

	return MODBUS_SUCCESS;
}

WORD CModbus::ReadHoldingRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf) {
	return ReadRegisters(nSlaveAddress, MODBUS_READ_HOLDING_REGISTERS, nRegAddress, nRegCount, pReturnBuf);
}

WORD CModbus::ReadInputRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nRegCount, BYTE* pReturnBuf) {
	return ReadRegisters(nSlaveAddress, MODBUS_READ_INPUT_REGISTERS, nRegAddress, nRegCount, pReturnBuf);
}

WORD CModbus::WriteSingleUint(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nRegAddress, WORD nUnitValue) {
	// Modbus address rule -- 0: Broadcasr address, 1-247: Slave individual address, 248-255: Reserved
	if ((nSlaveAddress < 1) || (nSlaveAddress > 247))
		return MODBUS_ILLEGAL_DEVICE_ADDRESS;
	// This function is only called by modbus function code: MODBUS_WRITE_SINGLE_COIL or MODBUS_WRITE_SINGLE_REGISTER
	if ((nFunctionCode != MODBUS_WRITE_SINGLE_COIL) && (nFunctionCode != MODBUS_WRITE_SINGLE_REGISTER))
		return MODBUS_ILLEGAL_FUNCTION_CODE;

	// Send request message frame
	m_pSendBuf[0] = nSlaveAddress;			// Slave device address
	m_pSendBuf[1] = nFunctionCode;			// Function code
	m_pSendBuf[2] = nRegAddress >> 8;       // Starting address Hi //得到后面的值

	m_pSendBuf[3] = nRegAddress & 0x00FF;	// Starting addresss Lo //得到前面的值
	m_pSendBuf[4] = nUnitValue >> 8;		// Unit value Hi  //同理
	m_pSendBuf[5] = nUnitValue & 0x00FF;	// Unit value Lo
	WORD nCRC = CRC16(m_pSendBuf, 6);		// Generate CRC and swap it's higher and lower bytes
	m_pSendBuf[6] = nCRC >> 8;				// CRC Hi
	m_pSendBuf[7] = nCRC & 0x00FF;			// CRC Lo
	Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);	// Discard all characters from the output and input buffer
	if (Write(m_pSendBuf, 8) != 8)			// Send request message frame
		return MODBUS_ERROR_WRITE_TIME_OUT;

	// Get slave response message frame
	DWORD dwStartTime = GetTickCount();
	DWORD dwResponseTime;
	WORD nReceivedBytes = 0;
	WORD nRequiredBytes = 8;
	while (nReceivedBytes < nRequiredBytes) {
		nReceivedBytes += (WORD)Read(m_pReceiveBuf + nReceivedBytes, nRequiredBytes - nReceivedBytes);
		dwResponseTime = GetTickCount() - dwStartTime;
		if (dwResponseTime > m_nResponseTimeOut)		// Time out
		{
			if (nReceivedBytes == 5)			// If the count of receive bytes equals exception message length
			{
				nCRC = CRC16(m_pReceiveBuf, nReceivedBytes - 2);			// CRC ok
				if ((m_pReceiveBuf[nReceivedBytes - 2] == (nCRC >> 8)) && (m_pReceiveBuf[nReceivedBytes - 1] == (nCRC & 0x00FF)))
					if (m_pReceiveBuf[0] == m_pSendBuf[0])					// Slave device address ok
						if (m_pReceiveBuf[1] == (m_pSendBuf[1] | 0x80))		// Exception: (Function code | 0x80)
							return MODBUS_EXCEPTION | m_pReceiveBuf[2];		// Return the exception code
			}
			return MODBUS_ERROR_RESPONSE_TIME_OUT;
		}
	}

	// Decode response message
	if (memcmp(m_pSendBuf, m_pReceiveBuf, nRequiredBytes) != 0)
		return MODBUS_ERROR_CRC;

	return MODBUS_SUCCESS;
}

WORD CModbus::WriteSingleCoil(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue) {
	if ((nUnitValue != 0x0000) && (nUnitValue != 0xFF00))
		return MODBUS_ILLEGAL_PARAMETER;
	return WriteSingleUint(nSlaveAddress, MODBUS_WRITE_SINGLE_COIL, nRegAddress, nUnitValue);
}

WORD CModbus::WriteSingleRegister(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitValue) {
	return WriteSingleUint(nSlaveAddress, MODBUS_WRITE_SINGLE_REGISTER, nRegAddress, nUnitValue);
}

// Buffer size >= nUnitCount / 8;  Buffer size >= nUnitCount * 2
WORD CModbus::WriteMultipleUnits(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf) {
	// Modbus address rule -- 0: Broadcasr address, 1-247: Slave individual address, 248-255: Reserved
	if ((nSlaveAddress < 1) || (nSlaveAddress > 247))
		return MODBUS_ILLEGAL_DEVICE_ADDRESS;
	// This function is only called by modbus function code: MODBUS_WRITE_MULTIPLE_COILS or MODBUS_WRITE_MULTIPLE_REGISTERS
	if ((nFunctionCode != MODBUS_WRITE_MULTIPLE_COILS) && (nFunctionCode != MODBUS_WRITE_MULTIPLE_REGISTERS))
		return MODBUS_ILLEGAL_FUNCTION_CODE;
	// Quantity of coils or registers
	if (nFunctionCode == MODBUS_WRITE_MULTIPLE_COILS)		// Write multiple coils
	{
		if ((nUnitCount < 1) || (nUnitCount > 0x07B0))		// Quantity of Outputs: 0x0001 to 0x07B0
			return MODBUS_ILLEGAL_REQUEST_COUNT;
	}
	else													// Write multiple registers
	{
		if ((nUnitCount < 1) || (nUnitCount > 0x007B))		// Quantity of Registers: 0x0001 to 0x007B
			return MODBUS_ILLEGAL_REQUEST_COUNT;
	}

	// Send request message frame
	m_pSendBuf[0] = nSlaveAddress;			// Slave device address
	m_pSendBuf[1] = nFunctionCode;			// Function code
	m_pSendBuf[2] = nRegAddress >> 8;		// Starting address Hi
	m_pSendBuf[3] = nRegAddress & 0x00FF;	// Starting addresss Lo
	m_pSendBuf[4] = nUnitCount >> 8;		// Unit count Hi
	m_pSendBuf[5] = nUnitCount & 0x00FF;	// Unit count Lo
	BYTE nByteCount;
	if (nFunctionCode == MODBUS_WRITE_MULTIPLE_COILS)		// Write multiple coils
	{
		nByteCount = nUnitCount / 8;
		if (nByteCount * 8 != nUnitCount) nByteCount += 1;
	}
	else													// Write multiple registers
	{
		nByteCount = nUnitCount * 2;
	}
	m_pSendBuf[6] = nByteCount;
	memcpy(m_pSendBuf + 7, pWriteBuf, nByteCount);
	WORD nCRC = CRC16(m_pSendBuf, 7 + nByteCount);			// Generate CRC and swap it's higher and lower bytes
	m_pSendBuf[7 + nByteCount] = nCRC >> 8;					// CRC Hi
	m_pSendBuf[8 + nByteCount] = nCRC & 0x00FF;				// CRC Lo
	Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);					// Discard all characters from the output and input buffer
	if (Write(m_pSendBuf, 9 + nByteCount) != 9 + nByteCount)		// Send request message frame
		return MODBUS_ERROR_WRITE_TIME_OUT;

	// Get slave response message frame
	DWORD dwStartTime = GetTickCount();
	DWORD dwResponseTime;
	WORD nReceivedBytes = 0;
	WORD nRequiredBytes = 8;
	while (nReceivedBytes < nRequiredBytes) {
		nReceivedBytes += (WORD)Read(m_pReceiveBuf + nReceivedBytes, nRequiredBytes - nReceivedBytes);
		dwResponseTime = GetTickCount() - dwStartTime;
		if (dwResponseTime > m_nResponseTimeOut)		// Time out
		{
			if (nReceivedBytes == 5)			// If the count of receive bytes equals exception message length
			{
				nCRC = CRC16(m_pReceiveBuf, nReceivedBytes - 2);			// CRC ok
				if ((m_pReceiveBuf[nReceivedBytes - 2] == (nCRC >> 8)) && (m_pReceiveBuf[nReceivedBytes - 1] == (nCRC & 0x00FF)))
					if (m_pReceiveBuf[0] == m_pSendBuf[0])					// Slave device address ok
						if (m_pReceiveBuf[1] == (m_pSendBuf[1] | 0x80))		// Exception: (Function code | 0x80)
							return MODBUS_EXCEPTION | m_pReceiveBuf[2];		// Return the exception code
			}
			return MODBUS_ERROR_RESPONSE_TIME_OUT;
		}
	}

	// Decode response message
	nCRC = CRC16(m_pReceiveBuf, nRequiredBytes - 2);	// CRC error
	if ((m_pReceiveBuf[nRequiredBytes - 2] != (nCRC >> 8)) || (m_pReceiveBuf[nRequiredBytes - 1] != (nCRC & 0x00FF)))
		return MODBUS_ERROR_CRC;
	if (memcmp(m_pSendBuf, m_pReceiveBuf, nRequiredBytes - 2) != 0)
		return MODBUS_ERROR_DATA;

	return MODBUS_SUCCESS;
}

WORD CModbus::WriteMultipleCoils(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf) {
	return WriteMultipleUnits(nSlaveAddress, MODBUS_WRITE_MULTIPLE_COILS, nRegAddress, nUnitCount, pWriteBuf);
}

WORD CModbus::WriteMultipleRegisters(BYTE nSlaveAddress, WORD nRegAddress, WORD nUnitCount, BYTE* pWriteBuf) {
	return WriteMultipleUnits(nSlaveAddress, MODBUS_WRITE_MULTIPLE_REGISTERS, nRegAddress, nUnitCount, pWriteBuf);
}

WORD CModbus::ReadMultipleUnits(BYTE nSlaveAddress, BYTE nFunctionCode, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf) {
	// Modbus address rule -- 0: Broadcasr address, 1-247: Slave individual address, 248-255: Reserved
	if ((nSlaveAddress < 1) || (nSlaveAddress > 247))
		return MODBUS_ILLEGAL_DEVICE_ADDRESS;
	// This function is only called by modbus function code: MODBUS_READ_COILS or MODBUS_READ_DISCRETE_INPUTS
	if ((nFunctionCode != MODBUS_READ_COILS) && (nFunctionCode != MODBUS_READ_DISCRETE_INPUTS))
		return MODBUS_ILLEGAL_FUNCTION_CODE;
	// Quantity of coils or inputs: 1 to 2000(0x07D0)
	if ((nUnitCount < 1) || (nUnitCount > 0x07D))
		return MODBUS_ILLEGAL_REQUEST_COUNT;

	// Send request message frame
	m_pSendBuf[0] = nSlaveAddress;			// Slave device address
	m_pSendBuf[1] = nFunctionCode;			// Function code
	m_pSendBuf[2] = nUnitAddress >> 8;		// Starting address Hi
	m_pSendBuf[3] = nUnitAddress & 0x00FF;	// Starting addresss Lo
	m_pSendBuf[4] = nUnitCount >> 8;		// Quantity of units Hi
	m_pSendBuf[5] = nUnitCount & 0x00FF;	// Quantity of units Lo
	WORD nCRC = CRC16(m_pSendBuf, 6);		// Generate CRC and swap it's higher and lower bytes
	m_pSendBuf[6] = nCRC >> 8;				// CRC Hi
	m_pSendBuf[7] = nCRC & 0x00FF;			// CRC Lo
	Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);	// Discard all characters from the output and input buffer
	if (Write(m_pSendBuf, 8) != 8)			// Send request message frame
		return MODBUS_ERROR_WRITE_TIME_OUT;

	// Get slave response message frame
	DWORD dwStartTime = GetTickCount();
	DWORD dwResponseTime;
	WORD nReceivedBytes = 0;
	BYTE nByteCount = nUnitCount / 8;
	if (nByteCount * 8 != nUnitCount) nByteCount += 1;
	WORD nRequiredBytes = 5 + nByteCount;
	while (nReceivedBytes < nRequiredBytes) {
		nReceivedBytes += (WORD)Read(m_pReceiveBuf + nReceivedBytes, nRequiredBytes - nReceivedBytes);
		dwResponseTime = GetTickCount() - dwStartTime;
		if (dwResponseTime > m_nResponseTimeOut)		// Time out
		{
			if (nReceivedBytes == 5)			// If the count of receive bytes equals exception message length
			{
				nCRC = CRC16(m_pReceiveBuf, nReceivedBytes - 2);			// CRC ok
				if ((m_pReceiveBuf[nReceivedBytes - 2] == (nCRC >> 8)) && (m_pReceiveBuf[nReceivedBytes - 1] == (nCRC & 0x00FF)))
					if (m_pReceiveBuf[0] == m_pSendBuf[0])					// Slave device address ok
						if (m_pReceiveBuf[1] == (m_pSendBuf[1] | 0x80))		// Exception: (Function code | 0x80)
							return MODBUS_EXCEPTION | m_pReceiveBuf[2];		// Return the exception code
			}
			return MODBUS_ERROR_RESPONSE_TIME_OUT;
		}
	}

	// Decode response message
	nCRC = CRC16(m_pReceiveBuf, nRequiredBytes - 2);	// CRC error
	if ((m_pReceiveBuf[nRequiredBytes - 2] != (nCRC >> 8)) || (m_pReceiveBuf[nRequiredBytes - 1] != (nCRC & 0x00FF)))
		return MODBUS_ERROR_CRC;
	if (m_pReceiveBuf[0] != m_pSendBuf[0])				// Slave device address error
		return MODBUS_ERROR_ADDRESS;
	if (m_pReceiveBuf[1] != m_pSendBuf[1])				// Function code error
	{
		return MODBUS_ERROR_FUNCTION_CODE;
	}
	if (m_pReceiveBuf[2] != nByteCount)
		return MODBUS_ERROR_RESPONSE_COUNT;
	memcpy(pReturnBuf, m_pReceiveBuf + 3, nByteCount);

	return MODBUS_SUCCESS;
}

WORD CModbus::ReadCoils(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf) {
	return ReadMultipleUnits(nSlaveAddress, MODBUS_READ_COILS, nUnitAddress, nUnitCount, pReturnBuf);
}

WORD CModbus::ReadDiscreteInputs(BYTE nSlaveAddress, WORD nUnitAddress, WORD nUnitCount, BYTE* pReturnBuf) {
	return ReadMultipleUnits(nSlaveAddress, MODBUS_READ_DISCRETE_INPUTS, nUnitAddress, nUnitCount, pReturnBuf);
}