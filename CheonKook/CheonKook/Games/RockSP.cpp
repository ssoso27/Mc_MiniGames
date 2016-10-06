#include "Header.h"
#include "..\Main.h"

namespace JH_RockSP
{

	char print[500];

	//char rsp[5][50] = { "rock", "scissor", "paper" };
	char result[20];

	int computer;
	int score = 0;

	char ComputerResult[20]; //computer 값 확인
	char FinalScore[20];

	bool IsRPrint; // result값 출력 판별
	clock_t RPrintOldTime; // result print한 마지막 시각


	typedef struct _CHOICE {

		int select;
		int x;
		int y;

	}CHOICE;

	CHOICE Choice;

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32,
		ESC = 27
	};

	void Init() {
		sprintf(print, " \t---------\t\t---------\t\t---------\n"
			"\t   rock   \t\t scissor \t\t  paper \n"
			"\t---------\t\t---------\t\t---------\n");

		Choice.select = 0;

		sprintf(FinalScore, "Score : 0");

	}//화면초기화

	void AssignCoord()
	{

		switch (Choice.select) {

		case 0:
			Choice.x = 12;
			Choice.y = 5;
			break;

		case 1:
			Choice.x = 36;
			Choice.y = 5;
			break;

		case 2:
			Choice.x = 60;
			Choice.y = 5;
			break;
		}
	}

	void Update()
	{
		AssignCoord();
	}

	void Render()
	{
		clock_t CurTime = clock();

		ScreenClear();

		if (IsRPrint == true)
		{
			ScreenPrint(10, 12, result); // 시간 제한 두기
			ScreenPrint(10, 10, ComputerResult);

			if (CurTime - RPrintOldTime >= 3 * 1000) // 출력 시간이 3초가 넘으면
			{
				IsRPrint = false; // 더이상 띄우지 않는다
			}
		}

		ScreenPrint(0, 0, print);

		ScreenPrint(68, 1, FinalScore);
		ScreenPrint(Choice.x, Choice.y, "▲");

		ScreenFlipping();
	}

	void SelectRSP() {


		computer = rand() % 3;

		switch (computer)
		{
		case 0:

			sprintf(ComputerResult, "Computer : Rock!");
			break;

		case 1:
			sprintf(ComputerResult, "Computer : Scissor!");
			break;

		case 2:
			sprintf(ComputerResult, "Computer : Paper!");
			break;

		default:
			break;
		}



		if ((Choice.select == 2 && Choice.select > computer) || (Choice.select < computer)) {
			sprintf(result, "Win!");
			score++;
		}
		else if (Choice.select == computer)
			sprintf(result, "Draw!");

		else sprintf(result, "Lose!");

		sprintf(FinalScore, "Score : %d", score);

		RPrintOldTime = clock(); // 마지막 출력 시각을 현재 시각으로 설정 
		IsRPrint = true; // result print 허용

	}
	//가위바위보선택

	void KeyControl(int key)
	{
		switch (key)
		{
		case LEFT:
		{
			if (Choice.select >= 1)
				Choice.select--;
			else
				Choice.select = 2;
			break;
		}

		case RIGHT:
		{
			if (Choice.select <= 1)
				Choice.select++;
			else
				Choice.select = 0;
			break;
		}

		case SPACE:
		{

			SelectRSP();
			break;
		}
		default:
			break;

		}
	}
}
using namespace JH_RockSP;

	void main() {

		int key;

		srand((unsigned)time(NULL));

		Init();
		ScreenInit();


		while (1) {


			if (_kbhit()) {

				key = _getch();

				if (key == 75 || key == 77 || key == 32)
					KeyControl(key);

			}

			// 테스트용 코드
			if (score >= 3)
				MainGame::MainGame();

			Update();
			Render();
		}

	}


