#pragma once

#ifdef AM_USERFLOW_EXPORTS
#define AM_USERFLOW_API __declspec(dllexport)
#else
#define AM_USERFLOW_API __declspec(dllimport)
#endif

class CIUserAction
{
public:
	CIUserAction() {};
	virtual ~CIUserAction() {};
	virtual BOOL Action(LPCTSTR lpstrType, LPCTSTR lpstrValue);
};

class CIUserFlow
{
public:
	CIUserFlow() {};
	virtual ~CIUserFlow() {};

	virtual void SetFlowDir(LPCTSTR lpstrFlowDir) = 0;
	virtual void SetFlowFile(LPCTSTR lpstrName) = 0;
	virtual BOOL LoadFlow() = 0;
	virtual BOOL Reset() = 0;
	virtual BOOL Start() = 0;
	virtual BOOL Suspend() = 0;
	virtual BOOL Resume() = 0;
	virtual BOOL IsSuspend() = 0;
	virtual BOOL IsRunning() = 0;
	virtual void Stop() = 0;
	virtual void SetAction(CIUserAction *pIAction) = 0;
};

extern "C"
{
	AM_USERFLOW_API void CreateUserFlow(CIUserFlow **ppIUserFlow);
	AM_USERFLOW_API void ReleaseUserFlow(CIUserFlow *pIUserFlow);
};