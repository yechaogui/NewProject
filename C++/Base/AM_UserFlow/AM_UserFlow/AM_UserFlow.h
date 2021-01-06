#pragma once
#include "AM_IUserFlow.h"

class CUserFlow : public CIUserFlow, public CIWork
{
public:
	CUserFlow();
	~CUserFlow();

	void SetFlowDir(LPCTSTR lpstrFlowDir);
	void SetFlowFile(LPCTSTR lpstrName);
	BOOL LoadFlow();
	BOOL Reset();
	BOOL Start();
	BOOL Suspend();
	BOOL Resume();
	BOOL IsSuspend();
	void Stop();
	void Work(int iMainStep, int iSubStep);
	BOOL IsRunning();
	void SetAction(CIUserAction *pIAction);
private:
	tstring m_strFlowDir;
	tstring m_strFileName;
	tstring m_strFlowFile;

	BOOL m_bRunning;
	BOOL m_bSuspend;
	BOOL m_bReset;
	CIUserAction *m_pIAction;

	map<int, map<int, UserFlow>> m_mapUserFlow;
	map<tstring, int> m_mapMainStep;
	map<int, BOOL> m_mapNoSuspend;
	map<tstring, DWORD> m_mapSTTime;

	BOOL LoadSubFlow(const int iMainStep, tstring strMainStepName, tstring strSubFlowFile);
};