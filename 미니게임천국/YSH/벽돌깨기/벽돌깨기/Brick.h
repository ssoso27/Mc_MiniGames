#pragma once


	// 열거형

	typedef enum _DIRECT { TOP, TOP_RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, TOP_LEFT } DIRECT; // 방향 설정. 시계방향. 

	// 구조체

	typedef struct _BALL
	{
		int X, Y;
		int IsReady; // 준비? 이동?
		int Life;
		DIRECT Direction; // 공 이동방향
		clock_t MoveTime;
		clock_t OldTime;

	} BALL;

	// 함수 원형
