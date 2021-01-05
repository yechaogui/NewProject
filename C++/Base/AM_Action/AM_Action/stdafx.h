// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
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


// TODO: 在此处引用程序需要的其他头文件

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