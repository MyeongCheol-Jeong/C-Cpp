// IOBoardTest1View.cpp: CIOBoardTest1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IOBoardTest1.h"
#endif

#include "IOBoardTest1Doc.h"
#include "IOBoardTest1View.h"
#include "CommThread.h"
#include "cstdlib"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIOBoardTest1View

IMPLEMENT_DYNCREATE(CIOBoardTest1View, CFormView)

BEGIN_MESSAGE_MAP(CIOBoardTest1View, CFormView)
	
	ON_BN_CLICKED(BTN_Music_1, &CIOBoardTest1View::OnBnClickedMusic1)
	ON_BN_CLICKED(BTN_Music_2, &CIOBoardTest1View::OnBnClickedMusic2)
	ON_BN_CLICKED(BTN_Music_3, &CIOBoardTest1View::OnBnClickedMusic3)
	ON_BN_CLICKED(BTN_Music_4, &CIOBoardTest1View::OnBnClickedMusic4)
	ON_BN_CLICKED(BTN_Music_5, &CIOBoardTest1View::OnBnClickedMusic5)
	ON_BN_CLICKED(BTN_Music_6, &CIOBoardTest1View::OnBnClickedMusic6)
	ON_BN_CLICKED(BTN_Music_7, &CIOBoardTest1View::OnBnClickedMusic7)
	ON_BN_CLICKED(BTN_Music_8, &CIOBoardTest1View::OnBnClickedMusic8)
	ON_BN_CLICKED(BTN_Music_Pause, &CIOBoardTest1View::OnBnClickedMusicPause)
	ON_BN_CLICKED(BTN_LAMP_1_R, &CIOBoardTest1View::OnBnClickedLamp1R)
	ON_BN_CLICKED(BTN_LAMP_1_Y, &CIOBoardTest1View::OnBnClickedLamp1Y)
	ON_BN_CLICKED(BTN_LAMP_1_G, &CIOBoardTest1View::OnBnClickedLamp1G)
	ON_BN_CLICKED(BTN_LAMP_1_RY, &CIOBoardTest1View::OnBnClickedLamp1Ry)
	ON_BN_CLICKED(BTN_LAMP_1_RG, &CIOBoardTest1View::OnBnClickedLamp1Rg)
	ON_BN_CLICKED(BTN_LAMP_1_YG, &CIOBoardTest1View::OnBnClickedLamp1Yg)
	ON_BN_CLICKED(BTN_LAMP_1_RYG, &CIOBoardTest1View::OnBnClickedLamp1Ryg)
	ON_BN_CLICKED(BTN_LAMP_1_Effect, &CIOBoardTest1View::OnBnClickedLamp1Effect)
	ON_BN_CLICKED(BTN_LAMP_1_PAUSE, &CIOBoardTest1View::OnBnClickedLamp1Pause)
	ON_BN_CLICKED(BTN_LAMP_2_R, &CIOBoardTest1View::OnBnClickedLamp2R)
	ON_BN_CLICKED(BTN_LAMP_2_Y, &CIOBoardTest1View::OnBnClickedLamp2Y)
	ON_BN_CLICKED(BTN_LAMP_2_G, &CIOBoardTest1View::OnBnClickedLamp2G)
	ON_BN_CLICKED(BTN_LAMP_2_RY, &CIOBoardTest1View::OnBnClickedLamp2Ry)
	ON_BN_CLICKED(BTN_LAMP_2_RG, &CIOBoardTest1View::OnBnClickedLamp2Rg)
	ON_BN_CLICKED(BTN_LAMP_2_YG, &CIOBoardTest1View::OnBnClickedLamp2Yg)
	ON_BN_CLICKED(BTN_LAMP_2_RYG, &CIOBoardTest1View::OnBnClickedLamp2Ryg)
	ON_BN_CLICKED(BTN_LAMP_2_Effect, &CIOBoardTest1View::OnBnClickedLamp2Effect)
	ON_BN_CLICKED(BTN_LAMP_2_PAUSE, &CIOBoardTest1View::OnBnClickedLamp2Pause)
	ON_BN_CLICKED(BTN_EDIT_CLEAR, &CIOBoardTest1View::OnBnClickedEditClear)
	ON_BN_CLICKED(BTN_RANDOM, &CIOBoardTest1View::OnBnClickedRandom)
	ON_BN_CLICKED(BTN_ALL_RESET, &CIOBoardTest1View::OnBnClickedAllReset)
	ON_BN_CLICKED(BTN_Stream, &CIOBoardTest1View::OnBnClickedStream)
	ON_BN_CLICKED(BTN_ROTATION, &CIOBoardTest1View::OnBnClickedRotation)
	ON_BN_CLICKED(BTN_SAME, &CIOBoardTest1View::OnBnClickedSame)
	ON_BN_CLICKED(BTN_EFFECT_RANDOM, &CIOBoardTest1View::OnBnClickedEffectRandom)
	ON_BN_CLICKED(BTN_EFFECT_PAUSE, &CIOBoardTest1View::OnBnClickedEffectPause)
	ON_BN_CLICKED(BTN_Fast, &CIOBoardTest1View::OnBnClickedFast)
	ON_BN_CLICKED(BTN_NORMAL, &CIOBoardTest1View::OnBnClickedNormal)
	ON_BN_CLICKED(BTN_Slow, &CIOBoardTest1View::OnBnClickedSlow)
	ON_BN_CLICKED(BTN_Sensor, &CIOBoardTest1View::OnBnClickedSensor)
END_MESSAGE_MAP()

// CIOBoardTest1View 생성/소멸

CIOBoardTest1View::CIOBoardTest1View() noexcept
	: CFormView(IDD_IOBOARDTEST1_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.	
	m_pDoc = NULL;
	
	m_HD_LP1_Red.SetFaceColor(RGB(153, 153, 153));
	m_HD_LP1_Yellow.SetFaceColor(RGB(153, 153, 153));
	m_HD_LP1_Green.SetFaceColor(RGB(153, 153, 153));
	m_HD_LP2_Red.SetFaceColor(RGB(153, 153, 153));
	m_HD_LP2_Yellow.SetFaceColor(RGB(153, 153, 153));
	m_HD_LP2_Green.SetFaceColor(RGB(153, 153, 153));
	m_Ch_Sensor.SetFaceColor(RGB(240, 240, 240));
	m_HD_EMS.SetFaceColor(RGB(153, 153, 153));
	// char
	strcpy(m_sMusicName[0], "노래 : 노래1");
	strcpy(m_sMusicName[1], "노래 : 노래2");
	strcpy(m_sMusicName[2], "노래 : 노래3");
	strcpy(m_sMusicName[3], "노래 : 노래4");
	strcpy(m_sMusicName[4], "노래 : 노래5");
	strcpy(m_sMusicName[5], "노래 : 노래6");
	strcpy(m_sMusicName[6], "노래 : 노래7");
	strcpy(m_sMusicName[7], "노래 : 노래8");

	strcpy(m_sLamp1Color[0], "램프 1 : 빨강");
	strcpy(m_sLamp1Color[1], "램프 1 : 주황");
	strcpy(m_sLamp1Color[2], "램프 1 : 초록");
	strcpy(m_sLamp1Color[3], "램프 1 : 빨강 주황");
	strcpy(m_sLamp1Color[4], "램프 1 : 빨강 초록");
	strcpy(m_sLamp1Color[5], "램프 1 : 주황 초록 ");
	strcpy(m_sLamp1Color[6], "램프 1 : 빨강 주황 초록");
	strcpy(m_sLamp1Color[7], "램프 1 : STREAM");
	strcpy(m_sLamp1Color[8], "램프 1 : 멈춤");
  
	strcpy(m_sLamp2Color[0], "램프 2 : 빨강");
	strcpy(m_sLamp2Color[1], "램프 2 : 주황");
	strcpy(m_sLamp2Color[2], "램프 2 : 초록");
	strcpy(m_sLamp2Color[3], "램프 2 : 빨강 주황");
	strcpy(m_sLamp2Color[4], "램프 2 : 빨강 초록");
	strcpy(m_sLamp2Color[5], "램프 2 : 주황 초록 ");
	strcpy(m_sLamp2Color[6], "램프 2 : 빨강 주황 초록");
	strcpy(m_sLamp2Color[7], "램프 2 : STREAM");
	strcpy(m_sLamp2Color[8], "램프 2 : 멈춤");

	strcpy(m_sEffect[0], "효과 : STREAM");
	strcpy(m_sEffect[1], "효과 : ROTATION");
	strcpy(m_sEffect[2], "효과 : SAME");
	strcpy(m_sEffect[3], "효과 : RANDOM");
	strcpy(m_sEffect[4], "효과 : PAUSE");

	strcpy(m_sEffectSpeed[0], "속도 : FAST");
	strcpy(m_sEffectSpeed[0], "속도 : NORMAL");
	strcpy(m_sEffectSpeed[0], "속도 : SLOW");

	m_bisMusicBtn = false;	// 노래 버튼이 눌렸나? Y/N
	m_bisLamp1Btn = false;	// 램프1 사용하는 버튼이 눌렸나?
	m_bisLamp2Btn = false;	// 램프1 사용하는 버튼이 눌렸나?

	m_bisEffectBtn = false;
	m_bisEffectPause = false;
	m_bisEffectSpeedBtn = false;
	m_bisTIM320 = false;

	// int

	m_nMusicNo = -1;	// 노래 번호

	m_nOnLamp1Type = -1;
	m_nOnLamp2Type = -1;
	m_nEffectType = -1;
	m_nEffectSpeedType = 1;

	nTIM320Type = -1;
}

CIOBoardTest1View::~CIOBoardTest1View()
{
}

void CIOBoardTest1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_HD_LP_1_RED, m_HD_LP1_Red);
	DDX_Control(pDX, IDC_HD_LP_1_YELLOW, m_HD_LP1_Yellow);
	DDX_Control(pDX, IDC_HD_LP_1_GREEN, m_HD_LP1_Green);
	DDX_Control(pDX, IDC_HD_LP_2_RED, m_HD_LP2_Red);
	DDX_Control(pDX, IDC_HD_LP_2_YELLOW, m_HD_LP2_Yellow);
	DDX_Control(pDX, IDC_HD_LP_2_GREEN, m_HD_LP2_Green);
	DDX_Control(pDX, HD_BTN_EMS, m_HD_EMS);
	DDX_Control(pDX, BTN_Sensor, m_Ch_Sensor);

	DDX_Control(pDX, BTN_Stream, m_Ef_Stream);
	DDX_Control(pDX, BTN_ROTATION, m_Ef_Rotation);
	DDX_Control(pDX, BTN_SAME, m_Ef_Same);
	DDX_Control(pDX, BTN_EFFECT_RANDOM, m_Ef_Random);
	DDX_Control(pDX, BTN_EFFECT_PAUSE, m_Ef_Pause);
	DDX_Control(pDX, BTN_Fast, m_Fast);
	DDX_Control(pDX, BTN_NORMAL, m_Normal);
	DDX_Control(pDX, BTN_Slow, m_Slow);
	DDX_Control(pDX, BTN_EDIT_CLEAR, m_Clear);
	DDX_Control(pDX, BTN_RANDOM, m_ARandom);
	DDX_Control(pDX, BTN_ALL_RESET, m_AReset);
	DDX_Control(pDX, BTN_Music_1, m_M1);
	DDX_Control(pDX, BTN_Music_2, m_M2);
	DDX_Control(pDX, BTN_Music_3, m_M3);
	DDX_Control(pDX, BTN_Music_4, m_M4);
	DDX_Control(pDX, BTN_Music_5, m_M5);
	DDX_Control(pDX, BTN_Music_6, m_M6);
	DDX_Control(pDX, BTN_Music_7, m_M7);
	DDX_Control(pDX, BTN_Music_8, m_M8);
	DDX_Control(pDX, BTN_Music_Pause, m_MPause);
	DDX_Control(pDX, BTN_LAMP_1_R, m_L1_R);
	DDX_Control(pDX, BTN_LAMP_1_Y, m_L1_Y);
	DDX_Control(pDX, BTN_LAMP_1_G, m_L1_G);
	DDX_Control(pDX, BTN_LAMP_1_RY, m_L1_RY);
	DDX_Control(pDX, BTN_LAMP_1_RG, m_L1_RG);
	DDX_Control(pDX, BTN_LAMP_1_YG, m_L1_YG);
	DDX_Control(pDX, BTN_LAMP_1_RYG, m_L1_RYG);
	DDX_Control(pDX, BTN_LAMP_1_Effect, m_L1_Stream);
	DDX_Control(pDX, BTN_LAMP_1_PAUSE, m_L1_Pause);
	DDX_Control(pDX, BTN_LAMP_2_R, m_L2_R);
	DDX_Control(pDX, BTN_LAMP_2_Y, m_L2_Y);
	DDX_Control(pDX, BTN_LAMP_2_G, m_L2_G);
	DDX_Control(pDX, BTN_LAMP_2_RY, m_L2_RY);
	DDX_Control(pDX, BTN_LAMP_2_RG, m_L2_RG);
	DDX_Control(pDX, BTN_LAMP_2_YG, m_L2_YG);
	DDX_Control(pDX, BTN_LAMP_2_RYG, m_L2_RYG);
	DDX_Control(pDX, BTN_LAMP_2_Effect, m_L2_Stream);
	DDX_Control(pDX, BTN_LAMP_2_PAUSE, m_L2_Pause);
}

BOOL CIOBoardTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CIOBoardTest1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	int iii = 0;
	m_pDoc = GetDocument();

	m_pDoc->m_ViewControl.pView = this;
	m_pDoc->m_ViewControl.pDoc = m_pDoc;

	m_HD_LP1_Red.EnableWindow(FALSE);
	m_HD_LP1_Yellow.EnableWindow(FALSE);
	m_HD_LP1_Green.EnableWindow(FALSE);
	m_HD_LP2_Red.EnableWindow(FALSE);
	m_HD_LP2_Yellow.EnableWindow(FALSE);
	m_HD_LP2_Green.EnableWindow(FALSE);
	m_HD_EMS.EnableWindow(FALSE);
}


// CIOBoardTest1View 진단

#ifdef _DEBUG
void CIOBoardTest1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CIOBoardTest1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIOBoardTest1Doc* CIOBoardTest1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIOBoardTest1Doc)));
	return (CIOBoardTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CIOBoardTest1View 메시지 처리기
void CIOBoardTest1View::DoUseBtn() {
	m_M1.SetFaceColor(RGB(240, 240, 240));
	m_Ef_Stream.SetFaceColor(RGB(240, 240, 240));
	m_Ef_Rotation.SetFaceColor(RGB(240, 240, 240));
	m_Ef_Same.SetFaceColor(RGB(240, 240, 240));
	m_Ef_Random.SetFaceColor(RGB(240, 240, 240));
	m_Ef_Pause.SetFaceColor(RGB(240, 240, 240));
	m_Fast.SetFaceColor(RGB(240, 240, 240));
	m_Normal.SetFaceColor(RGB(240, 240, 240));
	m_Slow.SetFaceColor(RGB(240, 240, 240));
	m_Clear.SetFaceColor(RGB(240, 240, 240));
	m_ARandom.SetFaceColor(RGB(240, 240, 240));
	m_AReset.SetFaceColor(RGB(240, 240, 240));
	m_M1.SetFaceColor(RGB(240, 240, 240));
	m_M2.SetFaceColor(RGB(240, 240, 240));
	m_M3.SetFaceColor(RGB(240, 240, 240));
	m_M4.SetFaceColor(RGB(240, 240, 240));
	m_M5.SetFaceColor(RGB(240, 240, 240));
	m_M6.SetFaceColor(RGB(240, 240, 240));
	m_M7.SetFaceColor(RGB(240, 240, 240));
	m_M8.SetFaceColor(RGB(240, 240, 240));
	m_MPause.SetFaceColor(RGB(240, 240, 240));
	m_L1_R.SetFaceColor(RGB(240, 240, 240));
	m_L1_Y.SetFaceColor(RGB(240, 240, 240));
	m_L1_G.SetFaceColor(RGB(240, 240, 240));
	m_L1_RY.SetFaceColor(RGB(240, 240, 240));
	m_L1_RG.SetFaceColor(RGB(240, 240, 240));
	m_L1_YG.SetFaceColor(RGB(240, 240, 240));
	m_L1_RYG.SetFaceColor(RGB(240, 240, 240));
	m_L1_Stream.SetFaceColor(RGB(240, 240, 240));
	m_L1_Pause.SetFaceColor(RGB(240, 240, 240));
	m_L2_R.SetFaceColor(RGB(240, 240, 240));
	m_L2_Y.SetFaceColor(RGB(240, 240, 240));
	m_L2_G.SetFaceColor(RGB(240, 240, 240));
	m_L2_RY.SetFaceColor(RGB(240, 240, 240));
	m_L2_RG.SetFaceColor(RGB(240, 240, 240));
	m_L2_YG.SetFaceColor(RGB(240, 240, 240));
	m_L2_RYG.SetFaceColor(RGB(240, 240, 240));
	m_L2_Stream.SetFaceColor(RGB(240, 240, 240));
	m_L2_Pause.SetFaceColor(RGB(240, 240, 240));
	//m_Ch_Sensor.EnableWindow(TRUE);
	m_Ef_Stream.EnableWindow(TRUE);
	m_Ef_Rotation.EnableWindow(TRUE);
	m_Ef_Same.EnableWindow(TRUE);
	m_Ef_Random.EnableWindow(TRUE);
	m_Ef_Pause.EnableWindow(TRUE);
	m_Fast.EnableWindow(TRUE);
	m_Normal.EnableWindow(TRUE);
	m_Slow.EnableWindow(TRUE);
	m_Clear.EnableWindow(TRUE);
	m_ARandom.EnableWindow(TRUE);
	m_AReset.EnableWindow(TRUE);
	m_M1.EnableWindow(TRUE);
	m_M2.EnableWindow(TRUE);
	m_M3.EnableWindow(TRUE);
	m_M4.EnableWindow(TRUE);
	m_M5.EnableWindow(TRUE);
	m_M6.EnableWindow(TRUE);
	m_M7.EnableWindow(TRUE);
	m_M8.EnableWindow(TRUE);
	m_MPause.EnableWindow(TRUE);
	m_L1_R.EnableWindow(TRUE);
	m_L1_Y.EnableWindow(TRUE);
	m_L1_G.EnableWindow(TRUE);
	m_L1_RY.EnableWindow(TRUE);
	m_L1_RG.EnableWindow(TRUE);
	m_L1_YG.EnableWindow(TRUE);
	m_L1_RYG.EnableWindow(TRUE);
	m_L1_Stream.EnableWindow(TRUE);
	m_L1_Pause.EnableWindow(TRUE);
	m_L2_R.EnableWindow(TRUE);
	m_L2_Y.EnableWindow(TRUE);
	m_L2_G.EnableWindow(TRUE);
	m_L2_RY.EnableWindow(TRUE);
	m_L2_RG.EnableWindow(TRUE);
	m_L2_YG.EnableWindow(TRUE);
	m_L2_RYG.EnableWindow(TRUE);
	m_L2_Stream.EnableWindow(TRUE);
	m_L2_Pause.EnableWindow(TRUE);
}
void CIOBoardTest1View::DoNotUseBtn() {
	m_Ef_Stream.SetFaceColor(RGB(153, 153, 153));
	m_Ef_Rotation.SetFaceColor(RGB(153, 153, 153));
	m_Ef_Same.SetFaceColor(RGB(153, 153, 153));
	m_Ef_Random.SetFaceColor(RGB(153, 153, 153));
	m_Ef_Pause.SetFaceColor(RGB(153, 153, 153));
	m_Fast.SetFaceColor(RGB(153, 153, 153));
	m_Normal.SetFaceColor(RGB(153, 153, 153));
	m_Slow.SetFaceColor(RGB(153, 153, 153));
	m_Clear.SetFaceColor(RGB(153, 153, 153));
	m_ARandom.SetFaceColor(RGB(153, 153, 153));
	m_AReset.SetFaceColor(RGB(153, 153, 153));
	m_M1.SetFaceColor(RGB(153, 153, 153));
	m_M2.SetFaceColor(RGB(153, 153, 153));
	m_M3.SetFaceColor(RGB(153, 153, 153));
	m_M4.SetFaceColor(RGB(153, 153, 153));
	m_M5.SetFaceColor(RGB(153, 153, 153));
	m_M6.SetFaceColor(RGB(153, 153, 153));
	m_M7.SetFaceColor(RGB(153, 153, 153));
	m_M8.SetFaceColor(RGB(153, 153, 153));
	m_MPause.SetFaceColor(RGB(153, 153, 153));
	m_L1_R.SetFaceColor(RGB(153, 153, 153));
	m_L1_Y.SetFaceColor(RGB(153, 153, 153));
	m_L1_G.SetFaceColor(RGB(153, 153, 153));
	m_L1_RY.SetFaceColor(RGB(153, 153, 153));
	m_L1_RG.SetFaceColor(RGB(153, 153, 153));
	m_L1_YG.SetFaceColor(RGB(153, 153, 153));
	m_L1_RYG.SetFaceColor(RGB(153, 153, 153));
	m_L1_Stream.SetFaceColor(RGB(153, 153, 153));
	m_L1_Pause.SetFaceColor(RGB(153, 153, 153));
	m_L2_R.SetFaceColor(RGB(153, 153, 153));
	m_L2_Y.SetFaceColor(RGB(153, 153, 153));
	m_L2_G.SetFaceColor(RGB(153, 153, 153));
	m_L2_RY.SetFaceColor(RGB(153, 153, 153));
	m_L2_RG.SetFaceColor(RGB(153, 153, 153));
	m_L2_YG.SetFaceColor(RGB(153, 153, 153));
	m_L2_RYG.SetFaceColor(RGB(153, 153, 153));
	m_L2_Stream.SetFaceColor(RGB(153, 153, 153));
	m_L2_Pause.SetFaceColor(RGB(153, 153, 153));
	//m_Ch_Sensor.EnableWindow(FALSE);
	m_Ef_Stream.EnableWindow(FALSE);
	m_Ef_Rotation.EnableWindow(FALSE);
	m_Ef_Same.EnableWindow(FALSE);
	m_Ef_Random.EnableWindow(FALSE);
	m_Ef_Pause.EnableWindow(FALSE);
	m_Fast.EnableWindow(FALSE);
	m_Normal.EnableWindow(FALSE);
	m_Slow.EnableWindow(FALSE);
	m_Clear.EnableWindow(FALSE);
	m_ARandom.EnableWindow(FALSE);
	m_AReset.EnableWindow(FALSE);
	m_M1.EnableWindow(FALSE);
	m_M2.EnableWindow(FALSE);
	m_M3.EnableWindow(FALSE);
	m_M4.EnableWindow(FALSE);
	m_M5.EnableWindow(FALSE);
	m_M6.EnableWindow(FALSE);
	m_M7.EnableWindow(FALSE);
	m_M8.EnableWindow(FALSE);
	m_MPause.EnableWindow(FALSE);
	m_L1_R.EnableWindow(FALSE);
	m_L1_Y.EnableWindow(FALSE);
	m_L1_G.EnableWindow(FALSE);
	m_L1_RY.EnableWindow(FALSE);
	m_L1_RG.EnableWindow(FALSE);
	m_L1_YG.EnableWindow(FALSE);
	m_L1_RYG.EnableWindow(FALSE);
	m_L1_Stream.EnableWindow(FALSE);
	m_L1_Pause.EnableWindow(FALSE);
	m_L2_R.EnableWindow(FALSE);
	m_L2_Y.EnableWindow(FALSE);
	m_L2_G.EnableWindow(FALSE);
	m_L2_RY.EnableWindow(FALSE);
	m_L2_RG.EnableWindow(FALSE);
	m_L2_YG.EnableWindow(FALSE);
	m_L2_RYG.EnableWindow(FALSE);
	m_L2_Stream.EnableWindow(FALSE);
	m_L2_Pause.EnableWindow(FALSE);
}

void CIOBoardTest1View::HD_Music_Update() {
	SetDlgItemText(EDIT_HD_MUSIC, "\r\n     " + csMusic);
}
void CIOBoardTest1View::HD_Lamp_Update() {
	m_HD_LP1_Red.EnableWindowsTheming(FALSE);
	m_HD_LP1_Yellow.EnableWindowsTheming(FALSE);
	m_HD_LP1_Green.EnableWindowsTheming(FALSE);
	if (m_pDoc->m_Io.m_bOutput[21]) 	m_HD_LP1_Red.SetFaceColor(RGB(255, 0, 0));
	else 				m_HD_LP1_Red.SetFaceColor(RGB(153, 153, 153));

	if (m_pDoc->m_Io.m_bOutput[22]) 	m_HD_LP1_Yellow.SetFaceColor(RGB(255, 127, 0));
	else 				m_HD_LP1_Yellow.SetFaceColor(RGB(153, 153, 153));

	if (m_pDoc->m_Io.m_bOutput[23]) 	m_HD_LP1_Green.SetFaceColor(RGB(0, 255, 0));
	else 				m_HD_LP1_Green.SetFaceColor(RGB(153, 153, 153));

	m_HD_LP2_Red.EnableWindowsTheming(FALSE);
	m_HD_LP2_Yellow.EnableWindowsTheming(FALSE);
	m_HD_LP2_Green.EnableWindowsTheming(FALSE);
	if (m_pDoc->m_Io.m_bOutput[0]) 	m_HD_LP2_Red.SetFaceColor(RGB(255, 0, 0));
	else 				m_HD_LP2_Red.SetFaceColor(RGB(153, 153, 153));

	if (m_pDoc->m_Io.m_bOutput[1]) 	m_HD_LP2_Yellow.SetFaceColor(RGB(255, 127, 0));
	else 				m_HD_LP2_Yellow.SetFaceColor(RGB(153, 153, 153));

	if (m_pDoc->m_Io.m_bOutput[2]) 	m_HD_LP2_Green.SetFaceColor(RGB(0, 255, 0));
	else 				m_HD_LP2_Green.SetFaceColor(RGB(153, 153, 153));
}
void CIOBoardTest1View::HD_EMS_Update() {
	GetDlgItemText(EDIT_SW_STATUS, csStatus);
	m_HD_EMS.EnableWindowsTheming(FALSE);
	
	if (!m_pDoc->m_Io.m_bInput[8] && m_pDoc->m_ViewControl.nThrdCnt != 0) { 
		m_HD_EMS.SetFaceColor(RGB(255, 0, 0)); 
		m_Ch_Sensor.SetFaceColor(RGB(153, 153, 153));
		//DoUseBtn();
		//SetDlgItemText(EDIT_SW_STATUS, csStatus + "\r\n비상 정지 버튼 : ON\r\n");
	}
	else {
		m_HD_EMS.SetFaceColor(RGB(153, 153, 153));
		m_Ch_Sensor.SetFaceColor(RGB(240, 240, 240));
		//DoNotUseBtn();
		//SetDlgItemText(EDIT_SW_STATUS, csStatus + "\r\n비상 정지 버튼 : OFF\r\n");
	}
	//SendMessage(WM_CLOSE, NULL, NULL);
}
void CIOBoardTest1View::HD_TIM320_Update() {
	if (m_pDoc->m_Io.m_bInput[24] && m_pDoc->m_Io.m_bInput[25] && m_pDoc->m_Io.m_bInput[26]) {
		csTIM320.Format("\r\n     TIM320 : 감지 안됨\r\n");
		SetDlgItemText(EDIT_HD_TIM320, csTIM320);
		nTIM320Type = 0;
	}
	else if (!m_pDoc->m_Io.m_bInput[24] && !m_pDoc->m_Io.m_bInput[25] && m_pDoc->m_Io.m_bInput[26]) {
		csTIM320.Format("\r\n     TIM320 : 거리 멈\r\n");
		SetDlgItemText(EDIT_HD_TIM320, csTIM320);
		nTIM320Type = 1;
	}
	else if (!m_pDoc->m_Io.m_bInput[24] && m_pDoc->m_Io.m_bInput[25] && m_pDoc->m_Io.m_bInput[26]) {
		csTIM320.Format("\r\n     TIM320 : 거리 중간\r\n");
		SetDlgItemText(EDIT_HD_TIM320, csTIM320);
		nTIM320Type = 2;
	}
	else if (!m_pDoc->m_Io.m_bInput[24] && !m_pDoc->m_Io.m_bInput[25] && !m_pDoc->m_Io.m_bInput[26]) {
		csTIM320.Format("\r\n     TIM320 : 거리 가까움\r\n");
		SetDlgItemText(EDIT_HD_TIM320, csTIM320);
		nTIM320Type = 3;
	}

}


void CIOBoardTest1View::SW_StatusUpdate() {
	GetDlgItemText(EDIT_SW_STATUS, csStatus);
	Music_Status();
	Lamp1_Status();
	Lamp2_Status();
	Effect_Status();
	Effect_Speed_Status();
}
void CIOBoardTest1View::Music_Status() {
	if (m_bisMusicBtn) {
		if (m_nMusicNo == -1) {
			csMusic.Format(" 노래 : 멈춤 \r\n");
			m_bisMusicBtn = false;
			SetDlgItemText(EDIT_SW_STATUS, csStatus + csMusic);
		}
		else {
			for (int i = 0; i < MUSIC_CNT; i++) {
				if (i != m_nMusicNo) continue;
				csMusic.Format(" %d번  %s \r\n", i + 1, m_sMusicName[m_nMusicNo]);
				m_bisMusicBtn = false;
				SetDlgItemText(EDIT_SW_STATUS, csStatus + csMusic);
			}
		}
	}

}
void CIOBoardTest1View::Lamp1_Status() {
	if (m_bisLamp1Btn) {
		csLamp.Format(" %s \r\n", m_sLamp1Color[m_nOnLamp1Type]);
		m_bisLamp1Btn = false;
		SetDlgItemText(EDIT_SW_STATUS, csStatus + csLamp);

	}

}
void CIOBoardTest1View::Lamp2_Status() {
	if (m_bisLamp2Btn) {
		csLamp.Format(" %s \r\n", m_sLamp2Color[m_nOnLamp2Type]);
		m_bisLamp2Btn = false;
		SetDlgItemText(EDIT_SW_STATUS, csStatus + csLamp);
		
	}

}
void CIOBoardTest1View::Effect_Status() {
	if (m_bisEffectBtn) {
		csEffect.Format(" %s \r\n", m_sEffect[m_nEffectType]);
		m_bisEffectBtn = false;
		SetDlgItemText(EDIT_SW_STATUS, csStatus + csEffect);

	}
}
void CIOBoardTest1View::Effect_Speed_Status(){
	if (m_bisEffectSpeedBtn) {
		csEffect.Format(" %s \r\n", m_sEffectSpeed[m_nEffectSpeedType]);
		m_bisEffectSpeedBtn = false;
		SetDlgItemText(EDIT_SW_STATUS, csStatus + csEffectSpeed);

	}
}

void CIOBoardTest1View::OnBnClickedMusic1()
{
	m_nMusicNo = 0;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusic2()
{
	m_nMusicNo = 1;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusic3()
{
	m_nMusicNo = 2;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusic4()
{
	m_nMusicNo = 3;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusic5()
{
	m_nMusicNo = 4;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusic6()
{
	m_nMusicNo = 5;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusic7()
{
	m_nMusicNo = 6;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusic8()
{
	m_nMusicNo = 7;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedMusicPause()
{
	m_nMusicNo = -1;
	m_bisMusicBtn = true;
	SW_StatusUpdate();
	 

}


void CIOBoardTest1View::OnBnClickedLamp1R()
{
	m_nOnLamp1Type = 0;
	m_bisLamp1Btn = true;
	SW_StatusUpdate();
	 

}	
void CIOBoardTest1View::OnBnClickedLamp1Y()
{
	m_nOnLamp1Type = 1;
	m_bisLamp1Btn = true;

	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp1G()
{	
	m_nOnLamp1Type = 2;
	m_bisLamp1Btn = true;

	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp1Ry()
{
	m_nOnLamp1Type = 3;
	m_bisLamp1Btn = true;

	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp1Rg()
{
	m_nOnLamp1Type = 4;
	m_bisLamp1Btn = true;

	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp1Yg()
{
	m_nOnLamp1Type = 5;
	m_bisLamp1Btn = true;

	SW_StatusUpdate();

}
void CIOBoardTest1View::OnBnClickedLamp1Ryg()
{
	m_nOnLamp1Type = 6;
	m_bisLamp1Btn = true;

	SW_StatusUpdate();

}
void CIOBoardTest1View::OnBnClickedLamp1Effect()
{
	m_nOnLamp1Type = 7;
	m_bisLamp1Btn = true;
	SW_StatusUpdate();


}
void CIOBoardTest1View::OnBnClickedLamp1Pause()
{
	m_nOnLamp1Type = 8;
	m_bisLamp1Btn = true;
	SW_StatusUpdate();


}


void CIOBoardTest1View::OnBnClickedLamp2R()
{
	m_nOnLamp2Type = 0;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2Y()
{
	m_nOnLamp2Type = 1;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2G()
{
	m_nOnLamp2Type = 2;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2Ry()
{
	m_nOnLamp2Type = 3;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2Rg()
{
	m_nOnLamp2Type = 4;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2Yg()
{
	m_nOnLamp2Type = 5;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2Ryg()
{
	m_nOnLamp2Type = 6;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2Effect()
{
	m_nOnLamp2Type = 7;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}
void CIOBoardTest1View::OnBnClickedLamp2Pause()
{
	m_nOnLamp2Type = 8;
	m_bisLamp2Btn = true;
	SW_StatusUpdate();
	 

}


void CIOBoardTest1View::OnBnClickedEditClear()
{
	SetDlgItemText(EDIT_SW_STATUS, "");
}
void CIOBoardTest1View::OnBnClickedRandom()
{
	int nRandNo = rand() % 22;

	if (nRandNo == 0) 	OnBnClickedMusic1();
	else if (nRandNo == 1)	OnBnClickedMusic2();
	else if (nRandNo == 2)	OnBnClickedMusic3();
	else if (nRandNo == 3)	OnBnClickedMusic4();
	else if (nRandNo == 4)	OnBnClickedMusic5();
	else if (nRandNo == 5)	OnBnClickedMusic6();
	else if (nRandNo == 6)	OnBnClickedMusic7();
	else if (nRandNo == 7)	OnBnClickedMusic8();
	else if (nRandNo == 8)	OnBnClickedLamp1R();
	else if (nRandNo == 9)	OnBnClickedLamp1Y();
	else if (nRandNo == 10)	OnBnClickedLamp1G();
	else if (nRandNo == 11)	OnBnClickedLamp1Ry();
	else if (nRandNo == 12)	OnBnClickedLamp1Rg();
	else if (nRandNo == 13)	OnBnClickedLamp1Yg();
	else if (nRandNo == 14)	OnBnClickedLamp1Ryg();
	else if (nRandNo == 15)	OnBnClickedLamp2R();
	else if (nRandNo == 16)	OnBnClickedLamp2Y();
	else if (nRandNo == 17)	OnBnClickedLamp2G();
	else if (nRandNo == 18)	OnBnClickedLamp2Ry();
	else if (nRandNo == 19)	OnBnClickedLamp2Rg();
	else if (nRandNo == 20)	OnBnClickedLamp2Yg();
	else if (nRandNo == 21)	OnBnClickedLamp2Ryg();
}
void CIOBoardTest1View::OnBnClickedAllReset()
{
	SetDlgItemText(EDIT_SW_STATUS, "");
	m_bisMusicBtn = false;	// 노래 버튼이 눌렸나? Y/N
	m_bisLamp1Btn = false;	// 램프1 사용하는 버튼이 눌렸나?
	m_bisLamp2Btn = false;	// 램프1 사용하는 버튼이 눌렸나?

	m_bisEffectBtn = false;
	m_bisEffectPause = false;
	m_bisEffectSpeedBtn = false;

	// int

	m_nMusicNo = -1;	// 노래 번호

	m_nOnLamp1Type = -1;
	m_nOnLamp2Type = -1;
	m_nEffectType = -1;
	m_nEffectSpeedType = -1;
}


void CIOBoardTest1View::OnBnClickedStream()
{
	m_nEffectType = 0;
	m_bisEffectBtn = true;
	SW_StatusUpdate();
}
void CIOBoardTest1View::OnBnClickedRotation()
{
	m_nEffectType = 1;
	m_bisEffectBtn = true;
	SW_StatusUpdate();
}
void CIOBoardTest1View::OnBnClickedSame()
{
	m_nEffectType = 2;
	m_bisEffectBtn = true;
	SW_StatusUpdate();
}
void CIOBoardTest1View::OnBnClickedEffectRandom()
{
	m_nEffectType = 3;
	m_bisEffectBtn = true;
	SW_StatusUpdate();
}
void CIOBoardTest1View::OnBnClickedEffectPause()
{
	m_nEffectType = 4;
	m_bisEffectBtn = true;
	m_bisEffectPause = true;
	SW_StatusUpdate();
}


void CIOBoardTest1View::OnBnClickedFast()
{
	m_nEffectSpeedType = 0;
	m_bisEffectSpeedBtn = true;
	SW_StatusUpdate();
}
void CIOBoardTest1View::OnBnClickedNormal()
{
	m_nEffectSpeedType = 1;
	m_bisEffectSpeedBtn = true;
	SW_StatusUpdate();
}
void CIOBoardTest1View::OnBnClickedSlow()
{
	m_nEffectSpeedType = 2;
	m_bisEffectSpeedBtn = true;
	SW_StatusUpdate();
}


void CIOBoardTest1View::OnBnClickedSensor()
{
	GetDlgItemText(EDIT_SW_STATUS, csStatus);
	

	if (m_bisTIM320) {
		m_bisTIM320 = false;
		SetDlgItemText(EDIT_HD_TIM320, "");
		SetDlgItemText(EDIT_SW_STATUS, csStatus + "\r\n 거리 센서 : OFF \r\n\n");
		m_nOnLamp1Type = 8;
		m_nOnLamp2Type = 8;

		DoUseBtn();
	}
	else {
		m_bisTIM320 = true;
		SetDlgItemText(EDIT_SW_STATUS, csStatus + "\r\n 거리 센서 : ON \r\n\n");
		m_nOnLamp1Type = 8;
		m_nOnLamp2Type = 8;
		
		DoNotUseBtn();
	}

	
	
}
