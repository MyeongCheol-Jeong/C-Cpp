// Config.cpp: implementation of the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
//#include "framework.h"
#include "Config.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CConfig::CConfig()
{
	m_nPortID = 3;
	m_dwBaud = 19200;
	m_strPortName = _T("COM3");	
	m_nParity = 0;
	m_nStop = 0;
	m_nChar = 8;
}

CConfig::~CConfig()
{

}













