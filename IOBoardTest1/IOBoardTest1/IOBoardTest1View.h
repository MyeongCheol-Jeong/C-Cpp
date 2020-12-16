
// IOBoardTest1View.h: CIOBoardTest1View 클래스의 인터페이스
//

#pragma once

#include "IOComm.h"
#include "CommThread.h"

#define MUSIC_CNT 8				// 노래 개수
#define MUSIC_NAME_LEN 40		// 노래 이름 길이
#define LAMP_CNT 2				// 램프 개수
#define LAMP1_TYPE 9	// 램프 1 색 종류
#define LAMP1_TYPE_NAME 30
#define LAMP2_TYPE 9	// " 2 "
#define LAMP2_TYPE_NAME 30
#define LAMP1_COLOR_CNT 3		// 램프 1 색 개수
#define LAMP2_COLOR_CNT 3		// " 2 "
#define EFFECT_TYPE 5
#define EFFECT_NAME 20
#define SPEED_TYPE 3
#define SPEED_TYPE_NAME 20

class CIOBoardTest1Doc;
class CIOBoardTest1View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CIOBoardTest1View() noexcept;
	DECLARE_DYNCREATE(CIOBoardTest1View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_IOBOARDTEST1_FORM };
#endif

// 특성입니다.
public:
	CIOBoardTest1Doc* GetDocument() const;

// 작업입니다.
public:
	CIOBoardTest1Doc* m_pDoc;

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CIOBoardTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:

	void HD_Music_Update();
	void HD_Lamp_Update();
	void HD_EMS_Update();
	void HD_TIM320_Update();

	void SW_StatusUpdate(); // EDIT_SW_STATUS 업데이트
	void Music_Status();
	void Lamp1_Status();
	void Lamp2_Status();
	void Effect_Status();
	void Effect_Speed_Status();

	void DoUseBtn();
	void DoNotUseBtn();

	
public:
	
	char m_sMusicName[MUSIC_CNT][MUSIC_NAME_LEN];	// 노래 이름
	char m_sLamp1Color[LAMP1_TYPE][LAMP1_TYPE_NAME];
	char m_sLamp2Color[LAMP2_TYPE][LAMP2_TYPE_NAME];
	char m_sEffect[EFFECT_TYPE][EFFECT_NAME];
	char m_sEffectSpeed[SPEED_TYPE][SPEED_TYPE_NAME];

									  
	bool m_bisMusicBtn;		// 노래 버튼이 눌렸나? Y/N
	bool m_bisLamp1Btn;		// 램프1 을 사용하는 버튼이 눌렸나? Y/N
	bool m_bisLamp2Btn;		// 램프2 을 사용하는 버튼이 눌렸나? Y/N

	bool m_bisEffectBtn;		// 효과 버튼이 눌렸나? Y/N
	bool m_bisEffectSpeedBtn;	// 효과 속도 버튼이 눌렸나? Y/N

	bool m_bisEffectPause;

	bool m_bisTIM320;		// TIM센서로 변환 확인 변수

	int m_nMusicNo;			// 노래 번호

	int m_nOnLamp1Type;
	int m_nOnLamp2Type;
	
	int m_nEffectType;
	int m_nEffectSpeedType;

	int nTIM320Type;


	CString csMusic;				
	CString csLamp;
	CString csEffect;
	CString csEffectSpeed;
	CString csStatus;
	CString csTIM320;

public:
	
	afx_msg void OnBnClickedMusic1();
	afx_msg void OnBnClickedMusic2();
	afx_msg void OnBnClickedMusic3();
	afx_msg void OnBnClickedMusic4();
	afx_msg void OnBnClickedMusic5();
	afx_msg void OnBnClickedMusic6();
	afx_msg void OnBnClickedMusic7();
	afx_msg void OnBnClickedMusic8();
	afx_msg void OnBnClickedMusicPause();
	afx_msg void OnBnClickedLamp1R();
	afx_msg void OnBnClickedLamp1Y();
	afx_msg void OnBnClickedLamp1G();
	afx_msg void OnBnClickedLamp1Ry();
	afx_msg void OnBnClickedLamp1Rg();
	afx_msg void OnBnClickedLamp1Yg();
	afx_msg void OnBnClickedLamp1Ryg();
	afx_msg void OnBnClickedLamp1Effect();
	afx_msg void OnBnClickedLamp1Pause();
	afx_msg void OnBnClickedLamp2R();
	afx_msg void OnBnClickedLamp2Y();
	afx_msg void OnBnClickedLamp2G();
	afx_msg void OnBnClickedLamp2Ry();
	afx_msg void OnBnClickedLamp2Rg();
	afx_msg void OnBnClickedLamp2Yg();
	afx_msg void OnBnClickedLamp2Ryg();
	afx_msg void OnBnClickedLamp2Effect();
	afx_msg void OnBnClickedLamp2Pause();
	afx_msg void OnBnClickedEditClear();
	afx_msg void OnBnClickedRandom();
	afx_msg void OnBnClickedAllReset();
	afx_msg void OnBnClickedStream();
	afx_msg void OnBnClickedRotation();
	afx_msg void OnBnClickedSame();
	afx_msg void OnBnClickedEffectRandom();
	afx_msg void OnBnClickedEffectPause();
	afx_msg void OnBnClickedFast();
	afx_msg void OnBnClickedNormal();
	afx_msg void OnBnClickedSlow();
	afx_msg void OnBnClickedSensor();

	CMFCButton m_HD_LP1_Red;
	CMFCButton m_HD_LP1_Yellow;
	CMFCButton m_HD_LP1_Green;
	CMFCButton m_HD_LP2_Red;
	CMFCButton m_HD_LP2_Yellow;
	CMFCButton m_HD_LP2_Green;
	CMFCButton m_HD_EMS;
	CMFCButton m_Ch_Sensor;
	CMFCButton m_Ef_Stream;
	CMFCButton m_Ef_Rotation;
	CMFCButton m_Ef_Same;
	CMFCButton m_Ef_Random;
	CMFCButton m_Ef_Pause;
	CMFCButton m_Fast;
	CMFCButton m_Normal;
	CMFCButton m_Slow;
	CMFCButton m_Clear;
	CMFCButton m_ARandom;
	CMFCButton m_AReset;
	CMFCButton m_M1;
	CMFCButton m_M2;
	CMFCButton m_M3;
	CMFCButton m_M4;
	CMFCButton m_M5;
	CMFCButton m_M6;
	CMFCButton m_M7;
	CMFCButton m_M8;
	CMFCButton m_MPause;
	CMFCButton m_L1_R;
	CMFCButton m_L1_Y;
	CMFCButton m_L1_G;
	CMFCButton m_L1_RY;
	CMFCButton m_L1_RG;
	CMFCButton m_L1_YG;
	CMFCButton m_L1_RYG;
	CMFCButton m_L1_Stream;
	CMFCButton m_L1_Pause;
	CMFCButton m_L2_R;
	CMFCButton m_L2_Y;
	CMFCButton m_L2_G;
	CMFCButton m_L2_RY;
	CMFCButton m_L2_RG;
	CMFCButton m_L2_YG;
	CMFCButton m_L2_RYG;
	CMFCButton m_L2_Stream;
	CMFCButton m_L2_Pause;

};

#ifndef _DEBUG  // IOBoardTest1View.cpp의 디버그 버전
inline CIOBoardTest1Doc* CIOBoardTest1View::GetDocument() const
   { return reinterpret_cast<CIOBoardTest1Doc*>(m_pDocument); }
#endif

