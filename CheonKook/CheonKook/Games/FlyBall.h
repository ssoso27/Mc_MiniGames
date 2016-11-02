#pragma once

namespace SH_FlyBall
{
#define BOARD_WIDTH 78
#define BOARD_HEIGH 24

	// ������
	typedef enum _DIRECT { M_TOP, M_RIGHT, M_BOTTOM, M_LEFT } DIRECT; // ���� ����. �ð����. 
	typedef enum _GAMESTATUS { START, INIT, READY, RUNNING, SUCCESS, FAILED, RESULT } GAMESTATUS;

	// ����ü
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
		int IsReady; // �غ�? �̵�?
		int Life;
		DIRECT Direction; // �� �̵�����
		clock_t MoveTime;
		clock_t OldTime;
	} PLAYER;

	typedef struct _PORTAL
	{
		int X, Y;
		int nextMap; // �̵��� ��
		bool IsEnable; // Ȱ��ȭ�� ��Ż�ΰ�?
	} PORTAL;

	typedef struct _GOAL
	{
		int X, Y;
		int whereMap; // � �ʿ� �ִ°�?
		bool IsSuccess; // ������ Ŭ���� �ߴ°�?
		bool IsEnable; // Ȱ��ȭ�� ���������ΰ�?
	} GOAL;

	typedef struct _STARTP
	{
		int whereMap; // � �ʿ� �ִ°�?
	} STARTP;

	typedef struct _STAGE
	{
		int level; // ���� ����
		//int createMapCount; // ���� �� ����
	} STAGE;

	// �Լ�����
	void PlayerMove(clock_t);
	void KeyControl(int);
	void AssignCoord(int);
	void MapMake(int);
	void CreateBlock(int);
	int Collision(int, int);
	void SetPortal(int);
	void MapReset();
	void SetStartGoal();
	void StatusPrint();

	void Init();
	void Update();
	void Render();
	void FlyBall();
}