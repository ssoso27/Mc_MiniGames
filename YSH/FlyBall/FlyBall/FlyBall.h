#pragma once

#define BOARD_WIDTH 78
#define BOARD_HEIGH 24

// 열거형
typedef enum _DIRECT { TOP, TOP_RIGHT, RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, LEFT, TOP_LEFT } DIRECT; // 방향 설정. 시계방향. 

// 구조체
typedef struct _BLOCK
{
	int X;
	int Y;
} BLOCK;

typedef struct _GOAL
{
	int X;
	int Y;
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

// 함수원형
void PlayerMove(clock_t );
void KeyControl(int);

void Init();
void Update();
void Render();
void FlyBall();