// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>
#include <tchar.h>
#include <string>
#include <map>
#include <atlconv.h>
#include <vector>
#include <list>
#include <WinBase.h>
#include <algorithm>
#include <process.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

#define map std::map
#define vector std::vector
#define count std::count


#include "../../AM_PLCCtrl/AM_PLCCtrl/AM_IPLCCtrl.h"
#include "../../AM_Robot/AM_Robot/AM_IRobot.h"
#include "../../AM_UserFlow/AM_UserFlow/AM_IUserFlow.h"
#include "Global_Define.h"
#include "CIniFile.h"

#ifdef _DEBUG
#pragma comment(lib, "../../../Bin/Debug/AM_PLCCtrl.lib")
#pragma comment(lib, "../../../Bin/Debug/AM_Robot.lib")
#else
#pragma comment(lib, "../../../Bin/Release/AM_PLCCtrl.lib")
#pragma comment(lib, "../../../Bin/Release/AM_Robot.lib")
#endif

#pragma warning(disable: 4996)