#include "Header.h"
#include "EqualCard.h"

// 상수
const int CardCount = 12; // Card의 개수
const int TypeCount = 6; // Type의 개수

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
CARD Card[CardCount]; // Card 생성
GAMESTATUS GameStatus;
BOARD Board;
CHOICE Choice;

// 전역변수
// Card 관련
char PrintArray[TypeCount][3] = { "♥" , "★" , "♣" , "♠" , "◀" , "☎" }; // 타입에 따른 출력 배열
char CoverPrint[3] = "●";
int ViewCard[2] = { 99, 99}; // 보이는 Card의 index 저장

// Game 진행 관련
clock_t OldTime; // Update 시간 측정용
clock_t TurnTime = 1.2 * 1000; // 커버 씌우기까지의 시간

// 함수

void SelectCard()
{
	int select; // 선택된 카드

	for (int i = 0; i < CardCount; i++) // 선택된 카드 찾기
	{
		if ((Choice.select) == Card[i].CellNum)
			select = i;
	}

	// Card.select 에 따른 Card 선택
	// 선택된 카드는 Card[i].PrintForm = PrintArray[Card[i].Type]
	Card[select].PrintForm = PrintArray[Card[select].Type];

	// ViewCell[0] 또는 ViewCell[1]에 Card의 index 입력
	if (ViewCard[0] == 99)
	{
		ViewCard[0] = select;
	}
	else
	{
		ViewCard[1] = select;
		OldTime = clock();
	}
}

void AssignCoord()// 좌표 부여 함수
{
	/*
	9 10 11 12
	5  6  7  8
	1  2  3  4
	*/

	// Choice 좌표 부여
	switch (Choice.select)
	{
	case 1: // X, Y 부여
		Choice.X = 21;
		Choice.Y = 16;
		break;

	case 2:
		Choice.X = 31;
		Choice.Y = 16;
		break;

	case 3:
		Choice.X = 41;
		Choice.Y = 16;
		break;

	case 4:
		Choice.X = 51;
		Choice.Y = 16;
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
		Choice.Y = 8;
		break;

	case 10:
		Choice.X = 31;
		Choice.Y = 8;
		break;

	case 11:
		Choice.X = 41;
		Choice.Y = 8;
		break;

	case 12:
		Choice.X = 51;
		Choice.Y = 8;
		break;

	default:
		break;

	}

	// Card 좌표 부여
	for (int index = 0; index < CardCount; index++)
	{
		switch (Card[index].CellNum)
		{
		case 1: // X, Y 부여
			Card[index].X = 24;
			Card[index].Y = 16;
			break;

		case 2:
			Card[index].X = 34;
			Card[index].Y = 16;
			break;

		case 3:
			Card[index].X = 44;
			Card[index].Y = 16;
			break;

		case 4:
			Card[index].X = 54;
			Card[index].Y = 16;
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
			Card[index].Y = 8;
			break;

		case 10:
			Card[index].X = 34;
			Card[index].Y = 8;
			break;

		case 11:
			Card[index].X = 44;
			Card[index].Y = 8;
			break;

		case 12:
			Card[index].X = 54;
			Card[index].Y = 8;
			break;

		default:
			break;	

		}
	}
}

void AssignCell(int start, int end) // start ~ end 범위의 랜덤 숫자 생성
{
	int randomnum;
	bool IsOverlapCell[CardCount + 1 ] = { false, }; // 중복 판별용 bool 배열
	srand((unsigned)time(NULL));

	for (int i = 0; i < CardCount; )
	{
		randomnum = (rand() % (end - start)) + start; // start ~ end 범위의 랜덤 숫자

		if (IsOverlapCell[randomnum] == false) // 중복이 없다면
		{
			IsOverlapCell[randomnum] = true; // 중복 표시
			Card[i].CellNum = randomnum; // 값 대입
			++i; // 다음 CellNum으로 넘어감
		} // if문 종료
	} // for문 종료

} // 함수 종료

void AssignType(int start, int end) // Type 부여 함수
{
	int randomnum;
	int IsOverlapType[TypeCount] = { 0, }; // 중복 판별용 int 배열

	srand((unsigned)time(NULL));

	for (int i = 0; i < CardCount; )
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
	for (int i = 0; i < CardCount; i++)
	{
		// Card[i].PrintForm = PrintArray[Card[i].Type]; // Type에 따른 PrintForm
		Card[i].PrintForm = CoverPrint; // Cover 씌우기
	}
}

void CreateCard() // 카드 생성 함수
{
	AssignCell(1, CardCount+1); // CellNum 부여 함수 (랜덤. 중복X)
	AssignCoord(); // CellNum에 따른 좌표 부여
	AssignType(0, TypeCount); // Type 부여 함수 (랜덤. 중복 1회) 
	AssignForm();// PrintForm 부여
}

void KeyControl(int key)
{
	// 모든 상태에서

	// RUNNING 상태에서
	switch (key)
	{
	case UP:
		if (Choice.select < 9)
			Choice.select += 4;
		break;

	case DOWN:
		if (Choice.select > 4)
			Choice.select -= 4;
		break;

	case LEFT:
		if ((Choice.select != 1) && (Choice.select != 5) && (Choice.select != 9))
		Choice.select--;
		break;

	case RIGHT:
		if ((Choice.select != 4) && (Choice.select != 8) && (Choice.select != 12))
		Choice.select++;
		break;

	case SPACE:
		SelectCard();
		break;

	default:
		break;
	}
}

// 프레임워크 함수
void Init()
{
	CreateCard();	// 카드 생성 함수 ( GameStatue == INIT 에 넣을까? )

	// Chocie 초기화
	Choice.select = 7;

	// Board 초기화
	Board.leftX = 15;
	Board.rightX = BOARD_WIDTH - 15;
	Board.topY = 4;
	Board.bottomY = BOARD_HEIGH - 4;
	
	// Game 상태 초기화
	//GameStatus = START;
}

void Update()
{
	clock_t CurTime = clock();

	AssignCoord();

	// 일정 시간이 지난 후, ViewCell[]을 0으로 초기화하며 Card[i].PrintForm = CoverPrint;
	if (ViewCard[1] != 99)
	{
		if (CurTime - OldTime > TurnTime)
		{
			// Cover 다시 씌우기
			Card[ViewCard[0]].PrintForm = CoverPrint;
			Card[ViewCard[1]].PrintForm = CoverPrint;
			
			// ViewCard 99 처리
			ViewCard[0] = 99;
			ViewCard[1] = 99;
		}
	}

}

void Render()
{

	ScreenClear();

	// GameStatus에 따른 화면 출력 함수
	
	// RUNNIG 시 출력 문구
	
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
	for (int i = 0; i < CardCount; i++)
	{
		ScreenPrint(Card[i].X, Card[i].Y, Card[i].PrintForm);
	}

	// Choice 출력
	ScreenPrint(Choice.X, Choice.Y, "▷");

	/*
	//test 시작
	for (int i = 0; i < 4; i++)
	{
		ScreenPrint(24 + (10*i), 8, "※");
	}
	for (int i = 0; i < 3; i++)
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

void main()
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

	ScreenRelease();
	Release();
}