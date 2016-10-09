#pragma once

#define BOARD_WIDTH 78
#define BOARD_HEIGH 24

// 열거형
typedef enum _DIRECT { TOP, TOP_RIGHT, RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, LEFT, TOP_LEFT } DIRECT; // 방향 설정. 시계방향. 

// 구조체
typedef struct _BOARD
{
	int topY;
	int bottomY;
	int leftX;
	int rightX;
	static const int Width = 64;
	static const int Height = 16;
} BOARD;

typedef struct _BLOCK
{
	int X;
	int Y;
} BLOCK;

typedef struct _GOAL
{
	int X;
	int Y;
	int nextMap; // 이동 맵 지정
} GOAL;

typedef struct _PLAYER
{
	int X, Y;
	int IsReady; // 준비? 이동?
	int Life;
	DIRECT Direction; // 공 이동방향
	clock_t MoveTime;
	clock_t OldTime;
} PLAYER;

typedef struct _PORTAL
{
	int X, Y;
	int nextMap; // 이동할 맵
	bool IsAvail; // 유효한 포탈인가?
} PORTAL;

// 함수원형
void PlayerMove(clock_t );
void KeyControl(int);
void AssignCoord(int);
void MapMake(int );
void CreateBlock(int );
int Collision(int, int);

void Init();
void Update();
void Render();
void FlyBall();