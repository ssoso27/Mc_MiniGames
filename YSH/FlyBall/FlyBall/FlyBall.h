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
	bool IsEnable; // 활성화된 포탈인가?
} PORTAL;

typedef struct _GOAL
{
	int X, Y;
	int whereMap; // 어떤 맵에 있는가?
	bool IsSuccess; // 게임을 클리어 했는가?
	bool IsEnable; // 활성화된 골인지점인가?
} GOAL;

typedef struct _STARTP
{
	int whereMap; // 어떤 맵에 있는가?
} STARTP;

// 함수원형
void PlayerMove(clock_t );
void KeyControl(int);
void AssignCoord(int);
void MapMake(int );
void CreateBlock(int );
int Collision(int, int);
void SetPortal(int);
void MapReset();
void SetStartGoal();

void Init();
void Update();
void Render();
void FlyBall();