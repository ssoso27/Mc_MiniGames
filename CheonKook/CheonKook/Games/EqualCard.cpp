#include "Header.h"
#include "EqualCard.h"

namespace SH_EqualCard
{
	// ���
	const int MaxCardCount = 16; // �ִ� Card�� ����
	const int MaxTypeCount = 8; // �ִ� Type�� ����

	// ������
	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32,
		ESC = 27
	};

	// ����ü���� & ����������
	CARD Card[MaxCardCount]; // Card ����
	GAMESTATUS GameStatus;
	BOARD Board;
	CHOICE Choice;
	STAGE Stage;

	// ��������
	// ��� ����
	char PrintArray[MaxTypeCount][3] = { "��" , "��" , "��" , "��" , "��" , "��" , "��" , "��" }; // Ÿ�Կ� ���� ��� �迭
	char CoverPrint[3] = "��";
	char StatString[500]; // ȭ�� ��� ����
	double PrintTime = 2.0 * 1000; // ȭ�� ��� �ð�
	clock_t Stat_OldTime = clock(); // PrintTime�� OldTime
	clock_t G_OldTime = clock(); // ���� ����ӵ� ����

	// Card ����
	int CardCountArray[3] = { 12, 16, 16 };
	int TypeCountArray[3] = { 6, 8, 8 };
	int ViewCard[2] = { -1, -1 }; // ���̴� Card�� index ����
	bool IsMatchCard[MaxCardCount] = {}; // ���� ī�� �Ǻ�
	int selectChance; // ������ �� �ִ� ��ȸ
	int matchCardCount; // ¦�� ���� Card

	// Game ���� ����
	int ChanceArray[3] = { 30, 40, 30 };
	clock_t Open_OldTime; // Update �ð� ������
	double TurnTime = 1.2 * 1000; // Ŀ�� ���������� �ð�

	// �Լ�

	void CardOpening() // Card�� ���µǾ� �ִ� ������ �۾�
	{
		clock_t CurTime = clock();

		if (IsEqualType()) // ���õ� �� ī���� Type�� ������
		{
			// ���� ī�� ó��
			IsMatchCard[ViewCard[0]] = true;
			IsMatchCard[ViewCard[1]] = true;
			matchCardCount++;

			// ViewCard -1 ó��
			ViewCard[0] = -1;
			ViewCard[1] = -1;
		}
		else // Type�� �ٸ���
		{
			// ���� �ð��� ���� ��, ViewCell[]�� -1 ���� �ʱ�ȭ�ϸ� Card[i].PrintForm = CoverPrint;
			if (CurTime - Open_OldTime > TurnTime)
			{
				// Cover �ٽ� �����
				Card[ViewCard[0]].PrintForm = CoverPrint;
				Card[ViewCard[1]].PrintForm = CoverPrint;

				// ViewCard -1 ó��
				ViewCard[0] = -1;
				ViewCard[1] = -1;
			}
		}
	}

	bool IsEqualType() // ���� Type���� �Ǻ�
	{
		if (Card[ViewCard[0]].Type == Card[ViewCard[1]].Type)
			return true;
		else
			return false;
	}

	void SelectCard()
	{
		int select; // ���õ� ī��

		select = Choice.select - 1;

		if (IsMatchCard[select]) // �̹� ���� ī��� return
			return;

		// ViewCell[0] �Ǵ� ViewCell[1]�� Card�� index �Է�
		if (ViewCard[0] == -1)
		{
			ViewCard[0] = select;
		}
		else
		{
			if (ViewCard[0] == select) // ���� CellNum �ߺ� ����
				return;

			ViewCard[1] = select;
			Open_OldTime = clock();
		}

		// Card.select �� ���� Card ����
		// ���õ� ī��� Card[i].PrintForm = PrintArray[Card[i].Type]
		Card[select].PrintForm = PrintArray[Card[select].Type];


		selectChance--; // ������ ��ȸ ����
	}

	void AssignCoord()// ��ǥ �ο� �Լ�
	{
		/*
		1 2 3 4
		5 6 7 8
		9 10 11 12
		13 14 15 16
		*/

		// Choice ��ǥ �ο�
		switch (Choice.select)
		{
		case 1: // X, Y �ο�
			Choice.X = 21;
			Choice.Y = 8;
			break;

		case 2:
			Choice.X = 31;
			Choice.Y = 8;
			break;

		case 3:
			Choice.X = 41;
			Choice.Y = 8;
			break;

		case 4:
			Choice.X = 51;
			Choice.Y = 8;
			break;

		case 5:
			Choice.X = 21;
			Choice.Y = 12;
			break;

		case 6:
			Choice.X = 31;
			Choice.Y = 12;
			break;

		case 7:
			Choice.X = 41;
			Choice.Y = 12;
			break;

		case 8:
			Choice.X = 51;
			Choice.Y = 12;
			break;

		case 9:
			Choice.X = 21;
			Choice.Y = 16;
			break;

		case 10:
			Choice.X = 31;
			Choice.Y = 16;
			break;

		case 11:
			Choice.X = 41;
			Choice.Y = 16;
			break;

		case 12:
			Choice.X = 51;
			Choice.Y = 16;
			break;

			// Stage Up

		case 13:
			Choice.X = 21;
			Choice.Y = 20;
			break;

		case 14:
			Choice.X = 31;
			Choice.Y = 20;
			break;

		case 15:
			Choice.X = 41;
			Choice.Y = 20;
			break;

		case 16:
			Choice.X = 51;
			Choice.Y = 20;
			break;

		default:
			break;

		}

		// Card ��ǥ �ο�
		for (int index = 0; index < Stage.CardCount; index++)
		{
			switch (Card[index].CellNum)
			{
			case 1: // X, Y �ο�
				Card[index].X = 24;
				Card[index].Y = 8;
				break;

			case 2:
				Card[index].X = 34;
				Card[index].Y = 8;
				break;

			case 3:
				Card[index].X = 44;
				Card[index].Y = 8;
				break;

			case 4:
				Card[index].X = 54;
				Card[index].Y = 8;
				break;

			case 5:
				Card[index].X = 24;
				Card[index].Y = 12;
				break;

			case 6:
				Card[index].X = 34;
				Card[index].Y = 12;
				break;

			case 7:
				Card[index].X = 44;
				Card[index].Y = 12;
				break;

			case 8:
				Card[index].X = 54;
				Card[index].Y = 12;
				break;

			case 9:
				Card[index].X = 24;
				Card[index].Y = 16;
				break;

			case 10:
				Card[index].X = 34;
				Card[index].Y = 16;
				break;

			case 11:
				Card[index].X = 44;
				Card[index].Y = 16;
				break;

			case 12:
				Card[index].X = 54;
				Card[index].Y = 16;
				break;

				// Stage Up

			case 13:
				Card[index].X = 24;
				Card[index].Y = 20;
				break;

			case 14:
				Card[index].X = 34;
				Card[index].Y = 20;
				break;

			case 15:
				Card[index].X = 44;
				Card[index].Y = 20;
				break;

			case 16:
				Card[index].X = 54;
				Card[index].Y = 20;
				break;

			default:
				break;

			}
		}
	}

	void AssignCell()
	{
		for (int i = 0; i < Stage.CardCount; i++)
		{
			Card[i].CellNum = i + 1;
		}
	}

	void AssignType(int start, int end) // Type �ο� �Լ�
	{
		int randomnum;
		int IsOverlapType[MaxTypeCount] = { 0, }; // �ߺ� �Ǻ��� int �迭

		srand((unsigned)time(NULL));

		for (int i = 0; i < Stage.CardCount; )
		{
			randomnum = (rand() % (end - start)) + start; // start ~ end ������ ���� ����

			if (IsOverlapType[randomnum] < 2) // �ߺ� 0 ~ 1 ȸ
			{
				++IsOverlapType[randomnum]; // �ߺ� ǥ��
				Card[i].Type = randomnum; // �� ����
				++i; // ���� Card[i] �� �Ѿ
			} // if�� ����
		} // for�� ����

	}

	void AssignForm() // PrintForm �ο�
	{
		for (int i = 0; i < Stage.CardCount; i++)
		{
			Card[i].PrintForm = CoverPrint; // Cover �����
		}
	}

	void CreateCard() // ī�� ���� �Լ�
	{
		AssignCell(); // CellNum �ο� �Լ�
		AssignCoord(); // CellNum�� ���� ��ǥ �ο�
		AssignType(0, Stage.TypeCount); // Type �ο� �Լ� (����. �ߺ� 1ȸ) 
		AssignForm();// PrintForm �ο�
	}

	void KeyControl(int key)
	{
		// ��� ���¿���

		// START ���¿���
		if (GameStatus == START)
		{
			if (key == SPACE)
			{
				GameStatus = INIT;
			}
		}

		// RUNNING ���¿���
		if (GameStatus == RUNNING)
		{
			switch (key)
			{
			case UP:
				if (Choice.select > 4)
					Choice.select -= 4;
				break;

			case DOWN:
				if (Choice.select < Stage.CardCount - 3)
					Choice.select += 4;
				break;

			case LEFT:
				if ((Choice.select != 1) && (Choice.select != 5) && (Choice.select != 9) && (Choice.select != 13))
					Choice.select--;
				break;

			case RIGHT:
				if ((Choice.select != 4) && (Choice.select != 8) && (Choice.select != 12))
					Choice.select++;
				break;

			case SPACE:
				if (ViewCard[1] == -1) // Card�� �� �� Open�� �ƴ϶��
				{
					SelectCard();
				}
				break;

			default:
				break;
			}
		}

		// SUCCESS ���¿���
		if (GameStatus == SUCCESS)
		{
			switch (key)
			{
			case 'Y': case 'y':
				if (Stage.Level < 2)
				{
					Stage.Level++;
					GameStatus = INIT;
				}
				else
				{
					GameStatus = RESULT;
				}
				break;

			case 'N': case 'n':
				GameStatus = RESULT;
				break;
			}
		}

		// FAILED ���¿���
		if (GameStatus == FAILED)
		{
			switch (key)
			{
			case 'Y': case 'y':
				GameStatus = INIT;
				break;

			case 'N': case 'n':
				GameStatus = RESULT;
				break;
			}
		}
	}

	void StatusPrint()
	{
		clock_t CurTime = clock();

		switch (GameStatus)
		{
		case START:
			sprintf(StatString, "\t\t\t  [���� ī�� ���߱�] \n\n"
				"\t\t===================================\n\n"
				"\t\t���� ī�带 ���ߴ� �����Դϴ�.\n"
				"\t\t�������� �� ������ ������ �ֽ��ϴ�.\n"
				"\t\tī�带 ���� ���߸� �̼� �����Դϴ�.\n"
				"\t\t������ ��ȸ�� 0�� �Ǹ� �̼� �����Դϴ�.\n"
				"\t\t���������� �� 3������ �����Ǿ��ֽ��ϴ�.\n\n"
				"\t\t===================================\n\n"
				"\t\t\t  - �� �� �� -\n\n"
				"\t\t�̵� : ����Ű | ī�� ���� : SPACE BAR\n"
				"\t\t-----------------------------------\n"
				"\t\t���� ���� : SPACE BAR | ���� ���� : q\n\n\n\n");
			ScreenPrint(0, 3, StatString);
			break;

		case INIT:
			// �ʱ�ȭ
			// Card �ʱ�ȭ
			Stage.CardCount = CardCountArray[Stage.Level]; // Stage Card ��
			Stage.TypeCount = TypeCountArray[Stage.Level]; // Stage CardType ��
			CreateCard();	// ī�� ���� �Լ�
			matchCardCount = 0; // ���� Card ��
			for (int i = 0; i < MaxCardCount; i++)
			{
				IsMatchCard[i] = false; // �̹� ���� Card �迭 
			}

			// Chocie �ʱ�ȭ
			Choice.select = 9;

			// Board �ʱ�ȭ
			Board.leftX = 15;
			Board.rightX = BOARD_WIDTH - 15;
			Board.topY = 4;
			Board.bottomY = BOARD_HEIGH - 4;

			// Game ���� �ʱ�ȭ
			selectChance = ChanceArray[Stage.Level];

			// ȭ�����
			if (CurTime - Stat_OldTime < PrintTime)
			{
				sprintf(StatString, "[INIT ȭ��]");
				ScreenPrint(30, 10, StatString);
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
				sprintf(StatString, "[READY] %d ��������", Stage.Level + 1);
				ScreenPrint(25, 10, StatString);
			}
			else
			{
				GameStatus = RUNNING;
				Stat_OldTime = CurTime;
			}
			break;

		case RUNNING:
			if (matchCardCount == (Stage.CardCount / 2))
			{
				GameStatus = SUCCESS;
			}
			else if (selectChance == 0)
			{
				GameStatus = FAILED;
			}
			break;

		case STOP:
			sprintf(StatString, "[STOP ȭ��]");
			ScreenPrint(30, 10, StatString);
			break;

		case SUCCESS:
			if (Stage.Level < 2)
			{
				sprintf(StatString, "%d �������� CLEAR \n\n"
					"\t\t\t���� ��������? [Y/N]", Stage.Level + 1);
			}
			else
			{
				sprintf(StatString, "��� �������� CLEAR \n\n"
					"\t\t\t���� ���â [Y]");
			}
			ScreenPrint(25, 10, StatString);
			break;

		case FAILED:
			sprintf(StatString, " %d �������� GAME OVER\n\n"
				"\t\t\t     �絵��? [Y/N]", Stage.Level + 1);
			ScreenPrint(25, 10, StatString);
			break;

		case RESULT:
			sprintf(StatString, "[���� ����]\n\n"
				"\t\t\t �������� Q�� ��������.");
			ScreenPrint(30, 10, StatString);
			break;

		default:
			break;
		}
	}

	// �����ӿ�ũ �Լ�
	void Init()
	{
		// Game ���� �ʱ�ȭ
		GameStatus = START;
		Stage.Level = 0;
	}

	void Update()
	{
		AssignCoord();

		if (ViewCard[1] != -1) // �� ī�尡 ��� Open
		{
			CardOpening();
		}
	}

	void Render()
	{
		char BarPrint[100];

		ScreenClear();

		// GameStatus�� ���� ȭ�� ��� �Լ�
		StatusPrint();

		// RUNNIG �� ��� ����
		if (GameStatus == RUNNING)
		{
			// ���¹� ���
			sprintf(BarPrint, "���� ������ : %d     ���� ī�� : %d    ���� ī�� : %d", selectChance, matchCardCount, (Stage.CardCount / 2) - matchCardCount);
			ScreenPrint(16, 2, BarPrint);

			// Board ���
			// ���𼭸�
			ScreenPrint(Board.leftX, Board.topY, "��"); // ���� ���
			ScreenPrint(Board.rightX, Board.topY, "��"); // ���� ���
			ScreenPrint(Board.leftX, Board.bottomY, "��"); // ���� �ϴ�
			ScreenPrint(Board.rightX, Board.bottomY, "��"); // ���� �ϴ�

			// ���Ʒ���
			for (int i = Board.leftX + 2; i < Board.rightX; i++)
			{
				ScreenPrint(i, Board.topY, "-");
				ScreenPrint(i, Board.bottomY, "-");
			}
			// �¿캮
			for (int i = Board.topY + 1; i < Board.bottomY; i++)
			{
				ScreenPrint(Board.leftX, i, "��");
				ScreenPrint(Board.rightX, i, "��");
			}

			// Card ���
			if (Stage.CardCount == 12)
			{
				for (int i = 0; i < Stage.CardCount; i++)
				{
					ScreenPrint(Card[i].X, Card[i].Y, Card[i].PrintForm);
				}
			}
			else
			{
				for (int i = 0; i < Stage.CardCount; i++)
				{
					ScreenPrint(Card[i].X, Card[i].Y - 2, Card[i].PrintForm);
				}
			}

			// Choice ���
			if (Stage.CardCount == 12)
			{
				ScreenPrint(Choice.X, Choice.Y, "��");
			}
			else
			{
				ScreenPrint(Choice.X, Choice.Y - 2, "��");
			}
		}
		/*
		//test ����
		for (int i = 0; i < 4; i++)
		{
			ScreenPrint(24 + (10*i), 8, "��");
		}
		for (int i = 0; i < 4; i++)
		{
			ScreenPrint(24, 8 + (4*i), "��");
		}
		//test ��
		*/

		ScreenFlipping();
	}

	void Release()
	{
	}

	void EqualCard()
	{
		int key;
		clock_t CurTime;

		Init();
		ScreenInit();

		while (1)
		{
			if (_kbhit()) // key �Է��� ������
			{
				key = _getch();

				if ((key == 'q') || (key == 'Q'))
				{
					Stage.Level = 0;
					break;
				}

				// key ����
				KeyControl(key);

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