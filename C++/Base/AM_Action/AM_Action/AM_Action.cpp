// AM_Action.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "AM_Action.h"


namespace Aciton
{

	CAction::CAction()
	{
		CIniFile cIniFile;
		m_strConfigDir = cIniFile.GetModulePath() + _T("\\Config\\");
		m_strConfigIni = m_strConfigDir + _T("Config.ini");
		cIniFile.SetIniFile(m_strConfigIni.c_str());
		m_strPointsDat = cIniFile.GetModulePath() + _T("\\Data\\Point.dat");
		m_strIODat = cIniFile.GetModulePath() + _T("\\Data\\IO.dat");
		m_strParamIni = m_strConfigDir + _T("Param.pm");
		m_mapActionType[IOTYPE] = 1;
		m_mapActionType[ROBOTTYPE] = 100;
		m_mapActionType[TIMEOUTTYPE] = 3;
		m_mapActionType[MSGTYPE] = 4;
		m_mapActionType[COMPARE] = 5;
		m_mapActionType[VOLUATION] = 2;
	} 

	CAction::~CAction()
	{
		while (m_mapIRobot.begin() != m_mapIRobot.end())
		{
			CIRobot *pIRobot = (m_mapIRobot.begin())->second;
			ReleaseRobot(pIRobot);
			m_mapIRobot.erase(m_mapIRobot.begin());
			Sleep(100);
		}

		while (m_mapIPLCCtrl.begin() != m_mapIPLCCtrl.end())
		{
			CIPLCCtrl *pIPLCCtrl = (m_mapIPLCCtrl.begin())->second;
			AM_ReleasePLCCtrl(pIPLCCtrl);
			m_mapIPLCCtrl.erase(m_mapIPLCCtrl.begin());
			Sleep(100);
		}
	}

	void CAction::LoadPosInfo()
	{
		m_mapRobotPosInfo.clear();

		int		iPosCount = 0;
		int		iLength = 0;
		tstring strName = _T("");
		tstring strTemp = _T("");
		CIniFile cIniFile;
		cIniFile.SetIniFile(m_strPointsDat.c_str());
		iPosCount = cIniFile.GetKeyCount(_T("Points"));


		for (int i = 0; i < iPosCount; ++i)
		{
			iLength = 0;
			strTemp = cIniFile.ReadString(_T("Points"), cIniFile.GetKeyName(_T("Points"), i).c_str(), _T(""));
			PosInfo sPosInfo;
	
			strName = strTemp.substr(iLength, strTemp.find(_T(","), iLength) - iLength);
			iLength =  strTemp.find(_T(","), iLength) + 1;
			sPosInfo.iRobotNo = _ttoi(strTemp.substr(iLength, strTemp.find(_T(","), iLength) - iLength).c_str());
			iLength =  strTemp.find(_T(","), iLength) + 1;
			sPosInfo.sRobotPos.dXPos = (float)_ttof(strTemp.substr(iLength, strTemp.find(_T(","), iLength) - iLength).c_str());
			iLength =  strTemp.find(_T(","), iLength) + 1;
			sPosInfo.sRobotPos.dYPos = (float)_ttof(strTemp.substr(iLength, strTemp.find(_T(","), iLength) - iLength).c_str());
			iLength =  strTemp.find(_T(","), iLength) + 1;
			sPosInfo.sRobotPos.dZPos = (float)_ttof(strTemp.substr(iLength, strTemp.find(_T(","), iLength) - iLength).c_str());
			iLength =  strTemp.find(_T(","), iLength) + 1;
			sPosInfo.sRobotPos.dUPos = (float)_ttof(strTemp.substr(iLength, strTemp.find(_T(","), iLength) - iLength).c_str());
			m_mapRobotPosInfo[strName] = sPosInfo;
		}
	}

	void CAction::LoadIOInfo()
	{
		CIniFile cIniFile;
		cIniFile.SetIniFile(m_strIODat.c_str());
		tstring strKey = _T("");
		tstring strSection = _T("");
		tstring strVal = _T("");
		m_mapIOInfo.clear();
		for (int i = 0; i < cIniFile.GetSectionCount(); ++i)
		{
			strSection = cIniFile.GetSectionName(i);

			for (int j = 0; j < cIniFile.GetKeyCount(strSection.c_str()); ++j)
			{
				IOInfo sPlcInfo;
				strKey = cIniFile.GetKeyName(strSection.c_str(), j);
				strVal = cIniFile.ReadString(strSection.c_str(), strKey.c_str(), _T("0,0,1,0"));
				swscanf(strVal.c_str(), _T("%d,%c,%d,%d"), &sPlcInfo.iPortNo, &sPlcInfo.ptcHex[0], &sPlcInfo.iStation, &sPlcInfo.iCardNo);
				m_mapIOInfo[strSection][strKey] = sPlcInfo;
			}
		}
	}

	int CAction::CheckRelay(LPCTSTR lpstrName)
	{
		int iRet = -1;

		if ((m_mapIOInfo.find(_T("Relay")) != m_mapIOInfo.end()) && (m_mapIOInfo[_T("Relay")].find(lpstrName) != m_mapIOInfo[_T("Relay")].end()))
		{
			USES_CONVERSION;
			int iCardNo = m_mapIOInfo[_T("Relay")][lpstrName].iCardNo;
			if (m_mapIPLCCtrl.find(iCardNo) != m_mapIPLCCtrl.end())
			{
				if (m_mapIPLCCtrl[iCardNo]->IsConnect())
				{
					iRet = m_mapIPLCCtrl[iCardNo]->CheckRelay(m_mapIOInfo[_T("Relay")][lpstrName].iPortNo, T2A(m_mapIOInfo[_T("Relay")][lpstrName].ptcHex));
				}
			}
		}

		return iRet;
	}

	int CAction::SetRelay(LPCTSTR lpstrName)
	{
		int iRet = -1;

		if ((m_mapIOInfo.find(_T("Relay")) != m_mapIOInfo.end()) && (m_mapIOInfo[_T("Relay")].find(lpstrName) != m_mapIOInfo[_T("Relay")].end()))
		{
			USES_CONVERSION;
			int iCardNo = m_mapIOInfo[_T("Relay")][lpstrName].iCardNo;

			if (m_mapIPLCCtrl.find(iCardNo) != m_mapIPLCCtrl.end())
			{
				if (m_mapIPLCCtrl[iCardNo]->IsConnect())
				{
					iRet = m_mapIPLCCtrl[iCardNo]->SetRelay(m_mapIOInfo[_T("Relay")][lpstrName].iPortNo, T2A(m_mapIOInfo[_T("Relay")][lpstrName].ptcHex));
				}
			}
		}

		return iRet;
	}

	int CAction::ClearRelay(LPCTSTR lpstrName)
	{
		int iRet = -1;

		if ((m_mapIOInfo.find(_T("Relay")) != m_mapIOInfo.end()) && (m_mapIOInfo[_T("Relay")].find(lpstrName) != m_mapIOInfo[_T("Relay")].end()))
		{
			USES_CONVERSION;
			int iCardNo = m_mapIOInfo[_T("Relay")][lpstrName].iCardNo;

			if (m_mapIPLCCtrl.find(iCardNo) != m_mapIPLCCtrl.end())
			{
				if (m_mapIPLCCtrl[iCardNo]->IsConnect())
				{
					iRet = m_mapIPLCCtrl[iCardNo]->ClearRelay(m_mapIOInfo[_T("Relay")][lpstrName].iPortNo, T2A(m_mapIOInfo[_T("Relay")][lpstrName].ptcHex));
				}
			}
		}

		return iRet;
	}

	int CAction::CheckInport(LPCTSTR lpstrName)
	{
		int iRet = -1;

		if ((m_mapIOInfo.find(_T("Inport")) != m_mapIOInfo.end()) && (m_mapIOInfo[_T("Inport")].find(lpstrName) != m_mapIOInfo[_T("Inport")].end()))
		{
			USES_CONVERSION;
			int iCardNo = m_mapIOInfo[_T("Inport")][lpstrName].iCardNo;

			if (m_mapIPLCCtrl.find(iCardNo) != m_mapIPLCCtrl.end())
			{
				if (m_mapIPLCCtrl[iCardNo]->IsConnect())
				{
					iRet = m_mapIPLCCtrl[iCardNo]->ReadInPort(m_mapIOInfo[_T("Inport")][lpstrName].iPortNo, T2A(m_mapIOInfo[_T("Inport")][lpstrName].ptcHex));
				}
			}
		}

		return iRet;
	}

	int CAction::CheckOutport(LPCTSTR lpstrName)
	{
		int iRet = -1;

		if ((m_mapIOInfo.find(_T("Outport")) != m_mapIOInfo.end()) && (m_mapIOInfo[_T("Outport")].find(lpstrName) != m_mapIOInfo[_T("Outport")].end()))
		{
			USES_CONVERSION;
			int iCardNo = m_mapIOInfo[_T("Outport")][lpstrName].iCardNo;

			if (m_mapIPLCCtrl.find(iCardNo) != m_mapIPLCCtrl.end())
			{
				if (m_mapIPLCCtrl[iCardNo]->IsConnect())
				{
					iRet = m_mapIPLCCtrl[iCardNo]->CheckOutPort(m_mapIOInfo[_T("Outport")][lpstrName].iPortNo, T2A(m_mapIOInfo[_T("Outport")][lpstrName].ptcHex));
				}
			}
		}

		return iRet;
	}

	int CAction::OpenOutport(LPCTSTR lpstrName)
	{
		int iRet = -1;


		if ((m_mapIOInfo.find(_T("Outport")) != m_mapIOInfo.end()) && (m_mapIOInfo[_T("Outport")].find(lpstrName) != m_mapIOInfo[_T("Outport")].end()))
		{
			USES_CONVERSION;
			int iCardNo = m_mapIOInfo[_T("Outport")][lpstrName].iCardNo;

			if (m_mapIPLCCtrl.find(iCardNo) != m_mapIPLCCtrl.end())
			{
				if (m_mapIPLCCtrl[iCardNo]->IsConnect())
				{
					iRet = m_mapIPLCCtrl[iCardNo]->OpenOutPort(m_mapIOInfo[_T("Outport")][lpstrName].iPortNo, T2A(m_mapIOInfo[_T("Outport")][lpstrName].ptcHex));
				}
			}
		}

		return iRet;
	}

	int CAction::CloseOutport(LPCTSTR lpstrName)
	{
		int iRet = -1;

		if ((m_mapIOInfo.find(_T("Outport")) != m_mapIOInfo.end()) && (m_mapIOInfo[_T("Outport")].find(lpstrName) != m_mapIOInfo[_T("Outport")].end()))
		{
			USES_CONVERSION;
			int iCardNo = m_mapIOInfo[_T("Outport")][lpstrName].iCardNo;

			if (m_mapIPLCCtrl.find(iCardNo) != m_mapIPLCCtrl.end())
			{
				if (m_mapIPLCCtrl[iCardNo]->IsConnect())
				{
					iRet = m_mapIPLCCtrl[iCardNo]->CloseOutPort(m_mapIOInfo[_T("Outport")][lpstrName].iPortNo, T2A(m_mapIOInfo[_T("Outport")][lpstrName].ptcHex));
				}
			}
		}

		return iRet;
	}

	BOOL CAction::GotoDistance(const int iAxisNo, double dDistance, const int iMoveMode, const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;
		
		if (m_mapIRobot.find(iRobotNo) != m_mapIRobot.end())
		{
			if (m_mapIRobot[iRobotNo]->IsRobotConnnect())
			{
				TCHAR ptcAXis[64] = {0};
				swprintf(ptcAXis, _T("%cXis"), iAxisNo);
				bRet = m_mapIRobot[iRobotNo]->GotoDistance(ptcAXis, dDistance, iMoveMode);
			}
		}

		return bRet;
	}

	BOOL CAction::GotoDistance(const LPCTSTR lpstrAxis, double dDistance, const int iMoveMode /* = 0 */, const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;

		if (m_mapIRobot.find(iRobotNo) != m_mapIRobot.end())
		{
			if (m_mapIRobot[iRobotNo]->IsRobotConnnect())
			{
				bRet = m_mapIRobot[iRobotNo]->GotoDistance(lpstrAxis, dDistance, iMoveMode);
			}
		}

		return bRet;
	}

	BOOL CAction::GotoPosMod(const LPCTSTR lpstrPosName, const double dZHight /* = -15.0 */, const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;

		if ((m_mapRobotPosInfo.find(lpstrPosName) != m_mapRobotPosInfo.end()) 
			&& (m_mapRobotPosInfo[lpstrPosName].iRobotNo == iRobotNo)
			&& (m_mapIRobot.find(iRobotNo) != m_mapIRobot.end())
			&& m_mapIRobot[iRobotNo]->IsRobotConnnect())
		{
			bRet = m_mapIRobot[iRobotNo]->GotoPosMod(m_mapRobotPosInfo[lpstrPosName].sRobotPos, dZHight);
		}

		return bRet;
	}

	BOOL CAction::IsRobotBusy(DWORD dwTimeOut /* = 10 */, const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;
		
		if ((m_mapIRobot.find(iRobotNo) != m_mapIRobot.end()) && m_mapIRobot[iRobotNo]->IsRobotConnnect())
		{
			bRet = m_mapIRobot[iRobotNo]->IsRobotBusy(dwTimeOut);
		}

		return bRet;
	}

	BOOL CAction::SetPower(const BOOL bPower, const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;

		if ((m_mapIRobot.find(iRobotNo) != m_mapIRobot.end()) && m_mapIRobot[iRobotNo]->IsRobotConnnect())
		{
			bRet = (m_mapIRobot[iRobotNo]->SetPower(bPower) == 1);
		}

		return bRet;
	}

	BOOL CAction::SetSpeed(const int iSpeed, const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;

		if ((m_mapIRobot.find(iRobotNo) != m_mapIRobot.end()) && m_mapIRobot[iRobotNo]->IsRobotConnnect())
		{
			bRet = (m_mapIRobot[iRobotNo]->SetSpeed(iSpeed, 120) == 1);
		}

		return bRet;
	}

	BOOL CAction::SuspendRobot(const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;

		if ((m_mapIRobot.find(iRobotNo) != m_mapIRobot.end()) && m_mapIRobot[iRobotNo]->IsRobotConnnect())
		{
			bRet = (m_mapIRobot[iRobotNo]->SuspendRobot() == 1);
		}

		return bRet;
	}

	BOOL CAction::ResumeRobot(const int iRobotNo /* = 0 */)
	{
		BOOL bRet = FALSE;

		if ((m_mapIRobot.find(iRobotNo) != m_mapIRobot.end()) && m_mapIRobot[iRobotNo]->IsRobotConnnect())
		{
			bRet = (m_mapIRobot[iRobotNo]->ResumeRobot() == 1);
		}

		return bRet;
	}

	BOOL CAction::InitParam()
	{
		BOOL bRet = TRUE;
		CIniFile cIniFile;
		tstring strSection = _T("");
		tstring strType = _T("");
		int iSectionCount = 0;

		cIniFile.SetIniFile(m_strParamIni.c_str());		
		iSectionCount = cIniFile.GetSectionCount();

		for (int i = 0; i < iSectionCount; ++i)
		{			
			strSection = cIniFile.GetSectionName(i);
			strType = cIniFile.ReadString(strSection.c_str(), _T("Type"), _T(""));
			if (strType == _T("Robot"))
			{
				bRet &= InitRobotParam(strSection);
			}
			else if (strType == _T("IO"))
			{
				bRet &= InitIOParam(strSection);
			}
		}

		return bRet;
	}

	BOOL CAction::InitRobotParam(tstring strSection)
	{
		BOOL bRet = TRUE;
		int iRobotNo = 0;
		tstring strIp = _T("");
		int iInitPort = 0;
		int iMovePort = 0;
		int iCtrlPort = 0;

		CIniFile cIniFile;
		cIniFile.SetIniFile(m_strParamIni.c_str());
		iRobotNo = cIniFile.ReadInt(strSection.c_str(), _T("No"), 0);
		strIp = cIniFile.ReadString(strSection.c_str(), _T("Ip"), _T("192.168.0.1"));
		iInitPort = cIniFile.ReadInt(strSection.c_str(), _T("InitPort"), 5000);
		iMovePort = cIniFile.ReadInt(strSection.c_str(), _T("MovePort"), 4000);
		iCtrlPort = cIniFile.ReadInt(strSection.c_str(), _T("CtrlPort"), 4001);

		if (m_mapIRobot.find(iRobotNo) != m_mapIRobot.end())
		{
			CIRobot *pIRobot = NULL;
			TCHAR ptcError[256] = {0};
			CreateRobot(&pIRobot, 0);
			pIRobot->SetRobotIp(strIp.c_str());
			pIRobot->SetInitPort(iInitPort);
			pIRobot->SetMovePort(iMovePort);
			pIRobot->SetCtrlPort(iCtrlPort);
			bRet = pIRobot->InitRobot(ptcError);
			m_mapIRobot[iRobotNo] = pIRobot;
		}
		else
		{
			TCHAR ptcError[256] = {0};
			m_mapIRobot[iRobotNo]->CloseConnect();
			m_mapIRobot[iRobotNo]->SetRobotIp(strIp.c_str());
			m_mapIRobot[iRobotNo]->SetInitPort(iInitPort);
			m_mapIRobot[iRobotNo]->SetMovePort(iMovePort);
			m_mapIRobot[iRobotNo]->SetCtrlPort(iCtrlPort);
			bRet = m_mapIRobot[iRobotNo]->InitRobot(ptcError);
		}

		return bRet;
	}

	BOOL CAction::InitIOParam(tstring strSection)
	{
		BOOL bRet = TRUE;
		int iComNo = 0;
		int iBaud = 0;
		int iStopBits = 0;
		int iParity = 0;
		int iDataBits = 0;
		CIniFile cIniFile;
		cIniFile.SetIniFile(m_strParamIni.c_str());

		for (int i = 0; i < cIniFile.GetKeyCount(strSection.c_str()); ++i)
		{
			tstring strKey = _T("");
			tstring strValue = _T("");
			strKey = cIniFile.GetKeyName(strSection.c_str(), i);
			iComNo = _ttoi(strKey.c_str());
			strValue = cIniFile.ReadString(strSection.c_str(), strKey.c_str(), _T("1,9600,8,0,0"));
			swscanf(strValue.c_str(), _T("%d,%d,%d,%d,%d"), &iComNo, &iBaud, &iDataBits, &iParity, &iStopBits);
			if (m_mapIPLCCtrl.find(iComNo) != m_mapIPLCCtrl.end())
			{
				CIPLCCtrl *pIPlcCtrl = NULL;
				AM_CreatePLCCtrl(&pIPlcCtrl, 0);
				
				bRet = pIPlcCtrl->SetCom(iComNo, iBaud, iDataBits, iParity, iStopBits);
				m_mapIPLCCtrl[iComNo] = pIPlcCtrl;
			}
			else
			{
				m_mapIPLCCtrl[iComNo]->DisConnect();
				bRet = m_mapIPLCCtrl[iComNo]->SetCom(iComNo, iBaud, iDataBits, iParity, iStopBits);
			}
		}

		return bRet;
	}

	BOOL CAction::Action(LPCTSTR lpstrType, LPCTSTR lpstrValue)
	{
		if (m_mapActionType.find(lpstrType) != m_mapActionType.end())
		{
			tstring strOpMode = _T("");
			tstring strName = _T("");
			tstring strValue = _T("");
			tstring strTemp = _T("");
			int iCount = 0;
			int iPos = 0;
			iCount = count(lpstrValue, lpstrValue + _tcslen(lpstrValue), ',');
			strTemp = lpstrValue;
			if (iCount == 1)
			{
				strOpMode = strTemp.substr(iPos, strTemp.find(',', iPos) - iPos);
				iPos = strTemp.find(',', iPos) + 1;
				strName = strTemp.substr(iPos, strTemp.find(',', iPos) - iPos);
			}
			else if (iCount > 1)
			{
				strOpMode = strTemp.substr(iPos, strTemp.find(',', iPos) - iPos);
				iPos = strTemp.find(',', iPos) + 1;
				strName = strTemp.substr(iPos, strTemp.find(',', iPos) - iPos);
				iPos = strTemp.find(',', iPos) + 1;
				strValue = strTemp.substr(iPos, strTemp.find(',', iPos) - iPos);

			}

			//
			switch (m_mapActionType[lpstrType])
			{
			case 1:
				{
					return IOAction(strOpMode.c_str(), strName.c_str(), strValue.c_str());
				}
				break;

			case 2:
				{
					return TimeAction(strOpMode.c_str(), strName.c_str(), strValue.c_str());
				}
				break;

			case 3:
				{
					return MsgAction(strOpMode.c_str(), strName.c_str(), strValue.c_str());
				}
				break;

			case 4:
				{
					return CmpAction(strOpMode.c_str(), strName.c_str(), strValue.c_str());
				}
				break;

			case 5:
				{
					return VolAction(strOpMode.c_str(), strName.c_str(), strValue.c_str());
				}
				break;

			default:
				{
					return FALSE;
				}
			}
		}

		return FALSE;
	}

	BOOL CAction::Action(LPCTSTR lpstrType, LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrType, IOTYPE) == 0)
		{
			return IOAction(lpstrOpMode, lpstrName, lpstrValue);
		}
		else if (_tcsicmp(lpstrType, ROBOTTYPE) == 0)
		{
			return RobotAction(lpstrOpMode, lpstrName, lpstrValue);
		}
		else if (_tcsicmp(lpstrType, TIMEOUTTYPE) == 0)
		{
			return TimeAction(lpstrOpMode, lpstrName, lpstrValue);
		}
		else if (_tcsicmp(lpstrType, MSGTYPE) == 0)
		{
			return MsgAction(lpstrOpMode, lpstrName, lpstrValue);
		}
		else if (_tcsicmp(lpstrType, COMPARE) == 0)
		{
			return CmpAction(lpstrOpMode, lpstrName, lpstrValue);
		}
		else if (_tcsicmp(lpstrType, VOLUATION) == 0)
		{
			return VolAction(lpstrOpMode, lpstrName, lpstrValue);
		}

		return FALSE;
	}

	BOOL CAction::IOAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrOpMode, OPENOUTPORT) == 0)
		{
			if (OpenOutport(lpstrName) == 1)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, CLOSEOUTPORT) == 0)
		{
			if (CloseOutport(lpstrName) == 1)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, CHECKINPORT) == 0)
		{
			if (CheckOutport(lpstrName) == _ttoi(lpstrValue))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, CHECKINPORT) == 0)
		{
			if (CheckInport(lpstrName) == _ttoi(lpstrValue))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, SETRELAY) == 0)
		{
			if (SetRelay(lpstrName) == 1)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, CLEARRELAY) == 0)
		{
			if (ClearRelay(lpstrName) == 1)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, CHECKRELAY) == 0)
		{
			if (CheckRelay(lpstrName) == _ttoi(lpstrValue))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	BOOL CAction::RobotAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrOpMode, GOTOPOSMOD) == 0)
		{
			return GotoPosMod(lpstrName);
		}
		else if (_tcsicmp(lpstrOpMode, XAXIS) == 0)
		{
			return GotoDistance(lpstrOpMode, _ttof(lpstrValue));
		}
		else if (_tcsicmp(lpstrOpMode, YAXIS) == 0)
		{
			return GotoDistance(lpstrOpMode, _ttof(lpstrValue));
		}
		else if (_tcsicmp(lpstrOpMode, ZAXIS) == 0)
		{
			return GotoDistance(lpstrOpMode, _ttof(lpstrValue));
		}
		else if (_tcsicmp(lpstrOpMode, UAXIS) == 0)
		{
			return GotoDistance(lpstrOpMode, _ttof(lpstrValue));
		}
		else if (_tcsicmp(lpstrOpMode, ISBUSY) == 0)
		{
			return IsRobotBusy(_ttoi(lpstrValue));
		}
		else if (_tcsicmp(lpstrOpMode, POWER) == 0)
		{
			if (_tcsicmp(lpstrOpMode, POWER) == 0)
			{
				return SetPower(_ttoi(lpstrValue));
			}				
		}
		else if (_tcsicmp(lpstrOpMode, SPEED) == 0)
		{
			return SetSpeed(_ttoi(lpstrName));
		}
		else
		{
			return FALSE;
		}
	}
	
	BOOL CAction::TimeAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrOpMode, BEGINTIME) == 0)
		{
			m_mapTimeOut[lpstrName] = ::GetTickCount();
			return TRUE;
		}
		else if (_tcsicmp(lpstrOpMode, ISTIMEOUT) == 0)
		{
			if (::GetTickCount() - m_mapTimeOut[lpstrName] > _ttoi(lpstrValue))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, SLEEP) == 0)
		{
			Sleep(_ttoi(lpstrValue));
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	BOOL CAction::MsgAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrOpMode, SENDMSG) == 0)
		{
			::SendMessage(m_mapMsgWnd[lpstrOpMode], _ttoi(lpstrName), _ttoi(lpstrValue), NULL);
			return TRUE;
		}
		else if (_tcsicmp(lpstrOpMode, POSTMSG) == 0)
		{
			::PostMessage(m_mapMsgWnd[lpstrOpMode], _ttoi(lpstrName), _ttoi(lpstrValue), NULL);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	BOOL CAction::CmpAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrOpMode, BOOLEAN) == 0)
		{
			if (m_mapBOOL.find(lpstrName) != m_mapBOOL.end())
			{
				return m_mapBOOL[lpstrName];
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, INTEGER) == 0)
		{
			if (m_mapInt.find(lpstrName) != m_mapInt.end())
			{
				if (m_mapInt.find(lpstrValue) != m_mapInt.end())
				{
					if (m_mapInt[lpstrName] == m_mapInt[lpstrValue])
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
				else
				{
					if (m_mapInt[lpstrName] == _ttoi(lpstrValue))
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, FLOATNUM) == 0)
		{
			if (m_mapFloat.find(lpstrName) != m_mapFloat.end())
			{
				if (m_mapFloat.find(lpstrValue) != m_mapFloat.end())
				{
					if (fabs(m_mapFloat[lpstrName] - m_mapFloat[lpstrValue]) < 0.001)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
				else
				{
					if (fabs(m_mapFloat[lpstrName] - (float)_ttof(lpstrValue)) < 0.001)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
			}
			else
			{
				return FALSE;
			}
		}
		else if (_tcsicmp(lpstrOpMode, FLOATNUM) == 0)
		{
			if (m_mapDouble.find(lpstrName) != m_mapDouble.end())
			{
				if (m_mapDouble.find(lpstrValue) != m_mapDouble.end())
				{
					if (fabs(m_mapDouble[lpstrName] - m_mapDouble[lpstrValue]) < 0.001)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
				else
				{
					if (fabs(m_mapDouble[lpstrName] - _ttof(lpstrValue)) < 0.001)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	BOOL CAction::VolAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrOpMode, BOOLEAN) == 0)
		{
			if (_ttoi(lpstrValue) != 0)
			{
				m_mapBOOL[lpstrName] = TRUE;
			}
			else
			{
				m_mapBOOL[lpstrName] = FALSE;
			}

			return TRUE;
		}
		else if (_tcsicmp(lpstrOpMode, INTEGER) == 0)
		{
			if (m_mapInt.find(lpstrValue) != m_mapInt.end())
			{
				m_mapInt[lpstrName] = m_mapInt[lpstrValue];						
			}
			else
			{
				m_mapInt[lpstrName] = _ttoi(lpstrValue);
			}

			return TRUE;
		}
		else if (_tcsicmp(lpstrOpMode, FLOATNUM) == 0)
		{

			if (m_mapFloat.find(lpstrValue) != m_mapFloat.end())
			{
				m_mapFloat[lpstrName] = m_mapFloat[lpstrValue];
			}
			else
			{
				m_mapFloat[lpstrName] = (float)_ttof(lpstrValue);		
			}

			return TRUE;
		}
		else if (_tcsicmp(lpstrOpMode, FLOATNUM) == 0)
		{
			if (m_mapDouble.find(lpstrValue) != m_mapDouble.end())
			{
				m_mapDouble[lpstrName] - m_mapDouble[lpstrValue];
			}
			else
			{
				m_mapDouble[lpstrName] = _ttof(lpstrValue);
			}
	
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	BOOL CAction::CalAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		return FALSE;
	}

	BOOL CAction::FCAction(LPCTSTR lpstrOpMode, LPCTSTR lpstrName, LPCTSTR lpstrValue)
	{
		if (_tcsicmp(lpstrOpMode, SUSPEND) == 0)
		{
			return Suspend();
		}
		else if (_tcsicmp(lpstrOpMode, RESUME) == 0)
		{
			return Resume();
		}
		else if (_tcsicmp(lpstrOpMode, STOP) == 0)
		{
			return Stop();
		}
		else
		{
			return FALSE;
		}
	}

	BOOL CAction::Suspend()
	{
		return TRUE;
	}

	BOOL CAction::Resume()
	{
		return TRUE;
	}

	BOOL CAction::Stop()
	{
		return TRUE;
	}
}