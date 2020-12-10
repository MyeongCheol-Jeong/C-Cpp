#include <iostream>
#include <time.h>
#include <Windows.h>

#define MAX_CNT 10

using namespace std;

void Process(int);	// 플래이어 입력과 스트라이크와 볼의 수를 체크
void Computer(int[], int); // 컴퓨터에게 난수 입력
void Player(int[], int); // 플레이어가 수를 입력
void StrkBlCheck(int[], int[], int); // 스트라이크와 볼의 개수를 체크


bool m_bisExit = false; // 게임 종료 판단 변수

int m_nComputerCnt; // 컴퓨터에게 난수가 입력이 제대로 된지 확인하는 카운트 변수
int m_nPlayerCnt; // 플레이어가 제대로 수를 입력했는지 확인하는 카운트 변수

int m_nStrike; // 스트라이크의 수를 출력하기 위한 변수
int m_nBall; // 볼의 수를 출력하기 위한 변수
int m_nCnt; // 몇 번째 문답 중 인지 알려주기 위한 변수

int main() {

	while (1) {
		m_bisExit = false;
		m_nComputerCnt = 0;
		m_nPlayerCnt = 0;

		m_nStrike = 0;
		m_nBall = 0;
		m_nCnt = 1;

		int nSelectNo = -1; // 몇 번을 골랐는지 판별하기 위한 변수

		cout << "========<< BASE BALL GAME >>========" << endl;
		for (int i = 1; i <= MAX_CNT; i++) {
			if (i >= 10) cout << "        " << i << ".  " << i << " BASE BALL" << endl;
			else cout << "         " << i << ".   " << i << " BASE BALL" << endl;
		}
		cout << "         0.   GAME EXIT" << endl;
		cout << "================================" << endl;

		cin >> nSelectNo; 
		system("cls"); // 콘솔창을 깔끔하게 지우는 Windows.h 함수

		if (nSelectNo == 0) return 0;	// 0. 게임 메뉴로 나가는 수를 입력하여 메인 함수가 종료되어 프로그램 종료
		else if (nSelectNo > 0 || nSelectNo <= 11) Process(nSelectNo); // 선택 메뉴얼에 있는 수를 입력하여 처리함수로 이동
		else cout << "NOT FOUND NUMBER" << endl << "PLAESE RE-ENTER" << endl << endl; // 선택 메뉴얼에 없는 수를 입력하여 다시 입력 출력
	
	}
}
void Process(int nNo) {
	int* m_nComputer = new int[nNo] {-1, };	// 동적할당을 하여 입력한 수에 맞게 배열 크기 생성
	int* m_nPlayer = new int[nNo] {-1, };		// 동적할당을 하여 입력한 수에 맞게 배열 크기 생성

	Computer(m_nComputer, nNo);	// 컴퓨터 배열에 난수 입력하는 함수 이동

	while (!m_bisExit) { // m_bisExit 변수가 true값이 들어올 때까지 무한 반복
		Player(m_nPlayer, nNo);  // 플레이어 수 입력
		StrkBlCheck(m_nComputer, m_nPlayer, nNo); // 스트라이크와 볼의 개수 체크 후 출력
	}

	delete[] m_nComputer; // 동적할당한 배열 삭제
	delete[] m_nPlayer;		 // 동적할당한 배열 삭제

	return; 

}

void Computer(int  m_nComputer[], int nNo) {
	srand((int)time(NULL)); // 난수 입력의 기준을 현재 시간으로 잡음

	for (int i = 0; i < nNo; i++)
	{
		m_nComputer[i] = rand() % 10; // 0~9 난수 생성
	}
	for (int i = 0; i < nNo; i++) {
		for (int j = nNo; j > nNo; j--) {
			if (m_nComputer[i] != m_nComputer[j]) { // 난수의 중복 체크
				m_nComputerCnt++; 
			}
		}
	}
	cout << "ENTERING COMPUTER...." << endl; // 컴퓨터 입력 중...

	cout << "COMPUTER INPUT COMPLETE!!" << endl; // 컴퓨터 입력 완료!!
}

void Player(int m_nPlayer[], int nNo) {

	cout << "GAME STOP : -1" << endl; // 게임을 도중에 멈추는 방법
	while (1)
	{

		cout << "ENTER " << nNo << " NUMBER : "; // 수 입력 : 

		for (int i = 0; i < nNo; i++) {
			cin >> m_nPlayer[i];

			if (m_nPlayer[i] == -1) { // 게임을 멈추는지 안멈추는지 판별
				m_bisExit = true; 
				system("cls");
				return;
			}
			if (m_nPlayer[i] > 9 || m_nPlayer[i] < 0) { // 0~9 사이의 수를 입력했는지 체크
				cout << "ONLY NUMBER FROM 0 ~ 9 CAN BE USED" << endl; // 0~9 사이의 수만 사용할 수 있다.
			}
			
		}
		
		for (int i = 0; i < nNo; i++) {
			for (int j = 0; j < i; j++) {
				if (m_nPlayer[i] == m_nPlayer[j]) {
					cout << "DUPLICATE NUMBERS CANNOT BE USED" << endl; // 중복된 수는 사용할 수 없다.
					m_nPlayerCnt++;
				}
			}
		}
		//if (m_nPlayerCnt == nNo * nNo) break;
		if (m_nPlayerCnt == 0) break;
		else m_nPlayerCnt = 0;
	}
}

void StrkBlCheck(int m_nComputer[], int m_nPlayer[], int nNo) {
	if (m_bisExit) return;

	for (int i = 0; i < 3; i++)
	{
		if (m_nComputer[i] == m_nPlayer[i]) // 스트라이크인지 아닌지 판별
			m_nStrike++;
	}

	if (m_nStrike < 3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (m_nComputer[i] == m_nPlayer[j] && i != j) // 볼인지 아닌지 판별
					m_nBall++;
			}
		}
	}

	cout << m_nCnt << ". " << "STRIKE : " << m_nStrike << " BALL : " << m_nBall << endl; // 스트라이크와 볼의 개수 출력

	if (m_nCnt > nNo * 8) { // 플레이어가 일정 횟수 초과 입력하면 컴퓨터 승리
		cout << nNo << " COUNT : " << m_nCnt << endl;
		cout << nNo << " BASE BALL : COMPUTER WIN!!!" << endl;
		m_bisExit = true;
	}
	else if (m_nStrike == nNo) { // 플레이어가 일정 횟수 이하 입력하면 플레이어 승리
		cout << nNo << " COUNT : " << m_nCnt << endl;
		cout << nNo << " BASE BALL : PLAYER WIN!!!" << endl;
		m_bisExit = true;
	}

	m_nStrike = 0;
	m_nBall = 0;
	m_nCnt++;

}

