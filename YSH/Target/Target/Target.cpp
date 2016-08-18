#include "Header.h"
#include "Target.h"


// 전역변수

// 구조체 변수
STAGE Stage;
TARGET_O Target_O[10];
TARGET_X Target_X[10];
TARGET_HEART Target_heart[3];
GAMESTATUS GameStatus;

// 출력 관련
int OArray[3] = {1,2,3};// O 개수 배열
int XArray[3] = {1,2,3};// X 개수 배열
						// ♥은 모든 Stage에서 3개

// 함수



void CreateTarget() // Target 생성 함수
{
	// O 생성

	// X 생성

	// ♥ 생성
}

// 프레임워크 함수

void Init()
{
	// Target들 초기화
	CreateTarget();

	// 게임 상태 초기화
	GameStatus = START;
}

void Update()
{

}

void Render()
{
	ScreenClear();

	ScreenFlipping();
}

void Release()
{

}

void main()
{
	int key;

	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit)
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;
		}

		Update();
		Render();
	}

	Release();
}