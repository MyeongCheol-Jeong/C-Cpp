#include <iostream>
#include <Windows.h>

#define RENT_MAX_CNT 10
#define USER_NAME 10
#define USER_PHONE 20
#define BOOK_TITLE 100
#define BOOK_PUBLISHER 30
#define BOOK_MAX_CNT 7

struct Player
{
	int nUserNum;
	char sUserName[USER_NAME];
	char sUserPhoneNum[USER_PHONE];
	int nUserRentCnt = 0;	// 대여한 권 수
	int nRentBookNum[RENT_MAX_CNT]; // 대여 책 번호
	int nRentInfoNo[RENT_MAX_CNT];
};

struct Library
{
	int nBookNum;
	char sBookTitle[BOOK_TITLE];	// 책 제목
	char sBookPublsher[BOOK_PUBLISHER];	// 책 출판사 
	int nBookMaxCnt = 7;	// 총 수량
	int nBookRentCnt;	// 대여 수량
	int nRentUserNum[BOOK_MAX_CNT]; // 대여한 유저 번호
	int nBookInfoNo[BOOK_MAX_CNT];
};

struct Player m_pUser[100];
struct Library m_pBook[100];

void UserListPrint(void);		// 유저 리스트
void UserMainMenu(void);		// 유저 메인메뉴
void UserSubMenu(int nNo);		// 유저 상세 메뉴
void UserPrint(int nNo);

bool UserCheck(int nNo);		// 유저 대여횟수
bool UserRentEnable(int nNo);	// 유저 대여 가능한지 판별

void BookListPrint(void);		// 책 리스트 확인
void BookMainMenu(void);
void BookSubMenu(int nNo);
void BookPrint(int nNo);

bool BookCheck(int nBookNo);	// 책 대여 횟수
bool BookRentEnable(int nNo);	// 책 대여 가능한지 판별

void BookRent(int nUserNo3);
void RentUpdata(int nUserNo, int nBookNo);

void BookReturn(int nNo);
void BookReturnUpdata(int nUserNo, int nBookNo);
void UserReturnEnable(int nNo);					

void BookForceReturn(void);
void BookForceReturnUpdata();

void AddMainMenu(void);
void UserAdd(void);
void BookAdd(void);

void ChangeMainMenu(void);
void UserChange(void);
void BookChange(void);


int m_nUserCnt = 7;	// 유저 수
int m_nBookCnt = 4;   // 책 수

int main()
{
			// 번호, 이름, 전화번호, 대여권수, 대여한책번호
	m_pUser[0] = { 1, "양소정", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	m_pUser[1] = { 2, "임효상", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	m_pUser[2] = { 3, "정명철", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	m_pUser[3] = { 4, "김대현", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	m_pUser[4] = { 5, "박정범", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	m_pUser[5] = { 6, "이병선", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	m_pUser[6] = { 7, "장소현", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
			// 번호, 책제목, 총수량, 대여수량, 대여한유저번호
	m_pBook[0] = { 1, "C 언어의 정석", "AAA", 7, 0, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7 };
	m_pBook[1] = { 2, "C++의 정석", "AAA",  7, 0, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7 };
	m_pBook[2] = { 3, "JAVA의 정석", "AAA", 7, 0, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7 };
	m_pBook[3] = { 4, "C# 의 정석", "AAA", 7, 0, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7 };

	while (true)
	{
		int nNo1 = 0;			// 도서 목록과 유저 목록 중 선택 변수

		printf("\n======<< L I S T >>============================================== \n\n");
		printf("	1. 유 저 목 록 \n\n");
		printf("	2. 도 서 목 록 \n\n");
		printf("	3. 추 가 하 기 \n\n");
		printf("	4. 수 정 하 기 \n\n");
		printf("	0.  끝 내 기\n\n");
		printf("\n================================================================= \n\n");
		printf(" 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");
		if (nNo1 == 0)
			return 0;

		switch (nNo1)
		{
			case 1:	// 유 저 목 록
			{
				UserMainMenu();
				break;
			}
			case 2: // 도 서 목 록
			{
				BookMainMenu();
				break;
			}
			case 3:		// 추 가 하 기
			{
				AddMainMenu();
				break;
			}
			case 4:	// 수정하기
			{
				ChangeMainMenu();
				break;
			}
		} // 큰 스위치 문
	} // 큰 와일 문
	return 0;
}

void UserListPrint(void)
{
	printf("\n======<< 유 저 목 록 >>========================================== \n\n");
	printf("	0. 뒤 로 가 기 \n\n");
	printf(" 번 호 |  이  름  |   전 화 번 호   |  대 여 책 수 \n\n");
	for (int i = 0; i < m_nUserCnt; i++)
	{
		printf("   %d   |  %s  |  %s  |      %d \n\n", m_pUser[i].nUserNum, m_pUser[i].sUserName, m_pUser[i].sUserPhoneNum, m_pUser[i].nUserRentCnt);
	}
	printf("\n================================================================= \n\n");
}

void UserMainMenu(void)
{
	int nUserNo1 = 0;
	
	while (1)
	{
		UserListPrint();

		printf(" 유 저 의 번 호 를 입 력 하 세 요 : ");
		scanf_s("%d", &nUserNo1);
		system("cls");

		if (nUserNo1 != 0)
		{
			if (UserCheck(nUserNo1) == true)
				UserSubMenu(nUserNo1);
			else
				printf(" 입 력 한 유 저 가 없 습 니 다. \n");
		}
		else
			return;
	}
}

void UserSubMenu(int nUserNo2)
{
	UserPrint(nUserNo2);

	int nNo1 = 0;

	while (true)
	{

		printf(" 1. 대 여 하 기		2. 반 납 하 기		0. 뒤 로 가 기 \n\n");
		printf(" 무 엇 을 할 지 입 력 하 세 요 : ");
		scanf_s("%d", &nNo1);
		system("cls");
		if (nNo1 == 0)
			break;
		if (nNo1 == 1 || nNo1 == 2)
		{
			switch (nNo1)
			{
				case 1:		// 대 여 하 기
				{
					BookRent(nUserNo2);
					break;
				}
				case 2:		// 반 납 하 기
				{
					BookReturn(nUserNo2);
					break;
				}
			} 
		}
		else
			printf(" [ 정 보 가 없 습 니 다. 다 시 선 택 해 주 세 요. ]\n\n");
		UserPrint(nUserNo2);
	}
}

void UserPrint(int nNo)
{
	printf("\n======<< 유 저 정 보 >>========================================== \n\n");
	for (int i = 0; i < m_nUserCnt; i++)
	{
		if (nNo == m_pUser[i].nUserNum)
		{
			printf("	유 저 번 호 : %d \n\n", m_pUser[i].nUserNum);
			printf("	유 저 이 름 : %s \n\n", m_pUser[i].sUserName);
			printf("   휴 대 폰 번 호 : %s \n\n", m_pUser[i].sUserPhoneNum);
			printf("	대 여 권 수 : %d \n\n\n", m_pUser[i].nUserRentCnt);
			printf("	=======<< 대 여 정 보 >>======= \n\n");
			for (int j = 0; j < RENT_MAX_CNT; j++)
			{
				if (m_pUser[i].nRentBookNum[j] == -1)
				{
					printf("	[ %2d ]. 대 여 정 보 없 음.\n\n", m_pUser[i].nRentInfoNo[j]);
				}
				else
				{
					bool BookCheck = false;
					for (int k = 0; k < RENT_MAX_CNT; k++)
					{
						if (m_pBook[k].nBookNum == m_pUser[i].nRentBookNum[j])
						{
							printf("	[ %2d ].    %d	%s \n\n", m_pUser[i].nRentInfoNo[j], m_pBook[k].nBookNum, m_pBook[k].sBookTitle);
							BookCheck = true;
							break;
						}
					}
					for (int k = 0; k < RENT_MAX_CNT; k++)
						if (!BookCheck)
							printf("	[%2d]. 대여 정보는 존재 하나 책 정보 찾을 수 없음.\n\n", m_pUser[i].nRentInfoNo[k]);
				}
			} // 큰 for 문
			printf("	=============================== \n\n\n");
		} // 큰 if 문
	} // 큰 for 문
	printf("================================================================= \n\n\n");
}

bool UserCheck(int nNo)
{
	for (int i = 0; i < m_nUserCnt; i++)
	{
		if (m_pUser[i].nUserNum == nNo)
			return true;
	}
	return false;
}

bool UserRentEnable(int nNo)
{
	for (int i = 0; i < m_nUserCnt; i++)
	{
		if (m_pUser[i].nUserNum != nNo) continue;

		if (m_pUser[i].nUserRentCnt < RENT_MAX_CNT)
			return true;
	}
	return false;
}

void BookListPrint()
{
	printf("\n======<< 도 서 목 록 >>========================================== \n\n");
	printf(" 책 번 호  |      책 이 름      |  총 수 량  |  대 여 수 \n\n");
	printf("     [ 0. 뒤 로 가 기 ] \n\n");
	for (int i = 0; i < m_nBookCnt; i++)
	{
		if (m_pBook[i].nBookNum <= 0) continue;
		printf("     %d     |   %s	|      %d     |      %d   \n\n", m_pBook[i].nBookNum, m_pBook[i].sBookTitle, m_pBook[i].nBookMaxCnt, m_pBook[i].nBookRentCnt);
	} 
	printf("================================================================= \n\n\n");

	return;
}

void BookMainMenu(void)
{
	int nBookNo;

	while (true)
	{
		BookListPrint();

		printf(" 책 의 번 호 를 입 력 하 세 요 : ");
		scanf_s("%d", &nBookNo);
		system("cls");

		if (nBookNo == 0)
			return;
		if (!BookCheck(nBookNo))
		{
			printf(" [ 없 는 책 번 호 입 니 다 . ]\n");
			printf(" [ 다 시 입 력 해 주 세 요 . ]\n");
		}
		else
			BookSubMenu(nBookNo);
	}
}

void BookSubMenu(int nNo)
{
	int nNo1;
	while (true)
	{
		BookPrint(nNo);
		printf(" 1. 강 제 반 납 \n\n");
		printf(" 2. 보 류 \n\n");
		printf(" 무 엇 을 할 지 입 력 : ");
		scanf_s("%d", &nNo1);
		system("cls");

		if (nNo1 == 0)
			return;
		switch (nNo1)
		{
			case 1:		// 강 제 반 납
			{
				BookForceReturn();
				break;
			}
			case 2:     // 보 류
			{
				break;
			}
		}
	}
	return;
}

void BookPrint(int nNo)
{
	printf("\n======<< 도 서 목 록 >>========================================== \n\n");
	printf("     [ 0. 뒤 로 가 기 ] \n\n");
	printf(" 책 번 호  |      책 이 름      |  총 수 량  |  대 여 수 \n\n");

	for (int i = 0; i < m_nBookCnt; i++)
	{
		if (m_pBook[i].nBookNum != nNo) continue;
		printf("     %d     |   %s	|      %d     |      %d   \n\n", m_pBook[i].nBookNum, m_pBook[i].sBookTitle, m_pBook[i].nBookMaxCnt, m_pBook[i].nBookRentCnt);
	}
	printf("\n----------------------------------------------------------------- \n\n");
	printf(" 번 호 | 유 저 번 호 | 유 저 이 름 \n\n");
	for (int i = 0; i < m_nBookCnt; i++)
	{
		if (m_pBook[i].nBookNum != nNo) continue;
		
		for (int j = 0; j < m_nUserCnt; j++)
		{
			for (int k = 0; k < BOOK_MAX_CNT; k++)
			{
				if (m_pBook[i].nRentUserNum[k] != m_pUser[j].nUserNum) continue;

				for (int v = 0; v < m_pBook[i].nBookRentCnt; v++)
				{
					printf("    [%2d]   |    %d    |    %s  \n\n", m_pBook[i].nBookInfoNo[v], m_pUser[j].nUserNum, m_pUser[j].sUserName);
				}
				break;
			}
			break;
		}
		break;
	}
	printf("================================================================= \n\n\n");

	return;
}

bool BookRentEnable(int nNo)
{
	bool Bcheck = false;
	for (int i = 0; i < m_nBookCnt; i++)
	{
		if (m_pBook[i].nBookNum != nNo) continue;

		if (m_pBook[i].nBookMaxCnt > m_pBook[i].nBookRentCnt)
			return true;
	}
	return false;
}

bool BookCheck(int nBookNo)
{
	bool Bcheck = false;
	for (int i = 0; i < m_nBookCnt; i++)
	{
		if (m_pBook[i].nBookNum == nBookNo)
			return true;
	}
	return false;
}

void BookRent(int nUserNo3)
{
	while (1)
	{
		if (UserRentEnable(nUserNo3) == false)
		{
			printf(" [ 해 당  유 저 는  더 이 상  대 여  할 수 없 습 니 다. ] \n");
			break;
		}
		printf("	<<< 대 여 하 기 >>>\n\n");
		BookListPrint();
		printf(" 책  번 호 를  입 력 하 세 요. ( 0 - 뒤 로 가 기 ) ! \n");
		
		int nBookNo = 0;
		scanf_s("%d", &nBookNo);
		system("cls");

		if (nBookNo == 0)
			break;
		if (BookCheck(nBookNo) == true)
		{
			if (BookRentEnable(nBookNo) == true)
			{
				RentUpdata(nUserNo3, nBookNo);
				printf("\n	<< 대여 정보 수정 완료 >> \n\n");
			}
			else
				printf(" [ 입 력 한 책 의 잔 여 수 량 이 부 족 합 니 다. ] \n");
		}
		else
			printf(" [ 해 당 책 번 호 에 대 한 정 보 가 없 습 니 다. ] \n");
		printf("       [ 다 시 입 력 하 여 주 십 시 오. ]\n");
	} // 와일 문
}

void RentUpdata(int nUserNo, int nBookNo)
{
	for (int i = 0; i < m_nUserCnt; i++)
	{
		if (m_pUser[i].nUserNum != nUserNo) continue;
		
		bool bcheck = false;
		for (int j = 0; j < m_nBookCnt; j++)
		{
			if (m_pBook[j].nBookNum != nBookNo) continue;

			for (int k = 0; k < RENT_MAX_CNT; k++)
			{
				if (m_pUser[i].nRentBookNum[k] != -1) continue;

				m_pUser[i].nRentBookNum[k] = m_pBook[j].nBookNum;
				m_pUser[i].nUserRentCnt++;
				break;
			}

			for (int k = 0; k < RENT_MAX_CNT; k++)
			{
				if (m_pBook[j].nRentUserNum[k] != -1) continue;

				m_pBook[j].nRentUserNum[k] = m_pUser[i].nUserNum;
				m_pBook[j].nBookRentCnt++;
				break;
			}
			bcheck = true;
			break;
		}

		if (bcheck)
			break;
	}
}

void BookReturn(int nNo)	// 책 반납
{
	int nCnt = 0;
	int nNo1 = 0;
	while (1)
	{
		for (int i = 0; i < RENT_MAX_CNT; i++)
		{
			if (m_pUser[nNo].nRentBookNum[i] != -1) continue;

			nCnt++;
			break;
		}
		if (nCnt == 0)
		{
			printf("\n        [ 해 당 유 저 는 반 납 할 책 이 없 습 니 다. ] \n\n");
			break;
		}
		UserPrint(nNo);
		printf("\n======<< 반 납 하 기 >>========================================== \n\n");
		printf("   반 납 할 번 호 입 력 : ");
		scanf_s("%d", &nNo1);
		
		if (nNo1 == 0)
			return;
		system("cls");
		BookReturnUpdata(nNo, nNo1);
	}
	return;
}

void BookReturnUpdata(int nUserNo, int nRentNo)
{
	for (int i = 0; i < m_nUserCnt; i++)
	{
		if (m_pUser[i].nUserNum != nUserNo) continue;

		for (int j = 0; j < RENT_MAX_CNT; j++)
		{
			if (m_pUser[i].nRentInfoNo[j] != nRentNo) continue;

			for (int k = 0; k < m_nBookCnt; k++)
			{
				if (m_pBook[k].nBookNum != m_pUser[i].nRentBookNum[j]) continue;

				for (int v = 0; v < RENT_MAX_CNT; v++)
				{
					if (m_pBook[k].nRentUserNum[v] != nUserNo) continue;

					m_pUser[i].nRentBookNum[j] = -1;
					m_pUser[i].nUserRentCnt--;

					m_pBook[k].nRentUserNum[v] = -1;
					m_pBook[k].nBookRentCnt--;
					break;
				}
			}
		}
	}
}

void UserReturnEnable(int nNo)
{
	
}

void BookForceReturn(void)
{
	int nUserNo2;
	int nReturnNo;

	while (1)
	{
		printf("\n 유 저 를 입 력 해 주 세 요 : ");
		scanf_s("%d", &nUserNo2);
		system("cls");

		UserPrint(nUserNo2);
		printf(" 반 납 할 책 입 력 : ");
		scanf_s("%d", &nReturnNo);

		BookForceReturnUpdata();
		break;
	}
}

void BookForceReturnUpdata()
{

}

void AddMainMenu(void)
{
	int nAdd;
	printf("\n======<< 추 가 하 기 >>========================================== \n\n");
	printf("	1. 유 저 추 가 \n\n");
	printf("	2. 도 서 추 가 \n\n");
	printf("	0. 뒤 로 가 기\n\n");
	printf("\n================================================================= \n\n");
	printf(" 무 엇 을 추 가 할 지 입 력 : ");
	scanf_s("%d", &nAdd);
	system("cls");
	if (nAdd == 0)
		return;

	switch (nAdd)
	{
		case 1:
		{
			UserAdd();
			break;
		}
		case 2:
		{
			BookAdd();
			break;
		}
	}
}

void UserAdd(void)
{
	UserListPrint();

	int nNo = 0;
	char sName[USER_NAME];
	char sPhoneNo[USER_PHONE];
	
	printf("\n 번 호 |  이  름  |   전 화 번 호 \n\n");
	printf("================================================================= \n\n\n");
	printf(" 번 호 : ");
	scanf_s("%d", &nNo);
	if (nNo == 0)
	{
		system("cls");
		return;
	}
	printf(" 이 름 : ");
	scanf_s("%s", &sName, USER_NAME);
	printf(" 전 화 번 호 : ");
	scanf_s("%s", &sPhoneNo, USER_PHONE);

	m_nUserCnt++;
	m_pUser[m_nUserCnt - 1] = { 1, "ㅇㅇㅇ", "010-0000-0000", 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 , 1};
	m_pUser[m_nUserCnt - 1].nUserNum = nNo;
	memcpy(m_pUser[m_nUserCnt - 1].sUserName, sName, sizeof(sName));
 	memcpy(m_pUser[m_nUserCnt - 1].sUserPhoneNum, sPhoneNo, sizeof(sPhoneNo));
	system("cls");
	printf("\n      [ 추 가 완 료 ]\n\n");
}

void BookAdd(void)
{
	BookListPrint();

	int nNo;
	char sName[BOOK_TITLE];
	int nMaxCnt;
	
	printf("\n 책 번 호  |      책 이 름      |  총 수 량  \n\n");
	printf("================================================================= \n\n\n");
	printf(" 책 번 호 : ");
	scanf_s("%d", &nNo);
	if (nNo == 0)
	{
		system("cls");
		return;
	}
	printf(" 책 이 름 : ");
	scanf_s("%s", &sName, BOOK_TITLE);
	printf(" 총 수 량 : ");
	scanf_s("%d", &nMaxCnt);

	m_nBookCnt++;
	m_pBook[m_nBookCnt - 1] = { 1, "ㅇㅇㅇㅇ", "ㅇㅇㅇㅇ", 5, 0, -1, -1, -1, -1, -1, -1, -1 };
	m_pBook[m_nBookCnt - 1].nBookNum = nNo;
	memcpy(m_pBook[m_nBookCnt - 1].sBookTitle, sName, sizeof(sName));
	m_pBook[m_nBookCnt - 1].nBookMaxCnt = nMaxCnt;
	m_pBook[m_nBookCnt - 1].nBookRentCnt = 0;
	system("cls");
	printf("\n      [ 추 가 완 료 ]\n\n");
}

void ChangeMainMenu(void)
{
	int nChange;

	printf("\n======<< 수 정 하 기 >>========================================== \n\n");
	printf("	 1. 유 저 수 정\n\n");
	printf("	 2. 도 서 수 정\n\n");
	printf("	 0. 뒤 로 가 기\n\n");
	printf("\n================================================================= \n\n");
	printf(" 무 엇 을 할 지 입 력 : ");
	scanf_s("%d", &nChange);
	system("cls");

	if (nChange == 0) return;

	switch (nChange)
	{
		case 1:		// 유 저 수 정 
		{
			UserChange();
			break;
		}
		case 2:		// 책 수 정 
		{
			BookChange();
			break;
		}
	}
}

void UserChange(void)
{
	int nNo1;
	int nNo2;
	int nNo3;
	char sName[USER_NAME];
	char sPhoneNo[USER_PHONE];
	
	while (1)
	{
		UserListPrint();
	
		printf(" 수 정 할 유 저 선 택 : ");
		scanf_s("%d", &nNo1);
	
		if (nNo1 != 0)
		{
			if (UserCheck(nNo1) == true)
				break;
			else
				printf(" 입 력 한 유 저 가 없 습 니 다. \n");
			printf(" 다 시 입 력 해 주 세 요. \n");
		}
	}
	system("cls");

	printf("\n======<< 수 정 하 기 >>========================================== \n\n");
	
	UserPrint(nNo1);

	printf("     0.   뒤 로 가 기 \n\n");
	printf("     1.   번 호 수 정 \n\n");
	printf("     2.   이 름 수 정 \n\n");
	printf("     3. 전 화 번 호 수 정 \n\n");
	printf("\n================================================================= \n\n");
	printf("   무 엇 을 수 정 할 지 선 택 : ");
	scanf_s("%d", &nNo2);
	if (nNo2 == 0)
		return;
	system("cls");

	switch (nNo2)
	{
		case 1: // 번 호 수 정
		{
			printf("\n======<< 번 호 수 정 >>==========================================\n\n");
			printf("\n  수 정 번 호 입 력 : ");
			scanf_s("%d", &nNo3);
			for (int i = 0; i < m_nUserCnt; i++)
			{
				if (m_pUser[i].nUserNum != nNo1) continue;

				m_pUser[i].nUserNum = nNo3;
				break;
			}
			system("cls");
			printf(" [ 수 정 이 완 료 되 었 습 니 다. ]\n");
			break;
		}
		case 2: // 이 름 수 정
		{
			printf("\n======<< 이 름 수 정 >>==========================================\n\n");
			printf(" 수 정 이 름 입 력 : ");
			scanf_s("%s", sName, USER_NAME);
			for (int i = 0; i < m_nUserCnt; i++)
			{
				if (m_pUser[i].nUserNum != nNo1) continue;

				memcpy(m_pUser[i].sUserName, sName, sizeof(sName));
				break;
			}
			system("cls");
			printf(" [ 수 정 이 완 료 되 었 습 니 다. ]\n");
			break;
		}
		case 3: // 전 화 번 호 수 정
		{
			printf("\n======<< 전 화 번 호 수 정 >>====================================\n\n");
			printf(" 수 정 전 화 번 호 입 력 : ");										
			scanf_s("%s", sPhoneNo, USER_PHONE);
			for (int i = 0; i < m_nUserCnt; i++)
			{
				if (m_pUser[i].nUserNum != nNo1) continue;

				memcpy(m_pUser[i].sUserPhoneNum, sPhoneNo, sizeof(sPhoneNo));
				break;
			}
			system("cls");
			printf(" [ 수 정 이 완 료 되 었 습 니 다. ]\n");
			break;
		}
	} // 큰 스위치 문
}

void BookChange(void)
{
	BookListPrint();
	
	int nNo1;
	int nNo2;
	int nBookNo;
	char sName[BOOK_TITLE];
	int nBookMaxCnt;

	while (1)
	{
		printf(" 수 정 할 책 번 호 입 력 : ");
		scanf_s("%d", &nNo1);
		
		if (nNo1 != 0)
		{
			if (UserCheck(nNo1) == true)
				break;
			else
				printf(" [ 입 력 한 책 이 없 습 니 다. ] \n");
			printf(" [ 다 시 입 력 해 주 세 요. ] \n");
		}
	}
	system("cls");

	printf("\n======<< 수 정 하 기 >>========================================== \n\n");
	
	BookPrint(nNo1);

	printf("   0.   뒤 로 가 기 \n\n");
	printf("   1.  책 번 호 수 정 \n\n");
	printf("   2.  책 이 름 수 정 \n\n");
	printf("   3. 책 총 수 량 수 정\n\n");
	printf("\n================================================================= \n\n");
	printf(" 무 엇 을 할 지 입 력 : ");
	scanf_s("%d", &nNo2);
	if (nNo2 == 0)
		return;
	system("cls");

	switch (nNo2)
	{
		case 1:	// 책 번 호 수 정
		{
			printf("\n======<< 번 호 수 정 >>==========================================\n\n");
			printf(" 수 정 번 호 입 력 : ");
			scanf_s("%d", &nBookNo);
			for (int i = 0; i < m_nBookCnt; i++)
			{
				if (m_pBook[i].nBookNum != nNo1) continue;

				m_pBook[i].nBookNum = nBookNo;
				break;
			}
			system("cls");
			printf(" [ 수 정 이 완 료 되 었 습 니 다. ]\n");
			break;
		}
		case 2:	// 책 이 름 수 정
		{
			printf("\n======<< 이 름 수 정 >>==========================================\n\n");
			printf(" 수 정 이 름 입 력 : ");
			scanf_s("%s", sName, BOOK_TITLE);
			for (int i = 0; i < m_nBookCnt; i++)
			{
				if (m_pBook[i].nBookNum != nNo1) continue;

				memcpy(m_pBook[i].sBookTitle, sName, sizeof(sName));
				break;
			}
			system("cls");
			printf(" [ 수 정 이 완 료 되 었 습 니 다. ]\n");
			break;
		}
		case 3:
		{
			printf("\n======<< 총 수 량 수 정 >>=======================================\n\n");
			printf(" 수 정 번 호 입 력 : ");												// 뒤에꺼
			scanf_s("%d", &nBookMaxCnt);
			for (int i = 0; i < m_nBookCnt; i++)
			{
				if (m_pBook[i].nBookNum != nNo1) continue;

				m_pBook[i].nBookNum = nBookMaxCnt;
				break;
			}
			system("cls");
			printf(" [ 수 정 이 완 료 되 었 습 니 다. ]\n");
			break;
		}
	}
}