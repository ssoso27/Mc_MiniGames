#pragma once

#define BOARD_WIDTH 78
#define BOARD_HEIGH 24

// 열거형
typedef enum _GAMESTAUTS { START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GAMESTATUS;

// 구조체
typedef struct _CARD
{
	int X;
	int Y;
	int CellNum; // 표시될 장소 
	clock_t PrintTime; // 화면 표시 시간
	clock_t OldTime;
	char* PrintForm; // 표시되는 모양
	int Type; // 카드 타입
} CARD;

typedef struct _BOARD
{
	int leftX;
	int rightX;
	int topY;
	int bottomY;
	/*
	int one_forthX;
	int two_forthX;
	int three_forthX;
	int one_thirdY;
	int two_thirdY;
	*/
} BOARD;

typedef struct _CHOICE
{
	int X;
	int Y;
	int select; // 선택된 선택지
	clock_t OldTime;
	clock_t MoveTime;
} CHOICE;

typedef struct _STAGE
{
	int Level;
	int CardCount;
} STAGE;

// 함수 원형
void CreateCard();
void AssignCell(int, int);
void AssignType(int, int);
void AssignForm();
void KeyControl(int);
void SelectCard();
bool IsEqualType();
void CardOpening();
void StatusPrint();

// 프레임워크 함수
void Init();
void Update();
void Render();
void Release();
void EqualCard();