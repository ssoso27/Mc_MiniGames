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
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;

	case 5:
		break;

	case 6:
		break;

	case 7:
		break;

	case 8:
		break;

	case 9:
		break;
		
	}
}

bool OverlapCell(int num) // 중복 Cell이 있는가?
{
	for (int i = 0; i < CardCount; i++)
	{
		if (Card[i].CellNum == num) // 중복 O
			return true;
	}

	return false; // 중복 X
}

int RandNumMake(int start, int end) // start ~ end 범위의 랜덤 숫자 생성
{
	int num;
	srand(time(NULL));

	num = (rand() % (end - start)) + start;

	return num;
}

void AssignCell(int index) // CellNum 부여 함수
{
	int randomNum;

	while (true)
	{
		randomNum = RandNumMake(0, CardCount); // 0 ~ CardCount 까지의 수 랜덤 생성

		if (OverlapCell(randomNum) == false) // 중복 Cell이 없으면
			break;	
	}
}

void CreateCard() // 카드 생성 함수
{
	for (int i = 0; i < CardCount; i++)
	{
		AssignCell(i); // CellNum 부여 함수 (랜덤. 중복X)
		AssignCoord(i);// CellNum에 따른 좌표 부여
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