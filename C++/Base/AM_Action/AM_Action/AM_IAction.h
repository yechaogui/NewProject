#pragma once

#ifdef AM_ACTION_EXPORTS
#define AM_ACTION_API __declspec(dllexport)
#else
#define AM_ACTION_API __declspec(dllimport)
#endif

class CIAction 
{
public:
	CIAction() {};
	virtual ~CIAction() {};
	virtual int GetIOState(LPCTSTR lpstrName, LPCTSTR lpstrType) = 0;
	virtual BOOL SetIOState(const BOOL bState, LPCTSTR lpstrName, LPCTSTR lpstrType) = 0;
};