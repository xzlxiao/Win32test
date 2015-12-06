#pragma once

/*------------------------------------------------
SYSMETS.H -- System metrics display structure
------------------------------------------------*/
#include <tchar.h>
#include <Windows.h>
#define NUMLINES ((int) (sizeof sysmetrics / sizeof sysmetrics[0]))

struct
{
	int iIndex;
	TCHAR *szLabel;
	TCHAR *szDesc;
}
sysmetrics[] = 
{
	SM_CXSCREEN,			TEXT("SM_CXSCREEN"),
							TEXT("Screen width in pixels")
};
