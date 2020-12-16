// IOComm.h: interface for the CIOComm class.
//
//////////////////////////////////////////////////////////////////////
//#ifndef IOCOMM
//#define IOCOMM


#if !defined(AFX_IOCOMM_H__D14B282C_9071_429B_9F18_3927E506AD38__INCLUDED_)
#define AFX_IOCOMM_H__D14B282C_9071_429B_9F18_3927E506AD38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "commthread.h"
#include "Config.h"
//
//#include "IOBoardTest1Doc.h"
//#include "IOBoardTest1View.h"

#define DIN  1
#define DOUT 3
#define OUTR 4

class CIOBoardTest1Doc;
class CIOBoardTest1View;
class CDocument;
class CIOComm  : public CCommThread
{
public:
	CIOComm();
	virtual ~CIOComm();	

	CIOBoardTest1View* m_pView;
	CIOBoardTest1Doc* m_pDoc;

	CConfig m_Config;
	CTime	m_TimeLastReceiveData;

	unsigned char m_ucRcv[512];
	unsigned char m_ucSnd[512];


	HANDLE m_hEventKilled,m_hEventThread;
	CWinThread				*m_pThread;

	int  m_nPioStatus;  // 
	BOOL m_bExit;
	int  m_nRcvCount;
	int  m_nSndListCnt;  //
	int	 m_nCommSts;
	BOOL m_bConnected;

	//input
	BOOL m_bInput[32];	

	//output
	BOOL m_bOutput[32];
		
	unsigned char m_ucInData[5];
	unsigned char m_ucRcvInData[9];

	unsigned char m_ucOutData[5];
	unsigned char m_ucRcvOutData[9]; //ascii

	CTime m_tTimeOn;
	CTime m_tTimeOff;

	bool m_bPioRetry;

public:

	BOOL PortOpen();
	void OnReceiveData();

	int IoEventUnPack(BYTE * buf, int m_size);
	int  ReadData(int nToRead);
	BOOL ReqSend(int nCmd,int nNo=0);
	int  DataWrite(int nCmd,unsigned char * szData);
	BOOL SignalOutProc();	
		
};

UINT IOBoardControlThread(LPVOID pParam);
#endif // !defined(AFX_IOCOMM_H__D14B282C_9071_429B_9F18_3927E506AD38__INCLUDED_)



//#endif IOCOMM// !IOCOMM