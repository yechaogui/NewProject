// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include <windows.h>
#include <string>
#include <WinBase.h>
#include <algorithm>
#include <tchar.h>
#include <atlconv.h>
#include <process.h>
#include <atltime.h>
#include <vector>
#include <winbase.h>

#ifdef UNICODE
#define tstring std::wstring
#else 
#define tstring std::string
#endif
#include "Global_Define.h"
#include "AM_IClient.h"

#ifdef _DEBUG
#pragma comment(lib, "../../../Bin/Debug/AM_Client.lib")
#else
#pragma comment(lib, "../../../Bin/Release/AM_Client.lib")
#endif

#pragma warning(disable:4996)