#pragma once

namespace SB_Tetris
{

#define true 1
#define false 0
#define bool int

#define BOARD_WIDTH 10        // 게임 영역의 가로(열) >= 10 : ━
#define BOARD_HEIGHT 20        // 게임 영역의 세로(행) >= 20 : | 

#define BOARD_X 4 //보드 열 x좌표 
#define BOARD_Y 2 //보드 행 y좌표

#define DELAY 100//지연

	// 함수

	void CursorVisible(bool);
	void SetCursorPosition(int, int);
	COORD GetCursorPosition(void);
	void ConsoleInit();
	void DrawField(void);
	void ShowPoint(void);
	bool CanPositionedAt(int, int, int);
	void WriteBlock(int);
	void BoardInit(int , int , int );
	void Stepper(int);
	void CountScore(void);
	void RemoveLine(void);
	void ClearBlock(int rotation, int move1, int move2);
	void StartGame(void);
	void EndGame();
	void Tetris();


}