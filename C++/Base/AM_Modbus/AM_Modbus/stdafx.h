// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>
#include <process.h>
#include <WinBase.h>
#include <mmsystem.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "..\..\AM_Client\AM_Client\AM_IClient.h"
#include "..\..\AM_SerialPort\AM_SerialPort\AM_ISerialPort.h"

#include "Global_Define.h"

#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#pragma comment(lib, "../../../Bin/Debug/AM_Client.lib")
#pragma comment(lib, "../../../Bin/Debug/AM_SerialPort.lib")
#else
#pragma comment(lib, "../../../Bin/Release/AM_Client.lib")
#pragma comment(lib, "../../../Bin/Release/AM_SerialPort.lib")
#endif