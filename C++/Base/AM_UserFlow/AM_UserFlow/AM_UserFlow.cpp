// AM_UserFlow.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "AM_UserFlow.h"

CUserFlow::CUserFlow()
{
	m_pIAction = NULL;
}

CUserFlow::~CUserFlow()
{

}

void CUserFlow::SetFlowDir(LPCTSTR lpstrFlowDir)
{
	m_strFlowDir = lpstrFlowDir;
	if (lpstrFlowDir[m_strFlowDir.size() - 1] != '\\')
	{
		m_strFlowDir = m_strFlowDir + _T("\\");
	}
}

void CUserFlow::SetFlowFile(LPCTSTR lpstrName)
{
	m_strFileName = lpstrName;

	if (m_strFileName.find('.') != -1)
	{
		m_strFlowFile = m_strFlowDir +  m_strFileName;
	}
	else
	{
		m_strFlowFile = m_strFlowDir +  m_strFileName + _T(".fl");
	}
}

BOOL CUserFlow::LoadFlow()
{
	BOOL bRet = FALSE;

	if (m_strFlowFile.size() > 0)
	{
		m_mapUserFlow.clear();
		CIniFile cIniFile;
		
		cIniFile.SetIniFile(m_strFlowFile.c_str());
		tstring strFlowFile = _T("");
		for (int i = 0; i < cIniFile.GetKeyCount(_T("UserFlow")); ++i)
		{
			tstring strKeyName = _T("");
			strKeyName = cIniFile.GetKeyName(_T("UserFlow"), i);
			strFlowFile = m_strFlowDir + strKeyName + _T(".fl");
			if (cIniFile.ReadString(_T("UserFlow"), strKeyName.c_str(), _T("")).find(',') != -1)
			{
				m_mapMainStep[strKeyName] = _ttoi(cIniFile.ReadString(_T("UserFlow"), strKeyName.c_str(), _T("")).substr(0, cIniFile.ReadString(_T("UserFlow"), strKeyName.c_str(), _T("")).find(',')).c_str());
				m_mapNoSuspend[m_mapMainStep[strKeyName]] = TRUE;
			}
			else
			{
				m_mapMainStep[strKeyName] = cIniFile.ReadInt(_T("UserFlow"), strKeyName.c_str(), i);
				m_mapNoSuspend[m_mapMainStep[strKeyName]] = FALSE;
			}
			
			LoadSubFlow(m_mapMainStep[strKeyName], strKeyName, strFlowFile);
		}
	}

	return bRet;
}

BOOL CUserFlow::LoadSubFlow(const int iMainStep, tstring strMainStepName, tstring strSubFlowFile)
{
	BOOL bRet = TRUE;
	CIniFile cFlowIni;
	cFlowIni.SetIniFile(strSubFlowFile.c_str());

	for (int i = 0; i < cFlowIni.GetKeyCount(strMainStepName.c_str()); ++i)
	{
		tstring strKeyName = _T("");
		tstring strKeyValue = _T("");
		tstring strTemp = _T("");
		int iPos = 0;
		int iCount = 0;
		strKeyName = cFlowIni.GetKeyName(strMainStepName.c_str(), i);
		strKeyValue = cFlowIni.ReadString(strMainStepName.c_str(), strKeyName.c_str(), _T(""));
		iCount = std::count(strKeyValue.begin(), strKeyValue.end(), ',');

		

		if (iCount > 5)
		{
			UserFlow sUserFlow;		
			sUserFlow.iCurStep = _ttoi(strKeyName.c_str());
			sUserFlow.strType = strKeyValue.substr(iPos, strKeyValue.find(',', iPos) - iPos);
			iPos = strKeyValue.find(',', iPos) + 1;	
			sUserFlow.strMainTrueStep = strKeyValue.substr(iPos, strKeyValue.find(',', iPos) - iPos);
			iPos = strKeyValue.find(',', iPos) + 1;
			sUserFlow.strMainFalseStep = strKeyValue.substr(iPos, strKeyValue.find(',', iPos) - iPos);
			iPos = strKeyValue.find(',', iPos) + 1;
			sUserFlow.strEndFlag = strKeyValue.substr(iPos, strKeyValue.find(',', iPos) - iPos);
			iPos = strKeyValue.find(',', iPos) + 1;
			strTemp = strKeyValue.substr(iPos, strKeyValue.find(',', iPos) - iPos);
			sUserFlow.iTrueStep = _ttoi(strTemp.c_str());
			iPos = strKeyValue.find(',', iPos) + 1;
			strTemp = strKeyValue.substr(iPos, strKeyValue.find(',', iPos) - iPos);
			sUserFlow.iFalseStep = _ttoi(strTemp.c_str());
			iPos = strKeyValue.find(',', iPos) + 1;
			sUserFlow.strData = strKeyValue.substr(iPos);	
			m_mapUserFlow[iMainStep][sUserFlow.iCurStep] = sUserFlow;
		}
	}

	return bRet;
}

BOOL CUserFlow::Reset()
{
	m_bReset = TRUE;
	return TRUE;
}

BOOL CUserFlow::Start()
{
	if (!m_bRunning)
	{
		m_bSuspend = FALSE;
	}

	return m_bRunning;
}

BOOL CUserFlow::Suspend()
{
	if (m_bRunning)
	{
		if (!m_bSuspend)
		{
			m_bSuspend = TRUE;
		}
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

BOOL CUserFlow::Resume()
{
	if (m_bRunning)
	{
		if (m_bSuspend)
		{
			m_bSuspend = FALSE;
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

void CUserFlow::Stop()
{
	m_bRunning = FALSE;
	m_bReset = FALSE;
	m_bSuspend = FALSE;
}

void CUserFlow::Work(int iMainStep, int iSubStep)
{
	if ((m_mapUserFlow.find(iMainStep) != m_mapUserFlow.end() )
		&& (m_mapUserFlow[iMainStep].find(iSubStep) != m_mapUserFlow[iMainStep].end()))
	{
		UserFlow sUserFlow = m_mapUserFlow[iMainStep][iSubStep];
		if (m_bRunning)
		{
			if (m_bSuspend && !m_mapNoSuspend[iMainStep])
			{
				Sleep(100);
				AddFlow(this, iMainStep, iSubStep);
			}
			else
			{
				if (m_pIAction)
				{
					if (m_pIAction->Action(sUserFlow.strType.c_str(), sUserFlow.strData.c_str()))
					{
						if (m_mapMainStep.find(sUserFlow.strMainTrueStep) != m_mapMainStep.end())
						{
							AddFlow(this, m_mapMainStep[sUserFlow.strMainTrueStep], sUserFlow.iTrueStep);
						}
						else
						{
							AddFlow(this, iMainStep, sUserFlow.iTrueStep);
						}
					}
					else
					{
						if (m_mapMainStep.find(sUserFlow.strMainFalseStep) != m_mapMainStep.end())
						{
							AddFlow(this, m_mapMainStep[sUserFlow.strMainFalseStep], sUserFlow.iFalseStep);
						}
						else
						{
							AddFlow(this, iMainStep, sUserFlow.iFalseStep);
						}
					}
				}
				
			}
		}
		else if (m_mapNoSuspend[iMainStep])
		{
			if (m_pIAction)
			{
				if (m_pIAction->Action(sUserFlow.strType.c_str(), sUserFlow.strData.c_str()))
				{
					if (m_mapMainStep.find(sUserFlow.strMainTrueStep) != m_mapMainStep.end())
					{
						AddFlow(this, m_mapMainStep[sUserFlow.strMainTrueStep], sUserFlow.iTrueStep);
					}
					else
					{
						AddFlow(this, iMainStep, sUserFlow.iTrueStep);
					}
				}
				else
				{
					if (m_mapMainStep.find(sUserFlow.strMainFalseStep) != m_mapMainStep.end())
					{
						AddFlow(this, m_mapMainStep[sUserFlow.strMainFalseStep], sUserFlow.iFalseStep);
					}
					else
					{
						AddFlow(this, iMainStep, sUserFlow.iFalseStep);
					}
				}
			}
		}
	}
}

void CUserFlow::SetAction(CIUserAction *pIAction)
{
	m_pIAction = pIAction;
}

BOOL CUserFlow::IsSuspend()
{
	return (m_bRunning & m_bSuspend);
}

BOOL CUserFlow::IsRunning()
{
	return m_bRunning;
}



//////////////////////////////////////////////////////////////////////////
void CreateUserFlow(CIUserFlow **ppIUserFlow)
{
	if (*ppIUserFlow)
	{
		delete *ppIUserFlow;
	}

	*ppIUserFlow = new CUserFlow();
}

void ReleaseUserFlow(CIUserFlow *pIUserFlow)
{
	if (pIUserFlow)
	{
		delete pIUserFlow;
	}

	pIUserFlow = NULL;
}