#pragma once

namespace JH_RockSP
{
	// 열거형
	typedef enum _GAMESTATUS { START, RUNNING } GAMESTATUS;
	
	// 구조체
	typedef struct _CHOICE {

		int select;
		int x;
		int y;

	}CHOICE;

	// 함수 원형
	void AssignCoord();
	void Init();
	void Update();
	void Render();
	void KeyControl(int key);
}