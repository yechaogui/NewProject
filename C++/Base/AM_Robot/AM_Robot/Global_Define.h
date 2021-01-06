#pragma once

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