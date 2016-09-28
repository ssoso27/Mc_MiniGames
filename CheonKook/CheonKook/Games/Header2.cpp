#pragma once

#include "Header.h"
#include "Header2.h"

	// 이 매크로가 정의되어 있으면 함수의 원형만 선언하고 정의는 하지 않는다.
//#ifndef SKOUT_PROTOTYPE_ONLY

	// 화면을 모두 지운다.
	void clrscr()
	{
		system("cls");
	}

	// 커서를 x,y좌표로 이동시킨다.
	void gotoxy(int x, int y)
	{
		COORD Cur;
		Cur.X = x;
		Cur.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	}

	// 커서의 x 좌표를 조사한다.
	int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO BufInfo;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
		return BufInfo.dwCursorPosition.X;
	}

	// 커서의 y좌표를 조사한다.
	int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO BufInfo;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
		return BufInfo.dwCursorPosition.Y;
	}

	// 커서를 숨기거나 다시 표시한다.
	void setcursortype(CURSOR_TYPE c)
	{
		CONSOLE_CURSOR_INFO CurInfo;

		switch (c) {
		case NOCURSOR:
			CurInfo.dwSize = 1;
			CurInfo.bVisible = FALSE;
			break;
		case SOLIDCURSOR:
			CurInfo.dwSize = 100;
			CurInfo.bVisible = TRUE;
			break;
		case NORMALCURSOR:
			CurInfo.dwSize = 20;
			CurInfo.bVisible = TRUE;
			break;
		}
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	}

//#endif  
