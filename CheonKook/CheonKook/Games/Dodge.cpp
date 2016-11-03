#include "Header.h"
#include "Dodge.h"

namespace SH_Dodge
{
	// ������

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32
	};

	// ���� ���� ����

	// ����ü ����

	PLAYER Player;
	DOT Dot[DotNum * 4];
	STAR Star;
	GAMESTATUS GameStatus;

	// �������� ����

	int Stage = 0;

	// ���� ���� ����

	char StatString[500]; // ���� ���� String
	int PrintTime = 3 * 1000; // ���� ���� ǥ�� �ð�
	clock_t Stat_OldTime = clock(); // PrintTime�� OldTime
	clock_t G_OldTime = clock(); // ���� ����ӵ� ����

									// ȭ�鿡 ǥ�õ� ��� 

	char Player_Shape[] = { "��" };
	char Dot_Shape[4][3] = { { "��" },{ "��" },{ "��" },{ "��" } };
	char Star_Shape[] = { "��" };


	// �Լ� ����

	void KeyControl(int key) // Ű �Է� ó��
	{

		switch (key)
		{
		case UP:
			if (Stage == 2)
			{
				if (Player.Y != 2)
					Player.Y--;
			}
			break;

		case DOWN:
			if (Stage == 2)
			{
				if (!(Player.Y == (BOARD_HEIGHT - 1)))
					Player.Y++;
			}
			break;

		case LEFT:
			if (!Player.X == 0)
				Player.X--;
			break;

		case RIGHT:
			if (!(Player.X == (BOARD_WIDTH - 1)))
				Player.X++;
			break;

		}
	}

	void IfCrash(int i) // Crash �߻� ó��
	{
		if ((Player.X == Dot[i].X && Player.Y == Dot[i].Y) || ((Player.X - 1) == Dot[i].X && Player.Y == Dot[i].Y))
		{
			Player.Life--;

			// Dot�� ������ ���� ��ġ y�� �ʱ�ȭ
			if (Stage != 0)
			{
				if (i >= 0 && i < DotNum) // ��
					Dot[i].Y = 2;
				else if (i >= DotNum && i < DotNum * 2) // ��
					Dot[i].Y = BOARD_HEIGHT - 1;
				else if (i >= DotNum * 2 && i < DotNum * 3) // ��
					Dot[i].X = 0;
				else // ��
					Dot[i].X = BOARD_WIDTH - 1;
			}
			else // Stage == 0
			{
				Dot[i].Y = 2; // ��
			}
		}
		if (Player.Life <= 0)
			GameStatus = NEXT;

	}

	void StarInit()
	{
		if (Stage == 2)
		{
			Star.X = rand() % BOARD_WIDTH;
			Star.Y = rand() % ((BOARD_HEIGHT - 4) + 2);
		}
		else
		{
			Star.X = rand() % BOARD_WIDTH;
			Star.Y = Player.Y;
		}
	}
	void MoveCoord(int i) // ��ǥ �̵�
	{
		clock_t CurTime = clock();

		if ((Player.X == Star.X && Player.Y == Star.Y) || ((Player.X - 1) == Star.X && Player.Y == Star.Y))
		{
			Star.Catch++;
			Star.SumCatch++;

			StarInit();
		}

		if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime�� ������ Update. -> �ӵ� ����
		{

			// ��ǥ �̵� ����

			if (Stage == 0) // ù��° �������� 
			{
				Dot[i].Y++; // ��ǥ �̵�

				if (Dot[i].Y == BOARD_HEIGHT - 1) // ���� ���� ��� 
				{
					Dot[i].X = rand() % BOARD_WIDTH;
					Dot[i].Y = 2;
					Dot[i].Speed = rand() % 3 + 1;
				}
			}
			else // Stage!=0
			{

				if (i >= 0 && i < DotNum) // ��
				{
					Dot[i].Y++;
					if (Dot[i].Y == BOARD_HEIGHT - 1)
					{
						Dot[i].X = rand() % BOARD_WIDTH;
						Dot[i].Y = 2;
						Dot[i].Speed = rand() % 3 + 1;
					}
				}
				if ((i >= DotNum) && (i < (DotNum * 2))) // ��
				{
					Dot[i].Y--;
					if (Dot[i].Y == 2)
					{
						Dot[i].X = rand() % BOARD_WIDTH;
						Dot[i].Y = BOARD_HEIGHT - 1;
						Dot[i].Speed = rand() % 3 + 1;
					}
				}
				if ((i >= (DotNum * 2)) && (i < (DotNum * 3))) // ��
				{
					Dot[i].X++;
					if (Dot[i].X == BOARD_WIDTH - 2)
					{
						Dot[i].X = 0;
						Dot[i].Y = (rand() % (BOARD_HEIGHT - 2)) + 2;
						Dot[i].Speed = rand() % 3 + 1;
					}
				}
				if ((i >= (DotNum * 3)) && (i < (DotNum * 4))) // ��
				{
					Dot[i].X--;
					if (Dot[i].X == 0)
					{
						Dot[i].X = BOARD_WIDTH - 2;
						Dot[i].Y = (rand() % (BOARD_HEIGHT - 2)) + 2;
						Dot[i].Speed = rand() % 3 + 1;
					}
				}
			}

			// �ð� �缳��

			Dot[i].OldTime = CurTime;

		}
	}

	void DotInit()
	{
		int i;

		srand((unsigned)time(NULL));

		switch (Stage)
		{
		case 2: // �� ��
			for (i = DotNum * 2; i < DotNum * 3; i++) // ��
			{
				// X Y ��ǥ �ʱ�ȭ

				Dot[i].X = 0;
				Dot[i].Y = (rand() % (BOARD_HEIGHT - 4)) + 2;

				// Dot �ð� & �ӵ� ����

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
			}

			for (i = DotNum * 3; i < DotNum * 4; i++) // ��
			{
				// X Y ��ǥ �ʱ�ȭ

				Dot[i].X = BOARD_WIDTH - 2;
				Dot[i].Y = (rand() % (BOARD_HEIGHT - 4)) + 2;

				// Dot �ð� & �ӵ� ����

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
			}
		case 1: // ���
			for (i = DotNum; i < DotNum * 2; i++) // ��
			{
				// X Y ��ǥ �ʱ�ȭ

				Dot[i].X = rand() % BOARD_WIDTH;
				Dot[i].Y = BOARD_HEIGHT - 1;

				// Dot �ð� & �ӵ� ����

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
			}

			for (i = 0; i < DotNum; i++) // �� ( Stage > 0 )
			{
				// X Y ��ǥ �ʱ�ȭ

				Dot[i].X = rand() % BOARD_WIDTH;
				Dot[i].Y = 2;

				// Dot �ð� & �ӵ� ����

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
			}
			break;

		case 0: // ��
			for (i = 0; i < Zero; i++) // �� ( Stage == 0 )
			{
				// X Y ��ǥ �ʱ�ȭ

				Dot[i].X = rand() % BOARD_WIDTH;
				Dot[i].Y = 2;

				// Dot �ð� & �ӵ� ����

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
			}

		}
	}


	void StatusPrint()
	{
		clock_t CurTime;

		CurTime = clock();

		switch (GameStatus)
		{
		case START:
			sprintf(StatString, "\t\t\t  [ȭ��ǥ ���ϱ� ����] \n\n"
				"\t\t===================================\n\n"
				"\t\t���ƿ��� ȭ��ǥ�� ���ϴ� �����Դϴ�.\n"
				"\t\t�� �������� �� Life�� 3 �Դϴ�.\n"
				"\t\tLife�� 0�� �Ǹ� ���� ���������� �Ѿ�ϴ�.\n"
				"\t\tStar(��)�� ȹ���ϸ� ������ �����ϴ�.\n"
				"\t\t���������� �� 3������ �����Ǿ��ֽ��ϴ�.\n\n"
				"\t\t===================================\n\n"
				"\t\t\t  - �� �� �� -\n\n"
				"\t\t�̵� : ����Ű | �Ͻ����� : SPACE BAR\n"
				"\t\t�� : �÷��̾� | �� : Star (��ǥ)\n\n"
				"\t\t-----------------------------------\n"
				"\t\t���� ���� : SPACE BAR | ���� ���� : q\n\n\n\n");
			ScreenPrint(0, 3, StatString);

			break;

		case INIT:
			if (CurTime - Stat_OldTime < PrintTime)
			{

				DotInit(); // Dot �ʱ�ȭ
				StarInit(); // Star �ʱ�ȭ
				Star.Catch = 0;

				// Player �ʱ�ȭ
				Player.X = 35;
				Player.Y = 15;
				Player.Life = 3;

				sprintf(StatString, "[INIT] ���� �ʱ�ȭ \n\n");
				ScreenPrint(25, 10, StatString);

			}
			else
			{
				GameStatus = READY;
				Stat_OldTime = CurTime;
			}

			break;

		case READY:
			if (CurTime - Stat_OldTime < PrintTime)
			{
				sprintf(StatString, "[READY] %d ��������", Stage + 1);
				ScreenPrint(25, 10, StatString);
			}
			else
			{
				GameStatus = GO;
				Stat_OldTime = CurTime;
			}

			break;

		case GO:
			sprintf(StatString, "SPACE : ���� ���� ");
			ScreenPrint(30, 10, StatString);


		case RUNNING:
			Stat_OldTime = CurTime;

			break;

		case STOP:
			sprintf(StatString, "[ STOP ȭ�� ]\n\n"
				"\t\t\t SPACE : ����ȭ������ ���ư� ");
			ScreenPrint(30, 10, StatString);

			break;

		case NEXT:
			if (CurTime - Stat_OldTime < PrintTime)
			{
				sprintf(StatString, " %d �������� GAME OVER", Stage + 1);
				ScreenPrint(25, 10, StatString);

			}
			else
			{
				Stat_OldTime = CurTime;

				if (Stage < 2)
				{
					Stage++;
					GameStatus = INIT;
				}
				else
					GameStatus = RESULT;
			}
			break;

		case RESULT:
			sprintf(StatString, "[ ���� ��� ]\n\n"
				"\t\t\t ȹ���� Star ���� : %d", Star.SumCatch);
			ScreenPrint(30, 10, StatString);

			break;
		}
	}

	// �����ӿ�ũ �Լ� ����

	void Init()
	{
		// �ʵ� ǥ��

		// GameStatus �ʱ�ȭ

		GameStatus = START; // ������ ���� : START

		// PLAYER �ʱ�ȭ

		Player.X = 35;
		Player.Y = 15;

		Player.Life = 3;

		// DOT[] �ʱ�ȭ -> RenDer() �Լ��� StatusPrint() �Լ��� case INIT:
		DotInit(); // Dot �ʱ�ȭ

		// Star �ʱ�ȭ
		StarInit();
		Star.Catch = Star.SumCatch = 0;

	}

	void Update()
	{
		int temp;

		switch (Stage)
		{
		case 0:
			temp = Zero;
			break;

		case 1:
			temp = DotNum * 2;
			break;

		case 2:
			temp = DotNum * 4;
			break;
		}

		if (GameStatus == RUNNING)
		{
			for (int i = 0; i < temp; i++)
			{
				MoveCoord(i); // ��ǥ�̵�

				IfCrash(i);
			}
		}
	}

	void Render()
	{
		char string[100];

		char MoveLine[] = { "===============================================================================" }; // �ൿ���� ����

		ScreenClear();

		// ������

		StatusPrint();

		if (GameStatus == RUNNING || GameStatus == STOP || GameStatus == GO)
		{
			sprintf(string, "\tLife : %d        Star : %d (�� %d �� )          ���� ���� : Q ��ư\n", Player.Life, Star.Catch, Star.SumCatch);
			ScreenPrint(0, 0, string);
			ScreenPrint(0, 1, MoveLine);

			// 1, 2 ������������ MoveLine

			if (Stage != 2)
			{
				ScreenPrint(0, Player.Y - 1, MoveLine);
				ScreenPrint(0, Player.Y + 1, MoveLine);
			}

			ScreenPrint(Player.X, Player.Y, Player_Shape); // �÷��̾� ǥ��

			// Dot ǥ��

			switch (Stage)
			{
			case 2:
				for (int i = DotNum * 2; i < DotNum * 3; i++) // ��
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[2]); // �� ǥ��
				}
				for (int i = DotNum * 3; i < DotNum * 4; i++) // ��
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[3]); // �� ǥ��
				}

			case 1:
				for (int i = DotNum; i < DotNum * 2; i++) // ��
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[1]); // �� ǥ��
				}

				for (int i = 0; i < DotNum; i++) // ��
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[0]); // �� ǥ��
				}
				break;

			case 0:
				for (int i = 0; i < Zero; i++) // ��
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[0]); // �� ǥ��
				}
				break;
			}

			ScreenPrint(Star.X, Star.Y, Star_Shape); // Star ǥ��
		}
		ScreenFlipping();
	}

	void Release()
	{

	}

	void Dodge()
	{
		int Key;
		clock_t CurTime;

		ScreenInit();
		Init();

		while (1)
		{
			if (_kbhit())
			{
				Key = _getch();

				if ((Key == 'q') || (Key == 'Q'))
				{
					Stage = 0;
					break;
				}

				if (Key == SPACE)
				{
					//���� ���� / �Ͻ����� 
					switch (GameStatus)
					{
					case START:
						GameStatus = INIT;
						break;

					case RUNNING:
						GameStatus = STOP;
						break;

					case GO:
						GameStatus = RUNNING;
						break;

					case STOP:
						GameStatus = RUNNING;
						break;
					}
				}

				if (GameStatus != GO && GameStatus != STOP)
					KeyControl(Key);

			}

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

}