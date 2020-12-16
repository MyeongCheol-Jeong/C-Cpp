#include "pch.h"
#include "ViewControl.h"

#include "IOBoardTest1Doc.h"
#include "IOBoardTest1View.h"
#include "IOComm.h"

CViewControl::CViewControl() {

	pThread = AfxBeginThread(ViewControlThread, this);

	pDoc = NULL;
	pView = NULL;
	
	bEMS = false;

	nThrdCnt = 0;
}
CViewControl::~CViewControl() {
	ClosePort();
}

void CViewControl::Music_Update() {
	for (int i = 0; i < 8; i++) {
		if (pView->m_nMusicNo != i) pView->m_pDoc->m_Io.m_bOutput[i + 24] = false;
		else _Io.m_bOutput[i + 24] = true;
	}
}
void CViewControl::Lamp1_Update() {
	switch (pView->m_nOnLamp1Type) {
		case 0:
			pView->m_pDoc->m_Io.m_bOutput[21] = true;
			pView->m_pDoc->m_Io.m_bOutput[22] = false;
			pView->m_pDoc->m_Io.m_bOutput[23] = false;
			break;
		case 1:
			pView->m_pDoc->m_Io.m_bOutput[21] = false;
			pView->m_pDoc->m_Io.m_bOutput[22] = true;
			pView->m_pDoc->m_Io.m_bOutput[23] = false;
			break;
		case 2:
			pView->m_pDoc->m_Io.m_bOutput[21] = false;
			pView->m_pDoc->m_Io.m_bOutput[22] = false;
			pView->m_pDoc->m_Io.m_bOutput[23] = true;
			break;
		case 3:
			pView->m_pDoc->m_Io.m_bOutput[21] = true;
			pView->m_pDoc->m_Io.m_bOutput[22] = true;
			pView->m_pDoc->m_Io.m_bOutput[23] = false;
			break;
		case 4:
			pView->m_pDoc->m_Io.m_bOutput[21] = true;
			pView->m_pDoc->m_Io.m_bOutput[22] = false;
			pView->m_pDoc->m_Io.m_bOutput[23] = true;
			break;
		case 5:
			pView->m_pDoc->m_Io.m_bOutput[21] = false;
			pView->m_pDoc->m_Io.m_bOutput[22] = true;
			pView->m_pDoc->m_Io.m_bOutput[23] = true;
			break;
		case 6:
			pView->m_pDoc->m_Io.m_bOutput[21] = true;
			pView->m_pDoc->m_Io.m_bOutput[22] = true;
			pView->m_pDoc->m_Io.m_bOutput[23] = true;
			break;
		case 7:
			Lamp1_Stream();
			break;
		case 8:
			pView->m_pDoc->m_Io.m_bOutput[21] = false;
			pView->m_pDoc->m_Io.m_bOutput[22] = false;
			pView->m_pDoc->m_Io.m_bOutput[23] = false;
			break;
		default:
			break;

	}
	pView->HD_Lamp_Update();
}
void CViewControl::Lamp2_Update() {
	switch (pView->m_nOnLamp2Type) {
	case 0: // R
		pView->m_pDoc->m_Io.m_bOutput[0] = true;
		pView->m_pDoc->m_Io.m_bOutput[1] = false;
		pView->m_pDoc->m_Io.m_bOutput[2] = false;
		break;
	case 1: // Y
		pView->m_pDoc->m_Io.m_bOutput[0] = false;
		pView->m_pDoc->m_Io.m_bOutput[1] = true;
		pView->m_pDoc->m_Io.m_bOutput[2] = false;
		break;
	case 2: // G
		pView->m_pDoc->m_Io.m_bOutput[0] = false;
		pView->m_pDoc->m_Io.m_bOutput[1] = false;
		pView->m_pDoc->m_Io.m_bOutput[2] = true;
		break;
	case 3: // RY
		pView->m_pDoc->m_Io.m_bOutput[0] = true;
		pView->m_pDoc->m_Io.m_bOutput[1] = true;
		pView->m_pDoc->m_Io.m_bOutput[2] = false;
		break;
	case 4: // RG
		pView->m_pDoc->m_Io.m_bOutput[0] = true;
		pView->m_pDoc->m_Io.m_bOutput[1] = false;
		pView->m_pDoc->m_Io.m_bOutput[2] = true;
		break;
	case 5: // YG
		pView->m_pDoc->m_Io.m_bOutput[0] = false;
		pView->m_pDoc->m_Io.m_bOutput[1] = true;
		pView->m_pDoc->m_Io.m_bOutput[2] = true;
		break;
	case 6: // RYG
		pView->m_pDoc->m_Io.m_bOutput[0] = true;
		pView->m_pDoc->m_Io.m_bOutput[1] = true;
		pView->m_pDoc->m_Io.m_bOutput[2] = true;
		break;
	case 7: // R Y G
		Lamp2_Stream();
		break;
	case 8: // 
		pView->m_pDoc->m_Io.m_bOutput[0] = false;
		pView->m_pDoc->m_Io.m_bOutput[1] = false;
		pView->m_pDoc->m_Io.m_bOutput[2] = false;
		break;
	default:
		break;

	}
	pView->HD_Lamp_Update();
}
void CViewControl::Effect_Update() {
	switch (pView->m_nEffectType)
	{
	case 0:
		Effect_Stream();
		break;
	case 1:
		Effect_Rotation();
		break;
	case 2:
		Effect_Same();
		break;
	case 3:
		Effect_Random();
		break;
	case 4:
		Effect_Pause();
	default:
		break;
	}
}


void CViewControl::Lamp1_Stream() {
	for (int i = 0; i < 3; i++) {
		if (pView->m_nEffectType != 0)
			if (pView->m_nOnLamp1Type != 7) return;
		if (pView->m_bisEffectPause) return;
		pView->m_pDoc->m_Io.m_bOutput[i + 21] = true;
		Effect_Speed();
		pView->HD_Lamp_Update();
		if(pView->m_nEffectType != 0)
			if (pView->m_nOnLamp1Type != 7) return;
		if (pView->m_bisEffectPause) return;
		pView->m_pDoc->m_Io.m_bOutput[i + 21] = false;
		Effect_Speed();
		pView->HD_Lamp_Update();
	}
}
void CViewControl::Lamp2_Stream() {
	for (int i = 0; i < 3; i++) {
		if (pView->m_nEffectType != 0)
			if (pView->m_nOnLamp2Type != 7) return;
		if (pView->m_bisEffectPause) return;
		pView->m_pDoc->m_Io.m_bOutput[i] = true;
		Effect_Speed();
		pView->HD_Lamp_Update();
		if (pView->m_nEffectType != 0)
			if (pView->m_nOnLamp2Type != 7) return;
		if (pView->m_bisEffectPause) return;
		pView->m_pDoc->m_Io.m_bOutput[i] = false;
		Effect_Speed();
		pView->HD_Lamp_Update();
	}
}

void CViewControl::Effect_Stream() {
	Lamp1_Stream();
	Lamp2_Stream();
}
void CViewControl::Effect_Rotation() {
	if (pView->m_nEffectType != 1) return;
	pView->m_pDoc->m_Io.m_bOutput[21] = true;
	pView->m_pDoc->m_Io.m_bOutput[2] = false;
	Effect_Speed();
	pView->HD_Lamp_Update();
	if (pView->m_nEffectType != 1) return;
	pView->m_pDoc->m_Io.m_bOutput[0] = true;
	pView->m_pDoc->m_Io.m_bOutput[21] = false;
	Effect_Speed();
	pView->HD_Lamp_Update();

	if (pView->m_nEffectType != 1) return;
	pView->m_pDoc->m_Io.m_bOutput[22] = true;
	pView->m_pDoc->m_Io.m_bOutput[0] = false;
	Effect_Speed();
	pView->HD_Lamp_Update();
	if (pView->m_nEffectType != 1) return;
	pView->m_pDoc->m_Io.m_bOutput[1] = true;
	pView->m_pDoc->m_Io.m_bOutput[22] = false;
	Effect_Speed();
	pView->HD_Lamp_Update();

	if (pView->m_nEffectType != 1) return;
	pView->m_pDoc->m_Io.m_bOutput[23] = true;
	pView->m_pDoc->m_Io.m_bOutput[1] = false;
	Effect_Speed();
	pView->HD_Lamp_Update();
	if (pView->m_nEffectType != 1) return;
	pView->m_pDoc->m_Io.m_bOutput[2] = true;
	pView->m_pDoc->m_Io.m_bOutput[23] = false;
	Effect_Speed();
	pView->HD_Lamp_Update();
}
void CViewControl::Effect_Same() {
	for (int i = 0; i < 3; i++) {
		if (pView->m_nEffectType != 2) return;
		pView->m_pDoc->m_Io.m_bOutput[i + 21] = true;
		pView->m_pDoc->m_Io.m_bOutput[i] = true;
		Effect_Speed();
		pView->HD_Lamp_Update();

		if (pView->m_nEffectType != 2) return;
		pView->m_pDoc->m_Io.m_bOutput[i + 21] = false;
		pView->m_pDoc->m_Io.m_bOutput[i] = false;
		Effect_Speed();
		pView->HD_Lamp_Update();
	}
}
void CViewControl::Effect_Random() {
	int nRandNo = rand() % 10;
	if (nRandNo == 1 || nRandNo == 2 || nRandNo == 3) pView->m_nEffectType = 0;
	if (nRandNo == 4 || nRandNo == 5 || nRandNo == 6) pView->m_nEffectType = 1;
	if (nRandNo == 7 || nRandNo == 8 || nRandNo == 9) pView->m_nEffectType = 2;
	Effect_Update();
}
void CViewControl::Effect_Pause() {
	pView->m_pDoc->m_Io.m_bOutput[21] = false;
	pView->m_pDoc->m_Io.m_bOutput[22] = false;
	pView->m_pDoc->m_Io.m_bOutput[23] = false;
	pView->m_pDoc->m_Io.m_bOutput[0] = false;
	pView->m_pDoc->m_Io.m_bOutput[1] = false;
	pView->m_pDoc->m_Io.m_bOutput[2] = false;
	pView->m_bisEffectPause = false;
	pView->HD_Lamp_Update();
}
void CViewControl::Effect_Speed() {
	switch (pView->m_nEffectSpeedType)
	{
	case 0: // fast
		Sleep(500);
		break;
	case 1: // normal
		Sleep(1000);
		break;
	case 2: // slow
		Sleep(2000);
		break;
	default:
		break;
	}
}

void CViewControl::EMS_Btn_Update() {
	bEMS = false;
	for (int i = 0; i < 32; i++) {
		pView->m_pDoc->m_Io.m_bInput[i] = false;
		pView->m_pDoc->m_Io.m_bOutput[i] = false;
	}
	pView->m_nMusicNo = -1;
	pView->m_nOnLamp1Type = -1;
	pView->m_nOnLamp2Type = -1;
	pView->m_nEffectType = -1;
	pView->HD_Lamp_Update();
	pView->HD_EMS_Update();
}

void CViewControl::TIM320_Update() {
	pView->HD_TIM320_Update();
	switch (pView->nTIM320Type) {
	case 0:	// ÃÊ·Ï ÄÑÁ®ÀÖÀ½
		pView->m_nOnLamp1Type = 2;
		pView->m_nOnLamp2Type = 2;
		pView->HD_Lamp_Update();

		break;
	case 1:	// ³ë¶û ±ôºýÀÓ
		pView->m_nOnLamp1Type = 1;
		pView->m_nOnLamp2Type = 1;
		Effect_Speed();
		pView->HD_Lamp_Update();
		
		pView->m_nOnLamp1Type = 8;
		pView->m_nOnLamp2Type = 8;
		Effect_Speed();
		pView->HD_Lamp_Update();
		 
		break;
	case 2:	// »¡°­ ±ôºýÀÓ
		pView->m_nOnLamp1Type = 0;
		pView->m_nOnLamp2Type = 0;
		Effect_Speed();
		pView->HD_Lamp_Update();

		pView->m_nOnLamp1Type = 8;
		pView->m_nOnLamp2Type = 8;
		Effect_Speed();
		pView->HD_Lamp_Update();
		break;

	case 3:	// »¡°­ ÄÑÁ®ÀÖÀ½
		pView->m_nOnLamp1Type = 0;
		pView->m_nOnLamp2Type = 0;
		break;
	}
	Lamp1_Update();
	Lamp2_Update();
}

UINT ViewControlThread(LPVOID pParam)
{
	CViewControl* pThis = (CViewControl*)pParam;
	int nSleepTime = 10;
	BOOL bModeChange = 0;
	pThis->bEMS = false;
	pThis->nThrdCnt = 0;
	while (1)
	{		
		if (pThis->pView == NULL) continue;
		if (pThis->nThrdCnt != 0) {
			if (!pThis->pView->m_pDoc->m_Io.m_bInput[8]) {
				int asdasdasdasd = 0;
				pThis->EMS_Btn_Update();
			}
			if (pThis->pView->m_bisTIM320) { 
				//for (int i = 0; i < 32; i++) pThis->pView->m_pDoc->m_Io.m_bOutput[i] = false;
				pThis->TIM320_Update();
			}
				
		
			if (pThis->nThrdCnt != 0) int n = 0;

			pThis->pView->HD_EMS_Update();

			pThis->Music_Update();
			pThis->Lamp1_Update();
			pThis->Lamp2_Update();
			pThis->Effect_Update();

		}
		
		Sleep(80);

		//pThis->pView->m_pDoc->m_Io.ReadData(23);
		pThis->nThrdCnt++;
	}

	AfxEndThread(0);
	return TRUE;
}


