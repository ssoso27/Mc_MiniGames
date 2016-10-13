#include "Header.h"

namespace SH_Intro
{
	const int printStr = 24; // 페이지 당 출력 문자열 개수
	const int strCount = 48; // 문자열 개수
	int startIndex; // 출력 시작 행 
	char IntroPrint[strCount][85]; // 소개 문구
	bool upFlag = true; // 화면이 올라가는가?
	clock_t OldTime;
	clock_t PrintTime;

	void Init()
	{
		// clock_t 초기화
		OldTime = clock();
		PrintTime = 1 * 1000;

		// 출력 시작 행
		startIndex = 0;

		// 1페이지
		for (int i = 0; i < printStr; i++)
		{
			sprintf(IntroPrint[i], " \n");
		}

		// 2페이지 (24 ~ 47행) // 수진언니 편집
		sprintf(IntroPrint[24], "수진언니");



		sprintf(IntroPrint[47], "바브");
	}

	void Render()
	{
		clock_t CurTime = clock();
		int j = 0;

		ScreenClear();


		for (int i = startIndex; i < startIndex + printStr - 1; i++, j++)
		{
			ScreenPrint(15, j, IntroPrint[i]); // (15,j) 지점에 출력 // 수진언니 편집
		}

		if (upFlag == true)
		{
			if (CurTime - OldTime > PrintTime) // 문구 올라가는 시간 : 2초
			{
				if (startIndex >= printStr)
					upFlag = false;

				startIndex++;

				OldTime = CurTime;
			}
		}

		ScreenFlipping();
	}

	void Intro()
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

			}

			Render();
		}
	}
}