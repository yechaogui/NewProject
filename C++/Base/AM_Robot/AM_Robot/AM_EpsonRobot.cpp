#include "stdafx.h"
#include "AM_EpsonRobot.h"

namespace ROBOT
{
	CEpsonRobot::CEpsonRobot()
	{
		m_bRunning = FALSE;
		m_bEable = FALSE;
		m_bPower = FALSE;
		m_bCtrl = FALSE;
		m_bInit = FALSE;
		m_bRmCtrl = TRUE;
		m_iCtrlPort = 4001;
		m_iMovePort = 4000;
		m_iInitPort = 5000;
		m_iFlowPort = 2001;
		m_iVisionPort = 4010;
		m_iEndCharCnt = 2;
		m_ptcEndChar[0]= 0x0D;
		m_ptcEndChar[1]= 0x0A;
		m_strRobotIp = _T("192.168.0.10");
		m_pIInit = NULL;
		m_pIMove = NULL;
		m_pICtrl = NULL;
		m_pIFlow = NULL;
		m_pIVision = NULL;
		AM_CreateClient(&m_pIInit);
		AM_CreateClient(&m_pIMove);
		AM_CreateClient(&m_pICtrl);
		AM_CreateClient(&m_pIVision);
	}

	CEpsonRobot::~CEpsonRobot()
	{

		if (m_pIVision)
		{
			m_pIVision->DisConnect();
		}

		if (m_pICtrl)
		{
			m_pICtrl->DisConnect();
		}

		if (m_pIMove)
		{
			m_pIMove->DisConnect();
		}

		if (m_pIInit)
		{
			m_pIInit->DisConnect();
		}


		AM_ReleaseClient(m_pIVision);
		AM_ReleaseClient(m_pICtrl);
		AM_ReleaseClient(m_pIMove);
		AM_ReleaseClient(m_pIInit);

		
	}

	void CEpsonRobot::SetRobotIp(const LPCTSTR lpStrRobotIp)
	{
		m_strRobotIp = lpStrRobotIp;
	}

	void CEpsonRobot::SetInitPort(const int iInitPort /* = 5000 */)
	{
		m_iInitPort = iInitPort;
	}

	void CEpsonRobot::SetMovePort(const int iMovePort /* = 4000 */)
	{
		m_iMovePort = iMovePort;
	}

	void CEpsonRobot::SetCtrlPort(const int iCtrlPort /* = 4001 */)
	{
		m_iCtrlPort = iCtrlPort;
	}

	void CEpsonRobot::SetFlowPort(const int iFlowPort /* = 2001 */)
	{
		m_iFlowPort = iFlowPort;
	}

	void CEpsonRobot::SetVisionPort(const int iVisionPort /* = 4010 */)
	{
		m_iVisionPort = iVisionPort;
	}

	void CEpsonRobot::SetEndChar(const TCHAR *pEndChar, const int iEndCharCnt /* = 1 */)
	{
		for (int i = 0; i < iEndCharCnt; ++i)
		{
			m_ptcEndChar[i] = pEndChar[i];
		}

		m_iEndCharCnt = iEndCharCnt;
	}

	BOOL CEpsonRobot::GotoDistance(const LPCTSTR lpstrAxis, double dDistance, const int iMoveMode)
	{
		if (!m_bInit)
		{
			return m_bInit;
		}
		m_csMove.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		if (!m_bRunning)
		{

			if (XAXIS == lpstrAxis)
			{
				strSend = DataTrans(iMoveMode * 10  + 1, dDistance, 0);
				bRet = Send(m_pIMove, strSend);
			}
			else if (YAXIS == lpstrAxis)
			{
				strSend = DataTrans(iMoveMode * 10  + 2, dDistance, 0);
				bRet = Send(m_pIMove, strSend);
			}
			else if (ZAXIS == lpstrAxis)
			{
				strSend = DataTrans(iMoveMode * 10  + 3, dDistance, 0);
				bRet = Send(m_pIMove, strSend);
			}
			else if (UAXIS == lpstrAxis)
			{
				strSend = DataTrans(iMoveMode * 10  + 4, dDistance, 0);
				bRet = Send(m_pIMove, strSend);
			}
			else if (VAXIS == lpstrAxis)
			{
				strSend = DataTrans(iMoveMode * 10  + 5, dDistance, 0);
				bRet = Send(m_pIMove, strSend);
			}
			else if (WAXIS == lpstrAxis)
			{
				strSend = DataTrans(iMoveMode * 10  + 6, dDistance, 0);
				bRet = Send(m_pIMove, strSend);
			}

			if (bRet)
			{
				m_bRunning = TRUE;
			}
		}
		m_csMove.Unlock();
		return bRet;
	}

	BOOL CEpsonRobot::IsRobotBusy(DWORD dTimeOut /* = 20000 */)
	{
		if (!m_bInit)
		{			
			return m_bInit;
		}

		m_csMove.Lock();
		long		nSTTime = ::GetTickCount();
		tstring		strMsgInfo = _T("");
		int			iRet = -1;
		if (m_bRunning)
		{
			while ((::GetTickCount() - nSTTime) < dTimeOut)
			{
				strMsgInfo = _T("");
				iRet = Receive(m_pIMove, strMsgInfo);
				if (iRet == 1)
				{
					
					if (strMsgInfo.find(_T("OK"))!=-1 || strMsgInfo.find(_T("POS"))!=-1 )
					{
						m_bRunning = FALSE;
					}
					else if (strMsgInfo.find(_T("ER")) != -1)
					{
						m_bRunning = FALSE;

					}
					else if (strMsgInfo.find(_T("err")) != -1)
					{
						m_bRunning = FALSE;
					}

					break;
				}
				else if (iRet == -1)
				{
					m_bRunning = FALSE;
					break;
				}

				Sleep(10);
			}
		}
		
		m_csMove.Unlock();
		return m_bRunning;
	}

	tstring CEpsonRobot::DataTrans(const int iMoveMode, const double dSingleDis, const double dZHight, const int iPassCnt /* = 0 */, RobotPosInfo *pRobotPos /* = NULL */)
	{
		tstring		strMsg = _T("");
		TCHAR		szTemp[128] = {0};
		int			i = 0; 
		strMsg = _T("CMD ");
		swprintf(szTemp, _T("%d "), iMoveMode);
		strMsg += szTemp;
		swprintf(szTemp, _T("%.3f "), dSingleDis);
		strMsg += szTemp;
		swprintf(szTemp, _T("%.3f "), dZHight);
		strMsg += szTemp;
		swprintf(szTemp, _T("%d "), iPassCnt);
		strMsg += szTemp;

		for (i = 0; i < iPassCnt; ++i)
		{
			swprintf(szTemp, _T("%.3f "), pRobotPos[i].dXPos);
			strMsg += szTemp;
			swprintf(szTemp, _T("%.3f "), pRobotPos[i].dYPos);
			strMsg += szTemp;
			swprintf(szTemp, _T("%.3f "), pRobotPos[i].dZPos);
			strMsg += szTemp;
			swprintf(szTemp, _T("%.3f "), pRobotPos[i].dUPos);
			strMsg += szTemp;
			swprintf(szTemp, _T("%.3f "), pRobotPos[i].dVPos);
			strMsg += szTemp;
			swprintf(szTemp, _T("%.3f "), pRobotPos[i].dWPos);
			strMsg += szTemp;
			swprintf(szTemp, _T("%d "), pRobotPos[i].nHand);
			strMsg += szTemp;
			swprintf(szTemp, _T("%d "), pRobotPos[i].nElbow);
			strMsg += szTemp;
			swprintf(szTemp, _T("%d "), pRobotPos[i].nFlip);
			strMsg += szTemp;
			swprintf(szTemp, _T("%d "), pRobotPos[i].nJ4Flag);
			strMsg += szTemp;
			swprintf(szTemp, _T("%d "), pRobotPos[i].nJ6Flag);
			strMsg += szTemp;
			swprintf(szTemp, _T("%d "), pRobotPos[i].nRunMod);
			strMsg += szTemp;
		}

		for (i = 0; i < m_iEndCharCnt; ++i)
		{
			strMsg = strMsg + m_ptcEndChar[i];
		}

		return strMsg;
	}



	BOOL CEpsonRobot::JumpPosMod(RobotPosInfo sRobotPosInfo, const double dZHight/* = 100.0*/)
	{
		if (!m_bInit)
		{		
			return m_bInit;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		m_csMove.Lock();

		if (!m_bRunning)
		{
			strSend = DataTrans(21, 0.0, dZHight, 1, &sRobotPosInfo);
			m_bRunning = Send(m_pIMove, strSend);
			bRet = m_bRunning;
		}

		m_csMove.Unlock();
		return bRet;
	}

	BOOL CEpsonRobot::GotoPosMod(RobotPosInfo sRobotPosInfo, const double dZHight/* = 100.0*/)
	{
		if (!m_bInit)
		{		
			return m_bInit;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		m_csMove.Lock();

		if (!m_bRunning)
		{
			strSend = DataTrans(20, 0.0, dZHight, 1, &sRobotPosInfo);
			m_bRunning = Send(m_pIMove, strSend);
			bRet = m_bRunning;
		}

		m_csMove.Unlock();
		return bRet;
	}


	BOOL CEpsonRobot::GotoPos(const int iPosIndex, const double dZHight /* = 600 */)
	{
		if (!m_bInit)
		{
			
			return m_bInit;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		m_csMove.Lock();

		if (!m_bRunning)
		{
			strSend = DataTrans(24, iPosIndex, dZHight);
			m_bRunning = Send(m_pIMove, strSend);
			bRet = m_bRunning;
		}

		m_csMove.Unlock();
		return bRet;
	}

	BOOL CEpsonRobot::PassPosMod(RobotPosInfo *pRobotPosInfo, const int iPassCnt, const double dZHight/* = 100.0*/)
	{
		if (!m_bInit)
		{
			return m_bInit;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		m_csMove.Lock();

		if (!m_bRunning)
		{
			for (int i = 0; i < iPassCnt; ++i)
			{
				pRobotPosInfo[i].nRunMod = 1;
			}
			strSend = DataTrans(22, 0.0, dZHight, iPassCnt, pRobotPosInfo);
			m_bRunning = Send(m_pIMove, strSend);
			bRet = m_bRunning;
		}

		m_csMove.Unlock();
		return bRet;
	}

	BOOL CEpsonRobot::MulitPosMod(RobotPosInfo *pRobotPosInfo, const int iPassCnt, const double dZHight/* = 100.0*/)
	{
		if (!m_bInit)
		{
			
			return m_bInit;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		m_csMove.Lock();

		if (!m_bRunning)
		{
			strSend = DataTrans(22, 0.0, dZHight, iPassCnt, pRobotPosInfo);
			m_bRunning = Send(m_pIMove, strSend);
			bRet = m_bRunning;
		}

		m_csMove.Unlock();
		return bRet;
	}

	BOOL  CEpsonRobot::SavePort(int iIndex, RobotPosInfo pRobotPosInfo)
	{
		if (!m_bInit)
		{			
			return m_bInit;
		}

		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		m_csMove.Lock();

		if (!m_bRunning)
		{
			strSend = DataTrans(25, 0.0, iIndex, 1, &pRobotPosInfo);
			m_bRunning = Send(m_pIMove, strSend);
			bRet = m_bRunning;
		}

		m_csMove.Unlock();
		return bRet;
	}

	BOOL CEpsonRobot::QryCurPos(RobotPosInfo &sCurPos)
	{
		if (!m_bInit)
		{
			
			return m_bInit;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");	
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		char		szOK[128] = {0};
		m_csCtrl.Lock();
		strSend = _T("CMD 15 0 0 0 ");
		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);

		long		nSTTime = ::GetTickCount();
		if (bRet)
		{		
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					USES_CONVERSION;
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						sscanf(T2A(szMsgInfo.c_str()), "%s%f%f%f%f%f%f%d%d%d%d%d", szOK, &sCurPos.dXPos, &sCurPos.dYPos, &sCurPos.dZPos, &sCurPos.dUPos,
							&sCurPos.dVPos, &sCurPos.dWPos, &sCurPos.nHand, &sCurPos.nElbow, &sCurPos.nFlip, &sCurPos.nJ4Flag, &sCurPos.nJ6Flag);
						bRet  = TRUE;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						bRet = FALSE;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						bRet = FALSE;
					}

					break;
				}
				else if (iRet == -1)
				{
					bRet = TRUE;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return bRet;
	}

	BOOL CEpsonRobot::QryToolCurPos(RobotPosInfo &sCurPos)
	{
		if (!m_bInit)
		{
			
			return m_bInit;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");	
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		char		szOK[128] = {0};

		strSend = _T("CMD 16 0 0 0 ");
		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);

		long		nSTTime = ::GetTickCount();
		if (bRet)
		{		
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						USES_CONVERSION;
						sscanf(T2A(szMsgInfo.c_str()), "%s%f%f%f%f%f%f%d%d%d%d%d", szOK, &sCurPos.dXPos, &sCurPos.dYPos, &sCurPos.dZPos, &sCurPos.dUPos,
							&sCurPos.dVPos, &sCurPos.dWPos, &sCurPos.nHand, &sCurPos.nElbow, &sCurPos.nFlip, &sCurPos.nJ4Flag, &sCurPos.nJ6Flag);
						bRet  = TRUE;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						bRet = FALSE;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						bRet = FALSE;
					}

					break;
				}
				else if (iRet == -1)
				{
					bRet = TRUE;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return bRet;
	}


	int CEpsonRobot::QryEnable()
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		char		szOK[128] = {0};
		strSend = _T("CMD 6 0 0 0 ");
		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}


		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);

		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						if (szMsgInfo.find(_T("Off")) >= 0)
						{
							iRet = 0;
						}
						else if (szMsgInfo.find(_T("On")) >= 0)
						{
							iRet = 1;
						}
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = -1;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = -1;
					}
					else
					{
						iRet = -1;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	int CEpsonRobot::QryPower()
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		char		szOK[128] = {0};
		strSend = _T("CMD 6 0 0 0 ");
		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}
		
		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);

		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						if (szMsgInfo.find(_T("Low")) >= 0)
						{
							iRet = 0;
						}
						else if (szMsgInfo.find(_T("High")) >= 0)
						{
							iRet = 1;
						}
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = -1;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = -1;
					}
					else
					{
						iRet = -1;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	BOOL CEpsonRobot::InitRobot(LPTSTR lpstrError)
	{

		tstring			szMessInfo = _T("");
		tstring			szSerCtrlSt = _T("");
		tstring			strRecv = _T("");
		int iRalayTime = 50;

		if (m_bRmCtrl && !m_pIInit->IsConnect())
		{
			if (!m_pIInit->IsConnect())
			{
				m_pIInit->DisConnect();

				if (!m_pIInit->ConnectServer(m_strRobotIp.c_str(), m_iInitPort))
				{
					swprintf(lpstrError, _T("连接 Robot 请重新连接 失败!"));
					m_bInit = FALSE;
					return m_bInit;
				}

				if (!Send(m_pIInit, DataCtrl(_T("Login,123456"))))
				{
					swprintf(lpstrError, _T("登录机器人控制器 失败! 发送指令:[Login]!"));
					m_bInit = FALSE;
					return m_bInit;
				}	

				Sleep(100);

				Receive(m_pIInit, strRecv);

				if (strRecv.find(_T("#")) == -1)
				{
					goto CONNECT;
				}
			}


			if (!Send(m_pIInit, DataCtrl(_T("GetStatus"))))     
			{  
				swprintf(lpstrError, _T("GetStatus 机器人端服务器程序 失败! 发送指令:[GetStatus]."));
				m_bInit = FALSE;
				return m_bInit;
			}
			
			Sleep(100);

			Receive(m_pIInit, szSerCtrlSt);

			szSerCtrlSt = szSerCtrlSt.substr(szSerCtrlSt.find(_T(","), 0) + 1, 11);
			if (szSerCtrlSt.at(4) - '0' == 1)
			{
				swprintf(lpstrError, _T("机器人程序已经崩溃, 请重新上电!"));
				m_bInit = FALSE;
				return m_bInit;
			}

			if (szSerCtrlSt.at(7) - '0' == 1)
			{
				if (!Send(m_pIInit, DataCtrl(_T("Reset"))))
				{  
					swprintf(lpstrError, _T("重置机器人端服务器程序 失败! 发送指令:[Reset]."));
					m_bInit = FALSE;
					return m_bInit;
				}

				Sleep(100);

				Receive(m_pIInit, strRecv);

				if (strRecv.find(_T("#")) == -1)
				{
					m_bInit = FALSE;
					return m_bInit;
				}

				Sleep(1000);
			}


// 			if (szSerCtrlSt.at(9) -'0' == 1)
// 			{
// 				return TRUE;
// 			}



			if (!Send(m_pIInit, DataCtrl(_T("Start,0"))))     
			{  
				swprintf(lpstrError, _T("启动机器人端服务器程序 失败! 发送指令:[Start]."));
				m_bInit = FALSE;
				return m_bInit;
			}

			
			Sleep(1000);

			Receive(m_pIInit, strRecv);

			if (strRecv.find(_T("#")) == -1)
			{
				m_bInit = FALSE;
				return m_bInit;
			}
		}	
		
		
CONNECT:
		//////////////////////////////////////////////////////////////////////////

		m_pIMove->DisConnect();

		Sleep(iRalayTime);


		if (!m_pIMove->ConnectServer(m_strRobotIp.c_str(), m_iMovePort)) //建立连接
		{
			swprintf(lpstrError, _T("Robot Move Contrl 连接 失败!"));
			m_bInit = FALSE;
			return m_bInit;
		}
		Sleep(iRalayTime);

		m_pICtrl->DisConnect();

		Sleep(iRalayTime);

		if (!m_pICtrl->ConnectServer(m_strRobotIp.c_str(), m_iCtrlPort)) //建立连接
		{
			swprintf(lpstrError, _T("Robot Ctrl Contrl 连接 失败!"));
			m_bInit = FALSE;
			return m_bInit;
		}

		m_pIVision->DisConnect();

		m_pIVision->ConnectServer(m_strRobotIp.c_str(), m_iVisionPort);

		m_bInit = TRUE;
		return m_bInit;
	}

	BOOL CEpsonRobot::IsRobotConnnect()
	{
		BOOL bRet = FALSE;

		if (m_pIInit && m_pIMove && m_pIVision && m_pICtrl)
		{
			bRet = m_pIMove->IsConnect() & m_pICtrl->IsConnect() & m_pIVision->IsConnect();
		}

		return bRet;
	}

	tstring	CEpsonRobot::DataCtrl(const tstring &szData)
	{
		tstring strSend = _T("$") + szData;
		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend  + m_ptcEndChar[i];
		}

		return strSend;
	}

	int CEpsonRobot::SetPower(const BOOL bPower)
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		char		szOK[128] = {0};
		if (bPower)
		{
			strSend = _T("CMD 4 0 0 0 ");
		}
		else
		{
			strSend = _T("CMD 3 0 0 0 ");
		}

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);

		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	int CEpsonRobot::SetEnable(const BOOL bEnable)
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		char		szOK[128] = {0};
		if (bEnable)
		{
			strSend = _T("CMD 1 0 0 0 ");
		}
		else
		{
			strSend = _T("CMD 2 0 0 0 ");
		}

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);

		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	int CEpsonRobot::SetSpeed(const int iSpeed, const int iAccel)
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD 10 %d %d 0 "), iSpeed, iAccel);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);
		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet =0;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	void CEpsonRobot::CloseConnect()
	{
		if (m_pICtrl)
		{
			m_pICtrl->DisConnect();
		}

		if (m_pIMove)
		{
			m_pIMove->DisConnect();
		}

		if (m_pIVision)
		{
			m_pIVision->DisConnect();
		}

		if (m_pIInit)
		{
			Send(m_pIInit, _T("LogOut"));
			m_pIInit->DisConnect();
		}

		m_bRunning = FALSE;
	}


	int CEpsonRobot::OpenOutPort(const int iOutPort)
	{
		if (!m_bInit)
		{		
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;

		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD 11 %d %d 0 "), iOutPort, 1);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}
		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);
		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{	
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = -1;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = -1;
					}
					else
					{
						iRet = -1;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	int CEpsonRobot::CloseOutPort(const int iOutPort)
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD 11 %d %d 0 "), iOutPort, 0);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}
		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);
		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{	
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = -1;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = -1;
					}
					else
					{
						iRet = -1;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	int CEpsonRobot::QryOutPort(const int iOutPort)
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD 13 %d 0 0 "), iOutPort);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}
		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);
		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						if (szMsgInfo.find(_T("Off")) >= 0)
						{
							iRet = 0;
						}
						else if (szMsgInfo.find(_T("On")) >= 0)
						{
							iRet = 1;
						}
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = -1;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = -1;
					}
					else
					{
						iRet = -1;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	int CEpsonRobot::QryInPort(const int iInPort)
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		m_csCtrl.Lock();
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD 14 %d 0 0 "), iInPort);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}
		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);
		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						if (szMsgInfo.find(_T("Off")) >= 0)
						{
							iRet = 0;
						}
						else if (szMsgInfo.find(_T("On")) >= 0)
						{
							iRet = 1;
						}
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = -1;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = -1;
					}
					else
					{
						iRet = -1;
					}

					break;
				}
				else if (iRet == -1)
				{
					
					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}
		m_csCtrl.Unlock();
		return iRet;
	}

	int CEpsonRobot::SuspendRobot()
	{
		int					iRet = -1;

		if (!m_bInit)
		{	
			return iRet;
		}

		if (Send(m_pIInit, DataCtrl(_T("Pause"))))
		{
			iRet = 1;
		}
		else
		{
			iRet = 0;
		}

		return  iRet;
	}

	int CEpsonRobot::ResumeRobot()
	{
		int					iRet = -1;

		if (!m_bInit)
		{
			
			return iRet;
		}

		if (Send(m_pIInit, DataCtrl(_T("Continue"))))
		{
			iRet = 1;
		}
		else
		{
			iRet = 0;
		}

		return  iRet;
	}

	int CEpsonRobot::StopRobot()
	{
		int					iRet = -1;

		if (!m_bInit)
		{
			
			return iRet;
		}

		if (Send(m_pIInit, DataCtrl(_T("Stop"))))
		{
			iRet = 1;
		}
		else
		{
			iRet = 0;
		}

		return  iRet;
	}

	int CEpsonRobot::GetPosInfo(const int iPosIndex, RobotPosInfo &sPosInfo)
	{
		if (!m_bInit)
		{
			
			return -1;
		}

		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");	
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		char		szOK[128] = {0};

		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD 30 %d 0 0 "), iPosIndex);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}
		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);//发送获取点数据的命令

		long		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						if (szMsgInfo.find(_T("Fail")) != -1)
						{
							iRet = 0;
						}
						else
						{
							USES_CONVERSION;
							sscanf(T2A(szMsgInfo.c_str()), "%s%f%f%f%f%f%f%d%d%d%d%d", szOK, &sPosInfo.dXPos, &sPosInfo.dYPos, &sPosInfo.dZPos, &sPosInfo.dUPos,
								&sPosInfo.dVPos, &sPosInfo.dWPos, &sPosInfo.nHand, &sPosInfo.nElbow, &sPosInfo.nFlip, &sPosInfo.nJ4Flag, &sPosInfo.nJ6Flag);
							iRet = 1;
						}

					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{
					break;
				}

				Sleep(10);
			}
		}

		return iRet;
	}

	int CEpsonRobot::StorePos(int iPosIndex)
	{
		if (!m_bInit)
		{
			
			return -1;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD 31 %d 0 0 "), iPosIndex);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}
		Receive(m_pICtrl, szMsgInfo);
		bRet = Send(m_pICtrl, strSend);
		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pICtrl, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{

					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}

		return iRet;
	}


	BOOL CEpsonRobot::Send(CIClient *pISend, tstring strSend)
	{
		BOOL bRet = FALSE;

		if (pISend && pISend->IsConnect())
		{
			USES_CONVERSION;
			bRet =pISend->SendData((BYTE *)T2A(strSend.c_str()), strSend.length());
		}

		return bRet;
	}

	int CEpsonRobot::Receive(CIClient *pISend, tstring &strRecv)
	{
		int iRet = -1;
		strRecv = _T("");

		if (pISend && pISend->IsConnect())
		{
			BYTE pbyRecv[1024] = {0};
			USES_CONVERSION;
			iRet = pISend->RecvData(pbyRecv, 1024);

			if (iRet > 0)
			{
				strRecv = A2T((char *)pbyRecv);
				iRet = 1;
			}
		}

		return iRet;
	}



	int CEpsonRobot::SetPosition(const int iPosition, RobotPosInfo sRobotPosInfo)
	{
		int		iRet = -1;
		m_csVision.Lock();
		if (m_pIVision && m_pIVision->IsConnect())
		{
			TCHAR		*ptcTemp = new TCHAR[1024];
			memset(ptcTemp, NULL, sizeof(TCHAR) * 1024);

			swprintf(ptcTemp, _T("CMD 1 %d %.3f %.3f %.3f %.3f %.3f %.3f %d %d %d %d %d\r\n"), iPosition, sRobotPosInfo.dXPos, sRobotPosInfo.dYPos, sRobotPosInfo.dZPos, sRobotPosInfo.dUPos, \
				     sRobotPosInfo.dVPos, sRobotPosInfo.dWPos, sRobotPosInfo.nHand, sRobotPosInfo.nElbow, sRobotPosInfo.nFlip, sRobotPosInfo.nJ4Flag, sRobotPosInfo.nJ6Flag);
			if (Send(m_pIVision, ptcTemp))
			{
				Sleep(100);
				tstring strRecv = _T("");
				Receive(m_pIVision, strRecv);

				if (strRecv.find(_T("OK")) != -1)
				{
					iRet = 1;
				}
				else
				{
					iRet = 0;
				}
			}

			if (ptcTemp)
			{
				delete[] ptcTemp;
				ptcTemp = NULL;
			}
		}
		m_csVision.Unlock();
		return iRet;
	}

	int CEpsonRobot::ChangeTool(const int iToolNo)
	{
		int		iRet = -1;
		m_csVision.Lock();
		if (m_pIVision && m_pIVision->IsConnect())
		{
			TCHAR ptcTemp[128] = {0};
			swprintf(ptcTemp, _T("CMD 0 %d\r\n"), iToolNo);
						
			if (Send(m_pIVision, ptcTemp))
			{
				Sleep(100);
				tstring strRecv = _T("");
				Receive(m_pIVision, strRecv);

				if (strRecv.find(_T("OK")) != -1)
				{
					iRet = 1;
				}
				else
				{
					iRet = 0;
				}
			}
		}
		m_csVision.Unlock();
		return iRet;
	}

	int CEpsonRobot::CreateTool(const int iCameraNo, const int iToolNo, const double dXVal, const double dYVal)
	{
		int		iRet = -1;
		m_csVision.Lock();
		if (m_pIVision && m_pIVision->IsConnect())
		{
			TCHAR ptcTemp[128] = {0};
			swprintf(ptcTemp, _T("CMD 4 %d %.3f %.3f %d\r\n"), iToolNo, dXVal, dYVal, iCameraNo);

			if (Send(m_pIVision, ptcTemp))
			{
				Sleep(100);
				tstring strRecv = _T("");
				Receive(m_pIVision, strRecv);

				if (strRecv.find(_T("OK")) != -1)
				{
					iRet = 1;
				}
				else
				{
					iRet = 0;
				}
			}
		}
		m_csVision.Unlock();
		return iRet;
	}

	int CEpsonRobot::TransPosition(RobotPosInfo &sTransPos, const double dXVal, const double dYVal, const double dUVal, const int iCameraNo)
	{
		int		iRet = -1;
		m_csVision.Lock();
		if (m_pIVision && m_pIVision->IsConnect())
		{
			
			TCHAR ptcTemp[128] = {0};
			swprintf(ptcTemp, _T("CMD 3 %.3f %.3f %.3f %d\r\n"), dXVal, dYVal, dUVal,iCameraNo);

			if (Send(m_pIVision, ptcTemp))
			{
				Sleep(100);
				tstring strRecv = _T("");
				Receive(m_pIVision, strRecv);

				if (strRecv.find(_T("OK")) != -1)
				{
					USES_CONVERSION;
					strRecv = strRecv.substr(strRecv.find(_T(",")) + 1);	
					swscanf(strRecv.c_str(), _T("%f,%f,%f,%f,%f,%f,%d,%d %d,%d,%d"), &sTransPos.dXPos, &sTransPos.dYPos, &sTransPos.dZPos, &sTransPos.dUPos,
						&sTransPos.dVPos, &sTransPos.dWPos, &sTransPos.nHand, &sTransPos.nElbow, &sTransPos.nFlip, &sTransPos.nJ4Flag, &sTransPos.nJ6Flag);
					iRet = 1;
				}
				else
				{
					iRet = 0;
				}
			}
		}
		m_csVision.Unlock();
		return iRet;
	}

	int CEpsonRobot::CameraCal(const int iCameraNo, const int iType, LPTSTR lpstrVisionRst)
	{
		int		iRet = -1;
		m_csVision.Lock();
		if (m_pIVision && m_pIVision->IsConnect())
		{
			TCHAR ptcTemp[128] = {0};
			swprintf(ptcTemp, _T("CMD 2 %d %d\r\n"), iCameraNo, iType);

			if (Send(m_pIVision, ptcTemp))
			{
				Sleep(100);
				tstring strRecv = _T("");
				Receive(m_pIVision, strRecv);

				if (strRecv.find(_T("OK")) != -1)
				{
					USES_CONVERSION;
					strRecv = strRecv.substr(strRecv.find(_T(",")) + 1);	
					_tcscpy(lpstrVisionRst, strRecv.c_str());
					iRet = 1;
				}
				else
				{
					iRet = 0;
				}
			}
		}
		m_csVision.Unlock();
		return iRet;
	}

	int CEpsonRobot::SetTool(const int iIndex, const double dXPos, const double dYPos, const double dZPos /* = 0.0 */, const double dUPos /* = 0.0 */)
	{
		if (!m_bInit)
		{

			return -1;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD %d %d %.3f %.3f  %.3f  %.3f "), 7, iIndex, dXPos, dYPos, dZPos, dUPos);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pIVision, szMsgInfo);
		bRet = Send(m_pIVision, strSend);

		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pIVision, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
							iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{

					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}

		return iRet;
	}

	int CEpsonRobot::GetTool(const int iIndex, double &dXPos, double &dYPos, double &dZPos, double &dUPos)
	{
		if (!m_bInit)
		{

			return -1;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD %d %d "), 8, iIndex);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pIVision, szMsgInfo);
		bRet = Send(m_pIVision, strSend);

		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pIVision, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						char		szOK[128] = {0};
						RobotPosInfo sTransPos;
						USES_CONVERSION;
						szMsgInfo = szMsgInfo.substr(szMsgInfo.find(_T(",")) + 1);	
						swscanf(szMsgInfo.c_str(), _T("%f,%f,%f,%f,%f,%f,%d,%d %d,%d,%d"), &sTransPos.dXPos, &sTransPos.dYPos, &sTransPos.dZPos, &sTransPos.dUPos,
							&sTransPos.dVPos, &sTransPos.dWPos, &sTransPos.nHand, &sTransPos.nElbow, &sTransPos.nFlip, &sTransPos.nJ4Flag, &sTransPos.nJ6Flag);
						dXPos = sTransPos.dXPos;
						dYPos = sTransPos.dYPos;
						dZPos = sTransPos.dZPos;
						dUPos = sTransPos.dUPos;
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{

					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}

		return iRet;
	}

	int CEpsonRobot::CreatePallet(const int iPalletNo, const int iRow, const int iCol)
	{
		if (!m_bInit)
		{

			return -1;
		}
		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD %d %d %d %d "), 5, iPalletNo, iRow, iCol);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pIVision, szMsgInfo);
		bRet = Send(m_pIVision, strSend);

		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pIVision, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
							iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{

					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}

		return iRet;
	}

	int CEpsonRobot::GetPalletPos(const int iPalletNo, const int iPositionNo, RobotPosInfo &sPosInfo)
	{
		if (!m_bInit)
		{
			return -1;
		}

		BOOL		bRet = FALSE;
		tstring		strSend = _T("");
		tstring		szRedv = _T("");
		long		nSTTime = ::GetTickCount();
		tstring		szMsgInfo = _T("");
		int			iRet = -1;
		TCHAR		ptcTemp[128] = {0};
		swprintf(ptcTemp, _T("CMD %d %d %d "), 6, iPalletNo, iPositionNo);
		strSend = ptcTemp;

		for (int i = 0; i < m_iEndCharCnt; ++i)
		{
			strSend = strSend + m_ptcEndChar[i];
		}

		Receive(m_pIVision, szMsgInfo);
		bRet = Send(m_pIVision, strSend);

		nSTTime = ::GetTickCount();
		if (bRet)
		{
			while ((::GetTickCount() - nSTTime) < 10000)
			{
				szMsgInfo = _T("");
				iRet = Receive(m_pIVision, szMsgInfo);
				if (iRet == 1)
				{
					if (szMsgInfo.find(_T("OK"))!=-1)
					{
						char		szOK[128] = {0};
						USES_CONVERSION;
						szMsgInfo = szMsgInfo.substr(szMsgInfo.find(_T(",")) + 1);	
						swscanf(szMsgInfo.c_str(), _T("%f,%f,%f,%f,%f,%f,%d,%d %d,%d,%d"), &sPosInfo.dXPos, &sPosInfo.dYPos, &sPosInfo.dZPos, &sPosInfo.dUPos,
							&sPosInfo.dVPos, &sPosInfo.dWPos, &sPosInfo.nHand, &sPosInfo.nElbow, &sPosInfo.nFlip, &sPosInfo.nJ4Flag, &sPosInfo.nJ6Flag);
						iRet = 1;
					}
					else if (szMsgInfo.find(_T("ER")) != -1)
					{
						iRet = 0;

					}
					else if (szMsgInfo.find(_T("err")) != -1)
					{
						iRet = 0;
					}
					else
					{
						iRet = 0;
					}

					break;
				}
				else if (iRet == -1)
				{

					iRet = -1;
					break;
				}

				Sleep(10);
			}
		}

		return iRet;
	}

}