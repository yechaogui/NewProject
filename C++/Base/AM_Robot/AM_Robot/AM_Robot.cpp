// AM_Robot.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "AM_EpsonRobot.h"

void CreateRobot(CIRobot **ppIRobot, const int iType)
{
	if (*ppIRobot)
	{
		delete *ppIRobot;
	}

	switch (iType)
	{
	case 0:
		{
			*ppIRobot = new ROBOT::CEpsonRobot();
		}
		break;

	default:
		{
			*ppIRobot = new ROBOT::CEpsonRobot();
		}
		break;
	}
}

void ReleaseRobot(CIRobot *pIRobot)
{
	if (pIRobot)
	{
		pIRobot->CloseConnect();
		delete pIRobot;
	}
}
