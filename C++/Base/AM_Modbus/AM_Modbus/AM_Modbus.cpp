// AM_Modbus.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include "ModbusRtu.h"
#include "ModBusTcp.h"

void AM_CreateModbus(CIModBus **ppIModbus, const int iType)
{
	if (*ppIModbus)
	{
		delete *ppIModbus;
		*ppIModbus = NULL;
	}

	switch (iType)
	{
	case 0:
		{
			*ppIModbus = new CModbusRtu();
		}
		break;

	case 1:
		{
			*ppIModbus = new CModBusTcp();
		}
		break;
		
	default:
		{
			*ppIModbus = new CModbusRtu();
		}
		break;
	}
}

void AM_ReleaseModbus(CIModBus *pIModbus)
{
	if (pIModbus)
	{
		delete pIModbus;
	}

	pIModbus = NULL;
}