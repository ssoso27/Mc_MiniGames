#pragma once

//namespace SJ_BaseBall
//{
	// 열거형
	typedef enum _GAMESTATUS { START, INIT, RUNNING, FINISH } GAMESTATUS;

	// 구조체
	typedef struct _COMPUTER
	{
		int x;
		int y;
		int z;
	} COMPUTER;

	typedef struct _PLAYER
	{
		int a;
		int b;
		int c;
		int life;
	} PLAYER;

	typedef struct _INBOX // 숫자 입력용 박스
	{
		int X;
		int Y;
		int num;
	} INBOX;

	// 함수원형
	void AssignMassage();
	void CheckAnswer();
	void GuessAnswer();
	void InputNumber(int);
	bool IsAnswer();
	void SetAnswer();
	void ResetVari();
	void KeyControl();
	void StatusPrint();

	// 프레임워크 함수
	void Init();
	void Update();
	void Render();
	void BaseBall();
//}