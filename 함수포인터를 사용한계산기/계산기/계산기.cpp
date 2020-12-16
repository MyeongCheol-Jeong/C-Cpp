#include <iostream>
#include <Windows.h>

void MainMenu(void);
int Add(int, int);
int Sub(int, int);
int Mul(int, int);
int Div(int, int);
int Calculator(int, int, int(*pFunc)(int, int));

int main()
{
	int nNo;

	MainMenu();
}

void MainMenu()
{
	int(*calc)(int, int) = NULL;
	int nResult = 0;

	int nNo1 = 0, nNo2 = 0;
	char c;

	while (true)
	{
		scanf_s("%d%c", &nNo2, &c, 1);

		if (c == '=')
			break;
		else
		{
			switch (c)
			{
			case '+':
				calc = Add;
				break;
			case '-':
				calc = Sub;
				break;
			case '*':
				calc = Mul;
				break;
			case '/':
				calc = Div;
				break;
			default:
				printf("사칙연산(+, -, *, /)만을 지원합니다.");
			}
			nNo1 = nNo2;
		}
	}
	nResult = Calculator(nNo1, nNo2, calc);
	printf("계산 결과는 %d입니다.\n", nResult);
	return;
}
int Add(int nNo1, int nNo2)
{
	return nNo1 + nNo2;
}
int Sub(int nNo1, int nNo2)
{
	return nNo1 - nNo2;
}
int Mul(int nNo1, int nNo2)
{
	return nNo1 * nNo2;
}
int Div(int nNo1, int nNo2)
{
	return nNo1 / nNo2;
}
int Calculator(int nNo1, int nNo2, int(*pFunc)(int, int))
{
	return pFunc(nNo1, nNo2);
}