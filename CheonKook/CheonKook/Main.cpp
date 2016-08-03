#include "Games\Header.h"
#include "Games\Dodge.h"
#include "Games\Shoot.h"
#include "Games\Tetris.h"

#pragma warning(disable:4996)

void main()
{
	
	int choice;
	bool qFlag = true;

	while (qFlag)
	{

		printf("미니게임을 선택하세요. 1 2 3 4 \n");
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
			qFlag = false;
		}


		ScreenFlipping();
	}
	
}