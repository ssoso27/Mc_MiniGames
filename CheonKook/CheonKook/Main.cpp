#include "Games\Header.h"
#include "Main.h"
#include "Games\Dodge.h"
#include "Games\Shoot.h"
#include "Games\Tetris.h"
#include "Games\Brick.h"
#include "Games\EqualCard.h"
#include "Games\Push.h"
#include "Games\Intro.h"
#include "Games\BaseBall.h"
#include "Games\FlyBall.h"

namespace MainGame
{

	// ������

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		SPACE = 32
	};

	// ��������
	// ���
	int const distractorNum = 7; // ������ ����

	// ����ü ����
	CHOICE Choice;

	// ��� ����
	char mainPrint[200]; // �⺻ ��� ����

	// �Լ�
	void SelectGame() // ���� ���� �� ���� �Լ�
	{
		switch (Choice.select)
		{
		case 0: // ��������
			SH_Brick::Brick();
			break;

		case 1: // ȭ��ǥ ���ϱ�
			SH_Dodge::Dodge();
			break;

		case 2: // ������
			SB_Shoot::Shoot();
			break;

		case 3: // ���� ī�� ã��
			SH_EqualCard::EqualCard();
			break;

		case 4 : // ���� �߱�
			SJ_BaseBall::BaseBall();
			break;

		case 5: // �ö��� ��
			SH_FlyBall::FlyBall();
			break;

		case 6: // �� �Ұ�
			SH_Intro::Intro();
			break;

		default:
			break;
		}
	}

	void KeyControl(int key) // Ű ���� �Լ�
	{
		clock_t CurTime = clock();

		switch (key)
		{
		case UP:
			if (CurTime - Choice.OldTime > Choice.MoveTime) // �̵� ���ѽð��� ������ 
			{
				if (Choice.select > 0)
					Choice.select--; // ���� �̵�
				else
					Choice.select = distractorNum - 1; // ���� �Ʒ��� �̵�

				Choice.OldTime = CurTime;
			}
			break;

		case DOWN:
			if (CurTime - Choice.OldTime > Choice.MoveTime) // �̵� ���ѽð��� ������
			{
				if (Choice.select < distractorNum - 1)
					Choice.select++; // �Ʒ��� �̵�
				else
					Choice.select = 0; // ���� ���� �̵�

				Choice.OldTime = CurTime;
			}
			break;

		case SPACE:
			Choice.OldTime = CurTime;
			SelectGame(); // ���� ���� �� ���� �Լ�
			break;

		default:
			break;
		}
	}

	void AssignCoord() // ��ǥ �ο� �Լ�
	{
		switch (Choice.select)
		{
		case 0:
			Choice.X = 25;
			Choice.Y = 12;
			break;

		case 1:
			Choice.X = 25;
			Choice.Y = 13;
			break;

		case 2:
			Choice.X = 25;
			Choice.Y = 14;
			break;

		case 3:
			Choice.X = 25;
			Choice.Y = 15;
			break;

		case 4:
			Choice.X = 25;
			Choice.Y = 16;
			break;

		case 5:
			Choice.X = 25;
			Choice.Y = 17;
			break;

		case 6:
			Choice.X = 25;
			Choice.Y = 18;
			break;

		default:
			break;
		}
	}

	// �����ӿ�ũ �Լ�
	void Init()
	{
		// Choice �ʱ�ȭ
		Choice.select = 0; // ���õ� ������
		Choice.MoveTime = 100;
		Choice.OldTime = clock();

		// �⺻ ��� ���� �ʱ�ȭ
		sprintf(mainPrint,
			"\t\t [ �̴ϰ���õ�� ]\n\n\n\n"
			"\t\t\t- ������ �����ϼ��� - \n\n\n"
			"\t\t\t �� ��������\n"
			"\t\t\t �� ȭ��ǥ ���ϱ�\n"
			"\t\t\t �� ������\n"
			"\t\t\t �� ���� ī�� ã��\n"
			"\t\t\t �� ���� �߱�\n"
			"\t\t\t �� �ö��� ��\n"
			"\t\t\t �� ���Ұ� \n\n\n\n\n\n");
	}

	void Update()
	{
		// �������� ���� ��ǥ �ο� �Լ�
		AssignCoord();
	}

	void Render()
	{
		ScreenClear();

		ScreenPrint(10, 10, mainPrint);
		ScreenPrint(Choice.X, Choice.Y, "��");

		ScreenFlipping();
	}

	void MainGame()
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

				// Ű ���� �Լ�
				KeyControl(key);
			}

			Update();
			Render();
		}

		ScreenRelease();
	}
}