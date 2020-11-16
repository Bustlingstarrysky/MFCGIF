#include "pch.h"
#include "SerialPort.h"

#include <stdio.h>
#include <wchar.h>
#include <tchar.h>

CSerialPort::CSerialPort()
	: m_hComm(INVALID_HANDLE_VALUE) {}

CSerialPort::~CSerialPort() {
	Close();
}

BOOL CSerialPort::OpenM(LPCTSTR pszPort, DWORD dwBaud, BYTE nDataBits, BYTE parity, BYTE stopBits) {
	// Close comms port if it's opened
	Close();

	//Call CreateFile to open the comms port
	m_hComm = CreateFile(pszPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hComm == INVALID_HANDLE_VALUE) {
		//TRACE(_T("CSerialPort::Open, Failed to open the comms port: %s\n"), pszPort);
		return FALSE;
	}

	// Cconfigure comms port with DCB structure
	DCB dcb;
	GetCommState(m_hComm, &dcb);
	dcb.BaudRate = dwBaud;			//Setup the baud rate
	dcb.Parity = parity;			//Setup the parity
	dcb.ByteSize = nDataBits;		//Setup the data bits
	dcb.StopBits = stopBits;		//Setup the stop bits
	//dcb.fDsrSensitivity = FALSE;	//Setup the flow control
	//dcb.fOutxCtsFlow = FALSE;
	//dcb.fOutxDsrFlow = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	//
	dcb.fBinary = TRUE;
	dcb.fDtrControl = 0;								/* ½ûÖ¹Á÷Á¿¿ØÖÆ */
	dcb.fRtsControl = 0;
	dcb.fTXContinueOnXoff = 0;
	//dcb.fParity = FALSE;
	if (!SetCommState(m_hComm, &dcb)) {
		//TRACE(_T("CSerialPort::Open, Failed to call SetCommState, Comms port: %s\n"), pszPort);
		Close();
		return FALSE;
	}

	// Specify the event to be monitored
	SetCommMask(m_hComm, EV_RXCHAR);
	// Specify the internal buffers sizes by the driver
	SetupComm(m_hComm, 16384, 16384);				// 16k bytes buffer
	// Set the time-out parameters
	COMMTIMEOUTS timeouts;
	int nReadInterval = (int)(1000 * 11 * 1.5 / dwBaud + 0.8);		// Modbus inter-character time-out(t1.5)
	if (nReadInterval <= 0) nReadInterval = 1;
	GetCommTimeouts(m_hComm, &timeouts);
	timeouts.ReadIntervalTimeout = nReadInterval;			// inter-character time-out: t1.5
	timeouts.ReadTotalTimeoutMultiplier = nReadInterval;	// total time-out: t1.5 * the count of bytes to read
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = nReadInterval;
	timeouts.WriteTotalTimeoutConstant = 0;
	//timeouts.ReadIntervalTimeout = MAXDWORD;		// Return immediately with the received bytes, even if no bytes have been received
	//timeouts.ReadTotalTimeoutMultiplier = 0;
	//timeouts.ReadTotalTimeoutConstant = 0;
	//timeouts.WriteTotalTimeoutMultiplier = 0;
	//timeouts.WriteTotalTimeoutConstant = 0;
	if (!SetCommTimeouts(m_hComm, &timeouts)) {
		//TRACE(_T("CSerialPort::Open, Failed to call SetCommTimeouts, Comms port: %s\n"), pszPort);
		Close();
		return FALSE;
	}
	// Discard all characters from the output and input buffer
	//PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
	Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);

	return TRUE;
}

BOOL CSerialPort::Open(int nPort, DWORD dwBaud, BYTE nDataBits, BYTE parity, BYTE stopBits) {
	if (nPort < 1 || nPort>9)
		return FALSE;
	TCHAR sPort[MAX_PATH];
	_stprintf_s(sPort, _T("COM%d:"), nPort);

	//return OpenM((LPCTSTR)"COM1:", dwBaud, nDataBits, parity, stopBits);
	return OpenM((LPCTSTR)sPort, dwBaud, nDataBits, parity, stopBits);
}

void CSerialPort::Close() {
	if (m_hComm != INVALID_HANDLE_VALUE) {
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
	}
}

DWORD CSerialPort::Read(void* lpBuf, DWORD dwCount) {
	if (m_hComm == INVALID_HANDLE_VALUE)
		return 0;

	DWORD dwBytes = 0;
	if (!ReadFile(m_hComm, lpBuf, dwCount, &dwBytes, NULL)) {
		//TRACE(_T("CSerialPort::Read, Failed to call ReadFile, Handle: %d\n"), m_hComm);
		Close();
		return 0;
	}

	return dwBytes;
}

DWORD CSerialPort::Write(const void* lpBuf, DWORD dwCount) {
	if (m_hComm == INVALID_HANDLE_VALUE)
		return 0;

	DWORD dwBytes = 0;
	if (!WriteFile(m_hComm, lpBuf, dwCount, &dwBytes, NULL)) {
		//TRACE(_T("CSerialPort::Write, Failed to call WriteFile, Handle: %d\n"), m_hComm);
		Close();
		return 0;
	}

	return dwBytes;
}