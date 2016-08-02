#pragma once
#include <time.h>

namespace SB_Shoot
{

	typedef struct _GOAL
	{
		int gMoveX, gMoveY;
		int gLength; //골대의 길이 
		int gLineX[9]; //골대의 골인식 좌표 
		int gDistance; // 골대 이동거리 
		clock_t MoveTime;
		clock_t OldTime;
	} GOAL;

	typedef struct _Ball
	{
		int ReadyB; // 1 = 준비, 0 = 슛 
		int bMoveX, bMoveY; //공 이동 좌표
		clock_t MoveTime; // 이동중 걸린 시간
		clock_t OldTime; // 이전 이동시간 
	} BALL;

	typedef struct _Player
	{
		int CenterX, CenterY; //X, Y 좌표 센터 
		int MoveX, MoveY; // X, Y 좌표 이동 
		int X, Y; // X, Y 현재 출력 좌표 값 
		int Index; // 중심좌표의 인덱스 
	} PLAYER;

	typedef struct _Position
	{
		int X, Y; // X, Y 현재 좌표 
	} Position;

	typedef struct _Effect
	{
		clock_t StartTime; // 효과 발생 시각
		clock_t StayTime; // 효과 지속시간
	}EFFECT;

	typedef enum _GameState { START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT } GameState;

	typedef struct _StageInfo // 스테이지 초기화 시, Init에서 초기화.
	{
		int GoalBall; // 목표 골인 개수
		clock_t LimitTime; // 제한 시간
		int GD_Length; // 골대 길이
		int GD_X; // 최초 X좌표
		int GD_Y; // 최초 Y좌표
		clock_t GD_MoveTime; // 골대 이동 시간 간격
		int GD_Dist; // 골대 이동 거리 
	} StageInfo;

	// 함수

	void Shoot();


}