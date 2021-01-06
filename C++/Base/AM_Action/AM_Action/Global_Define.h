#pragma once

#define IOTYPE		_T("IOCTRL")
#define ROBOTTYPE	_T("ROBOT")
#define TIMEOUTTYPE _T("TIME")
#define MSGTYPE		_T("MESSAGE")
#define COMPARE     _T("COMPARE")
#define VOLUATION   _T("VOLUATION")
#define FLOWCTLR    _T("FLOWCTLR")


#define OPENOUTPORT		_T("OpenOutPort")
#define CLOSEOUTPORT	_T("CloseOutPort")
#define CHECKOUTPORT	_T("CheckOutPort")
#define CHECKINPORT		_T("CheckInPort")
#define SETRELAY		_T("SetRelay")
#define CLEARRELAY		_T("ClearRelay")
#define CHECKRELAY		_T("CheckRelay")

#define GOTOPOSMOD		_T("GotoPosMod")
#define PASSPOSMOD		_T("PassPosMod")
#define MULITPOSMOD		_T("MulitPosMod")
#define XAXIS			_T("XAxis")
#define YAXIS			_T("YAxis")
#define ZAXIS			_T("ZAxis")
#define UAXIS			_T("UAxis")
#define ISBUSY			_T("IsBusy")
#define POWER			_T("Power")
#define SPEED			_T("Speed")


#define SENDMSG			_T("SendMsg")
#define POSTMSG			_T("PostMsg")

#define BEGINTIME		_T("BeginTime")
#define ISTIMEOUT		_T("IsTimeOut")
#define SLEEP			_T("Sleep")

#define BOOLEAN			_T("BOOL")
#define INTEGER			_T("Int")
#define FLOATNUM		_T("Float")
#define DOUBLENUM		_T("Double")
#define STRINGVAL		_T("String")

#define SUSPEND			_T("Suspend")
#define RESUME			_T("Resume")
#define STOP			_T("Stop")

typedef struct IOINFO
{
	int iStation;
	int iPortNo;
	int iCardNo;
	TCHAR ptcHex[2];
	IOINFO ()
	{
		ptcHex[0] = 0;
		ptcHex[1] = 0;
		iStation = 1;
		iPortNo = 0;
		iCardNo = 0;
	}
}IOInfo, *PIOInfo;

typedef struct POSINFO
{
	int iRobotNo;
	RobotPosInfo sRobotPos;
	POSINFO ()
	{
		iRobotNo = 0;
	}
}PosInfo, *PPosInfo;

class CLock
{
public: 
	CLock()
	{
		::InitializeCriticalSection(&m_csLock);
	}

	~CLock()
	{
		::DeleteCriticalSection(&m_csLock);
	}

	void Lock()
	{
		::EnterCriticalSection(&m_csLock);
	}

	void Unlock()

	{
		::LeaveCriticalSection(&m_csLock);	
	}

private:
	CRITICAL_SECTION m_csLock;
};