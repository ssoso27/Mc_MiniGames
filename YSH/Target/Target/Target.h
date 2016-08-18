#pragma once

// 구조체
typedef struct _STAGE
{
	int level; // Stage level
	// int 배열로 초기화 
	int targetCount; // 총 target의 개수
	int OCount; // O target의 개수
	int XCount; // X target의 개수
	int heartCount; // ♥ target의 개수
} STAGE;

typedef struct _TARGET_O
{
	int X;
	int Y;
} TARGET_O;

typedef struct _TARGET_X
{
	int X;
	int Y;
} TARGET_X;

typedef struct _TARGET_HEART
{
	int X;
	int Y;
} TARGET_HEART;

// 열거형
typedef enum _GAMESTATUS {START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GAMESTATUS;


// 함수원형
void CreateTarget();

void Init();
void Update();
void Render();
void Release();
void Target();