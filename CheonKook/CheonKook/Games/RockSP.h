#pragma once

namespace JH_RockSP
{
	// ������
	typedef enum _GAMESTATUS { START, RUNNING } GAMESTATUS;
	
	// ����ü
	typedef struct _CHOICE {

		int select;
		int x;
		int y;

	}CHOICE;

	// �Լ� ����
	void AssignCoord();
	void Init();
	void Update();
	void Render();
	void KeyControl(int key);
}