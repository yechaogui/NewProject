#pragma once

#ifdef AM_MODBUS_EXPORTS
#define AM_MODBUS_API __declspec(dllexport)
#else
#define AM_MODBUS_API __declspec(dllexport)
#endif

class CIModBus
{
public:
	CIModBus() {};
	virtual ~CIModBus() {};

	virtual BOOL Connect(const int iPortNo, const DWORD dwBaud, const int iDataBits, const int iPairty, const int iStopBits) = 0;

	virtual BOOL Connect(LPCTSTR lpstrIp, const int iPortNo) = 0;
	virtual void DisConnect() = 0;
	virtual BOOL IsConnect() = 0;

	virtual BOOL ReadCoilByBit(const int iAddr, int *piVal, const int iCount = 1) = 0;			 //����Ȧ ��λ
	virtual BOOL ReadDispersedByBit(const int iAddr, int *piVal, const int iCount = 1) = 0;       //����ɢ ��λ
	virtual BOOL ReadHoldRegisterByByte(const int iAddr, int *piVal, const int iCount = 1) = 0;	 //�����ּĴ��� ���ֽ�
	virtual BOOL ReadInRegisterByByte(const int iAddr, int *piVal, const int iCount = 1) = 0;	 //������Ĵ��� ���ֽ�

	virtual BOOL WriteSingleCoilByByte(const int iAddr, const int iVal) = 0;	 //д������Ȧ ���ֽ�
	virtual BOOL WriteSingleRegisterByByte(const int iAddr, const int iVal) = 0; // д�����Ĵ��� ���ֽ�
	virtual BOOL WriteMultiCoilByByte(const int iAddr, const int *piVal, const int iCount) = 0;	   //д�����Ȧ ���ֽ�
	virtual BOOL WriteMultiRegisterByByte(const int iAddr, const int *piVal, const int iCount) = 0;  // д����Ĵ��� ���ֽ�
	virtual DWORD GetLastError() = 0;
	virtual void SetFollowID(const int iFollowID) = 0; //���÷��ʵ�֪�� ����վ Ĭ��Ϊ0x01
};

extern "C"
{
	void AM_MODBUS_API AM_CreateModbus(CIModBus **ppIModbus, const int iType);
	void AM_MODBUS_API AM_ReleaseModbus(CIModBus *pIModbus);
};