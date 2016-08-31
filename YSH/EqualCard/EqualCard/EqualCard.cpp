#include "Header.h"
#include "EqualCard.h"

// 구조체변수 & 열거형변수
CARD Card[9]; // Card 9개 
GAMESTATUS GameStatus;

// 전역변수
const int CardCount = 9; // Card의 개수
char PrintArray[5][3] = { "♡" , "☆" , "♧" , "♤" , "J" }; // 타입에 따른 출력 배열
char TypeArray[5][7] = { "Heart", "Star", "Clover", "Spade" , "Joker" }; // 타입 이름 배열 
 
// 함수

void AssignCoord(int index)// 좌표 부여 함수
{
	switch (Card[index].CellNum)
	{
	case 1: // X, Y 부여
		Card[index].X = 10;
		Card[index].Y = 20;
		break;

	case 2:
		Card[index].X = 13;
		Card[index].Y = 20;
		break;

	case 3:
		Card[index].X = 16;
		Card[index].Y = 20;
		break;

	case 4:
		Card[index].X = 10;
		Card[index].Y = 17;
		break;

	case 5:
		Card[index].X = 13;
		Card[index].Y = 17;
		break;

	case 6:
		Card[index].X = 16;
		Card[index].Y = 17;
		break;

	case 7:
		Card[index].X = 10;
		Card[index].Y = 13;
		break;

	case 8:
		Card[index].X = 13;
		Card[index].Y = 13;
		break;

	case 9:
		Card[index].X = 16;
		Card[index].Y = 13;
		break;
		
	}
}

bool OverlapCell(int start, int end, int num) // 중복 Cell이 있는가?
{
	if (start == end)
		return false; 

	for (int i = start; i < end; i++)
	{
		if (Card[i].CellNum == num) // 중복 O
			return true;
	}

	return false; // 중복 X
}

int RandNumMake(int start, int end) // start ~ end 범위의 랜덤 숫자 생성
{
	int num;
	srand((unsigned) time(NULL));

	num = (rand() % (end - start)) + start;

	return num;
}

void AssignCell(int index) // CellNum 부여 함수
{
	int randomNum;

	while (true)
	{
		randomNum = RandNumMake(0, CardCount); // 0 ~ CardCount 까지의 수 랜덤 생성

		if (OverlapCell(0, index, randomNum) == false) // 중복 Cell이 없으면
			break;	
	}

	//Card[index].CellNum = randomNum;
}

void CreateCard() // 카드 생성 함수
{
	for (int i = 0; i < CardCount; i++)
	{
		AssignCell(i); // CellNum 부여 함수 (랜덤. 중복X)
		//AssignCoord(i);// CellNum에 따른 좌표 부여
		// Type 부여 함수 (랜덤. 중복 1회) 
		// Type에 따른 PrintForm 부여
	}
}

// 프레임워크 함수
void Init()
{
	CreateCard();	// 카드 생성 함수 ( GameStatue == INIT 에 넣을까? )
	
	// Game 상태 초기화
	//GameStatus = START;
}

void Update()
{

}

void Render()
{

	ScreenClear();

	// GameStatus에 따른 화면 출력 함수
	
	// RUNNIG 시 출력 문구
/*	for (int i = 0; i < CardCount; i++)
	{
		ScreenPrint(Card[i].X, Card[i].Y, "T");
	}*/
	// test용 출력 시작
	char test[30];
	for (int i = 0; i < CardCount; i++)
	{
		sprintf(test, "card cell : " + Card[i].CellNum);
		ScreenPrint(30, i * 2, test);
	}
	// test용 출력 종료

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
		}

		Update();
		Render();
	}

	ScreenRelease();
	Release();
}