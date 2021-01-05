#pragma once
#include "AM_IRobot.h"

namespace ROBOT
{
	const tstring XAXIS = _T("XAxis");
	const tstring YAXIS = _T("YAxis");
	const tstring ZAXIS	= _T("ZAxis");
	const tstring UAXIS = _T("UAxis");
	const tstring VAXIS	= _T("VAxis");
	const tstring WAXIS	= _T("WAxis");

	class CEpsonRobot : public CIRobot
	{
	public:
		CEpsonRobot();
		virtual ~CEpsonRobot();

		void				SetRobotIp(const LPCTSTR lpStrRobotIp);
		void				SetInitPort(const int iInitPort = 5000);
		void				SetMovePort(const int iMovePort = 4000);
		void				SetCtrlPort(const int iCtrlPort = 4001);
		void				SetFlowPort(const int iFlowPort = 2001);
		void				SetVisionPort(const int iVisionPort = 4010);
		void				SetEndChar(const TCHAR *pEndChar, const int iEndCharCnt = 1);

		//运动
		BOOL				GotoDistance(const LPCTSTR lpstrAxis, double dDistance, const int iMoveMode);   //iMoveMode : 0. 轴运动 1.Jog运动
		BOOL				IsRobotBusy(DWORD dTimeOut = 20000);	
		BOOL				JumpPosMod(RobotPosInfo sRobotPosInfo, const double dZHight = 600.0);
		BOOL				GotoPosMod(RobotPosInfo sRobotPosInfo, const double dZHight = 100.0);
		BOOL                GotoPos(const int iPosIndex, const double dZHight  = 600);
		BOOL				PassPosMod(RobotPosInfo *pRobotPosInfo, const int iPassCnt, const double dZHight = 100.0);		//Pass Mode Use: pPasspPos中最后一个Pos 是目标点, iPassCnt Pos的个数包含目标点		
		BOOL				MulitPosMod(RobotPosInfo *pRobotPosInfo, const int iPassCnt, const double dZHight = 100.0);		//Pass Mode Use: pPasspPos中最后一个Pos 是目标点, iPassCnt Pos的个数包含目标点		
		BOOL                SavePort(int iIndex, RobotPosInfo pRobotPosInfo);



		//控制
		int					SetPower(const BOOL bPower);				//Power: FALSE-Low TRUE-High
		int					SetEnable(const BOOL bEnable);				//bEnable: FALSE-MotorOff TRUE-MotorOn
		int					SetSpeed(const int iSpeed, const int iAccel);					//Set Speed Min:0 Max:100
		int					OpenOutPort(const int iOutPort);
		int					CloseOutPort(const int iOutPort);
		int					QryOutPort(const int iOutPort);
		int					QryInPort(const int iInPort);
		int					QryCurPos(RobotPosInfo &sCurPos);
		int					QryToolCurPos(RobotPosInfo &sCurPos);
		int					QryEnable();
		int					QryPower();
		void				CloseConnect();

		int					GetPosInfo(const int iPosIndex, RobotPosInfo &sPosInfo);//获取单个点
		int					StorePos(const int iPosIndex);   //在机械手中保存当前位置到点P（iPosIndex）
		int                 SetTool(const int iIndex, const double dXPos, const double dYPos, const double dZPos = 0.0, const double dUPos = 0.0);
		int					GetTool(const int iIndex, double &dXPos, double &dYPos, double &dZPos, double &dUPos);

		int					SetPosition(const int iPosition, RobotPosInfo sRobotPosInfo);
		int					CreateTool(const int iCameraNo, const int iToolNo, const double dXVal, const double dYVal);
		int					ChangeTool(const int iToolNo);
		int					CameraCal(const int iCameraNo, const int iType, LPTSTR lpstrVisionRst);
		int					TransPosition(RobotPosInfo &sTransPos, const double dXVal, const double dYVal, const double dUVal, const int iCameraNo);
		 		//Robot Program Init
		BOOL				InitRobot(LPTSTR lpstrError);
		int					SuspendRobot();
		int					ResumeRobot();
		int					StopRobot();
		BOOL				IsRobotConnnect();
		BOOL				Send(CIClient *piSend, tstring strSend);
		int					Receive(CIClient *piSend, tstring &strRecv);

		//Pallet 
		int					CreatePallet(const int iPalletNo, const int iRow, const int iCol);
		int					GetPalletPos(const int iPalletNo, const int iPositionNo, RobotPosInfo &sPosInfo);//获取单个点

	private:
		tstring 			DataTrans(const int iMoveMode, const double dSingleDis/*dSpeed*/, const double dZHight/*dAccel*/, const int iPassCnt = 0, RobotPosInfo *pRobotPos = NULL);
		tstring				DataCtrl(const tstring &strData);


	private:
		int					m_iInitPort;
		int					m_iMovePort;
		int					m_iCtrlPort;
		int                 m_iFlowPort;
		int					m_iVisionPort;
		int					m_iEndCharCnt;

		TCHAR 				m_ptcEndChar[10];
		tstring				m_strRobotIp;

		BOOL				m_bPower;
		BOOL				m_bEable;
		BOOL				m_bRunning;
		BOOL				m_bInit;
		BOOL				m_bCtrl;
		BOOL                m_bRmCtrl;

		CIClient			*m_pIMove;
		CIClient         *m_pICtrl;
		CIClient         *m_pIInit;
		CIClient         *m_pIFlow;
		CIClient         *m_pIVision;
		CLock				m_csMove;
		CLock				m_csCtrl;
		CLock				m_csVision;
	};
}