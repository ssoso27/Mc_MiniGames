#pragma once

	// 상수

	#define BAR_FIRST_X 30 // Bar 첫 x[0]좌표
	#define BAR_FIRST_Y 20 // Bar 첫 y좌표

//	#define BLOCK_COUNT 20 // Block 갯수 	

	#define BOARD_WIDTH 78
	#define BOARD_HEIGH 24

	// 열거형

	typedef enum _DIRECT { TOP, TOP_RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, TOP_LEFT } DIRECT; // 방향 설정. 시계방향. 
	typedef enum _GAMESTAUTS { START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GAMESTATUS; // stage 상태

	// 구조체

	typedef struct _WALL
	{
		int leftX; // 왼쪽 벽
		int rightX; // 오른쪽 벽
		int topY; // 위쪽 벽
		int bottomY; // 아래쪽 벽
	} WALL;

	typedef struct _STAGE
	{
		int BlockCount;
		int Level;
	} STAGE;

	typedef struct _BALL
	{
		int X, Y;
		int IsReady; // 준비? 이동?
		int Life;
		DIRECT Direction; // 공 이동방향
		clock_t MoveTime;
		clock_t OldTime;

	} BALL;

	typedef struct _BAR
	{
		int X[3];
		int Y;
		int Life;
		int Length;
		clock_t OldTime;
		clock_t MoveTime;
	} BAR;

	typedef struct _BLOCK
	{
		int X;
		int Y;
		int Life;
	} BLOCK;

	// 함수 원형

	void BallDirect(int);
	void Init();
	void Update();
	void Render();
	void Release();