#include "Header.h"
#include "Shoot.h"

namespace SB_Shoot
{

	// typedef �ø���
	enum ControlKeys
	{
		SPACE = 32,
		LEFT = 75,
		RIGHT = 77
	};

	clock_t G_OldTime = clock(); // ���� ����ӵ� ����
	GameState p_GameState = START; // ������ ���� : START
	int p_Goal, p_Stage = -1, p_GameStartTime; // GoalIn? , �� ��������, ���� ���� �ð�

	char StateString[500]; // ���� ���� ����
	clock_t p_OldTime; // ���� ���� ���̸� ���� �̵� �ð� ����

	StageInfo p_StageInfo[] = { { 2, 1000 * 20, 2, 20, 3, 300,2}, {10, 1000 * 30, 2, 20, 5, 300,2 } ,{ 15, 1000 * 30, 2, 20, 5, 300,2 } };
	EFFECT Effect;
	GOAL Goal;
	BALL Ball;
	PLAYER Player;
	char strPlayer[] = { "|__��__|" }; //ĳ����
	int Length; // ���ΰ� ĳ���� ����
	int BallCount = 0; // �� ���� ���� ����
	int GoalIn; // GoalIn �ߴ°�?
	clock_t p_LimitTime; // ���� �ð�
	int p_GoalCount; // ��ǥ ���� ����

	// �ʱ�ȭ
	void Init() {

		//StageInfo. �������� �������
		if (p_Stage == -1) // ���� ù ����
			p_Stage = 0;

		p_LimitTime = p_StageInfo[p_Stage].LimitTime; // ���� �ð� ����
		p_GoalCount = p_StageInfo[p_Stage].GoalBall; // ��ǥ ���� ����

		//�÷��̾�
		Player.CenterX = 3; //���ΰ� X �߽� ��ǥ
		Player.CenterY = 15; //���ΰ� Y �߽� ��ǥ 
		Player.MoveX = 20; // ���ΰ� �̵� X��ǥ �ʱ�ȭ
		Player.Y = Player.MoveY = 22; // ���ΰ� �̵� Y��ǥ �ʱ�ȭ
		Player.X = Player.MoveX - Player.CenterX; //���ΰ� ĳ���� ��� ��ǥ
		Length = strlen(strPlayer); //���ΰ� ��ü ����

		//��
		Ball.ReadyB = 1;
		Ball.bMoveX = Player.MoveX;
		Ball.bMoveY = Player.MoveY - 1;
		Ball.MoveTime = 100;

		//��� (����)
		int gLength, i;

		Goal.gMoveX = p_StageInfo[p_Stage].GD_X;
		Goal.gMoveY = p_StageInfo[p_Stage].GD_Y;
		Goal.gLength = p_StageInfo[p_Stage].GD_Length; // ��� ���� = gLength * 2 + 1 
		Goal.MoveTime = p_StageInfo[p_Stage].GD_MoveTime;
		Goal.OldTime = clock();
		Goal.gDistance = p_StageInfo[p_Stage].GD_Dist;
		gLength = Goal.gLength * 2 + 1; // �迭�� �ִ� ����
		for (i = 0; i < gLength; i++) {
			Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
		}

		//�����Ӵ�
		Effect.StayTime = 3000; // �����Ӵ� ȭ�� 3��

		//
		p_OldTime = clock();
	}
	// ������ ����
	void Update()
	{
		clock_t CurTime = clock();
		int gLength = Goal.gLength * 2 + 1;
		int i;



		if ((CurTime - Goal.OldTime) > Goal.MoveTime)
		{
			Goal.OldTime = CurTime;
			if (Goal.gMoveX + Goal.gDistance >= 0 && ((Goal.gLineX[gLength - 1] + 3) + Goal.gDistance) <= 79)
			{
				Goal.gMoveX += Goal.gDistance;
				for (i = 0; i < gLength; i++)
				{
					Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
				}
			}
			else {
				Goal.gDistance = Goal.gDistance * (-1); // ����ٲٱ� 
			}
		}

		if (Ball.ReadyB == 0) //���̵��� 
		{
			if ((CurTime - Ball.OldTime) > Ball.MoveTime) {
				if (Ball.bMoveY - 1 > 0) {
					Ball.bMoveY--;
					Ball.OldTime = CurTime;

					//����Ƕ��ΰ� �浹 
					if (Ball.bMoveX >= Goal.gLineX[0] && Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1]) {
						if (Ball.bMoveY <= Goal.gMoveY) {//�� �ʱ�ȭ 
							Ball.ReadyB = 1;
							Ball.bMoveX = Player.MoveX;
							Ball.bMoveY = Player.MoveY - 1;
							BallCount++; //����
							GoalIn = 1;
							Effect.StartTime = clock();
						}
						//��� �浹 
					}
					else if ((Ball.bMoveX >= Goal.gLineX[0] - 2 && Ball.bMoveX <= Goal.gLineX[0] - 1) || (Ball.bMoveX + 1 >= Goal.gLineX[0] - 2) && (Ball.bMoveX + 1 <= Goal.gLineX[0] - 1) || (Ball.bMoveX >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX <= Goal.gLineX[gLength - 1] + 3) || (Ball.bMoveX + 1 >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1] + 3)) {
						if (Ball.bMoveY <= Goal.gMoveY) {
							Ball.ReadyB = 1;
							Ball.bMoveX = Player.MoveX;
							Ball.bMoveY = Player.MoveY - 1;
						}
					}
				}
				else {
					Ball.ReadyB = 1;
					Ball.bMoveX = Player.MoveX;
					Ball.bMoveY = Player.MoveY - 1;
				}
			}
		}
		else {
			Ball.bMoveX = Player.MoveX;
		}

		//�����Ӵ�
		if (GoalIn == 1)
		{
			if ((CurTime - Effect.StartTime) > Effect.StayTime)
				GoalIn = 0;
		}

		//
		switch (p_GameState)
		{
		case START: // ���� ���� ȭ��

			sprintf(StateString, "\t  [������ ����] \n\n"
				"\t\t===================================\n\n"
				"\t\t���� ���� ��뿡 �ִ� �����Դϴ�.\n"
				"\t\t�� ������������ ���� �ð��� ��ǥ ������ \n"
				"\t\t�ֽ��ϴ�.\n"
				"\t\t���� �ð��� ��ǥ ������ ���� ���� ��,\n"
				"\t\t�Ǵ� ���� �߿� ���� �˴ϴ�.\n\n"
				"\t\t===================================\n\n"
				"\t\t\t  - �� �� �� -\n\n"
				"\t\t�̵� : ����Ű | �� ������ : SPACE BAR\n\n"
				"\t\t-----------------------------------\n"
				"\t\t���� ���� : SPACE BAR | ���� ���� : q\n\n\n\n\n");

			break;

		case INIT: // case �ʱ�ȭ
			if (p_Stage != -1)
			{
				sprintf(StateString, "%s", "���� �� ���� �ʱ�ȭ");
				if (CurTime - p_OldTime > 3000) // ���� ���� ����?
				{
					p_OldTime = CurTime;
					BallCount = 0;
					p_GameState = READY; // READY ���·� �Ѿ
				}
				else // �ð��� �� ����.
				{ // INIT â ���
					sprintf(StateString, "[INIT] ���� �������� �ʱ�ȭ");

					if (CurTime - p_OldTime > 3000) // â ��� ��, ���� ����?
					{
						p_OldTime = CurTime;
					}
				}
			}
			break;

		case READY: // READY ����
			sprintf(StateString, "[READY] %d �������� \n \t\t\t\t\t\t��ǥ Goal : %d\n \t\t\t\t\t\t���� �ð� : %d��", p_Stage + 1, p_GoalCount, p_StageInfo[p_Stage].LimitTime / 1000);
			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
				p_GameState = RUNNING;
				p_GameStartTime = CurTime;
			}
			break;

		case RUNNING: // RUNNING ����
			if (CurTime - p_GameStartTime > p_StageInfo[p_Stage].LimitTime || BallCount >= p_GoalCount) // ���ѽð� LimitTime�� �ѱ� �Ǵ� �̼� ����
			{
				p_GameState = STOP; // STOP ���·� �Ѿ -> �Ǻ�
			}
			else
			{
				sprintf(StateString, "[RUNNING] ���� �ð� : %d��. ���� �ð� : %d", p_StageInfo[p_Stage].LimitTime / 1000, (CurTime - p_GameStartTime) / 1000); // ���� ���
			}
			break;
		case STOP: // STOP ����. ����/���� ����
			if (BallCount >= p_GoalCount)
			{
				p_GameState = SUCCESS;
			}
			else
			{
				p_GameState = FAILED;
			}
			break;
		case SUCCESS: // SUCCESS ����. �̼� ����
			if (p_Stage < 3)
			{
				sprintf(StateString, "�������� %d �̼� ����. ���� �ܰ�? (Y/N)", p_Stage + 1);
			}
			else // ��� �������� Ŭ����
			{
				sprintf(StateString, "��� �������� Ŭ���� \n");
			}

			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
			}
			break;
		case FAILED: // FAILED ����. �̼� ����
			sprintf(StateString, "�������� %d �̼� ����.\n"
				"\t\t�ƹ� Ű�� ������, ���â�� ���ɴϴ�.", p_Stage + 1); // Y,N �Է�. Stage ���� �״��.
			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
			}
			break;
		case RESULT: // RESULT ����. ���� ���
			sprintf(StateString, "[���� ��� ȭ��]\n\n\t\t\t���� �ֱ� ������������ ���� �� �� : %d\n\t\t\t���� �������� : %d", BallCount, p_Stage);
			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
			}
			break;
		}
	}
	// ���
	void Render()
	{
		char string[100] = { 0 };
		ScreenClear();
		int gLength, i;
		// ��� ����

		if (p_GameState == RUNNING)
		{

			// �¿쿡 ���� ���� (Ŭ����) 

			if (Player.X < 0)
				ScreenPrint(0, Player.MoveY, &strPlayer[Player.X * (-1)]);
			else if (Player.MoveX + (Length - Player.MoveX + Player.CenterX + 1) > 79)
			{
				strncat(string, strPlayer, Length - ((Player.MoveX + Player.CenterX + 1) - 79));
				ScreenPrint(Player.X, Player.Y, string);
			}
			else {
				ScreenPrint(Player.X, Player.Y, strPlayer);
			}

			ScreenPrint(Ball.bMoveX, Ball.bMoveY, "��");
			sprintf(string, "���ΰ� �̵���ǥ : %d, %d              �� �� : %d/%d               �ʱ�ȭ : R ��ư ", Player.MoveX, Player.Y, BallCount, p_GoalCount);
			ScreenPrint(0, 0, string);


			//��� ��� 

			ScreenPrint(Goal.gMoveX, Goal.gMoveY, "��");
			gLength = Goal.gLength * 2 + 1;

			for (i = 0; i < gLength; i++)
				ScreenPrint(Goal.gLineX[i], Goal.gMoveY, "��");

			ScreenPrint(Goal.gLineX[gLength - 1] + 2, Goal.gMoveY, "��");

			//�����Ӵ� ���

			if (GoalIn == 1)
			{
				//ScreenClear();
				//GoalCere(10,5);
				ScreenPrint(50, 5, "** G O A L  I N **");
			}

		}
		// ���� ���
		ScreenPrint(20, 10, StateString);

		//��� ��


		ScreenFlipping();
	}

	//����

	void Release()
	{
	}


	void Shoot()
	{
		int Key, Remain;
		clock_t CurTime;

		ScreenInit();
		Init(); // �ʱ�ȭ

		while (1) //���ѹݺ� 
		{
			if (_kbhit()) // Ű �Է�?
			{
				Key = _getch();
				if (p_GameState == RESULT) // RESULT Ű�Է� -> ����
				{
					p_GameState = START;
					break;
				}

				// RESULT ���°� �ƴ� ��

				if (Key == 'q' || Key == 'Q')
				{
					p_Stage = -1;
					p_GameState = START;
					break;
				}

				// START ���¿����� Ű ����
				if (p_GameState == START)
				{
					if (Key == SPACE)
						p_GameState = INIT;
				}

				// SUCCESS ���¿����� Ű ����
				if (p_GameState == SUCCESS)
				{
					p_OldTime = clock();
					switch (Key)
					{
					case 'Y': case 'y':
						if (p_Stage < 2) 
						{
							++p_Stage;
							p_GameState = INIT;
						}
						else // ��� ���� Ŭ����
						{
							p_GameState = RESULT;
						}

						break;
					case 'N': case 'n':
						p_GameState = RESULT;
						break;
					}
				}
				// FAILED ���¿����� Ű ����
				if (p_GameState == FAILED)
				{
					p_GameState = RESULT;
					p_OldTime = clock();
					p_Stage--;

					getchar();
				}
				/*
				if (p_GameState == FAILED || p_GameState==SUCCESS)
				{
					switch (Key)
					{
					case 'Y': case 'y':
						if (p_GameState == SUCCESS)
						{
							++p_Stage; // �̼Ǽ��� + �������� ���� ��, �������� ���� ����
							p_GameState = INIT;
						}
						if (p_GameState==FAILED)
							p_GameState = RESULT;
						p_OldTime = clock();
						break;
					case 'N': case 'n':
						if (p_GameState == FAILED)
						{
							p_Stage--; // ���Ӱ��â�� ���� --
						}
						p_GameState = RESULT;
						p_OldTime = clock();
						break;
					}
				}
				*/
				switch (Key)
				{
					// S F Y
				case 'S': case 's':
					p_Goal = 1;
					break;
				case 'F': case 'f':
					p_Goal = 0;
					break;

					// �÷��̾� ĳ���� ����
				case LEFT:
					if (Player.MoveX > 0) {
						Player.MoveX--;
						Remain = Length - (Player.CenterX + 1); // �������� = ��ü ���� - (�߽���ǥ + 1)
						if (Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX < 0)
							Player.MoveX--;
						Player.X = Player.MoveX - Player.CenterX;
					}
					break;
				case RIGHT:
					if (Player.MoveX + 1 < 79) {
						Player.MoveX++;
						Remain = Length - (Player.CenterX + 1);
						if (Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX < 0)
							Player.MoveX++;
						Player.X = Player.MoveX - Player.CenterX;
					}
					break;
				case SPACE:
					if (Ball.ReadyB)
					{
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						Ball.OldTime = clock();
						Ball.ReadyB = 0;
					}

					break;
				case 'r':
					if (BallCount != 0)
					{
						BallCount = 0;
						Ball.ReadyB = 1;
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						p_GameState = INIT;
					}
					break;
				}
			}

			Update();//������ ���� 
			Render(); //ȭ�� ��� 

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