#include "Header.h"
#include "EqualCard.h"

namespace SH_EqualCard
{
	// 상수
	const int MaxCardCount = 16; // 최대 Card의 개수
	const int MaxTypeCount = 8; // 최대 Type의 개수

	// 열거형
	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32,
		ESC = 27
	};

	// 구조체변수 & 열거형변수
	CARD Card[MaxCardCount]; // Card 생성
	GAMESTATUS GameStatus;
	BOARD Board;
	CHOICE Choice;
	STAGE Stage;

	// 전역변수
	// 출력 관련
	char PrintArray[MaxTypeCount][3] = { "☆" , "◇" , "♡" , "♤" , "♧" , "△" , "▣" , "◐" }; // 타입에 따른 출력 배열
	char CoverPrint[3] = "▒";
	char StatString[500]; // 화면 출력 문구
	double PrintTime = 2.0 * 1000; // 화면 출력 시간
	clock_t Stat_OldTime = clock(); // PrintTime의 OldTime

	// Card 관련
	int CardCountArray[3] = { 12, 16, 16 };
	int TypeCountArray[3] = { 6, 8, 8 };
	int ViewCard[2] = { -1, -1 }; // 보이는 Card의 index 저장
	bool IsMatchCard[MaxCardCount] = {}; // 맞춘 카드 판별
	int selectChance; // 뒤집을 수 있는 기회
	int matchCardCount; // 짝을 맞춘 Card

	// Game 진행 관련
	int ChanceArray[3] = { 30, 40, 30 };
	clock_t Open_OldTime; // Update 시간 측정용
	double TurnTime = 1.2 * 1000; // 커버 씌우기까지의 시간

	// 함수

	void CardOpening() // Card가 오픈되어 있는 동안의 작업
	{
		clock_t CurTime = clock();

		if (IsEqualType()) // 선택된 두 카드의 Type이 같으면
		{
			// 맞춘 카드 처리
			IsMatchCard[ViewCard[0]] = true;
			IsMatchCard[ViewCard[1]] = true;
			matchCardCount++;

			// ViewCard -1 처리
			ViewCard[0] = -1;
			ViewCard[1] = -1;
		}
		else // Type이 다르면
		{
			// 일정 시간이 지난 후, ViewCell[]을 -1 으로 초기화하며 Card[i].PrintForm = CoverPrint;
			if (CurTime - Open_OldTime > TurnTime)
			{
				// Cover 다시 씌우기
				Card[ViewCard[0]].PrintForm = CoverPrint;
				Card[ViewCard[1]].PrintForm = CoverPrint;

				// ViewCard -1 처리
				ViewCard[0] = -1;
				ViewCard[1] = -1;
			}
		}
	}

	bool IsEqualType() // 같은 Type인지 판별
	{
		if (Card[ViewCard[0]].Type == Card[ViewCard[1]].Type)
			return true;
		else
			return false;
	}

	void SelectCard()
	{
		int select; // 선택된 카드

		select = Choice.select - 1;

		if (IsMatchCard[select]) // 이미 맞춘 카드면 return
			return;

		// ViewCell[0] 또는 ViewCell[1]에 Card의 index 입력
		if (ViewCard[0] == -1)
		{
			ViewCard[0] = select;
		}
		else
		{
			if (ViewCard[0] == select) // 같은 CellNum 중복 방지
				return;

			ViewCard[1] = select;
			Open_OldTime = clock();
		}

		// Card.select 에 따른 Card 선택
		// 선택된 카드는 Card[i].PrintForm = PrintArray[Card[i].Type]
		Card[select].PrintForm = PrintArray[Card[select].Type];


		selectChance--; // 뒤집기 기회 감소
	}

	void AssignCoord()// 좌표 부여 함수
	{
		/*
		1 2 3 4
		5 6 7 8
		9 10 11 12
		13 14 15 16
		*/

		// Choice 좌표 부여
		switch (Choice.select)
		{
		case 1: // X, Y 부여
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

		// Card 좌표 부여
		for (int index = 0; index < Stage.CardCount; index++)
		{
			switch (Card[index].CellNum)
			{
			case 1: // X, Y 부여
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

	void AssignType(int start, int end) // Type 부여 함수
	{
		int randomnum;
		int IsOverlapType[MaxTypeCount] = { 0, }; // 중복 판별용 int 배열

		srand((unsigned)time(NULL));

		for (int i = 0; i < Stage.CardCount; )
		{
			randomnum = (rand() % (end - start)) + start; // start ~ end 범위의 랜덤 숫자

			if (IsOverlapType[randomnum] < 2) // 중복 0 ~ 1 회
			{
				++IsOverlapType[randomnum]; // 중복 표시
				Card[i].Type = randomnum; // 값 대입
				++i; // 다음 Card[i] 로 넘어감
			} // if문 종료
		} // for문 종료

	}

	void AssignForm() // PrintForm 부여
	{
		for (int i = 0; i < Stage.CardCount; i++)
		{
			Card[i].PrintForm = CoverPrint; // Cover 씌우기
		}
	}

	void CreateCard() // 카드 생성 함수
	{
		AssignCell(); // CellNum 부여 함수
		AssignCoord(); // CellNum에 따른 좌표 부여
		AssignType(0, Stage.TypeCount); // Type 부여 함수 (랜덤. 중복 1회) 
		AssignForm();// PrintForm 부여
	}

	void KeyControl(int key)
	{
		// 모든 상태에서

		// START 상태에서
		if (GameStatus == START)
		{
			if (key == SPACE)
			{
				GameStatus = INIT;
			}
		}

		// RUNNING 상태에서
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
				if (ViewCard[1] == -1) // Card가 둘 다 Open이 아니라면
				{
					SelectCard();
				}
				break;

			default:
				break;
			}
		}

		// SUCCESS 상태에서
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

		// FAILED 상태에서
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
			sprintf(StatString, "\t\t\t  [같은 카드 맞추기] \n\n"
				"\t\t===================================\n\n"
				"\t\t같은 카드를 맞추는 게임입니다.\n"
				"\t\t스테이지 당 뒤집기 제한이 있습니다.\n"
				"\t\t카드를 전부 맞추면 미션 성공입니다.\n"
				"\t\t뒤집기 기회가 0이 되면 미션 실패입니다.\n"
				"\t\t스테이지는 총 3레벨로 구성되어있습니다.\n\n"
				"\t\t===================================\n\n"
				"\t\t\t  - 조 작 법 -\n\n"
				"\t\t이동 : 방향키 | 카드 선택 : SPACE BAR\n"
				"\t\t-----------------------------------\n"
				"\t\t게임 시작 : SPACE BAR | 게임 종료 : q\n\n\n\n");
			ScreenPrint(0, 3, StatString);
			break;

		case INIT:
			// 초기화
			// Card 초기화
			Stage.CardCount = CardCountArray[Stage.Level]; // Stage Card 수
			Stage.TypeCount = TypeCountArray[Stage.Level]; // Stage CardType 수
			CreateCard();	// 카드 생성 함수
			matchCardCount = 0; // 맞춘 Card 수
			for (int i = 0; i < MaxCardCount; i++)
			{
				IsMatchCard[i] = false; // 이미 맞춘 Card 배열 
			}

			// Chocie 초기화
			Choice.select = 9;

			// Board 초기화
			Board.leftX = 15;
			Board.rightX = BOARD_WIDTH - 15;
			Board.topY = 4;
			Board.bottomY = BOARD_HEIGH - 4;

			// Game 상태 초기화
			selectChance = ChanceArray[Stage.Level];

			// 화면출력
			if (CurTime - Stat_OldTime < PrintTime)
			{
				sprintf(StatString, "[INIT 화면]");
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
				sprintf(StatString, "[READY] %d 스테이지", Stage.Level + 1);
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
			sprintf(StatString, "[STOP 화면]");
			ScreenPrint(30, 10, StatString);
			break;

		case SUCCESS:
			if (Stage.Level < 2)
			{
				sprintf(StatString, "%d 스테이지 CLEAR \n\n"
					"\t\t\t다음 스테이지? [Y/N]", Stage.Level + 1);
			}
			else
			{
				sprintf(StatString, "모든 스테이지 CLEAR \n\n"
					"\t\t\t게임 결과창 [Y]");
			}
			ScreenPrint(25, 10, StatString);
			break;

		case FAILED:
			sprintf(StatString, " %d 스테이지 GAME OVER\n\n"
				"\t\t\t     재도전? [Y/N]", Stage.Level + 1);
			ScreenPrint(25, 10, StatString);
			break;

		case RESULT:
			sprintf(StatString, "[게임 종료]\n\n"
				"\t\t\t 나가려면 Q를 누르세요.");
			ScreenPrint(30, 10, StatString);
			break;

		default:
			break;
		}
	}

	// 프레임워크 함수
	void Init()
	{
		// Game 상태 초기화
		GameStatus = START;
		Stage.Level = 0;
	}

	void Update()
	{
		AssignCoord();

		if (ViewCard[1] != -1) // 두 카드가 모두 Open
		{
			CardOpening();
		}
	}

	void Render()
	{
		char BarPrint[100];

		ScreenClear();

		// GameStatus에 따른 화면 출력 함수
		StatusPrint();

		// RUNNIG 시 출력 문구
		if (GameStatus == RUNNING)
		{
			// 상태바 출력
			sprintf(BarPrint, "남은 뒤집기 : %d     맞춘 카드 : %d    남은 카드 : %d", selectChance, matchCardCount, (Stage.CardCount / 2) - matchCardCount);
			ScreenPrint(16, 2, BarPrint);

			// Board 출력
			// 각모서리
			ScreenPrint(Board.leftX, Board.topY, "┌"); // 좌측 상단
			ScreenPrint(Board.rightX, Board.topY, "┐"); // 우측 상단
			ScreenPrint(Board.leftX, Board.bottomY, "└"); // 좌측 하단
			ScreenPrint(Board.rightX, Board.bottomY, "┘"); // 우측 하단

			// 위아래벽
			for (int i = Board.leftX + 2; i < Board.rightX; i++)
			{
				ScreenPrint(i, Board.topY, "-");
				ScreenPrint(i, Board.bottomY, "-");
			}
			// 좌우벽
			for (int i = Board.topY + 1; i < Board.bottomY; i++)
			{
				ScreenPrint(Board.leftX, i, "│");
				ScreenPrint(Board.rightX, i, "│");
			}

			// Card 출력
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

			// Choice 출력
			if (Stage.CardCount == 12)
			{
				ScreenPrint(Choice.X, Choice.Y, "▷");
			}
			else
			{
				ScreenPrint(Choice.X, Choice.Y - 2, "▷");
			}
		}
		/*
		//test 시작
		for (int i = 0; i < 4; i++)
		{
			ScreenPrint(24 + (10*i), 8, "※");
		}
		for (int i = 0; i < 4; i++)
		{
			ScreenPrint(24, 8 + (4*i), "※");
		}
		//test 끝
		*/

		ScreenFlipping();
	}

	void Release()
	{
	}

	void EqualCard()
	{
		int key;

		Init();
		ScreenInit();

		while (1)
		{
			if (_kbhit()) // key 입력이 있으면
			{
				key = _getch();

				if ((key == 'q') || (key == 'Q'))
					break;

				// key 조작
				KeyControl(key);

			}

			Update();
			Render();
		}

	}
}