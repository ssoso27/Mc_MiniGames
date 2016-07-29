#pragma once
#include <time.h>

namespace SH_Dodge
{
#define DotNum 17 // Dot의 개수
#define StageNum 3 // Stage 개수
#define BOARD_WIDTH 80      // 화면의 너비
#define BOARD_HEIGHT 25      // 화면의 높이
#define Zero 50 // Stage==0 일 때의 Dot의 수

	// 열거형 선언


	typedef enum _GAMESTATUS { START, INIT, READY, GO, RUNNING, STOP, NEXT, RESULT } GAMESTATUS;

	// 구조체 선언

	typedef struct _PLAYER
	{
		int X, Y; // 플레이어 캐릭터의 X, Y 좌표
				  //	clock_t MoveTime;
		int InStop; // Stop상태? OR Move 상태?
		int Life; // Life.
				  //	int Crash; // Dot과의 충돌. if (Crash==1) -> Life--; Crash=0;
	}PLAYER;

	typedef struct _DOT
	{
		int X, Y; // 점의 X, Y 좌표
				  //	int Crash; // 벽에 충돌?
		clock_t MoveTime, OldTime;
		clock_t	Speed; // 속도
		int DirectionX, DirectionY; // 이동방향
	}DOT;

	typedef struct _STAR
	{
		int X, Y; // Star의 X, Y 좌표
		int Catch; // Player가 Star를 캐치한 횟수
		int SumCatch; // 모든 스테이지의 Catch의 합
	}STAR;


	// 함수

	void KeyControl(int);
	void IfCrash(int);
	void StarInit();
	void MoveCoord(int);
	void DotInit();
	void StatusPrint();
	void Init();
	void Update();
	void Render();
	void Release();
	void Dodge();

}