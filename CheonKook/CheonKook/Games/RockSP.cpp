#include "Header.h"
#include "..\Main.h"
#include "RockSP.h"

namespace JH_RockSP
{
	clock_t G_OldTime = clock(); // 게임 실행속도 제한

	char print[500];

	//char rsp[5][50] = { "rock", "scissor", "paper" };
	char result[20];

	int computer;
	int score = 0;

	char ComputerResult[20]; //computer 값 확인
	char FinalScore[20];

	bool IsRPrint; // result값 출력 판별
	clock_t RPrintOldTime; // result print한 마지막 시각

	// 구조체 변수
	GAMESTATUS GameStatus;
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
		GameStatus = START;

		Choice.select = 0;

		sprintf(FinalScore, "Score : 0");

	}//화면초기화

	void StatusPrint()
	{
		switch (GameStatus)
		{
		case START:
			sprintf(print, "\t\t\t   [가위바위보] \n\n"
				"\t\t===================================\n\n"
				"\t\t   가위바위보 게임입니다.\n\n"
				"\t\t   누적 3회 승리 시, \n"
				"\t\t   본 게임에 들어갈 수 있습니다. \n"
				"\t\t===================================\n\n"
				"\t\t\t  - 조 작 법 -\n\n"
				"\t\t선택 : 방향키 | 패 내기 : SPACE BAR\n"
				"\t\t-----------------------------------\n\n"
				"\t\t모든 게임은 Q를 누르면 종료됩니다.\n"
				"\t\t\n"
				"\t\t게임 시작 : SPACE BAR | 게임 종료 : Q\n\n\n\n");
			ScreenPrint(0, 3, print);
			break;

		case RUNNING:
			sprintf(print, " \t---------\t\t---------\t\t---------\n"
				"\t   rock   \t\t scissor \t\t  paper \n"
				"\t---------\t\t---------\t\t---------\n");
			ScreenPrint(0, 0, print);
			break;

		default:
			break;
		}
	}

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

		StatusPrint();

		if (GameStatus == RUNNING)
		{
			if (IsRPrint == true)
			{
				ScreenPrint(10, 12, result); // 시간 제한 두기
				ScreenPrint(10, 10, ComputerResult);

				if (CurTime - RPrintOldTime >= 3 * 1000) // 출력 시간이 3초가 넘으면
				{
					IsRPrint = false; // 더이상 띄우지 않는다
				}
			}

			ScreenPrint(68, 1, FinalScore);
			ScreenPrint(Choice.x, Choice.y, "▲");
		}

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

		// START 상태에서의 키조작
		if (GameStatus == START)
		{
			if (key == SPACE)
			{
				GameStatus = RUNNING;
				return;
			}
		}

		// RUNNING 상태에서의 키조작
		if (GameStatus == RUNNING)
		{
			switch (key)
			{
				case LEFT:				
					if (Choice.select >= 1)
						Choice.select--;
					else
						Choice.select = 2;
					break;				

				case RIGHT:				
					if (Choice.select <= 1)
						Choice.select++;
					else
						Choice.select = 0;
					break;
				

				case SPACE:
					SelectRSP();
					break;
				
				default:
					break;
			}
		}
	}
}
using namespace JH_RockSP;

	void main() {

		int key;
		clock_t CurTime;

		srand((unsigned)time(NULL));

		Init();
		ScreenInit();


		while (1) {


			if (_kbhit()) {

				key = _getch();

				KeyControl(key);

			}

			// 테스트용 코드
			if (score >= 3)
				MainGame::MainGame();

			Update();
			Render();

			while (1)
			{
				CurTime = clock();
				if (CurTime - G_OldTime > DelayT)
				{
					G_OldTime = CurTime;
					break;
				}
			}
		}

	}


