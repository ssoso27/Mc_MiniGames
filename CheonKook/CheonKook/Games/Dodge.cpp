#include "Header.h"
#include "Dodge.h"

namespace SH_Dodge
{
	// 열거형

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32
	};

	// 전역 변수 선언

	// 구조체 변수

	PLAYER Player;
	DOT Dot[DotNum * 4];
	STAR Star;
	GAMESTATUS GameStatus;

	// 스테이지 관련

	int Stage = 0;

	// 게임 상태 관련

	char StatString[500]; // 게임 상태 String
	int PrintTime = 3 * 1000; // 게임 상태 표시 시간
	clock_t Stat_OldTime = clock(); // PrintTime의 OldTime
	clock_t G_OldTime = clock(); // 게임 실행속도 제한

									// 화면에 표시될 모양 

	char Player_Shape[] = { "＊" };
	char Dot_Shape[4][3] = { { "↓" },{ "↑" },{ "→" },{ "←" } };
	char Star_Shape[] = { "★" };


	// 함수 설정

	void KeyControl(int key) // 키 입력 처리
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

	void IfCrash(int i) // Crash 발생 처리
	{
		if ((Player.X == Dot[i].X && Player.Y == Dot[i].Y) || ((Player.X - 1) == Dot[i].X && Player.Y == Dot[i].Y))
		{
			Player.Life--;

			// Dot의 종류에 따른 위치 y값 초기화
			if (Stage != 0)
			{
				if (i >= 0 && i < DotNum) // ↓
					Dot[i].Y = 2;
				else if (i >= DotNum && i < DotNum * 2) // ↑
					Dot[i].Y = BOARD_HEIGHT - 1;
				else if (i >= DotNum * 2 && i < DotNum * 3) // →
					Dot[i].X = 0;
				else // ←
					Dot[i].X = BOARD_WIDTH - 1;
			}
			else // Stage == 0
			{
				Dot[i].Y = 2; // ↓
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
	void MoveCoord(int i) // 좌표 이동
	{
		clock_t CurTime = clock();

		if ((Player.X == Star.X && Player.Y == Star.Y) || ((Player.X - 1) == Star.X && Player.Y == Star.Y))
		{
			Star.Catch++;
			Star.SumCatch++;

			StarInit();
		}

		if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime이 지나야 Update. -> 속도 조절
		{

			// 좌표 이동 시작

			if (Stage == 0) // 첫번째 스테이지 
			{
				Dot[i].Y++; // 좌표 이동

				if (Dot[i].Y == BOARD_HEIGHT - 1) // 벽에 닿을 경우 
				{
					Dot[i].X = rand() % BOARD_WIDTH;
					Dot[i].Y = 2;
					Dot[i].Speed = rand() % 3 + 1;
				}
			}
			else // Stage!=0
			{

				if (i >= 0 && i < DotNum) // ↓
				{
					Dot[i].Y++;
					if (Dot[i].Y == BOARD_HEIGHT - 1)
					{
						Dot[i].X = rand() % BOARD_WIDTH;
						Dot[i].Y = 2;
						Dot[i].Speed = rand() % 3 + 1;
					}
				}
				if ((i >= DotNum) && (i < (DotNum * 2))) // ↑
				{
					Dot[i].Y--;
					if (Dot[i].Y == 2)
					{
						Dot[i].X = rand() % BOARD_WIDTH;
						Dot[i].Y = BOARD_HEIGHT - 1;
						Dot[i].Speed = rand() % 3 + 1;
					}
				}
				if ((i >= (DotNum * 2)) && (i < (DotNum * 3))) // →
				{
					Dot[i].X++;
					if (Dot[i].X == BOARD_WIDTH - 2)
					{
						Dot[i].X = 0;
						Dot[i].Y = (rand() % (BOARD_HEIGHT - 2)) + 2;
						Dot[i].Speed = rand() % 3 + 1;
					}
				}
				if ((i >= (DotNum * 3)) && (i < (DotNum * 4))) // ←
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

			// 시간 재설정

			Dot[i].OldTime = CurTime;

		}
	}

	void DotInit()
	{
		int i;

		srand((unsigned)time(NULL));

		switch (Stage)
		{
		case 2: // → ←
			for (i = DotNum * 2; i < DotNum * 3; i++) // →
			{
				// X Y 좌표 초기화

				Dot[i].X = 0;
				Dot[i].Y = (rand() % (BOARD_HEIGHT - 4)) + 2;

				// Dot 시간 & 속도 설정

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
			}

			for (i = DotNum * 3; i < DotNum * 4; i++) // ←
			{
				// X Y 좌표 초기화

				Dot[i].X = BOARD_WIDTH - 2;
				Dot[i].Y = (rand() % (BOARD_HEIGHT - 4)) + 2;

				// Dot 시간 & 속도 설정

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
			}
		case 1: // ↑↓
			for (i = DotNum; i < DotNum * 2; i++) // ↑
			{
				// X Y 좌표 초기화

				Dot[i].X = rand() % BOARD_WIDTH;
				Dot[i].Y = BOARD_HEIGHT - 1;

				// Dot 시간 & 속도 설정

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
			}

			for (i = 0; i < DotNum; i++) // ↓ ( Stage > 0 )
			{
				// X Y 좌표 초기화

				Dot[i].X = rand() % BOARD_WIDTH;
				Dot[i].Y = 2;

				// Dot 시간 & 속도 설정

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
			}
			break;

		case 0: // ↓
			for (i = 0; i < Zero; i++) // ↓ ( Stage == 0 )
			{
				// X Y 좌표 초기화

				Dot[i].X = rand() % BOARD_WIDTH;
				Dot[i].Y = 2;

				// Dot 시간 & 속도 설정

				Dot[i].OldTime = clock();
				Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
				Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
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
			sprintf(StatString, "\t\t\t  [화살표 피하기 게임] \n\n"
				"\t\t===================================\n\n"
				"\t\t날아오는 화살표를 피하는 게임입니다.\n"
				"\t\t각 스테이지 당 Life는 3 입니다.\n"
				"\t\tLife가 0이 되면 다음 스테이지로 넘어갑니다.\n"
				"\t\tStar(★)를 획득하면 점수가 오릅니다.\n"
				"\t\t스테이지는 총 3레벨로 구성되어있습니다.\n\n"
				"\t\t===================================\n\n"
				"\t\t\t  - 조 작 법 -\n\n"
				"\t\t이동 : 방향키 | 일시정지 : SPACE BAR\n"
				"\t\t＊ : 플레이어 | ★ : Star (목표)\n\n"
				"\t\t-----------------------------------\n"
				"\t\t게임 시작 : SPACE BAR | 게임 종료 : q\n\n\n\n");
			ScreenPrint(0, 3, StatString);

			break;

		case INIT:
			if (CurTime - Stat_OldTime < PrintTime)
			{

				DotInit(); // Dot 초기화
				StarInit(); // Star 초기화
				Star.Catch = 0;

				// Player 초기화
				Player.X = 35;
				Player.Y = 15;
				Player.Life = 3;

				sprintf(StatString, "[INIT] 게임 초기화 \n\n");
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
				sprintf(StatString, "[READY] %d 스테이지", Stage + 1);
				ScreenPrint(25, 10, StatString);
			}
			else
			{
				GameStatus = GO;
				Stat_OldTime = CurTime;
			}

			break;

		case GO:
			sprintf(StatString, "SPACE : 게임 시작 ");
			ScreenPrint(30, 10, StatString);


		case RUNNING:
			Stat_OldTime = CurTime;

			break;

		case STOP:
			sprintf(StatString, "[ STOP 화면 ]\n\n"
				"\t\t\t SPACE : 게임화면으로 돌아감 ");
			ScreenPrint(30, 10, StatString);

			break;

		case NEXT:
			if (CurTime - Stat_OldTime < PrintTime)
			{
				sprintf(StatString, " %d 스테이지 GAME OVER", Stage + 1);
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
			sprintf(StatString, "[ 게임 결과 ]\n\n"
				"\t\t\t 획득한 Star 개수 : %d", Star.SumCatch);
			ScreenPrint(30, 10, StatString);

			break;
		}
	}

	// 프레임워크 함수 시작

	void Init()
	{
		// 필드 표시

		// GameStatus 초기화

		GameStatus = START; // 최초의 상태 : START

		// PLAYER 초기화

		Player.X = 35;
		Player.Y = 15;

		Player.Life = 3;

		// DOT[] 초기화 -> RenDer() 함수의 StatusPrint() 함수의 case INIT:
		DotInit(); // Dot 초기화

		// Star 초기화
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
				MoveCoord(i); // 좌표이동

				IfCrash(i);
			}
		}
	}

	void Render()
	{
		char string[100];

		char MoveLine[] = { "===============================================================================" }; // 행동범위 제한

		ScreenClear();

		// 렌더링

		StatusPrint();

		if (GameStatus == RUNNING || GameStatus == STOP || GameStatus == GO)
		{
			sprintf(string, "\tLife : %d        Star : %d (총 %d 점 )          게임 종료 : Q 버튼\n", Player.Life, Star.Catch, Star.SumCatch);
			ScreenPrint(0, 0, string);
			ScreenPrint(0, 1, MoveLine);

			// 1, 2 스테이지에서 MoveLine

			if (Stage != 2)
			{
				ScreenPrint(0, Player.Y - 1, MoveLine);
				ScreenPrint(0, Player.Y + 1, MoveLine);
			}

			ScreenPrint(Player.X, Player.Y, Player_Shape); // 플레이어 표시

			// Dot 표시

			switch (Stage)
			{
			case 2:
				for (int i = DotNum * 2; i < DotNum * 3; i++) // →
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[2]); // 점 표시
				}
				for (int i = DotNum * 3; i < DotNum * 4; i++) // ←
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[3]); // 점 표시
				}

			case 1:
				for (int i = DotNum; i < DotNum * 2; i++) // ↑
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[1]); // 점 표시
				}

				for (int i = 0; i < DotNum; i++) // ↓
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[0]); // 점 표시
				}
				break;

			case 0:
				for (int i = 0; i < Zero; i++) // ↓
				{
					ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[0]); // 점 표시
				}
				break;
			}

			ScreenPrint(Star.X, Star.Y, Star_Shape); // Star 표시
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
					//게임 시작 / 일시정지 
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