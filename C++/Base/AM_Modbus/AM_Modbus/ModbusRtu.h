#pragma once
#include "AM_IModbus.h"

class CModbusRtu : public CIModBus
{
public:
	CModbusRtu();
	virtual ~CModbusRtu();

	virtual BOOL Connect(const int iPortNo, const DWORD dwBaud, const int iDataBits, const int iPairty, const int iStopBits);

	virtual BOOL Connect(LPCTSTR lpstrIp, const int iPortNo);
	virtual void DisConnect();
	virtual BOOL IsConnect();

	virtual BOOL ReadCoilByBit(const int iAddr, int *piVal, const int iCount = 1);			 //����Ȧ ��λ
	virtual BOOL ReadDispersedByBit(const int iAddr, int *piVal, const int iCount = 1);       //����ɢ ��λ
	virtual BOOL ReadHoldRegisterByByte(const int iAddr, int *piVal, const int iCount = 1);	 //�����ּĴ��� ���ֽ�
	virtual BOOL ReadInRegisterByByte(const int iAddr, int *piVal, const int iCount = 1);	 //������Ĵ��� ���ֽ�

	virtual BOOL WriteSingleCoilByByte(const int iAddr, const int iVal);	 //д������Ȧ ���ֽ�
	virtual BOOL WriteSingleRegisterByByte(const int iAddr, const int iVal); // д�����Ĵ��� ���ֽ�
	virtual BOOL WriteMultiCoilByByte(const int iAddr, const int *piVal, const int iCount);	   //д�����Ȧ ���ֽ�
	virtual BOOL WriteMultiRegisterByByte(const int iAddr, const int *piVal, const int iCount);  // д����Ĵ��� ���ֽ�
	virtual DWORD GetLastError();
	virtual void SetFollowID(const int iFollowID); //���÷��ʵ�֪�� ����վ Ĭ��Ϊ0x01

private:
	int m_iFollowID;

	CISerialPort *m_pISerialPort;
	CMyLock m_csMyLock;
	DWORD m_dwErrCode;
	void ASleep(const int iSleepTime);
	USHORT CalcRtuCrc(const BYTE *pbyData, const int iLength);
	int CreateReadSendData(const int iType, const int iAddr, BYTE *pbyRecvData, const int iCount);
	int CreateWriteSendData(const int iType, const int iAddr, BYTE *pbyRecvData, const int *piData, const int iCount);
	BOOL ParseRecvData(const int iType, const BYTE *pbyRecvData, int *piData, const int iCount = 1);

};