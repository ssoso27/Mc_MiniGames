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

// 함수
void SelectGame() // 게임 선택 및 실행 함수
{
	switch (Choice.select)
	{
	case 0: // 벽돌깨기
		SH_Brick::Brick();
		break;

	case 1: // 화살표 피하기
		SH_Dodge::Dodge();
		break;

	case 2: // 슛골인
		SB_Shoot::Shoot();
		break;

	case 3: // 테트리스
		SB_Tetris::Tetris();
		break;

	case 4: // 팀 소개
		break;

	default:
		break;
	}
}

void KeyControl(int key) // 키 조작 함수
{
	clock_t CurTime = clock();

	switch (key)
	{
	case UP:
		if (CurTime - Choice.OldTime > Choice.MoveTime) // 이동 제한시간이 지나면 
		{
			if (Choice.select > 0)
				Choice.select--; // 위로 이동
			else
				Choice.select = distractorNum - 1; // 제일 아래로 이동

			Choice.OldTime = CurTime;
		}
		break;

	case DOWN:
		if (CurTime - Choice.OldTime > Choice.MoveTime) // 이동 제한시간이 지나면
		{
			if (Choice.select < distractorNum - 1)
				Choice.select++; // 아래로 이동
			else
				Choice.select = 0; // 제일 위로 이동

			Choice.OldTime = CurTime;
		}
		break;

	case SPACE:
		Choice.OldTime = CurTime;
		SelectGame(); // 게임 선택 및 실행 함수
		break;

	default:
		break;
	}
}

void AssignCoord() // 좌표 부여 함수
{
	switch (Choice.select)
	{
	case 0:
		Choice.X = 25;
		Choice.Y = 12;
		break;

	case 1:
		Choice.X = 25;
		Choice.Y = 13;
		break;

	case 2:
		Choice.X = 25;
		Choice.Y = 14;
		break;

	case 3:
		Choice.X = 25;
		Choice.Y = 15;
		break;

	case 4:
		Choice.X = 25;
		Choice.Y = 16;
		break;
		
	default:
		break;
	}
}

// 프레임워크 함수
void Init()
{
	// Choice 초기화
	Choice.select = 0; // 선택된 선택지
	Choice.MoveTime = 100;
	Choice.OldTime = clock();

	// 기본 출력 문구 초기화
	sprintf(mainPrint,
		"\t\t [ 미니게임천국 ]\n\n\n\n"
		"\t\t\t- 게임을 선택하세요 - \n\n\n"
		"\t\t\t ◎ 벽돌깨기\n"
		"\t\t\t ◎ 화살표피하기\n"
		"\t\t\t ◎ 슛골인\n"
		"\t\t\t ◎ 테트리스\n"
		"\t\t\t ◎ 팀소개\n\n\n\n\n\n\n\n");
}

void Update()
{
	// 선택지에 따른 좌표 부여 함수
	AssignCoord();
}

void Render()
{
	ScreenClear();

	ScreenPrint(10, 10, mainPrint);
	ScreenPrint(Choice.X, Choice.Y, "⊙");
	
	ScreenFlipping();
}

void main()
{
	int key;

	Init();
	ScreenInit();

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;

			// 키 조작 함수
			KeyControl(key);
		}

		Update();
		Render();
	}

	ScreenRelease();
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