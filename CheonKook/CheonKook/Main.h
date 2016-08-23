#pragma once

// 구조체
typedef struct _CHOICE
{
	int X;
	int Y;
	int select; // 선택된 선택지
	clock_t OldTime;
	clock_t MoveTime;
} CHOICE;

// 함수원형
void KeyControl(int);
void AssignCoord();
void SelectGame();

// 프레임워크 함수
void Init();
void Update();
void Render();
