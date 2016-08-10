#pragma once

	// 상수

	#define BAR_FIRST_X 30 // Bar 첫 x[0]좌표
	#define BAR_FIRST_Y 20 // Bar 첫 y좌표

	#define BLOCK_COUNT 20 // Block 갯수 	

	#define BOARD_WIDTH 78
	#define BOARD_HEIGH 24

	// 열거형

	typedef enum _DIRECT { TOP, TOP_RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, TOP_LEFT } DIRECT; // 방향 설정. 시계방향. 
	typedef enum _GAMESTAUTS { START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GAMESTATUS; // stage 상태

	// 구조체

	typedef struct _STAGE_INFO
	{
		int BlockCount;
		clock_t LimitTime;
	} STAGE_INFO;

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