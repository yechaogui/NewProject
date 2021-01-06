#pragma once
typedef struct USER_FLOW
{
	tstring strType;	  //¿‡–Õ
	tstring strMainTrueStep;
	tstring strMainFalseStep;
	tstring strEndFlag;
	tstring strData;
	int iTrueStep;
	int iFalseStep;
	int iCurStep;

	USER_FLOW ()
	{
		strType = _T("");
		strData = _T("");
		iTrueStep = -1;
		iFalseStep = -1;
		iCurStep = -1;
		strMainTrueStep = _T("");
		strMainFalseStep = _T("");
		strEndFlag = _T("FALSE");
	}
}UserFlow, *PUserFlow;

class CIniFile
{
public:
	CIniFile() {};
	virtual ~CIniFile() {};

	BOOL SetIniFile(LPCTSTR strIniPath);
	tstring GetModulePath();
	tstring GetFolderPath();
	tstring GetFileName();

	int GetSectionCount();
	int GetKeyCount(LPCTSTR strSection);
	tstring GetSectionName(int iIndex);
	tstring GetKeyName(LPCTSTR strSection, int iIndex);

	tstring ReadString(LPCTSTR strSection, LPCTSTR strKey, LPCTSTR strDefault);
	int ReadInt(LPCTSTR strSection, LPCTSTR strKey, int iDefault);
	double ReadDouble(LPCTSTR strSection, LPCTSTR strKey, double dDefault);
	BOOL WriteInt(LPCTSTR strSection, LPCTSTR strKey, int iValue);
	BOOL WriteDouble(LPCTSTR strSection, LPCTSTR strKey, double dValue);
	BOOL WriteString(LPCTSTR strSection, LPCTSTR strKey, LPCTSTR strValue);

private:
	tstring m_strIniFile;
};


class CLock
{
public:
	CLock()
	{
		::InitializeCriticalSection(&m_csLock);
	};

	~CLock()
	{
		::DeleteCriticalSection(&m_csLock);
	}

	inline void Lock()
	{
		::EnterCriticalSection(&m_csLock);
	};

	inline void Unlock()
	{
		::LeaveCriticalSection(&m_csLock);
	};

private:
	CRITICAL_SECTION m_csLock;
};