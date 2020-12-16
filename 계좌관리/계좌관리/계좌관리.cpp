#include <iostream>
#include <time.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#define BANK_NAME 50
#define JOIN_MAX_CNT 10
#define USER_NAME 15
#define ACCOUNT_NUM 20 
#define BREAKDOWN 10

int m_nUserMaxCnt = 10;
int m_nBankMaxCnt = 10;

struct BankInfo
{
	int nBankNo;					// 은행 번호
	char sBankName[BANK_NAME];		// 은행 이름
	double dInterestRate;			// 은행 금리
	int nJoinUserNo[JOIN_MAX_CNT];	// 가입한 유저 번호
	int nJoinMaxCnt;				// 가입한 최대 인원 수
	int nJoinCnt;					// 가입한 인원 수
	int nBankInfoNo[JOIN_MAX_CNT];	// 가입한 유저수를 세는 번호
};
struct UserInfo
{
	int nUserNo;						// 유저 번호
	char sUserName[USER_NAME];			// 유저 이름
	int nUserJoinBankNo[JOIN_MAX_CNT];	// 가입된 은행 번호
	int nUserACNo[JOIN_MAX_CNT];		// 가입한 계좌 번호
	int nJoinCnt;						// 가입한 은행 수
	int nUserInfoNo[JOIN_MAX_CNT];		// 가입한 은행 수를 세는 번호
	double nMoney[JOIN_MAX_CNT] = { 0.0, };			// 각 은행의 돈
};
struct ScanAndPrint
{
	int nHour[ACCOUNT_NUM] = { 0, };		// 시
	int nMin[ACCOUNT_NUM] = { 0, };			// 분
	int nSec[ACCOUNT_NUM] = { 0, };			// 초
	int nInOutMoney[ACCOUNT_NUM] = { 0, };	// 돈
	int nCnt = 0;							// 입출금내역 바꾸기위한 카운트
	int nSecCnt = 0;						// 금리 업뎃하기위한 카운트
	int nSignCnt = 0;
	int nSign[ACCOUNT_NUM] = { -1, };			// 부호
};
struct BankInfo m_pBank[100];
struct UserInfo m_pUser[100];
struct ScanAndPrint m_pSPInfo[JOIN_MAX_CNT];

void BankListPrint(void);		// 은행 리스트 출력
void BankMainMenu(void);		// 은행이 유/무 판별
void BankSubMenu(int nBankNo);		// 세부사항 선택
void BankPrint(int nBankNo);		// 은행 정보 출력

void UserListPrint(void);		// 유저 리스트 출력
void UserMainMenu(void);		// 유저의 유/무 판별
void UserSubMenu(int nUserNo);		// 세부사항 선택
void UserPrint(int nUserNo);		// 유저 정보 출력

void ForceJoin(int nBankNo);		// 은행측에서 가입
void ForceReturn(int nBankNo);		// 은행측에서 탈퇴
void Join(int nUserNo);				// 유저측에서 가입
void Return(int nUserNo);			// 유저측에서 탈퇴
void ForceJoinUpdata(int nBankNo, int nUserNo);		// 가입 업데이트
void ForceReturnUpdata(int nBankNo, int nUserNo);	// 탈퇴 업데이트
void JoinUpdata(int nBankNo, int nUserNo);
void ReturnUpdata(int nBankNo, int nUserNo);

int ForceJoinEnable(int nBankNo, int nUserNo);		// 가입의 가능/불가능 판별
int ForceReturnEnable(int nBankNo, int nNo);		// 탈퇴의 가능/불가능 판별
int JoinEnable(int nUserNo, int nBankNo);
int ReturnEnable(int nUserNo, int nBankNo);

void InMoney(int nUserNo, int nSign);				// 입금
void OutMoney(int nUserNo, int nSign);				// 출금
void InMoneyUpdata(int nUserNo, int BankNo, int nMoney);		// 입금업데이트
void OutMoneyUpdata(int nUserNo, int BankNo, int nMoney);		// 출금업데이트
void InOutMoneyList(int nUserNo, int nBankNo, int nSign);			// 입/출금 내역
void InOutListSwap(int nBankNo);					// 입출금내역 순서바꾸기
void InterestRateUpdata(int nUserNo, int nBankNo);				// 금리 업데이트

bool SignSwap(int nBankNo);
int OutMoneyEnable(int nUserNo, int nBankNo);				// 출금 가능/불가능 판별

void ChangeMainMenu(void);
void BankChange(void);
void UserChange(void);

void AddMainMenu(void);
void BankAdd(void);
void UserAdd(void);

int main(void)
{   
	// 은 행 정 보 초 기 화
	if (1)
	{
		//			 번호    이름     금리            가입한 유저 번호      최대인원  가입수      번호정보  
		m_pBank[0] = { 1, "하나은행", 0.004, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[1] = { 2, "우리은행", 0.003, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[2] = { 3, "한국은행", 0.002, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[3] = { 4, "농협은행", 0.001, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[4] = { 5, "수협은행", 0.003, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[5] = { 6, "국민은행", 0.004, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[6] = { 7, "신한은행", 0.002, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[7] = { 8, "제일은행", 0.004, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[8] = { 9, "제주은행", 0.003, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		m_pBank[9] = {10, "기업은행", 0.002, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	}

	 // 유 저 정 보 초 기 화
	if (1)
	{
		//			 번호   이름    		가입한 은행 번호						 은행에 따른 계좌번호		    가입수		번호정보				돈
		m_pUser[0] = { 1, "양소정", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[1] = { 2, "임효상", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[2] = { 3, "정명철", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[3] = { 4, "김대현", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[4] = { 5, "박정범", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[5] = { 6, "이병선", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[6] = { 7, "장소현", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[7] = { 8, "진상훈", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[8] = { 9, "박형진", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		m_pUser[9] = { 10, "김현준", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	}

	// 입 / 출 금 내 역 초 기 화
	if (1)
	{
	// 시/분초/돈 카운트1 카운트2 부호
		m_pSPInfo[0] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[1] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[2] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[3] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[5] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[6] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[7] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[8] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

		m_pSPInfo[9] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	}

	while (true)
	{
		int nNo;
		
		printf("\n======<< 선 택 목 록 >>========================================== \n\n");
		printf("	0.   끝 내 기  \n\n");
		printf("	1. 은 행 목 록 \n\n");
		printf("	2. 유 저 목 록 \n\n");
		printf("	3. 수 정 하 기 \n\n");
		printf("	4. 추 가 하 기 \n\n");
		printf("\n================================================================= \n\n");
		printf(" 무 엇 을 할 지 입 력 : ");
		scanf_s("%d", &nNo);
		system("cls");

		if (nNo == 0)
			return 0;
		switch (nNo)
		{
			case 1:	// 은 행 목 록
			{
				BankMainMenu();
				break;
			}
			case 2:	// 유 저 목 록
			{
				UserMainMenu();
				break;
			}
			case 3: // 수 정 하 기
			{
				ChangeMainMenu();
				break;
			}
			case 4: // 추 가 하 기
			{
				AddMainMenu();
				break;
			}
		}
	}
}

void BankListPrint(void)
{
	printf("\n======<< 은 행 목 록 >>========================================== \n\n");
	printf("	0. 뒤 로 가 기 \n\n");
	printf(" 은 행 번 호 |    은 행 이 름    | 금 리 | 최 대 인 원 수 | 가 입 한 유 저 수 \n\n");
	
	for (int i = 0; i < m_nBankMaxCnt; i++)
	{
		if (m_pBank[i].nBankNo < 10)
			printf("      %d      |      %s     |   %.3lf   |       %d       |        %d \n\n", m_pBank[i].nBankNo, m_pBank[i].sBankName, m_pBank[i].dInterestRate, m_pBank[i].nJoinMaxCnt, m_pBank[i].nJoinCnt);
		else
			printf("     %d      |      %s     |   %.3lf   |       %d       |        %d \n\n", m_pBank[i].nBankNo, m_pBank[i].sBankName, m_pBank[i].dInterestRate, m_pBank[i].nJoinMaxCnt, m_pBank[i].nJoinCnt);
	}
	printf("\n================================================================= \n\n");
}
void BankMainMenu(void)
{
	int nNo;

	while (true)
	{
		BankListPrint();

		printf(" 은 행 번 호 입 력 : ");
		scanf_s("%d", &nNo);
		system("cls");

		if (nNo == 0)
			return;

		else if (nNo > 10)
		{
			printf("\n [ 은 행 정 보 가 없 습 니 다. ]\n");
			printf("    [ 다 시 입 력 하 세 요. ]\n\n");
		}
		else
		{
			BankSubMenu(nNo);
		}
	}
}
void BankSubMenu(int nBankNo)
{
	int nNo1;

	while (true)
	{
		BankPrint(nBankNo);
		
		printf(" 1. 가 입 하 기 \n\n");
		printf(" 2. 탈 퇴 하 기 \n\n");
		printf(" 무 엇 을 할 지 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0 || nBankNo > 2)
			return;

		switch (nNo1)
		{
			case 1:	// 가 입
			{
				ForceJoin(nBankNo);
				break;
			}
			case 2: // 탈 퇴
			{
				ForceReturn(nBankNo);
				break;
			}
		}
	}
}
void BankPrint(int nBankNo)
{
	printf("\n======<< 은 행 정 보 >>========================================== \n\n");
	printf("	0. 뒤 로 가 기 \n\n");
	for (int i = 0; i < m_nBankMaxCnt; i++)
	{
		if (m_pBank[i].nBankNo != nBankNo) continue;

		printf(" 은 행 번 호 : %d \n", m_pBank[i].nBankNo);
		printf(" 은 행 이 름 : %s \n", m_pBank[i].sBankName);
		printf(" 은 행 금 리 : %.3lf \n", m_pBank[i].dInterestRate);
		printf(" 은 행 가 입 유 저 수 : %d \n\n", m_pBank[i].nJoinCnt);
		printf("	------[ 가 입 정 보 ]------------------------ \n\n");
		printf("		 번호	  이름    계좌번호 잔돈\n\n");
		for (int j = 0; j < m_nBankMaxCnt; j++)
		{
			if (m_pBank[i].nJoinUserNo[j] == -1)
			{
				printf("		[ %2d ].    가 입 된 유 저 없 음 \n\n", m_pBank[i].nBankInfoNo[j]);
			}
			else
			{
				for (int k = 0; k < JOIN_MAX_CNT; k++)
				{
					if (m_pUser[k].nUserNo != m_pBank[i].nJoinUserNo[j]) continue;

					printf("		[ %2d ].  %s    %d    %.1lf \n\n", m_pBank[i].nBankInfoNo[j], m_pUser[k].sUserName, m_pUser[k].nUserACNo[j], m_pUser[k].nMoney[j]);
				}
			}
		}
		printf("	--------------------------------------------- \n\n");
		printf("\n================================================================= \n\n");
		return;
	}
}

void UserListPrint(void)
{
	printf("\n======<< 유 저 목 록 >>========================================== \n\n");
	printf("	0. 뒤 로 가 기 \n\n");
	printf(" 유 저 번 호 |  유 저 이 름  | 은 행 가 입 수\n\n");
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo < 10)
			printf("      %d      |     %s    |      %d  \n\n", m_pUser[i].nUserNo, m_pUser[i].sUserName, m_pUser[i].nJoinCnt);
		else
			printf("     %d      |     %s    |      %d  \n\n", m_pUser[i].nUserNo, m_pUser[i].sUserName, m_pUser[i].nJoinCnt);
	}
	printf("\n================================================================= \n\n");
}
void UserMainMenu(void) 
{
	int nNo;

	while (true)
	{
		UserListPrint();

		printf(" 유 저 번 호 입 력 : ");
		scanf_s("%d", &nNo);
		system("cls");
		
		if (nNo == 0)
			return;
		else if (nNo > 10)
		{
			printf("\n [ 유 저 정 보 가 없 습 니 다. ]\n");
			printf("    [ 다 시 입 력 하 세 요. ] \n");
		}
		else
		{
			UserSubMenu(nNo);
		}
	}
}
void UserSubMenu(int nUserNo)
{
	int nNo1;

	while (true)
	{
		UserPrint(nUserNo);

		printf(" 1. 가 입 하 기 \n\n");
		printf(" 2. 탈 퇴 하 기 \n\n");
		printf(" 3. 입 금 하 기 \n\n");
		printf(" 4. 출 금 하 기 \n\n");
		printf(" 무 엇 을 할 지 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0)
			return;
		switch (nNo1)
		{
			case 1:	// 가입하기
			{
				Join(nUserNo);
				break;
			}
			case 2: // 탈퇴하기
			{
				Return(nUserNo);
				break;
			}
			case 3: // 입금하기
			{
				InMoney(nUserNo, nNo1);
				break;
			}
			case 4: // 출금하기
			{
				OutMoney(nUserNo, nNo1);
				break;
			}
		}
	}
}
void UserPrint(int nUserNo)
{
	printf("\n======<< 유 저 정 보 >>========================================== \n\n");
	printf("	0. 뒤 로 가 기 \n\n");
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo != nUserNo) continue;

		printf(" 유 저 번 호 : %d \n", m_pUser[i].nUserNo);
		printf(" 유 저 이 름 : %s \n", m_pUser[i].sUserName);
		printf(" 은 행 가 입 횟 수 : %d \n\n", m_pUser[i].nJoinCnt);
		printf("	------[ 가 입 정 보 ]---------------------------- \n\n");
		printf("		 번호	  이름    게좌번호   잔돈\n\n");
		for (int j = 0; j < m_nUserMaxCnt; j++)
		{
			if (m_pUser[i].nUserJoinBankNo[j] == -1)
				printf("		[ %2d ].	가 입 된 은 행 없 음 \n\n", m_pUser[i].nUserInfoNo[j]);
			else
			{
				for (int k = 0; k < JOIN_MAX_CNT; k++)
				{
					if (m_pUser[i].nUserJoinBankNo[j] != m_pBank[k].nBankNo) continue;
					
					printf("		[ %2d ].  %s    %d     %.1lf \n\n", m_pUser[i].nUserInfoNo[j], m_pBank[k].sBankName, m_pUser[i].nUserACNo[j], m_pUser[i].nMoney[j]);
				}
			}
		}
		printf("	------------------------------------------------- \n\n");
	}
	printf("\n================================================================= \n\n");
}

void ForceJoin(int nBankNo)
{
	int nNo1;

	while (true)
	{
		UserListPrint();
		
		printf(" 가 입 시 킬 유 저 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0)	return;
		else if (nNo1 > 10)
		{
			printf("\n [ 유 저 정 보 가 없 습 니 다. ] \n");
			printf("    [ 다 시 입 력 하 세 요. ] \n\n");
		}
		else if (ForceJoinEnable(nBankNo, nNo1) == 1)
		{
			printf("\n [ 해 당 은 행 은 만 원 입 니 다. ] \n");
			printf("      [ 다 시 입 력 하 세 요. ] \n\n");
		}
		else if (ForceJoinEnable(nBankNo, nNo1) == 2)
		{
			printf("\n [ 해 당 유 저 는 더 이 상 가 입 할 수 없 습 니 다. ] \n");
			printf("		    [ 다 시 입 력 하 세 요. ] \n\n");
		}
		else if (ForceJoinEnable(nBankNo, nNo1) == 3)
		{
			printf("        [ 해 당 은 행 은 만 원 입 니 다. ] \n");
			printf(" [해 당 유 저 는 더 이 상 가 입 할 수 없 습 니 다.] \n");
			printf("	    	[ 다 시 입 력 하 세 요. ] \n\n");
		}
		else
		{
			ForceJoinUpdata(nBankNo, nNo1);
			printf("\n [ 가 입 이 완 료 되 었 습 니 다. ] \n\n");
		}
		return;
	}
}
void ForceReturn(int nBankNo)
{
	int nNo1;

	while (1)
	{
		BankPrint(nBankNo);

		printf(" 탈 퇴 시 킬 번 호 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0) return;
		else if (nNo1 > 10 || ForceReturnEnable(nBankNo, nNo1) == 3)
		{
			printf("\n [ 번 호 정 보 가 없 습 니 다. ]\n");
			printf("    [ 다 시 입 력 하 세 요. ] \n");
		}
		else
		{
			ForceReturnUpdata(nBankNo, nNo1);
			printf(" \n [ 탈 퇴 가 완 료 되 었 습 니 다. ] \n\n");
		}
		return;
	}
}
void Join(int nUserNo)
{
	int nNo1;
	
	while (1)
	{
		BankListPrint();
		
		printf(" 가 입 할 은 행 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0) return;
		else if (nNo1 > 10)
		{
			printf(" [ 은 행 정 보 가 없 습 니 다. ] \n");
			printf("    [ 다 시 입 력 하 세 요. ] \n");
		}
		else if (JoinEnable(nUserNo, nNo1) == 1)
		{
			printf(" [ 해 당 은 행 은 만 원 입 니 다. ]\n");
			printf("     [ 다 시 입 력 하 세 요. ]\n\n");
		}
		else if (JoinEnable(nUserNo, nNo1) == 2)
		{
			printf(" [ 해 당 유 저 는 더 이 상 가 입 할 수 없 습 니 다. ]\n");
			printf("            [ 다 시 입 력 하 세 요. ] \n\n");
		}
		else if (JoinEnable(nUserNo, nNo1) == 3)
		{
			printf("        [ 해 당 은 행 은 만 원 입 니 다. ] \n");
			printf(" [해 당 유 저 는 더 이 상 가 입 할 수 없 습 니 다.] \n");
			printf("	    	[ 다 시 입 력 하 세 요. ] \n\n");
		}
		else
		{
			JoinUpdata(nNo1, nUserNo);
			printf("\n [ 가 입 이 완 료 되 었 습 니 다. ] \n\n");
		}
		return;
	}
}
void Return(int nUserNo)
{
	int nNo1;

	while (1)
	{
		UserPrint(nUserNo);
		
		printf(" 탈 퇴 할 번 호 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0) return;
		else if (nNo1 > 10 || ForceReturnEnable(nUserNo, nNo1) == 3)
		{
			printf("\n [ 번 호 정 보 가 없 습 니 다. ]\n");
			printf("    [ 다 시 입 력 하 세 요. ] \n");
		}
		else
		{
			ReturnUpdata(nNo1, nUserNo);
			printf(" \n [ 탈 퇴 가 완 료 되 었 습 니 다. ] \n\n");
		}
		return;
	}
}

void ForceJoinUpdata(int nBankNo, int nUserNo)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < m_nBankMaxCnt; i++)
	{
		if (m_pBank[i].nBankNo != nBankNo) continue;

		for (int j = 0; j < m_nUserMaxCnt; j++)
		{
			if (m_pUser[j].nUserNo != nUserNo) continue;

			for (int k = 0; k < JOIN_MAX_CNT; k++)
			{
				if (m_pBank[i].nJoinUserNo[k] != -1) continue;

				m_pBank[i].nJoinUserNo[k] = nUserNo;
				m_pBank[i].nJoinCnt++;
				break;
			}
			for (int k = 0; k < JOIN_MAX_CNT; k++)
			{
				if (m_pUser[j].nUserJoinBankNo[k] != -1) continue;

				m_pUser[j].nUserJoinBankNo[k] = nBankNo;
				m_pUser[j].nJoinCnt++;

				m_pUser[j].nUserACNo[k] = rand() % 1000;
				for (int v = 0; v < m_nUserMaxCnt; v++)
				{
					for (int x = 0; x < JOIN_MAX_CNT; x++)
					{
						srand((unsigned int)time(NULL));
						if (m_pUser[v].nUserACNo[x] == m_pUser[j].nUserACNo[k]) continue;

						m_pUser[j].nUserACNo[k] = rand() % 1000;
					}
				}
				break;
			}
			return;
		}
	}
}
void ForceReturnUpdata(int nBankNo, int nUserNo)
{
	for (int i = 0; i < m_nBankMaxCnt; i++)
	{
		if (m_pBank[i].nBankNo != nBankNo) continue;

		for (int j = 0; j < JOIN_MAX_CNT; j++)
		{
			if (m_pBank[i].nBankInfoNo[j] != nUserNo) continue;
			
			for (int k = 0; k < m_nUserMaxCnt; k++)
			{
				if (m_pBank[i].nJoinUserNo[j] != m_pUser[k].nUserNo) continue;

				for (int v = 0; v < JOIN_MAX_CNT; v++)
				{
					if (m_pUser[k].nUserJoinBankNo[v] != nBankNo) continue;

					m_pUser[k].nUserJoinBankNo[v] = -1;
					m_pUser[k].nJoinCnt--;

					m_pBank[i].nJoinUserNo[j] = -1;
					m_pBank[i].nJoinCnt--;
					break;
				}
				return;
			}
		}
	}
}
void JoinUpdata(int nBankNo, int nUserNo)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo != nUserNo) continue;

		for (int j = 0; j < m_nBankMaxCnt; j++)
		{
			if (m_pBank[j].nBankNo != nBankNo) continue;

			for (int k = 0; k < JOIN_MAX_CNT; k++)
			{
				if (m_pUser[i].nUserJoinBankNo[k] != -1) continue;

				m_pUser[i].nUserJoinBankNo[k] = nBankNo;
				m_pUser[i].nJoinCnt++;
				m_pUser[i].nUserACNo[k] = rand() % 1000;
				for (int v = 0; v < m_nUserMaxCnt; v++)
				{
					for (int x = 0; x < JOIN_MAX_CNT; x++)
					{
						srand((unsigned int)time(NULL));
						if (m_pUser[v].nUserACNo[x] == m_pUser[i].nUserACNo[k]) continue;

						m_pUser[i].nUserACNo[k] = rand() % 1000;
					}
				}
				break;
			}
			for (int k = 0; k < JOIN_MAX_CNT; k++)
			{
				if (m_pBank[j].nJoinUserNo[k] != -1) continue;

				m_pBank[j].nJoinUserNo[k] = nUserNo;
				m_pBank[j].nJoinCnt++;
				break;
			}
			return;
		}
	}
}
void ReturnUpdata(int nBankNo, int nUserNo)
{
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo != nUserNo) continue;

		for (int j = 0; j < JOIN_MAX_CNT; j++)
		{
			if (m_pUser[i].nUserInfoNo[j] != nBankNo) continue;

			for (int k = 0; k < m_nBankMaxCnt; k++)
			{
				if (m_pUser[i].nUserJoinBankNo[j] != m_pBank[k].nBankNo) continue;

				for (int v = 0; v < JOIN_MAX_CNT; v++)
				{
					if (m_pBank[k].nJoinUserNo[v] != nUserNo) continue;

					m_pBank[k].nJoinUserNo[v] = -1;
					m_pBank[k].nJoinCnt--;

					m_pUser[i].nUserJoinBankNo[j] = -1;
					m_pUser[i].nJoinCnt--;
					return;
				}
			}
		}
	}
}

int ForceJoinEnable(int nBankNo, int nUserNo)
{
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo != nUserNo) continue;

		for (int j = 0; j < m_nBankMaxCnt; j++)
		{
			if (m_pBank[j].nBankNo != nBankNo) continue;

			if (m_pBank[j].nJoinCnt > 10 && m_pUser[i].nJoinCnt > 10) return 3;

			else if (m_pBank[j].nJoinCnt > 10) return 1;

			else if (m_pUser[i].nJoinCnt > 10) return 2;

			else return 0;
		}
	}
	return 0;
}
int ForceReturnEnable(int nBankNo, int nNo)
{
	for (int j = 0; j < m_nBankMaxCnt; j++)
	{
		if (m_pBank[j].nBankNo != nBankNo) continue;

		for (int k = 0; k < JOIN_MAX_CNT; k++)
		{
			if (m_pBank[j].nBankInfoNo[k] != nNo) continue;
			
			return 0;
		}
		return 3;
	}
	return 0;
}
int JoinEnable(int nUserNo, int nBankNo)
{
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo != nUserNo) continue;

		for (int j = 0; j < m_nBankMaxCnt; j++)
		{
			if (m_pBank[j].nBankNo != nBankNo) continue;

			if (m_pBank[j].nJoinCnt > 10 && m_pUser[i].nJoinCnt > 10) return 3;
			else if (m_pBank[j].nJoinCnt > 10) return 1;
			else if (m_pUser[i].nJoinCnt > 10) return 2;
			else return 0;
		}
	}
	return 0;
}
int ReturnEnable(int nUserNo, int nBankNo)
{
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo != nUserNo) continue;

		for (int j = 0; j < m_nBankMaxCnt; j++)
		{
			if (m_pBank[j].nBankNo != nBankNo) continue;

			for (int k = 0; k < JOIN_MAX_CNT; k++)
			{
				if (m_pUser[i].nUserJoinBankNo[k] != nBankNo) continue;

				return 0;
			}
			return 3;
		}
	}
	return 0;
}

void InMoney(int nUserNo, int nSign)
{
	int nBankNo;
	int nMoney;
	
	while (1)
	{
		UserPrint(nUserNo);

		printf(" 입 금 할 은 행 입 력 : ");
		scanf_s("%d", &nBankNo);
		system("cls");
		if (nBankNo == 0) return;

		InOutMoneyList(nUserNo, nBankNo, nSign);

		printf(" 입 금 할 금 액 입 력 : ");
		scanf_s("%d", &nMoney);
		system("cls");
		if (nMoney == 0) return;
		InMoneyUpdata(nUserNo, nBankNo, nMoney);
		return;
	}
}
void OutMoney(int nUserNo, int nSign)
{
	int nBankNo;
	int nMoney;

	while (1)
	{
		UserPrint(nUserNo);

		printf(" 출 금 할 은 행 입 력 : ");
		scanf_s("%d", &nBankNo);
		system("cls");
		if (nBankNo == 0) return;

		InOutMoneyList(nUserNo, nBankNo, nSign);

		printf(" 출 금 할 금 액 입 력 : ");
		scanf_s("%d", &nMoney);
		system("cls");
		if (nMoney == 0) return;
		OutMoneyUpdata(nUserNo, nBankNo, nMoney);
		return;
	}
}
void InMoneyUpdata(int nUserNo, int nBankNo, int nMoney)
{
	time_t timer;
	struct tm t;
	time(&timer);
	localtime_s(&t ,&timer);
	for (int i = 0; i < m_nBankMaxCnt; i++)
	{
		if (m_pBank[i].nBankNo != nBankNo) continue;

		for (int j = 0; j < m_nUserMaxCnt; j++)
		{
			if (m_pUser[j].nUserNo != nUserNo) continue;

			m_pUser[j].nMoney[i] += nMoney;
			break;
		}
		for (int j = 0; j < ACCOUNT_NUM; j++)
		{
			if (m_pSPInfo[i].nInOutMoney[j] != 0) continue;

			m_pSPInfo[i].nInOutMoney[j] = nMoney;
			m_pSPInfo[i].nSign[m_pSPInfo[i].nSignCnt] = 1; 	
			m_pSPInfo[i].nSignCnt++;
			m_pSPInfo[i].nCnt++;

			m_pSPInfo[i].nHour[j] = t.tm_hour;
			m_pSPInfo[i].nMin[j] = t.tm_min;
			m_pSPInfo[i].nSec[j] = t.tm_sec;
			if (m_pSPInfo[i].nSec[j] < t.tm_min)
				m_pSPInfo[i].nSecCnt++;
			return;
		}
	}
}
void OutMoneyUpdata(int nUserNo, int nBankNo, int nMoney)
{
	time_t timer;
	struct tm t;
	time(&timer);
	localtime_s(&t, &timer);
	for (int i = 0; i < m_nBankMaxCnt; i++)
	{
		if (m_pBank[i].nBankNo != nBankNo) continue;

		for (int j = 0; j < m_nUserMaxCnt; j++)
		{
			if (m_pUser[j].nUserNo != nUserNo) continue;

			m_pUser[j].nMoney[i] -= nMoney;
			break;
		}
		for (int j = 0; j < ACCOUNT_NUM; j++)
		{
			if (m_pSPInfo[i].nInOutMoney[j] != 0) continue;

			m_pSPInfo[i].nInOutMoney[j] = nMoney;
			m_pSPInfo[i].nSign[m_pSPInfo[i].nSignCnt] = 0;
			m_pSPInfo[i].nSignCnt++;
			m_pSPInfo[i].nCnt++;

			m_pSPInfo[i].nHour[j] = t.tm_hour;
			m_pSPInfo[i].nMin[j] = t.tm_min;
			m_pSPInfo[i].nSec[j] = t.tm_sec;
			if (m_pSPInfo[i].nSec[j] < t.tm_sec)
				m_pSPInfo[i].nSecCnt++;
			return;
		}
	}
}
void InOutMoneyList(int nUserNo, int nBankNo, int nSign)
{
	InterestRateUpdata(nUserNo, nBankNo);
	printf("\n======<< 입 금 출 금 >>========================================== \n\n");
	for (int i = 0; i < m_nUserMaxCnt; i++)
	{
		if (m_pUser[i].nUserNo != nUserNo) continue;
		
		for (int j = 0; j < m_nBankMaxCnt; j++)
		{
			if (m_pBank[j].nBankNo != nBankNo) continue;

			printf(" 은 행 이 름 : %s \n", m_pBank[j].sBankName);
			printf(" 유 저 이 름 : %s \n", m_pUser[i].sUserName);
			printf(" 계 좌 번 호 : %d \n", m_pUser[i].nUserACNo[j]);
			printf(" 남 은 금 액 : %.0lf \n", m_pUser[i].nMoney[j]);
			break;
		}

		printf("\n	------<< 입 출 금 내 역 >>-----------------------\n\n");
		printf("		시/분/초	+/-	금액 \n\n");

		for (int k = 0; k < BREAKDOWN; k++)
		{
			SignSwap(nBankNo);
			if (m_pSPInfo[nBankNo - 1].nCnt == 11)
				InOutListSwap(nBankNo - 1);
			if (m_pSPInfo[nBankNo - 1].nInOutMoney[k] == 0)
				printf("		거 래 정 보 없 음 \n\n");
			else if (m_pSPInfo[nBankNo - 1].nSign[k] == 1)
				printf("		 %02d.%02d.%02d    +   %d \n\n", m_pSPInfo[nBankNo - 1].nHour[k], m_pSPInfo[nBankNo - 1].nMin[k], m_pSPInfo[nBankNo - 1].nSec[k], m_pSPInfo[nBankNo - 1].nInOutMoney[k]);
			else
				printf("		 %02d.%02d.%02d    -   %d \n\n", m_pSPInfo[nBankNo - 1].nHour[k], m_pSPInfo[nBankNo - 1].nMin[k], m_pSPInfo[nBankNo - 1].nSec[k], m_pSPInfo[nBankNo - 1].nInOutMoney[k]);
		}
		printf("\n	-------------------------------------------------\n\n");
		break;
	}
	printf("\n================================================================= \n\n");
}
void InOutListSwap(int nBankNo) 
{
	int tmp = 0;
	for (int i = 0; i < ACCOUNT_NUM; i++)
	{
		tmp = m_pSPInfo[nBankNo].nHour[i];
		m_pSPInfo[nBankNo].nHour[i] = m_pSPInfo[nBankNo].nHour[i + 1];
		tmp = 0;
	}
	for (int i = 0; i < ACCOUNT_NUM; i++)
	{
		tmp = m_pSPInfo[nBankNo].nMin[i];
		m_pSPInfo[nBankNo].nMin[i] = m_pSPInfo[nBankNo].nMin[i + 1];
		tmp = 0;
	}
	for (int i = 0; i < ACCOUNT_NUM; i++)
	{
		tmp = m_pSPInfo[nBankNo].nSec[i];
		m_pSPInfo[nBankNo].nSec[i] = m_pSPInfo[nBankNo].nSec[i + 1];
		tmp = 0;
	}
	for (int i = 0; i < ACCOUNT_NUM; i++)
	{
		tmp = m_pSPInfo[nBankNo].nInOutMoney[i];
		m_pSPInfo[nBankNo].nInOutMoney[i] = m_pSPInfo[nBankNo].nInOutMoney[i + 1];
		tmp = 0;
	}
	for (int i = 0; i < ACCOUNT_NUM; i++)
	{
		tmp = m_pSPInfo[nBankNo].nSign[i];
		m_pSPInfo[nBankNo].nSign[i] = m_pSPInfo[nBankNo].nSign[i + 1];
		tmp = 0;
	}
	m_pSPInfo[nBankNo].nCnt--;
	m_pSPInfo[nBankNo].nSignCnt--;
	return;
}
void InterestRateUpdata(int nUserNo, int nBankNo)
{
	int nNo = 0, i = 0;
	i = m_pSPInfo[nBankNo - 1].nSecCnt;
	nNo = m_pSPInfo[nBankNo - 1].nSec[i] - m_pSPInfo[nBankNo - 1].nSec[i - 1];
	if (m_pSPInfo[nBankNo - 1].nSec[i - 1] < m_pSPInfo[nBankNo - 1].nSec[i])
	{
		if (nNo == 0) return;
		else if (nNo > 0)
		{
			for (int j = 0; j < nNo; j++)
			{
				m_pUser[nUserNo - 1].nMoney[nBankNo - 1] += (m_pUser[nUserNo - 1].nMoney[nBankNo - 1] * m_pBank[nBankNo - 1].dInterestRate) / 100;
			}
		}
		else
		{
			nNo *= -1;
			for (int j = 0; j < nNo; j++)
			{
				m_pUser[nUserNo - 1].nMoney[nBankNo - 1] += (m_pUser[nUserNo - 1].nMoney[nBankNo - 1] * m_pBank[nBankNo - 1].dInterestRate) / 100;
			}
		}
		return;
	}
}

bool SignSwap(int nBankNo)
{
	for (int i = 0; i < m_nBankMaxCnt; i++)
	{
		if (m_pBank[i].nBankNo != nBankNo) continue;

		for (int j = 0; j < ACCOUNT_NUM; j++)
		{
			if (m_pSPInfo[i].nInOutMoney[j] != 0) continue;

			if (m_pSPInfo[i].nSign[j] != 0) return true;
			else return false;
		}
	}
	return false;
}
int OutMoneyEnable(int nUserNo, int nBankNo)
{
	 for (int i = 0; i < m_nUserMaxCnt; i++)
	 {
		 return 0;
	 }
	 return 1;
}

void ChangeMainMenu(void)
{
	int nNo;

	while (1)
	{
		printf("\n======<< 수 정 하 기 >>========================================== \n\n");
		printf(" 1. 은 행 수 정 \n\n");
		printf(" 2. 유 저 수 정 \n\n");
		printf(" 0. 뒤 로 가 기 \n\n");
		printf("================================================================= \n\n");
		printf(" 무 엇 을 할 지 입 력 : ");
		scanf_s("%d", &nNo);
		system("cls");

		if (nNo == 0) return;
		else if (nNo == 1)
		{
			BankChange();
			return;
		}
		else if (nNo == 2)
		{
			UserChange();
			return;
		}
		else
		{
			printf("\n [ 번 호 정 보 가 없 습 니 다. ]\n");
			printf("    [ 다 시 입 력 하 세 요. ]\n\n");
		}
	}
}
void BankChange(void)
{	
	int nNo;
	int nNo1;

	while (1)
	{
		BankListPrint();

		printf(" 수 정 할 은 행 입 력 : ");
		scanf_s("%d", &nNo);

		if (nNo != 0) break;
		else if (nNo == 0) return;
		else
		{
			printf("\n [ 은 행 정 보 가 없 습 니 다. ] \n");
			printf("    [ 다 시 입 력 하 세 요. ] \n\n");
		}
	}

	printf("\n======<< 수 정 하 기 >>==========================================\n\n");
	printf(" 1. 은 행 이 름 수 정 \n\n");
	printf(" 2. 은 행 금 리 수 정 \n\n");
	printf("=================================================================\n\n");
	printf(" 무 엇 을 수 정 할 지 입 력 : ");
	scanf_s("%d", &nNo1);
	system("cls");

	if (nNo1 == 0) return;
	else if (nNo1 == 1)
	{
		char sName[BANK_NAME];
		printf("======<< 은 행 수 정 >>========================================== \n\n");
		printf(" 은 행 이 름 입 력 : ");
		scanf_s("%s", &sName, BANK_NAME);
		
		printf("================================================================= \n\n");

		for (int i = 0; i < m_nBankMaxCnt; i++)
		{
			if (m_pBank[i].nBankNo != nNo) continue;

			memcpy(m_pBank[i].sBankName, sName, sizeof(sName));
		}
	}
	else if (nNo1 == 2)
	{
		double dInterest;

		printf("======<< 은 행 수 정 >>========================================== \n\n");
		printf(" 은 행 금 리 입 력 : ");
		scanf_s("%lf", &dInterest);
		printf("================================================================= \n\n");
		for (int i = 0; i < m_nBankMaxCnt; i++)
		{
			if (m_pBank[i].nBankNo != nNo) continue;

			m_pBank[i].dInterestRate = dInterest;
		}
	}
	else
	{
		printf("\n [ 번 호 정 보 가 없 습 니 다.] \n");
		printf("    [ 다 시 입 력 하 세 요, ] \n\n");
	}
}
void UserChange(void)
{
	int nNo;
	int nNo1;
	char sName[USER_NAME];
	while (1)
	{
		UserListPrint();
		printf(" 수 정 할 유 저 입 력 : ");
		scanf_s("%d", &nNo);
		system("cls");
		if (nNo == 0) return;

		UserPrint(nNo);

		printf("\n======<< 수 정 하 기 >>==========================================\n\n");
		printf(" 1. 이 름 수 정 \n\n");
		printf(" 0. 뒤 로 가 기 \n\n");
		printf("=================================================================\n\n");
		printf(" 무 엇 을 수 정 할 지 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0) return;
		switch (nNo1)
		{
			case 1: 
			{
				printf(" 수 정 이 름 입 력 : ");
				scanf_s("%s", &sName, USER_NAME);
				memcpy(m_pUser[nNo - 1].sUserName, sName, sizeof(sName));
			}
		}
	}
}

void AddMainMenu(void)
{
	int nNo;

	while (1)
	{
		printf("\n======<< 추 가 하 기 >>========================================== \n\n");
		printf(" 1. 은 행 추 가 \n\n");
		printf(" 2. 유 저 추 가 \n\n");
		printf(" 0. 뒤 로 가 기 \n\n");
		printf("================================================================= \n\n");
		printf(" 무 엇 을 할 지 입 력 : ");
		scanf_s("%d", &nNo);
		system("cls");

		if (nNo == 0) return;
		else if (nNo == 1)
		{
			BankAdd();
			return;
		}
		else if (nNo == 2)
		{
			UserAdd();
			return;
		}
		else
		{
			printf(" [ 정 보 가 없 습 니 다. ]\n");
			printf(" [ 다 시 입 력 하 세 요. ]\n\n");
		}
	}
}
void BankAdd(void)
{
	char sName[BANK_NAME];
	double dInterestRate;

	while (1)
	{
		BankListPrint();

		printf(" 은 행 이 름 입 력 : ");
		scanf_s("%s", &sName, BANK_NAME);
		printf(" 은 행 금 리 입 력 : ");
		scanf_s("%lf", &dInterestRate);
		system("cls");

		m_nBankMaxCnt++;
		m_pBank[m_nBankMaxCnt - 1].nBankNo = m_nBankMaxCnt;
		memcpy(m_pBank[m_nBankMaxCnt - 1].sBankName, sName, sizeof(sName));
		m_pBank[m_nBankMaxCnt - 1].dInterestRate = dInterestRate;
		return;
	}
}
void UserAdd(void)
{
	char sName[USER_NAME];
	while (1)
	{
		printf(" 유 저 이 름 입 력 : ");
		scanf_s("%s", &sName, USER_NAME);

		m_nUserMaxCnt++;
		m_pUser[m_nUserMaxCnt - 1].nUserNo = m_nUserMaxCnt;
		memcpy(m_pUser[m_nUserMaxCnt - 1].sUserName, sName, sizeof(sName));
		
		return;
	}
}