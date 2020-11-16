#pragma once
#include <Windows.h>
class CSerialPort
{
public:

	CSerialPort();
	virtual ~CSerialPort();

	BOOL Open(int nPort, DWORD dwBaud = 9600, BYTE nDataBits = 8, BYTE parity = 0,
		BYTE stopBits = 0);
	BOOL OpenM(LPCTSTR pszPort, DWORD dwBaud = 9600, BYTE nDataBits = 8, BYTE parity = 0,
		BYTE stopBits = 0);
	inline BOOL Purge(DWORD dwFlags) {
		return PurgeComm(m_hComm, dwFlags);
	}
	void Close();
	DWORD Read(void* lpBuf, DWORD dwCount);
	DWORD Write(const void* lpBuf, DWORD dwCount);

protected:
	HANDLE     m_hComm;        // Handle to the comms port
};
