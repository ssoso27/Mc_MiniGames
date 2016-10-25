#pragma once

namespace SJ_BaseBall
{
	// ������
	typedef enum _GAMESTATUS { START, INIT, RUNNING, FINISH } GAMESTATUS;

	// ����ü
	typedef struct _COMPUTER
	{
		int x;
		int y;
		int z;
	} COMPUTER;

	typedef struct _PLAYER
	{
		int a;
		int b;
		int c;
		int life;
	} PLAYER;

	typedef struct _INBOX // ���� �Է¿� �ڽ�
	{
		int X;
		int Y;
		int num;
	} INBOX;

	// �Լ�����
	void AssignMassage();
	void CheckAnswer();
	void GuessAnswer();
	void InputNumber(int);
	bool IsAnswer();
	void SetAnswer();
	void ResetVari();
	void KeyControl();
	void StatusPrint();

	// �����ӿ�ũ �Լ�
	void Init();
	void Update();
	void Render();
	void BaseBall();
}