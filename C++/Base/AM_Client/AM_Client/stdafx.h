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
#include <algorithm>
#include <process.h>
#include <WinSock2.h>
#include <vector>
#include <atlconv.h>
#include <MSTcpIP.h>
#include <ws2tcpip.h>
#include <assert.h>

#pragma comment(lib, "WS2_32.lib")
//mswsock.lib
#pragma comment(lib, "mswsock.lib")

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
