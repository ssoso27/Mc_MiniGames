#include "Games\Header.h"
#include "Main.h"
#include "Games\Dodge.h"
#include "Games\Shoot.h"
#include "Games\Tetris.h"
#include "Games\Brick.h"

#pragma warning(disable:4996)

// 열거형
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	SPACE = 32
};

// 전역변수
// 상수
int const distractorNum = 5; // 선택지 개수

// 구조체 변수
CHOICE Choice;

// 출력 관련
char mainPrint[200]; // 기본 출력 문구
char choicePrint[3] = "◀"; // 선택 표시

// 조작 관련
int select_dis; // 선택된 선택지

// 함수
void KeyControl(int key) // 키 조작 함수
{
	switch (key)
	{
	case UP:
		if (select_dis > 0)
			select_dis--; // 위로 이동
		else
			select_dis = distractorNum - 1; // 제일 아래로 이동

		break;

	case DOWN:
		if (select_dis < distractorNum - 1)
			select_dis++; // 아래로 이동
		else
			select_dis = 0; // 제일 위로 이동

		break;

	default:
		break;
	}
}

void AssignCoord() // 좌표 부여 함수
{

}

// 프레임워크 함수
void Init()
{
	// 선택된 선택지 초기화
	select_dis = 0;

	// 기본 출력 문구 초기화
	sprintf(mainPrint,
		"\t\t [ 미니게임천국 ]\n\n\n\n"
		"\t\t\t- 게임을 선택하세요 - \n\n\n"
		"\t\t\t ◎ 닷지\n"
		"\t\t\t ◎ 벽돌깨기\n"
		"\t\t\t ◎ 슛골인\n"
		"\t\t\t ◎ 테트리스\n"
		"\t\t\t ◎ 팀소개\n\n\n\n\n\n\n\n");
}

void Update()
{
	// 선택지에 따른 좌표 부여 함수
}

void Render()
{
	ScreenClear();

	ScreenPrint(10, 10, mainPrint);

	ScreenFlipping();
}

void main()
{
	int key;

	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;

			// 키 조작 함수 -> 선택지 변경
		}

		Update();
		Render();
	}
}

void main2()
{
	int choice;
	bool qFlag = true;

	while (qFlag)
	{
		ScreenClear();

		printf("미니게임을 선택하세요. Dodge(1) Shoot(2) Tetris(3) Brick(4) 나가기(5) \n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			SH_Dodge::Dodge();
			break;

		case 2:
			SB_Shoot::Shoot();
			break;

		case 3:
			SB_Tetris::Tetris();
			break;

		case 4:
			SH_Brick::Brick();
			break;

		case 5:
			qFlag = false;
			break;

		default:
			break;
		}


		ScreenFlipping();
	}
	
}