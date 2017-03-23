#include "Header.h"
#include "Screen.h"
#include "FlyBall.h"

namespace SH_FlyBall
{
	// ����ü ���� & ������
	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32,
		ESC = 27
	};

	// �迭
	int createMapCount[3] = { 4 , 6 , 8 }; // ���������� �� ����

	// ���
	const int PlayerFirstX = 10; // �÷��̾��� ���� X��ǥ
	const int PlayerFirstY = 6; // �÷��̾��� ���� Y��ǥ
	const int MaxBlockCount = 512; // Map�� ���� �ִ� Block ��
	const int MAXMAPNUM = 8; // �ִ� Map ��

	// ���� ����
	clock_t G_OldTime = clock(); // ���� ����ӵ� ����
	int MapIndex; // ���� Map�� Index
	char StatString[500]; // ȭ�� ��� ���� ����� char[]
	int PrintTime = 3 * 1000;
	clock_t Stat_OldTime = clock(); // PrintTime�� OldTime

	// ����ü ����
	BLOCK Block[MaxBlockCount];
	BOARD Board;
	PLAYER Player;
	PORTAL Portal[4]; // ��, ��, ��, ��
	GOAL Goal;
	STARTP StartP;
	GAMESTATUS GameStatus;
	STAGE Stage;

	// �迭
	bool IsBlock[Board.Height][Board.Width / 2] = { false, }; // Block ���� ��ġ �Ǻ�

	// �Լ�
	// Start, Goal ���� Map ����
	void SetStartGoal()
	{
		srand((unsigned)time(NULL));

		StartP.whereMap = rand() % createMapCount[Stage.level];

		do
		{
			Goal.whereMap = rand() % createMapCount[Stage.level];
		} while (StartP.whereMap == Goal.whereMap);


	}

	// ���� Map ���� ����
	void MapReset()
	{
		// Player ����
		Player.X = PlayerFirstX;
		Player.Y = PlayerFirstY;
		Player.Direction = M_RIGHT;
		Player.OldTime = clock();
		Player.IsReady = 1;

		// Block ����
		for (int i = 0; i < Board.Height; i++)
		{
			for (int j = 0; j < Board.Width / 2; j++)
			{
				IsBlock[i][j] = false;
			}
		}

		for (int i = 0; i < MaxBlockCount; i++)
		{
			Block[i].X = 0;
			Block[i].Y = 0;
		}

		// Portal ����
		for (int i = 0; i < 4; i++)
		{
			Portal[i].IsEnable = false;
		}

		// Goal ����
		Goal.IsEnable = false;
	}

	// Portal Ȱ��ȭ �� ����
	void SetPortal(int i)
	{
		switch (i)
		{
		case 0: // ��
			Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
			Portal[i].nextMap = MapIndex - 1; // �̵� �� ����
			break;

		case 1: // ��
			Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
			Portal[i].nextMap = MapIndex + 2; // �̵� �� ����
			break;

		case 2: // ��
			Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
			Portal[i].nextMap = MapIndex + 1; // �̵� �� ����
			break;

		case 3: // ��
			Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
			Portal[i].nextMap = MapIndex - 2; // �̵� �� ����
			break;

		default:
			break;
		}
	}

	// Block ��ǥ ����
	void AssignCoord(int k)
	{
		for (int i = 0; i < Board.Height; i++) // i��
		{
			for (int j = 0; j < Board.Width / 2; j++) // j��
			{
				if (IsBlock[i][j] == true) // MapMake()�� ���� ������ ���� �ڸ�
				{
					// Block ��ǥ �ʱ�ȭ
					Block[k].X = Board.leftX + (j * 2) + 1;
					Block[k].Y = Board.topY + i + 1;

					// ���� �ڸ� false
					IsBlock[i][j] = false;

					// k��° Block ��ǥ �ʱ�ȭ ����
					return;
				} // if�� end
			} // for j end
		} // for i end
	}

	// Block Map ����
	void MapMake(int index)
	{
		// Map ������ ���� �ٸ��� ����
		switch (index)
		{
		case 0: // Map0
				// bool IsBlock[][] �� true ������ [14][31]
			for (int i = 2; i <= 31; i++) { IsBlock[0][i] = true; } // 0
			for (int i = 4; i <= 10; i++) { IsBlock[1][i] = true; }	//1
			for (int i = 21; i <= 27; i++) { IsBlock[1][i] = true; }//1
			for (int i = 14; i <= 18; i++) { IsBlock[2][i] = true; }//2
			for (int i = 17; i <= 24; i++) { IsBlock[3][i] = true; }//3		
			for (int i = 0; i <= 13; i++) { IsBlock[4][i] = true; }// 4
			for (int i = 24; i <= 29; i++) { IsBlock[5][i] = true; }//5
			for (int i = 0; i <= 9; i++) { IsBlock[6][i] = true; }//6
			for (int i = 19; i <= 21; i++) { IsBlock[6][i] = true; }//6
			for (int i = 0; i <= 11; i++) { IsBlock[7][i] = true; }//7
			for (int i = 16; i <= 28; i++) { IsBlock[7][i] = true; }//7
			for (int i = 0; i <= 12; i++) { IsBlock[8][i] = true; }//8
			for (int i = 24; i <= 29; i++) { IsBlock[8][i] = true; }//8
			for (int i = 17; i <= 19; i++) { IsBlock[9][i] = true; }//9
			for (int i = 26; i <= 31; i++) { IsBlock[9][i] = true; }//9
			for (int i = 10; i <= 14; i++) { IsBlock[10][i] = true; }//10
			for (int i = 24; i <= 28; i++) { IsBlock[10][i] = true; }//10
			for (int i = 1; i <= 6; i++) { IsBlock[11][i] = true; }//11
			for (int i = 11; i <= 18; i++) { IsBlock[11][i] = true; }//11
			for (int i = 5; i <= 7; i++) { IsBlock[12][i] = true; }//12
			for (int i = 17; i <= 22; i++) { IsBlock[12][i] = true; }//12
			for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14
																	// ��Ż ���� 
			SetPortal(1);
			SetPortal(2);

			break;


		case 1: //Map1
				// bool IsBlock[][] �� true ������ [14][31]
			for (int i = 2; i <= 10; i++) { IsBlock[0][i] = true; } // 0
			for (int i = 21; i <= 31; i++) { IsBlock[0][i] = true; } //0
			for (int i = 5; i <= 8; i++) { IsBlock[1][i] = true; }//1
			for (int i = 17; i <= 19; i++) { IsBlock[1][i] = true; }//1
			for (int i = 2; i <= 3; i++) { IsBlock[2][i] = true; }//2
			for (int i = 11; i <= 29; i++) { IsBlock[2][i] = true; }//2
			for (int i = 11; i <= 29; i++) { IsBlock[3][i] = true; }//3		
			for (int i = 0; i <= 8; i++) { IsBlock[4][i] = true; }// 4
			for (int i = 12; i <= 26; i++) { IsBlock[5][i] = true; }//5
			for (int i = 0; i <= 9; i++) { IsBlock[6][i] = true; }//6
			for (int i = 14; i <= 27; i++) { IsBlock[6][i] = true; }//6
			for (int i = 0; i <= 9; i++) { IsBlock[7][i] = true; }//7
			for (int i = 0; i <= 9; i++) { IsBlock[8][i] = true; }//8
			for (int i = 15; i <= 29; i++) { IsBlock[8][i] = true; }//8
			for (int i = 0; i <= 12; i++) { IsBlock[9][i] = true; }//9
			for (int i = 24; i <= 30; i++) { IsBlock[9][i] = true; }//9
			for (int i = 2; i <= 14; i++) { IsBlock[10][i] = true; }//10
			for (int i = 24; i <= 30; i++) { IsBlock[10][i] = true; }//10
			for (int i = 3; i <= 15; i++) { IsBlock[11][i] = true; }//11
			for (int i = 18; i <= 31; i++) { IsBlock[11][i] = true; }//11
			for (int i = 5; i <= 7; i++) { IsBlock[12][i] = true; }//12
			for (int i = 4; i <= 7; i++) { IsBlock[13][i] = true; }//13
			for (int i = 19; i <= 23; i++) { IsBlock[13][i] = true; }//13
			for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14

																	// ��Ż ���� 
			SetPortal(0);
			SetPortal(1);

			break;


		case 2: //Map2
				// bool IsBlock[][] �� true ������ [14][31]
			for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
			for (int i = 14; i <= 17; i++) { IsBlock[1][i] = true; }//1
			for (int i = 14; i <= 17; i++) { IsBlock[2][i] = true; }//2
			for (int i = 0; i <= 11; i++) { IsBlock[3][i] = true; }//3
			for (int i = 14; i <= 17; i++) { IsBlock[3][i] = true; }//3
			for (int i = 14; i <= 17; i++) { IsBlock[4][i] = true; }//4
			for (int i = 14; i <= 17; i++) { IsBlock[5][i] = true; }//5
			for (int i = 21; i <= 31; i++) { IsBlock[6][i] = true; }//6
			for (int i = 12; i <= 18; i++) { IsBlock[7][i] = true; }//1
			for (int i = 0; i <= 9; i++) { IsBlock[8][i] = true; }//8
			for (int i = 14; i <= 17; i++) { IsBlock[9][i] = true; }//9
			for (int i = 14; i <= 20; i++) { IsBlock[10][i] = true; }//10
			for (int i = 10; i <= 24; i++) { IsBlock[11][i] = true; }//11
			for (int i = 14; i <= 27; i++) { IsBlock[12][i] = true; }//12
			for (int i = 14; i <= 17; i++) { IsBlock[13][i] = true; }//13
			for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14

			// ��Ż ���� (IsEnable, nextMap)
			if (Stage.level != 0)
			{
				SetPortal(1);
			}
			SetPortal(2);
			SetPortal(3);

			break;


		case 3: //Map3
				// bool IsBlock[][] �� true ������ [14][31]
				//0
			for (int i = 6; i <= 9; i++) { IsBlock[0][i] = true; }
			for (int i = 16; i <= 19; i++) { IsBlock[0][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[0][i] = true; }
			//1
			for (int i = 6; i <= 9; i++) { IsBlock[1][i] = true; }
			for (int i = 16; i <= 19; i++) { IsBlock[1][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[1][i] = true; }
			//2
			for (int i = 6; i <= 9; i++) { IsBlock[2][i] = true; }
			for (int i = 16; i <= 19; i++) { IsBlock[2][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[2][i] = true; }
			//3
			for (int i = 0; i <= 3; i++) { IsBlock[3][i] = true; }
			for (int i = 6; i <= 13; i++) { IsBlock[3][i] = true; }
			for (int i = 16; i <= 19; i++) { IsBlock[3][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[3][i] = true; }
			//4
			for (int i = 16; i <= 19; i++) { IsBlock[4][i] = true; }
			for (int i = 22; i <= 28; i++) { IsBlock[4][i] = true; }
			//5
			for (int i = 16; i <= 19; i++) { IsBlock[5][i] = true; }
			for (int i = 22; i <= 28; i++) { IsBlock[5][i] = true; }
			//6
			for (int i = 12; i <= 19; i++) { IsBlock[6][i] = true; }
			//7
			for (int i = 0; i <= 9; i++) { IsBlock[7][i] = true; }
			//8
			for (int i = 23; i <= 28; i++) { IsBlock[8][i] = true; }
			//9
			for (int i = 6; i <= 9; i++) { IsBlock[9][i] = true; }
			for (int i = 22; i <= 28; i++) { IsBlock[9][i] = true; }
			//10
			for (int i = 6; i <= 9; i++) { IsBlock[10][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[10][i] = true; }
			//11
			for (int i = 6; i <= 9; i++) { IsBlock[11][i] = true; }
			for (int i = 16; i <= 19; i++) { IsBlock[11][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[11][i] = true; }
			//12
			for (int i = 6; i <= 9; i++) { IsBlock[12][i] = true; }
			for (int i = 16; i <= 19; i++) { IsBlock[12][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[12][i] = true; }
			//13
			for (int i = 6; i <= 9; i++) { IsBlock[13][i] = true; }
			for (int i = 16; i <= 19; i++) { IsBlock[13][i] = true; }
			for (int i = 25; i <= 28; i++) { IsBlock[13][i] = true; }
			//14
			for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }

			// ��Ż ���� (IsEnable, nextMap)
			SetPortal(0);
			if (Stage.level != 0)
			{
				SetPortal(1);
			}
			SetPortal(3);

			break;


		case 4: //Map4
				// bool IsBlock[][] �� true ������ [14][31]
			for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
			for (int i = 10; i <= 31; i++) { IsBlock[1][i] = true; }//1
			for (int i = 10; i <= 31; i++) { IsBlock[2][i] = true; }//2
			for (int i = 0; i <= 7; i++) { IsBlock[3][i] = true; }//3
			for (int i = 10; i <= 27; i++) { IsBlock[3][i] = true; }//3
			for (int i = 10; i <= 26; i++) { IsBlock[4][i] = true; }//4
			for (int i = 10; i <= 25; i++) { IsBlock[5][i] = true; }//5
			for (int i = 3; i <= 25; i++) { IsBlock[6][i] = true; }//6
			for (int i = 6; i <= 10; i++) { IsBlock[7][i] = true; }//7
			for (int i = 0; i <= 3; i++) { IsBlock[8][i] = true; }//8
			for (int i = 6; i <= 10; i++) { IsBlock[8][i] = true; }//8
			for (int i = 6; i <= 10; i++) { IsBlock[9][i] = true; }//9
			for (int i = 15; i <= 29; i++) { IsBlock[9][i] = true; }//9
			for (int i = 6; i <= 10; i++) { IsBlock[10][i] = true; }//10
			for (int i = 15; i <= 24; i++) { IsBlock[10][i] = true; }//10
			for (int i = 3; i <= 8; i++) { IsBlock[11][i] = true; }//11
			for (int i = 13; i <= 24; i++) { IsBlock[11][i] = true; }//11
			for (int i = 15; i <= 24; i++) { IsBlock[12][i] = true; }//12
			for (int i = 27; i <= 31; i++) { IsBlock[12][i] = true; }//12
			for (int i = 15; i <= 24; i++) { IsBlock[13][i] = true; }//13
			for (int i = 3; i <= 10; i++) { IsBlock[14][i] = true; }//14
			for (int i = 15; i <= 24; i++) { IsBlock[14][i] = true; }//14

			 // ��Ż ���� (IsEnable, nextMap)
			if (Stage.level != 1)
			{
				SetPortal(1);
			}
			SetPortal(2);
			SetPortal(3);

			break;


		case 5: //Map5
				// bool IsBlock[][] �� true ������ [14][31]
			for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
			for (int i = 8; i <= 10; i++) { IsBlock[1][i] = true; }//1
			for (int i = 21; i <= 25; i++) { IsBlock[1][i] = true; }//1
			for (int i = 8; i <= 10; i++) { IsBlock[2][i] = true; }//2
			for (int i = 21; i <= 25; i++) { IsBlock[2][i] = true; }//2
			for (int i = 0; i <= 5; i++) { IsBlock[3][i] = true; }//3
			for (int i = 8; i <= 10; i++) { IsBlock[3][i] = true; }//3
			for (int i = 16; i <= 18; i++) { IsBlock[3][i] = true; }//3
			for (int i = 8; i <= 10; i++) { IsBlock[4][i] = true; }//4
			for (int i = 13; i <= 18; i++) { IsBlock[4][i] = true; }//4
			for (int i = 8; i <= 10; i++) { IsBlock[5][i] = true; }//5
			for (int i = 16; i <= 21; i++) { IsBlock[5][i] = true; }//5
			for (int i = 8; i <= 10; i++) { IsBlock[6][i] = true; }//6
			for (int i = 16; i <= 28; i++) { IsBlock[6][i] = true; }//6
			for (int i = 3; i <= 13; i++) { IsBlock[7][i] = true; }//7
			for (int i = 16; i <= 21; i++) { IsBlock[7][i] = true; }//7
			for (int i = 8; i <= 10; i++) { IsBlock[8][i] = true; }//8
			for (int i = 16; i <= 21; i++) { IsBlock[8][i] = true; }//8
			for (int i = 8; i <= 10; i++) { IsBlock[9][i] = true; }//9
			for (int i = 16; i <= 21; i++) { IsBlock[9][i] = true; }//8
			for (int i = 26; i <= 31; i++) { IsBlock[9][i] = true; }//9
			for (int i = 0; i <= 5; i++) { IsBlock[10][i] = true; }//10
			for (int i = 8; i <= 10; i++) { IsBlock[10][i] = true; }//10
			for (int i = 13; i <= 21; i++) { IsBlock[10][i] = true; }//10
			for (int i = 8; i <= 10; i++) { IsBlock[11][i] = true; }//11
			for (int i = 16; i <= 24; i++) { IsBlock[11][i] = true; }//11
			for (int i = 16; i <= 21; i++) { IsBlock[12][i] = true; }//12
			for (int i = 26; i <= 29; i++) { IsBlock[12][i] = true; }//12
			for (int i = 16; i <= 21; i++) { IsBlock[13][i] = true; }//13
			for (int i = 26; i <= 29; i++) { IsBlock[13][i] = true; }//13
			for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14

			// ��Ż ���� (IsEnable, nextMap)
			SetPortal(0);
			if (Stage.level != 1)
			{
				SetPortal(1);
			}
			SetPortal(3);

			break;

		case 6: //Map6
				// bool IsBlock[][] �� true ������ [14][31]
			for (int i = 0; i <= 6; i++) { IsBlock[0][i] = true; }//0
			for (int i = 18; i <= 31; i++) { IsBlock[0][i] = true; }//0
			for (int i = 4; i <= 7; i++) { IsBlock[1][i] = true; }//1
			for (int i = 19; i <= 31; i++) { IsBlock[1][i] = true; }//1
			for (int i = 5; i <= 8; i++) { IsBlock[2][i] = true; }//2
			for (int i = 6; i <= 9; i++) { IsBlock[3][i] = true; }//3
			for (int i = 2; i <= 5; i++) { IsBlock[5][i] = true; }//5
			for (int i = 11; i <= 13; i++) { IsBlock[5][i] = true; }//5
			for (int i = 1; i <= 4; i++) { IsBlock[6][i] = true; }//6
			for (int i = 11; i <= 13; i++) { IsBlock[6][i] = true; }//6
			for (int i = 0; i <= 13; i++) { IsBlock[7][i] = true; }//7
			for (int i = 17; i <= 31; i++) { IsBlock[7][i] = true; }//7
			for (int i = 0; i <= 13; i++) { IsBlock[8][i] = true; }//8
			for (int i = 17; i <= 31; i++) { IsBlock[8][i] = true; }//8
			for (int i = 10; i <= 12; i++) { IsBlock[9][i] = true; }//9
			for (int i = 10; i <= 12; i++) { IsBlock[10][i] = true; }//10
			for (int i = 10; i <= 12; i++) { IsBlock[11][i] = true; }//11
			for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14
			SetPortal(2);
			SetPortal(3);
			break;

		case 7: //Map7
				// bool IsBlock[][] �� true ������ [14][31]
			for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
			for (int i = 7; i <= 12; i++) { IsBlock[1][i] = true; }//1
			for (int i = 20; i <= 25; i++) { IsBlock[1][i] = true; }//1
			for (int i = 15; i <= 17; i++) { IsBlock[2][i] = true; }//2
			for (int i = 2; i <= 4; i++) { IsBlock[3][i] = true; }//3
			for (int i = 20; i <= 25; i++) { IsBlock[4][i] = true; }//4
			for (int i = 7; i <= 12; i++) { IsBlock[5][i] = true; }//5
			for (int i = 15; i <= 17; i++) { IsBlock[5][i] = true; }//5
			for (int i = 2; i <= 4; i++) { IsBlock[7][i] = true; }//7
			for (int i = 20; i <= 25; i++) { IsBlock[7][i] = true; }//7
			for (int i = 15; i <= 17; i++) { IsBlock[8][i] = true; }//8
			for (int i = 7; i <= 12; i++) { IsBlock[9][i] = true; }//9
			for (int i = 20; i <= 25; i++) { IsBlock[10][i] = true; }//10
			for (int i = 2; i <= 4; i++) { IsBlock[11][i] = true; }//11
			for (int i = 15; i <= 17; i++) { IsBlock[11][i] = true; }//11
			for (int i = 7; i <= 12; i++) { IsBlock[13][i] = true; }//13
			for (int i = 20; i <= 25; i++) { IsBlock[13][i] = true; }//13
			for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14
			SetPortal(0);
			SetPortal(3);
			break;

		default:
			break;
		}

	}

	// index�� �´� Map Block ����
	void CreateBlock(int MapIndex)
	{
		MapReset(); // ���� �� ����

		if (MapIndex == Goal.whereMap) // Goal Map �̸�
			Goal.IsEnable = true; // Goal Ȱ��ȭ

		MapMake(MapIndex); // �� ����
		for (int i = 0; i < MaxBlockCount; i++)
		{
			AssignCoord(i); // ��ǥ �ο�
		}
	}

	// �浹 üũ
	int Collision(int x, int y)
	{
		int count = 0;

		// Player�� Goal�� �浹
		if (Goal.Y == y) // y �Ǵ� y+1�� ����
		{
			if (Goal.X == (x + 1) || Goal.X == (x + 2) ||
				(Goal.X + 1) == (x + 1) || (Goal.X + 1) == (x + 2)) // x �Ǵ� x+1�� ����
			{
				// �浹 �� ����
				GameStatus = SUCCESS; // �̼� ����

				return 1; // �浹 O
			}
		}

		// Player�� Portal[i]�� �浹
		for (int i = 0; i < 4; i++)
		{
			if (Portal[i].IsEnable == false) // ��ȿ���� ���� ��Ż�̸�
				continue;

			if (Portal[i].Y == y) // y �Ǵ� y+1�� ����
			{
				if (Portal[i].X == (x + 1) || Portal[i].X == (x + 2) ||
					(Portal[i].X + 1) == (x + 1) || (Portal[i].X + 1) == (x + 2)) // x �Ǵ� x+1�� ����
				{
					// �浹 �� ����
					// Portal[i].nextMap�� ���� �� �̵�
					MapIndex = Portal[i].nextMap;
					CreateBlock(MapIndex);

					return 1; // �浹 O
				}
			}
		}
		// Player�� Block�� �浹
		for (int i = 0; i < MaxBlockCount; i++)
		{
			if (Block[i].Y == y) // y �Ǵ� y+1�� ����
			{
				if (Block[i].X == (x + 1) || Block[i].X == (x + 1) ||
					(Block[i].X + 1) == (x + 2) || (Block[i].X + 1) == (x + 2)) // x �Ǵ� x+1�� ����
				{
					// Player ���� �ʱ�ȭ
					Player.X = PlayerFirstX;
					Player.Y = PlayerFirstY;
					Player.Direction = M_RIGHT;
					Player.OldTime = clock();
					Player.IsReady = 1;

					// �浹 �� ����
					Player.Life--; // Life ����

					count++; // �浹üũ
				}
			}
		}

		if (count > 0)
			return 1;

		// Player�� ���� �浹
		if (y < Board.topY + 1 || x > Board.rightX - 1 || y > Board.bottomY - 1 || x < Board.leftX + 1)
		{
			// �浹 �� ����
			Player.Life--; // Life ����

						   // Player ���� �ʱ�ȭ
			Player.X = PlayerFirstX;
			Player.Y = PlayerFirstY;
			Player.Direction = M_RIGHT;
			Player.OldTime = clock();
			Player.IsReady = 1;

			return 1; // �浹 O
		}

		return 0; // �浹 X
	}

	// Player�� �̵�
	void PlayerMove(clock_t CurTime)
	{
		if (Player.IsReady == 0) // �غ���°� �ƴϸ�
		{
			if (CurTime - Player.OldTime > Player.MoveTime) // �̵����ѽð� ���
			{
				Player.OldTime = CurTime;

				// ���⿡ ���� ��ǥ ��ȭ 
				switch (Player.Direction)
				{
				case M_TOP:
					if (Collision(Player.X, Player.Y - 1) == 0) // �̵��� ��ǥ���� �浹�� �� �Ͼ�� 
					{
						Player.Y--; // �̵��Ѵ�
					}
					// �浹�� �Ͼ�� ���, Collision���� �浹 ó��
					break;

				case M_RIGHT:
					if (Collision(Player.X + 2, Player.Y) == 0)
					{
						Player.X += 2;
					}
					break;

				case M_BOTTOM:
					if (Collision(Player.X, Player.Y + 1) == 0)
					{
						Player.Y++;
					}
					break;

				case M_LEFT:
					if (Collision(Player.X - 2, Player.Y) == 0)
					{
						Player.X -= 2;
					}
					break;

				default:
					break;

				}
			}
			if (Player.X < 0 || Player.X >BOARD_WIDTH || Player.Y < 0 || Player.Y > BOARD_HEIGH) // ���� �浹
			{
				Player.IsReady = 1;
				Player.Direction = M_RIGHT;
				Player.X = PlayerFirstX;
				Player.Y = PlayerFirstY;
			}
		}
		else // �غ� ���¸�
		{
			Player.X = PlayerFirstX;
			Player.Y = PlayerFirstY;
		}
	}

	// Ű����
	void KeyControl(int key)
	{
		int direction;

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
			case SPACE:
				//(Player.IsReady == 1) ? (Player.IsReady = 0) : (Player.IsReady = 1); // Player.IsReady �ٲ� 
				if (Player.IsReady == 1)
				{
					Player.OldTime = clock();
					Player.IsReady = 0; // �غ� O -> �غ� X
				}
				break;

			case UP: // ��
				if (Player.IsReady == 0)
				{
					direction = M_TOP;
					Player.Direction = (DIRECT)direction;
					Player.OldTime = clock();
				}
				break;

			case RIGHT: // ��
				if (Player.IsReady == 0)
				{
					direction = M_RIGHT;
					Player.Direction = (DIRECT)direction;
					Player.OldTime = clock();
				}
				break;

			case DOWN: // ��
				if (Player.IsReady == 0)
				{
					direction = M_BOTTOM;
					Player.Direction = (DIRECT)direction;
					Player.OldTime = clock();
				}
				break;

			case LEFT: // ��
				if (Player.IsReady == 0)
				{
					direction = M_LEFT;
					Player.Direction = (DIRECT)direction;
					Player.OldTime = clock();
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
				if (Stage.level != 2)
				{
					Stage.level++;
					MapReset();
					GameStatus = INIT;
				}
				else
				{
					GameStatus = RESULT;
				}
				break;

			case 'N': case 'n':
				MapReset();
				GameStatus = RESULT;
				break;

			default:
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

			default:
				break;
			}
		}
	}

	// ���¿� ���� ��� & ��ȭ
	void StatusPrint()
	{
		clock_t CurTime = clock();

		switch (GameStatus)
		{
		case START:
			sprintf(StatString, "\t\t\t  [�ö��� ��] \n\n"
				"\t\t===================================\n\n"
				"\t\t���� �ε����� �ʰ� ��ǥ�� �����ϴ� �����Դϴ�.\n"
				"\t\t���� ��ü(��)�� �ε����� �������� �����մϴ�.\n"
				"\t\t��Ż(��)�� ���� Map�� �̵��� �� �ֽ��ϴ�.\n"
				"\t\t��������(G)�� �����ϸ� �̼� �����Դϴ�.\n"
				"\t\t���������� �� 3������ �����Ǿ��ֽ��ϴ�.\n\n"
				"\t\t===================================\n\n"
				"\t\t\t  - �� �� �� -\n\n"
				"\t\t�̵� : ����Ű | �̵� ���� : SPACE BAR\n"
				"\t\t-----------------------------------\n"
				"\t\t���� ���� : SPACE BAR | ���� ���� : q\n\n\n\n");
			ScreenPrint(0, 3, StatString);
			break;

		case INIT:
			// �ʱ�ȭ
			for (int i = 0; i < 4; i++)
			{
				Portal[i].IsEnable = false; // ��� Portal ��Ȱ��ȭ
			}

			// Start, Goal ���� �ʱ�ȭ
			Goal.X = 70;
			Goal.Y = 18;
			SetStartGoal();

			// Map �ʱ�ȭ 
			MapIndex = StartP.whereMap;
			CreateBlock(MapIndex);


			// Player �ʱ�ȭ
			Player.X = PlayerFirstX;
			Player.Y = PlayerFirstY;
			Player.Life = 15;
			Player.Direction = M_RIGHT;
			Player.OldTime = clock();
			Player.IsReady = 1;
			Player.MoveTime = 170;

			// ȭ�� ���
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
				sprintf(StatString, "[��������%d - Map0~%d]", Stage.level+1, createMapCount[Stage.level] - 1);
				ScreenPrint(25, 10, StatString);
			}
			else
			{
				GameStatus = RUNNING;
				Stat_OldTime = CurTime;
			}
			break;

		case RUNNING:
			if (Player.Life <= 0)
			{
				GameStatus = FAILED; // ���� ����
			}
			break;

		case SUCCESS:
			if (Stage.level < 2)
			{
				sprintf(StatString, "%d �������� CLEAR \n\n"
					"\t\t\t���� ��������? [Y/N]", Stage.level + 1);
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
				"\t\t\t     �絵��? [Y/N]", Stage.level + 1);
			ScreenPrint(25, 10, StatString);
			break;

		case RESULT:
			sprintf(StatString, "���� ����. �����ϼ̽��ϴ�. \n"
				"\t\t\t %d ������������ �÷����ϼ̽��ϴ�. \n"
				"\t\t\t �������� Q�� ��������.", Stage.level + 1);
			ScreenPrint(30, 10, StatString); 
			break;

		default:
			break;
		}
	}


	// �����ӿ�ũ �Լ�
	void Init()
	{
		// Stage �ʱ�ȭ
		Stage.level = 0;

		// Board �ʱ�ȭ
		Board.topY = 4;
		Board.bottomY = Board.topY + Board.Height;
		Board.leftX = 8;
		Board.rightX = Board.leftX + Board.Width;

		// Portal �ʱ�ȭ
		// ��
		Portal[0].X = 35;
		Portal[0].Y = 6;
		// ��
		Portal[1].X = 70;
		Portal[1].Y = 10;
		// ��
		Portal[2].X = 35;
		Portal[2].Y = 18;
		// ��
		Portal[3].X = 10;
		Portal[3].Y = 10;

		for (int i = 0; i < 4; i++)
		{
			Portal[i].IsEnable = false; // ��� Portal ��Ȱ��ȭ
		}

		// Start, Goal ���� �ʱ�ȭ
		Goal.X = 70;
		Goal.Y = 18;
		SetStartGoal();

		// Map �ʱ�ȭ
		MapIndex = StartP.whereMap;
		CreateBlock(MapIndex);


		// Player �ʱ�ȭ
		Player.X = PlayerFirstX;
		Player.Y = PlayerFirstY;
		Player.Life = 15;
		Player.Direction = M_RIGHT;
		Player.OldTime = clock();
		Player.IsReady = 1;
		Player.MoveTime = 170;
	}

	void Update()
	{
		clock_t CurTime = clock(); // ���� �ð�

		PlayerMove(CurTime);
	}

	void Render()
	{
		ScreenClear();

		char TheTopBar[81];

		StatusPrint(); // ���º� ȭ�� ���

		// ���� ȭ��
		if (GameStatus == RUNNING)
		{
			// ��ܹ� ���
			sprintf(TheTopBar, "�� �������� : %d | Life : %d  \t\t    [Map%d]", Stage.level + 1, Player.Life, MapIndex);
			ScreenPrint(17, 2, TheTopBar);

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

			// Goal ���
			if (Goal.IsEnable)
			{
				ScreenPrint(Goal.X, Goal.Y, "G");
			}

			// Player ���
			ScreenPrint(Player.X, Player.Y, "-��-");

			// Block ���
			for (int i = 0; i < MaxBlockCount; i++)
			{
				if (Block[i].X == 0 && Block[i].Y == 0) continue; // ��ǥ�� �־����� ���� Block ǥ�� X
				ScreenPrint(Block[i].X, Block[i].Y, "��");
			}

			// Portal ���
			for (int i = 0; i < 4; i++)
			{
				if (Portal[i].IsEnable == false) // ��ȿ���� ���� ��Ż�̸�
					continue;

				ScreenPrint(Portal[i].X, Portal[i].Y, "��");
			}
		}
		ScreenFlipping();
	}

	void FlyBall()
	{
		int key;
		clock_t CurTime;

		Init();
		ScreenInit();

		while (1)
		{
			if (_kbhit())
			{
				key = _getch();

				if (key == 'q' || key == 'Q')
				{	
					Stage.level = 0;
					GameStatus = START;
					break;
				}

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
//996
//997
//998
//999
//1000