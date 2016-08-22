#include "Games\Header.h"
#include "Main.h"
#include "Games\Dodge.h"
#include "Games\Shoot.h"
#include "Games\Tetris.h"
#include "Games\Brick.h"

#pragma warning(disable:4996)

// 전역변수
char mainPrint[200];

// 함수
void Init()
{
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