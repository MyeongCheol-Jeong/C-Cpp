// IOComm.cpp: implementation of the CIOComm class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "framework.h"
#include "IOComm.h"
#include "lib.h"
//#include "ValueTransfer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIOComm::CIOComm()
{
	m_pView = NULL;
	m_pDoc = NULL;

	m_bExit = false;
	m_TimeLastReceiveData = CTime::GetCurrentTime();
	memset(m_ucRcv,0,sizeof(m_ucRcv));
	memset(m_ucOutData,0,sizeof(m_ucOutData));
	memset(m_ucRcvOutData,0,sizeof(m_ucRcvOutData));	
	

	for(int i=0; i<32; i++)
	{
		m_bInput[i] = FALSE;		
		m_bOutput[i] = FALSE;
	}
	
	m_bInput[8] = true;
	m_bInput[24] = false;
	m_bInput[25] = false;
	m_bInput[26] = false;

	m_hEventThread = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEventKilled = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_pThread = AfxBeginThread(IOBoardControlThread, this);

	m_tTimeOn=m_tTimeOff =CTime::GetCurrentTime();

	

	PortOpen();	
}

CIOComm::~CIOComm()
{
	m_bExit=1;
	DWORD dwExitCode;
	CString strLog=_T("");

	while ( m_pThread != NULL &&
			GetExitCodeThread(m_pThread->m_hThread, &dwExitCode) &&
			dwExitCode == STILL_ACTIVE )
	{	
		//SetEvent(m_hEventThread);
		//WaitForSingleObject(m_hEventKilled, INFINITE);
		Sleep(100);
	}
	TRACE("IO 보드  쓰레드 Terminated success !\n");

	ClosePort();	

}


BOOL CIOComm::PortOpen()
{	
	
	if(OpenPort(m_Config.m_strPortName, m_Config.m_dwBaud, m_Config.m_nChar, m_Config.m_nStop, m_Config.m_nParity) == FALSE)
	{			
		m_bConnected = FALSE;
		return FALSE;
	}
	else
		m_bConnected = TRUE;
	
	return TRUE;
}



void CIOComm::OnReceiveData()
{

}


int CIOComm::ReadData(int nToRead)
{
	int iiii = 0;
	int dwRead=0,nStCnt=0;
	int nRetryCnt=10;
	int nRetCnt=0,nTotal=0;
	UCHAR bRcv=0;
	BYTE buf=0;

	int nsize=0;

	nRetryCnt=10;

	while(nRetryCnt-- > 0 )
	{
		if(m_bConnected ==0) return 0;
		Sleep(5);
	 
		nsize = m_QueueRead.GetSize();
		
		 if(nsize < 1) 
		 {
			Sleep(10);
			continue;
		 }

		 for(int i =0; i<  nsize;i++)
		 {		
			m_QueueRead.GetByte(&buf);

			if( buf != 0 && (buf == '$' || m_ucRcv[0]=='$') )
			{
				m_ucRcv[nTotal]= buf;
				nTotal++;
				if(	nTotal > 5 && m_ucRcv[nTotal-5]=='#' && m_ucRcv[nTotal-2]==0x0d && m_ucRcv[nTotal-1]==0x0a)
					 break;
			}
			else	
				nTotal=0;
		 }

		if(nTotal < 5) continue;
		if( m_ucRcv[nTotal-5] !='#' || m_ucRcv[nTotal-2] !=0x0d || m_ucRcv[nTotal-1] !=0x0a)	continue;

		if(nTotal != nToRead)
		{
			
			TRACE("COMM IS NOT SYNC.nToReadCnt=%d,rcv=%s \n",	nToRead,m_ucRcv);
	
			Sleep(20);
			memset(m_ucRcv,0,sizeof(m_ucRcv));
			nTotal=0;
			continue;
		}
		else
		{

				BYTE CheckSum = 0;
				BYTE rxCheckSum = 0;
				BYTE tmp[2]; 
				tmp[0] = m_ucRcv[nTotal-4];
				tmp[1] = m_ucRcv[nTotal-3];
				CLib::HexStr1Word(tmp, &rxCheckSum);
				for(int i=0; i <= nTotal-5; i++)
				{
					CheckSum ^= m_ucRcv[i];
				}

				if(rxCheckSum == CheckSum)
				{
					m_ucRcv[nTotal]=0;
					IoEventUnPack(m_ucRcv, nTotal);
				
					//TRACE("IO Board rcv=%s\n",m_ucRcv);
				}
				else
				{
					TRACE("ERROR rxCheckSum = %d, CheckSum = %d\n", rxCheckSum, CheckSum);
				}


			//Dataparsing1(nTotal);
			nTotal=0;
		}

		 if((nsize=m_QueueRead.GetSize())>0) 
		 {
			TRACE("Comm . Problem.. ncnt=%d,rcv=%s \n",nsize,m_ucRcv);
			memset(m_ucRcv,0,sizeof(m_ucRcv));
			continue;
		 }		
		 return 1;

	}//while
	return 0;

}

int CIOComm::IoEventUnPack(BYTE *buf, int nSize)
{
	CString strMsg=_T("");
	BYTE bByte=0;
	int iiii = 0;
	if(buf[0]=='$' && buf[6]=='D' && buf[7]=='I' && buf[8]=='N' && buf[9]=='=')
	{		
		CLib::HexStr1Word(buf+10, &bByte); //10
		for(int i=0; i<8; i++)
			m_bInput[i] = (bByte >> i) & 0x01;	
		
		CLib::HexStr1Word(buf+12, &bByte); //12
		for (int i = 0; i < 8; i++)
			m_bInput[i+8] = (bByte >> i) & 0x01;

		CLib::HexStr1Word(buf + 14, &bByte); //14
		for (int i = 0; i < 8; i++)
			m_bInput[i + 16] = (bByte >> i) & 0x01;

		CLib::HexStr1Word(buf + 16, &bByte); //14
		for (int i = 0; i < 8; i++)
			m_bInput[i + 24] = (bByte >> i) & 0x01;


		TRACE(_T("%d \n"), m_bInput[31]);
		int iiiiii = 0;
	}

	//OUTPUT SIGNAL CHECK
	else if(buf[0]=='$' && buf[6]=='O' && buf[7]=='U' && buf[8]=='T' && buf[9]=='=')
	{
		memcpy(m_ucRcvOutData,buf+10,8);
	}

	else if(buf[0]=='$' && buf[6]=='O' && buf[7]=='K')
	{
		TRACE("Write sucess! %s", buf);
	}
	else
	{
		TRACE("IoComm NoProtocal.. Error ..%s \n",buf);
		return 0;
	}
	return 1;
}

BOOL CIOComm::ReqSend(int nCmd,int nNo)
{
	BYTE buf[512];
	memset(buf,0,sizeof(buf));

	if(nCmd == DIN) //
	{
		memcpy(buf,"$ID01:DIN#",10);

		BYTE CheckSum = 0;
		for(int i=0; i<10; i++)
			CheckSum ^= buf[i];
		CConversion::HtoA(CheckSum, buf+10);
		buf[12] = 0x0d; //cr
		buf[13] = 0x0a; //lf
		WriteComm(buf,14);
		TRACE("DIN-----%s \n", buf);
	}
	else if(nCmd == OUTR) //
	{
		memcpy(buf,"$ID01:OUTR#",11);

		BYTE CheckSum = 0;
		for(int i=0; i<11; i++)
			CheckSum ^= buf[i];
		CConversion::HtoA(CheckSum, buf+11);
		buf[13] = 0x0d; //cr
		buf[14] = 0x0a; //lf
		WriteComm(buf,15);
		
		TRACE("OUTR-----%s \n", buf);

	}

	return TRUE;
}



int CIOComm::DataWrite(int nCmd,unsigned char * szData)
{
	
	BYTE buf[512];
	memset(buf,0,sizeof(buf));


	if(nCmd == DOUT) //
	{
		memcpy(buf,"$ID01:CMP=",10);
		memcpy(buf+10,szData,8);
		
		buf[18] = '0';	
		buf[19] = '#';
		BYTE CheckSum = 0;
		for(int i=0; i<20; i++)
			CheckSum ^= buf[i];
		CConversion::HtoA(CheckSum, buf+20);
		buf[22] = 0x0d; //cr
		buf[23] = 0x0a; //lf
		WriteComm(buf,24);

		TRACE("SEND DATA -----  %s\n",buf);	
	}

	return 1;
}


UINT IOBoardControlThread(LPVOID pParam)
{
	CIOComm* pThis = (CIOComm*) pParam;
	//CIOComm* pCom;
	int nSleepTime=10;
	BOOL bModeChange=0;

	
	while(!pThis->m_bExit)
	{
		if (WaitForSingleObject(pThis->m_hEventThread, nSleepTime) == WAIT_OBJECT_0  )
		{
		}
		if(pThis->m_bExit) break;
		if(!pThis->m_bConnected) continue;	

		//상태 읽기 
		if(pThis->ReqSend(DIN) == 0) continue;
		if(pThis->ReadData(23) == 0) continue;	
		if(pThis->m_bConnected==FALSE ) continue;	

		pThis->SignalOutProc();
		
		Sleep(80);	
	}

	AfxEndThread(0);
	return TRUE;
}

BOOL CIOComm::SignalOutProc()
{

	BOOL bRet=0;
	unsigned char szOutHexaStr[9];
	memset(szOutHexaStr,0,sizeof(szOutHexaStr));
	memset(m_ucOutData,0,sizeof(m_ucOutData));	

	BYTE byteVal = (m_bOutput[24]);
	byteVal = byteVal | ((m_bOutput[25]) << 1);
	byteVal = byteVal | ((m_bOutput[26]) << 2);
	byteVal = byteVal | ((m_bOutput[27]) << 3);
	byteVal = byteVal | ((m_bOutput[28]) << 4);
	byteVal = byteVal | ((m_bOutput[29]) << 5);
	byteVal = byteVal | ((m_bOutput[30]) << 6);
	byteVal = byteVal | ((m_bOutput[31]) << 7);
	m_ucOutData[3] = byteVal;

	byteVal = (m_bOutput[16]);
	byteVal = byteVal | ((m_bOutput[17]) << 1);
	byteVal = byteVal | ((m_bOutput[18]) << 2);
	byteVal = byteVal | ((m_bOutput[19]) << 3);
	byteVal = byteVal | ((m_bOutput[20]) << 4);
	byteVal = byteVal | ((m_bOutput[21]) << 5);
	byteVal = byteVal | ((m_bOutput[22]) << 6);
	byteVal = byteVal | ((m_bOutput[23]) << 7);
	m_ucOutData[2] = byteVal;

	byteVal = (m_bOutput[8]);
	byteVal = byteVal | ((m_bOutput[9]) << 1);
	byteVal = byteVal | ((m_bOutput[10]) << 2);
	byteVal = byteVal | ((m_bOutput[11]) << 3);
	byteVal = byteVal | ((m_bOutput[12]) << 4);
	byteVal = byteVal | ((m_bOutput[13]) << 5);
	byteVal = byteVal | ((m_bOutput[14]) << 6);
	byteVal = byteVal | ((m_bOutput[15]) << 7);
	m_ucOutData[1] = byteVal;

	byteVal = (m_bOutput[0]);
	byteVal = byteVal | ((m_bOutput[1]) << 1);
	byteVal = byteVal | ((m_bOutput[2]) << 2);
	byteVal = byteVal | ((m_bOutput[3]) << 3);
	byteVal = byteVal | ((m_bOutput[4]) << 4);
	byteVal = byteVal | ((m_bOutput[5]) << 5);
	byteVal = byteVal | ((m_bOutput[6]) << 6);
	byteVal = byteVal | ((m_bOutput[7]) << 7);
	m_ucOutData[0] = byteVal;
			

	for(int i=0;i<4;i++)
	{
		CConversion::HtoA(m_ucOutData[i], szOutHexaStr + (i * 2));
	}


		
	//읽어들인 출력값과 지령할 출력값이 틀리면 전송함
	if(strncmp((char *)m_ucRcvOutData,(char *)szOutHexaStr,8) != 0)
	{
		DataWrite(DOUT,szOutHexaStr);
		Sleep(10);
		bRet = ReadData(13);

		if(bRet==0) return 0;			
		
		ReqSend(OUTR);
		ReadData(23);
		
	}

	return bRet;

}




