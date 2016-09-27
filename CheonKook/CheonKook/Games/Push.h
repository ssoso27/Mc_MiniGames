#pragma once
#include "Header2.h"

namespace SB_Push
{
#define MAXSTAGE 1


	//+======================================+

#define putchxy(x,y,z) { gotoxy(x,y); _putch(z);} //gotoxy 함수와 putch함수의 복합체 (.... 귀찮아서)

	//+======================================+

	void LoadingStage();
	void DrawStage();
	void PlayerMove();
	int Push();
}