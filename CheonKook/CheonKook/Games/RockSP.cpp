#include "Header.h"
#include "..\Main.h"
#include "RockSP.h"

namespace JH_RockSP
{
	clock_t G_OldTime = clock(); // ���� ����ӵ� ����

	char print[500];

	//char rsp[5][50] = { "rock", "scissor", "paper" };
	char result[20];

	int computer;
	int score = 0;

	char ComputerResult[20]; //computer �� Ȯ��
	char FinalScore[20];

	bool IsRPrint; // result�� ��� �Ǻ�
	clock_t RPrintOldTime; // result print�� ������ �ð�

	// ����ü ����
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

	}//ȭ���ʱ�ȭ

	void StatusPrint()
	{
		switch (GameStatus)
		{
		case START:
			sprintf(print, "\t\t\t   [����������] \n\n"
				"\t\t===================================\n\n"
				"\t\t   ���������� �����Դϴ�.\n\n"
				"\t\t   ���� 3ȸ �¸� ��, \n"
				"\t\t   �� ���ӿ� �� �� �ֽ��ϴ�. \n"
				"\t\t===================================\n\n"
				"\t\t\t  - �� �� �� -\n\n"
				"\t\t���� : ����Ű | �� ���� : SPACE BAR\n"
				"\t\t-----------------------------------\n\n"
				"\t\t��� ������ Q�� ������ ����˴ϴ�.\n"
				"\t\t\n"
				"\t\t���� ���� : SPACE BAR | ���� ���� : Q\n\n\n\n");
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
				ScreenPrint(10, 12, result); // �ð� ���� �α�
				ScreenPrint(10, 10, ComputerResult);

				if (CurTime - RPrintOldTime >= 3 * 1000) // ��� �ð��� 3�ʰ� ������
				{
					IsRPrint = false; // ���̻� ����� �ʴ´�
				}
			}

			ScreenPrint(68, 1, FinalScore);
			ScreenPrint(Choice.x, Choice.y, "��");
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

		RPrintOldTime = clock(); // ������ ��� �ð��� ���� �ð����� ���� 
		IsRPrint = true; // result print ���

	}
	//��������������

	void KeyControl(int key)
	{

		// START ���¿����� Ű����
		if (GameStatus == START)
		{
			if (key == SPACE)
			{
				GameStatus = RUNNING;
				return;
			}
		}

		// RUNNING ���¿����� Ű����
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

			// �׽�Ʈ�� �ڵ�
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


