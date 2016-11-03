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
	clock_t G_OldTime = clock(); // 게임 실행속도 제한

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
		sprintf(IntroPrint[24], "                               제작자");
		sprintf(IntroPrint[25], "");
		sprintf(IntroPrint[26], "                       가위바위보     강재희");
		sprintf(IntroPrint[27], "");
		sprintf(IntroPrint[28], "                       벽돌깨기       양소희");
		sprintf(IntroPrint[29], "");
		sprintf(IntroPrint[30], "                       같은그림찾기   양소희");
		sprintf(IntroPrint[31], "");
		sprintf(IntroPrint[32], "                       화살표피하기   양소희");
		sprintf(IntroPrint[33], "");
		sprintf(IntroPrint[34], "                       슛골인         허승범");
		sprintf(IntroPrint[35], "");
		sprintf(IntroPrint[36], "                       숫자야구       김수진");
		sprintf(IntroPrint[37], "");
		sprintf(IntroPrint[38], "");
		sprintf(IntroPrint[39], "                          도움을 주신 분들");
		sprintf(IntroPrint[40], "");
		sprintf(IntroPrint[41], "                              김미연님");
		sprintf(IntroPrint[42], "");
		sprintf(IntroPrint[43], "                              이민혁님");
		sprintf(IntroPrint[44], "");
		sprintf(IntroPrint[45], "                            좋은아침 분과");



		sprintf(IntroPrint[47], "                                END");
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
		clock_t CurTime;

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

			while (1)
			{
				CurTime = clock();
				if (CurTime - G_OldTime > DelayT)
				{
					G_OldTime = CurTime;
					break;
				}
			}
		}
	}
}