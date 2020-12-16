// Config.h: interface for the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIG_H__FF16D068_5E99_4221_8825_9929F5326E93__INCLUDED_)
#define AFX_CONFIG_H__FF16D068_5E99_4221_8825_9929F5326E93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfig  
{
public:	
	CConfig();
	virtual ~CConfig();

	CString m_strPortName;
	int		m_nPortID;
	DWORD   m_dwBaud;
	int		m_nParity;
	int		m_nStop;
	int		m_nChar;

	
};
#endif // !defined(AFX_CONFIG_H__FF16D068_5E99_4221_8825_9929F5326E93__INCLUDED_)
