#include <iostream>
#include <Windows.h>

#define SCHOOL_CNT 2
#define GRADE_CNT 3
#define CLASS_CNT 3
#define STUDENT_CNT 4
#define SUBJECT_CNT 5
#define RATING_CNT 5

#define SCHOOL_NAME 20
#define STUDENT_NAME 8
#define STUDENT_ADRESS 30
#define STUDENT_PHONE_NUM 20
#define MAJOR_NAME 20
#define SUBJECT_NAME 20

#define GRADE_NAME_CNT 7
#define CLASS_NAME_CNT 5

struct School {
	char sName[SCHOOL_NAME];
};
struct Grade {
	int nGradeNo;
};
struct Class {
	int nClassNo;
};
struct Student {
	int nSchoolNo;
	int nGradeNo;
	int nClassNo;
	int nStudentNo;

	char sStudentName[STUDENT_NAME];

	int nSub1Score;
	int nSub2Score;
	int nSub3Score;
	int nAverage;

	char sStudentAdress[STUDENT_ADRESS];
	char sStudentPhoneNum[STUDENT_PHONE_NUM];
};
struct Subject {
	char sSub1[SUBJECT_NAME];
	char sSub2[SUBJECT_NAME];
	char sSub3[SUBJECT_NAME];
};

struct School m_pSchool[SCHOOL_CNT];
struct Grade m_pGrade[GRADE_CNT];
struct Class m_pClass[CLASS_CNT];
struct Student m_pStudent[SCHOOL_CNT][GRADE_CNT][CLASS_CNT][STUDENT_CNT];
struct Subject m_pSubject[SCHOOL_CNT][GRADE_CNT];

void Initialization();
void ReEnter();

void SchoolChoice();	// 학교 선택 창
void SchoolMenu(int);	// 학교 메인메뉴 ( 학교 정보, 학년 선택)
void SchoolInFormation(int);

void GradeMenu(int);
void ClassMenu(int, int);
void StudentMenu(int, int, int);

void StudentInfo(int, int, int, int);
void StudentInfoPrint(int, int, int, int);

void StudentInfoChange(int, int, int, int);
void StudentScoreChange(int, int, int, int);

void SubjectPrint(int);
void SubjectChangeMain(int);
void SubjectChangeSub(int, int);

//삼일상고
int m_nCommrcialMaxClassCnt = 9;		// 최대 반 수
int m_nCommrcialMaxStudentCnt = 36;	// 최대 학생 수
// 삼일공고
int m_nTechnicalMaxClassCnt = 9;		// 최대 반 수
int m_nTechnicalMaxStudentCnt = 36;	// 최대 학생 수

int m_nChoiceNo = 0;

int main()
{
	Initialization(); // 구조체 초기화

	SchoolChoice();	// 학교 선택 창으로 이동
	return 0;
}

void Initialization(){
	// m_pSchool
	if (1) {
		m_pSchool[0] = { "삼일상업고등학교" };
		m_pSchool[1] = { "삼일공업고등학교" };
	}
	// m_pGrade
	if (1) {
		m_pGrade[0] = { 1 };
		m_pGrade[1] = { 2 };
		m_pGrade[2] = { 3 };
	}
	// m_pClass
	if (1) {
		m_pClass[0] = { 1 };
		m_pClass[1] = { 2 };
		m_pClass[2] = { 3 };
		m_pClass[3] = { 4 };
	}
	// m_pStudent
	if (1) {
		// 삼일상업고등학교
		if (1) {
			// 1학년
			if (1) {
				m_pStudent[0][0][0][0] = { 0, 1, 1, 1, "양소정", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };
				m_pStudent[0][0][0][1] = { 0, 1, 1, 2, "임효상", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };
				m_pStudent[0][0][0][2] = { 0, 1, 1, 3, "정명철", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][0][0][3] = { 0, 1, 1, 4, "진상훈", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[0][0][1][0] = { 0, 1, 2, 1, "이유빈", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][0][1][1] = { 0, 1, 2, 2, "조원석", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][0][1][2] = { 0, 1, 2, 3, "이민석", 0, 0, 0, 0, "서울시 ㅅㅇ동", "010-0000-0000" };
				m_pStudent[0][0][1][3] = { 0, 1, 2, 4, "김준서", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[0][0][2][0] = { 0, 1, 3, 1, "강수민", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][0][2][1] = { 0, 1, 3, 2, "조건호", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };
				m_pStudent[0][0][2][2] = { 0, 1, 3, 3, "김현준", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][0][2][3] = { 0, 1, 3, 4, "전철환", 0, 0, 0, 0, "서울시 ㅅㅇ동", "010-0000-0000" };
			}
			// 2학년
			if (1) {
				m_pStudent[0][1][0][0] = { 0, 2, 1, 1, "김수아", 0, 0, 0, 0, "용인시 ㅂㅂ동", "010-0000-0000" };
				m_pStudent[0][1][0][1] = { 0, 2, 1, 2, "김영훈", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][1][0][2] = { 0, 2, 1, 3, "김우빈", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };
				m_pStudent[0][1][0][3] = { 0, 2, 1, 4, "문서준", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[0][1][1][0] = { 0, 2, 2, 1, "박수진", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[0][1][1][1] = { 0, 2, 2, 2, "박형진", 0, 0, 0, 0, "용인시 ㅂㅂ동", "010-0000-0000" };
				m_pStudent[0][1][1][2] = { 0, 2, 2, 3, "송도예", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][1][1][3] = { 0, 2, 2, 4, "신연주", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };

				m_pStudent[0][1][2][0] = { 0, 2, 3, 1, "이민희", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][1][2][1] = { 0, 2, 3, 2, "이서진", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][1][2][2] = { 0, 2, 3, 3, "이성민", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][1][2][3] = { 0, 2, 3, 4, "이소현", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
			}
			// 3학년
			if (1) {
				m_pStudent[0][2][0][0] = { 0, 3, 1, 1, "이지한", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };
				m_pStudent[0][2][0][1] = { 0, 3, 1, 2, "이지혜", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][2][0][2] = { 0, 3, 1, 3, "황수현", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][2][0][3] = { 0, 3, 1, 4, "황순성", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };

				m_pStudent[0][2][1][0] = { 0, 3, 2, 1, "김재민", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };
				m_pStudent[0][2][1][1] = { 0, 3, 2, 2, "윤민상", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[0][2][1][2] = { 0, 3, 2, 3, "소상윤", 0, 0, 0, 0, "익산시 ㄱㄴ동", "010-0000-0000" };
				m_pStudent[0][2][1][3] = { 0, 3, 2, 4, "박민재", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[0][2][2][0] = { 0, 3, 3, 1, "정도연", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[0][2][2][1] = { 0, 3, 3, 2, "김성균", 0, 0, 0, 0, "순천시 ㄱㄷ동", "010-0000-0000" };
				m_pStudent[0][2][2][2] = { 0, 3, 3, 3, "송영혁", 0, 0, 0, 0, "부산시 ㅎㅈ동", "010-0000-0000" };
				m_pStudent[0][2][2][3] = { 0, 3, 3, 4, "이하늘", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
			}
		}
		// 삼일공업고등학교
		if (1) {
			// 1학년
			if (1) {
				m_pStudent[1][0][0][0] = { 0, 1, 1, 1, "이기세", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][0][0][1] = { 0, 1, 1, 2, "석현우", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][0][0][2] = { 0, 1, 1, 3, "최병현", 0, 0, 0, 0, "서울시 ㅅㅇ동", "010-0000-0000" };
				m_pStudent[1][0][0][3] = { 0, 1, 1, 4, "홍성원", 0, 0, 0, 0, "제주시 ㅇㄴ동", "010-0000-0000" };

				m_pStudent[1][0][1][0] = { 0, 1, 2, 1, "이강현", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[1][0][1][1] = { 0, 1, 2, 2, "최주원", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[1][0][1][2] = { 0, 1, 2, 3, "유태윤", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[1][0][1][3] = { 0, 1, 2, 4, "박지연", 0, 0, 0, 0, "군포시 ㄱㅍ동", "010-0000-0000" };

				m_pStudent[1][0][2][0] = { 0, 1, 3, 1, "임채명", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[1][0][2][1] = { 0, 1, 3, 2, "박만준", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[1][0][2][2] = { 0, 1, 3, 3, "서한수", 0, 0, 0, 0, "오산시 ㅇㅅ동", "010-0000-0000" };
				m_pStudent[1][0][2][3] = { 0, 1, 3, 4, "양주민", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
			}
			// 2학년
			if (1) {
				m_pStudent[1][1][0][0] = { 0, 2, 1, 1, "지승혁", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][0][1] = { 0, 2, 1, 2, "장영식", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][0][2] = { 0, 2, 1, 3, "이다운", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][0][3] = { 0, 2, 1, 4, "박세아", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[1][1][1][0] = { 0, 2, 2, 1, "이가민", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][1][1] = { 0, 2, 2, 2, "임소예", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][1][2] = { 0, 2, 2, 3, "강예린", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][1][3] = { 0, 2, 2, 4, "신서희", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[1][1][2][0] = { 0, 2, 3, 1, "신승준", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][2][1] = { 0, 2, 3, 2, "이수현", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][2][2] = { 0, 2, 3, 3, "이민서", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][1][2][3] = { 0, 2, 3, 4, "한민서", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
			}
			// 3학년
			if (1) {
				m_pStudent[1][2][0][0] = { 0, 3, 1, 1, "이규현", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][0][1] = { 0, 3, 1, 2, "한승규", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][0][2] = { 0, 3, 1, 3, "장동규", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][0][3] = { 0, 3, 1, 4, "주가영", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[1][2][1][0] = { 0, 3, 2, 1, "오은빈", 0, 0, 0, 0, "화성시 ㅇㅇ동", "010-0000-0000" };
				m_pStudent[1][2][1][1] = { 0, 3, 2, 2, "윤지연", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][1][2] = { 0, 3, 2, 3, "임한나", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][1][3] = { 0, 3, 2, 4, "임창대", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };

				m_pStudent[1][2][2][0] = { 0, 3, 3, 1, "김바울", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][2][1] = { 0, 3, 3, 2, "한태현", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][2][2] = { 0, 3, 3, 3, "정민구", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
				m_pStudent[1][2][2][3] = { 0, 3, 3, 4, "김준하", 0, 0, 0, 0, "수원시 ㅁㅁ동", "010-0000-0000" };
			}
		}
	}
	// m_pSubiect()
	if (1) {
		m_pSubject[0][0] = { "국어", "수학", "한국사" };
		m_pSubject[0][1] = { "국어", "수학", "영어" };
		m_pSubject[0][2] = { "국어", "수학", "사회" };

		m_pSubject[1][0] = { "국어", "수학", "사회" };
		m_pSubject[1][1] = { "국어", "수학", "한국사" };
		m_pSubject[1][2] = { "국어", "수학", "영어" };
	}
}

void ReEnter() {
	printf("번호정보가 없습니다.	다시입력해주세요.");
}

void SchoolChoice() {

	while (1)
	{
		printf("\n==============================<< 학교 선택 창 >>==============================\n");
		printf("			     1. 삼일상업고등학교 \n");
		printf("			     2. 삼일공업고등학교 \n");
		printf("				  0. 끝내기 \n");
		printf("==============================================================================\n\n");
		printf("번호를 입력해 주세요 : ");
		scanf_s("%d", &m_nChoiceNo);
		system("cls");

		if (m_nChoiceNo == 0) return;
		else if (m_nChoiceNo > SCHOOL_CNT || m_nChoiceNo < 0) ReEnter();
		else { 
			m_nChoiceNo -= 1;
			SchoolMenu(m_nChoiceNo);
		}
	}
}

void SchoolMenu(int nSchoolNo) {

	while (1) 
	{
		printf("\n==============================<< %s >>==============================\n", m_pSchool[nSchoolNo].sName);
		printf("			     1. 학교 정보 \n");
		printf("			     2. 학생 정보 \n");
		printf("				  0. 뒤로가기 \n");
		printf("==================================================================================\n\n");
		printf("번호를 입력해 주세요 : ");
		scanf_s("%d", &m_nChoiceNo);
		system("cls");

		if (m_nChoiceNo == 0) return;
		else if (m_nChoiceNo == 1) SchoolInFormation(nSchoolNo);
		else if (m_nChoiceNo == 2) GradeMenu(nSchoolNo);
		else ReEnter();
	}
}

void SchoolInFormation(int nSchoolNo) {

	printf("학교 이름 : %s \n", m_pSchool[nSchoolNo].sName);
	if (nSchoolNo == 0) {
		printf("학생 총수 : %d \n", m_nCommrcialMaxStudentCnt);
		printf("학급 총수 : %d \n", m_nCommrcialMaxClassCnt);
		SubjectPrint(nSchoolNo);
	}
	else {
		printf("학생 총수 : %d \n", m_nTechnicalMaxStudentCnt);
		printf("학급 총수 : %d \n", m_nTechnicalMaxClassCnt);
		SubjectPrint(nSchoolNo);
	}
	printf("1. 과목변경 \n");
	printf("0. 뒤로가기 \n");
	scanf_s("%d", &m_nChoiceNo);
	system("cls");

	if (m_nChoiceNo == 1) SubjectChangeMain(nSchoolNo);
	else return;
}

void SubjectPrint(int nSchoolNo) {
	printf("1학년 과목 : %s %s %s \n", m_pSubject[nSchoolNo][0].sSub1, m_pSubject[nSchoolNo][0].sSub2, m_pSubject[nSchoolNo][0].sSub3);
	printf("2학년 과목 : %s %s %s \n", m_pSubject[nSchoolNo][1].sSub1, m_pSubject[nSchoolNo][1].sSub2, m_pSubject[nSchoolNo][1].sSub3);
	printf("3학년 과목 : %s %s %s \n", m_pSubject[nSchoolNo][2].sSub1, m_pSubject[nSchoolNo][2].sSub2, m_pSubject[nSchoolNo][2].sSub3);
}

void SubjectChangeMain(int nSchoolNo) {
	char sSub1[SUBJECT_NAME];
	char sSub2[SUBJECT_NAME];
	char sSub3[SUBJECT_NAME];

	printf("변경할 학년 입력 : ");
	scanf_s("%d", &m_nChoiceNo);
	system("cls");

	if (m_nChoiceNo == 0) return;
	// else 

}

void SubjectChangeSub(int nSchoolNo, int nGradeNo) {

}

void GradeMenu(int nSchoolNo) {

	while (1) {
		printf("\n==============================<< %s >>==============================\n", m_pSchool[nSchoolNo].sName);
		for (int i = 1; i <= GRADE_CNT; i++)
			printf("			     %d. %d 학년 \n", i, i);

		printf("				  0. 뒤로가기 \n");
		printf("==================================================================================\n\n");
		printf("번호를 입력해 주세요 : ");
		scanf_s("%d", &m_nChoiceNo);
		system("cls");

		if (m_nChoiceNo == 0) return;
		else if (m_nChoiceNo > GRADE_CNT || m_nChoiceNo < 0) ReEnter();
		else {
			m_nChoiceNo -= 1;
			ClassMenu(nSchoolNo, m_nChoiceNo);
		}
	}
}

void ClassMenu(int nSchoolNo, int nGradeNo) {

	while (1) {
		printf("\n==============================<< %d 학년 >>==============================\n", m_pGrade[nGradeNo].nGradeNo);
		for (int i = 1; i <= CLASS_CNT; i++)
			printf("			%d. %d 반 \n", i, i);

		printf("			0. 뒤로가기 \n");
		printf("===========================================================================\n\n");
		printf("번호를 입력해 주세요 : ");
		scanf_s("%d", &m_nChoiceNo);
		system("cls");

		if (m_nChoiceNo == 0) return;
		else if (m_nChoiceNo > CLASS_CNT || m_nChoiceNo < 0) ReEnter();
		else {
			m_nChoiceNo -= 1;
			StudentMenu(nSchoolNo, nGradeNo, m_nChoiceNo);
		}
	}
}

void StudentMenu(int nSchoolNo, int nGradeNo, int nClassNo) {

	while (1) {
		printf("\n==============================<< %d 반 >>==============================\n", m_pClass[nClassNo].nClassNo);
		for (int i = 1; i <= STUDENT_CNT; i++)
			printf("			%d. %d 번 %s \n", i, i, m_pStudent[nSchoolNo][nGradeNo][nClassNo][i-1].sStudentName);

		printf("			0. 뒤로가기 \n");
		printf("=========================================================================\n\n");
		printf("번호를 입력해 주세요 : ");
		scanf_s("%d", &m_nChoiceNo);
		system("cls");

		if (m_nChoiceNo == 0) return;
		else if (m_nChoiceNo > STUDENT_CNT || m_nChoiceNo < 0) ReEnter();
		else {
			m_nChoiceNo -= 1;
			StudentInfo(nSchoolNo, nGradeNo, nClassNo, m_nChoiceNo);
		}
	}
}

void StudentInfo(int nSchoolNo, int nGradeNo, int nClassNo, int nStudentNo) {
	
	while (1) {
		StudentInfoPrint(nSchoolNo, nGradeNo, nClassNo, nSchoolNo);
		
		printf("	1. 학생정보 변경 \n");
		printf("	2. 점수 변경 \n");
		printf("	0. 뒤로가기 \n");
		scanf_s("%d", &m_nChoiceNo);
		system("cls");

		if (m_nChoiceNo == 0) return;
		else if (m_nChoiceNo == 1) {
			StudentInfoChange(nSchoolNo, nGradeNo, nClassNo, nSchoolNo);
		}
		else if (m_nChoiceNo == 2) {
			StudentScoreChange(nSchoolNo, nGradeNo, nClassNo, nSchoolNo);
		}
		else {
			ReEnter();
		}
	}
}

void StudentInfoPrint(int nSchoolNo, int nGradeNo, int nClassNo, int nStudentNo) {
	printf("\n==============================<< %s >>==============================\n", m_pSchool[nSchoolNo].sName);
	printf("		%d 학년	%d 반	%d 번	%s	\n", m_pGrade[nGradeNo].nGradeNo, m_pClass[nClassNo].nClassNo, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nStudentNo, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].sStudentName);
	printf("		%s : %d	%s : %d	%s : %d 평균 : %d	\n", m_pSubject[nSchoolNo][nGradeNo].sSub1, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub1Score, m_pSubject[nSchoolNo][nGradeNo].sSub2, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub2Score, m_pSubject[nSchoolNo][nGradeNo].sSub3, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub3Score, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nAverage);
	printf("\n=================================================================================\n");

}

void StudentInfoChange(int nSchoolNo, int nGradeNo, int nClassNo, int nStudentNo) {
	char sName[STUDENT_NAME];
	char sAdress[STUDENT_ADRESS];
	char sPhoneNum[STUDENT_PHONE_NUM];

	int STNo = 0;

	StudentInfoPrint(nSchoolNo, nGradeNo, nClassNo, nStudentNo);

	printf("변경할 이름 : ");
	scanf_s("%s", sName, STUDENT_NAME);
	printf("변경할 주소 : ");
	scanf_s("%s", sAdress, STUDENT_ADRESS);
	printf("변경할 전화번호 : ");
	scanf_s("%s", sName, STUDENT_PHONE_NUM);
	
	memcpy(m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].sStudentName, sName, sizeof(sName));
	memcpy(m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].sStudentAdress, sAdress, sizeof(sAdress));
	memcpy(m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].sStudentPhoneNum, sPhoneNum, sizeof(sPhoneNum));

}

void StudentScoreChange(int nSchoolNo, int nGradeNo, int nClassNo, int nStudentNo) {
	int nSub1;
	int nSub2;
	int nSub3;

	StudentInfoPrint(nSchoolNo, nGradeNo, nClassNo, nStudentNo);

	printf("\n		%s		%d		", m_pSubject[nSchoolNo][nGradeNo].sSub1, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub1Score);
	printf("\n		%s		%d		", m_pSubject[nSchoolNo][nGradeNo].sSub2, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub2Score);
	printf("\n		%s		%d		", m_pSubject[nSchoolNo][nGradeNo].sSub3, m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub3Score);

	printf("\n		%s :	", m_pSubject[nSchoolNo][nGradeNo].sSub1);
	scanf_s("	%d", &nSub1);
	printf("\n		%s :	", m_pSubject[nSchoolNo][nGradeNo].sSub2);
	scanf_s("	%d", &nSub2);
	printf("\n		%s :	", m_pSubject[nSchoolNo][nGradeNo].sSub3);
	scanf_s("	%d", &nSub3);

	m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub1Score = nSub1;
	m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub1Score = nSub2;
	m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nSub1Score = nSub3;

	m_pStudent[nSchoolNo][nGradeNo][nClassNo][nStudentNo].nAverage = (nSub1+nSub2+nSub3)/3;
}