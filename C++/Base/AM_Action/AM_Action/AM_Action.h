#pragma once
#include "AM_IAction.h"

namespace Aciton
{
	class CAction : public CIAction, public CIUserAction
	{
	public:
		CAction();
		virtual ~CAction();
		BOOL Action(LPCTSTR lpstrType, LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);
		BOOL Action(LPCTSTR lpstrType, LPCTSTR lpstrValue);
		
		void InitAction(LPCTSTR lpstrActionFile);
		int GetIOState(LPCTSTR lpstrName, LPCTSTR lpstrType);
		BOOL SetIOState(const BOOL bState, LPCTSTR lpstrName, LPCTSTR lpstrType);

		BOOL GotoDistance(const int iAxisNo, double dDistance, const int iMoveMode, const int iRobotNo = 0);   //iMoveMode : 0. 轴运动 1.Jog运动
		BOOL GotoDistance(const LPCTSTR lpstrAxis, double dDistance, const int iMoveMode = 0, const int iRobotNo = 0);
		BOOL IsRobotBusy(DWORD dwTimeOut = 10, const int iRobotNo = 0);	
		BOOL GotoPosMod(const LPCTSTR lpstrPosName, const double dZHight = -15.0, const int iRobotNo = 0);
		BOOL SetPower(const BOOL bPower, const int iRobotNo = 0);
		BOOL SetSpeed(const int iSpeed, const int iRobotNo = 0);
		BOOL SuspendRobot(const int iRobotNo = 0);
		BOOL ResumeRobot(const int iRobotNo = 0);

		int CheckRelay(LPCTSTR lpstrName);
		int SetRelay(LPCTSTR lpstrName);
		int ClearRelay(LPCTSTR lpstrName);
		int CheckInport(LPCTSTR lpstrName);
		int CheckOutport(LPCTSTR lpstrName);
		int OpenOutport(LPCTSTR lpstrName);
		int CloseOutport(LPCTSTR lpstrName);
		int ReadDT(const int iAddress);
		int WriteDT(const int iAddress, int iVal);

		BOOL InitParam();
		BOOL Connect(const int iType, const int iNo);

		BOOL Suspend();
		BOOL Resume();
		BOOL IsSuspend();
		BOOL Stop();

	private:
		map<tstring, map<tstring, IOInfo>> m_mapIOInfo; 
		map<tstring, PosInfo> m_mapRobotPosInfo; 
		map<int, CIPLCCtrl *> m_mapIPLCCtrl;
		map<int, CIRobot *> m_mapIRobot;
		map<tstring, DWORD> m_mapTimeOut;
		map<tstring, HWND> m_mapMsgWnd;

		map<tstring, BOOL> m_mapBOOL;
		map<tstring, int> m_mapInt;
		map<tstring, float> m_mapFloat;
		map<tstring, double> m_mapDouble;
		map<tstring, tstring> m_mapString;

		map<tstring, int> m_mapActionType;

		tstring m_strIODat;
		tstring m_strInitDat;
		tstring m_strPointsDat;
		tstring m_strConfigIni;
		tstring m_strConfigDir;
		tstring m_strParamIni;

		void LoadPosInfo();
		void LoadIOInfo();
		BOOL InitRobotParam(tstring strSection);
		BOOL InitIOParam(tstring strSection);

		BOOL IOAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);
		BOOL RobotAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);
		BOOL TimeAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);		//设置开始时间 检测超时 等待时间
		BOOL MsgAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);			//发送消息
		BOOL CmpAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);			//比较 只有等于和不等于
		BOOL VolAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);			//赋值
		BOOL CalAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);
		BOOL FCAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue);
	};
}
