#pragma once
#include "CommThread.h"
#include "IOComm.h"

class CIOBoardTest1Doc;
class CIOBoardTest1View;
class CIOComm;
class CViewControl :
    public CCommThread 
{
public:
    CIOBoardTest1Doc* pDoc;
    CIOBoardTest1View* pView;
    CWinThread* pThread;
    
    CIOComm _Io;

public:
    CViewControl();
    virtual ~CViewControl();
    
public:
    


    void Music_Update();
    void Lamp1_Update();
    void Lamp2_Update();
    void Effect_Update();

    void Lamp1_Stream();
    void Lamp2_Stream();

    void Effect_Stream();
    void Effect_Rotation();
    void Effect_Same();
    void Effect_Random();
    void Effect_Pause();
    void Effect_Speed();
    
    void EMS_Btn_Update();
    void TIM320_Update();
public:
    bool bEMS;
    int nThrdCnt;
    // EMS버튼 눌리면 모두 끄기
};

UINT ViewControlThread(LPVOID pParam);

