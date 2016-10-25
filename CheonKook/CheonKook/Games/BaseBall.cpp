#include "Header.h"
#include "Screen.h"
#include "BaseBall.h"

/*
//���� �߱� �����
// ���� �߱���?
// ��Ʈ����ũ : ���ڿ� �ڸ��� ���߸�
// �� : ���ڴ� �´µ� �ڸ��� Ʋ����

// ���� : ���� ���ڰ� ������ �ȵ�

//���� �߱�
/*  �������
���ӹ��, �ȳ� - ���߿� �����

-���� ����
�� - ������ ���� ����, ȭ�鿡�� _ _ _ ���ڸ� �Է��ϼ���.
	 ���� �Է� ����.
�ݺ�
(
��� - ���� �Է�
�� - ��Ʈ����ũ�� ���� Ȯ��
	 ��Ʈ����ũ �����ϰ� �� Ȯ��
	 ���� ��� ���
	 ���ڸ� �Է��ϼ���.
)

*/

namespace SJ_BaseBall
{
	// ���� ����
	//char startPrint[400]; // ���� ȭ�� ǥ�ÿ� ���ڿ�
	char statPrint[400]; // StatusPrint()���� ��� ���ڿ�. ���� ���� ���� ǥ��.
	char gueAftPrint[100]; // ���� �� ��� �޽���
	char guidePrint[100]; // ���� ���� �ȳ� �޽���

	int strike; // strike ����
	int ball; // ball ����

	bool enterFlag;

	clock_t stat_OldTime = clock(); // StatusPrint ���� ���� ��¿�. ������ ���� �ð�.

	// ����ü & ������ ����
	COMPUTER Computer;
	PLAYER Player;
	INBOX InBox[3];
	GAMESTATUS GameStatus;

	// �Լ�
	void SetAnswer() // Computer�� ���� ����
	{
		srand((unsigned)time(NULL)); // rand �Լ��� ���� ����

									 // ��ǻ���� ���� ����
		Computer.x = (rand() % 9) + 1; // ���� 1~9������ ����� �� - ������ 9�� ���� ������ 0~8 -> 1~9

		Computer.y = (rand() % 9) + 1;
		if (Computer.y == Computer.x) {

			Computer.y = (rand() % 9) + 1;

		}// �ٸ� �� ���� ������ �ݺ�
		Computer.z = (rand() % 9) + 1;
		while (Computer.z == Computer.x || Computer.z == Computer.y) {

			Computer.z = (rand() % 9) + 1;

		}//x,y �Ѱ� �ٸ���
	}

	void InputNumber(int key) // InputBox�� key �Է�
	{
		for (int i = 0; i < 3; i++)
		{
			if (InBox[i].num == -1) // InBox[i]�� ���ڰ� ������
			{
				InBox[i].num = key; // ���� �Է��ϰ�
				break; // for�� ����
			}
		}
	}

	void GuessAnswer() // Player�� ���� ����
	{
		Player.a = InBox[0].num;
		Player.b = InBox[1].num;
		Player.c = InBox[2].num;
	}

	bool IsAnswer() // ������ ������� �Ǻ�
	{
		if (strike == 3)
		{
			return true;
		}

		return false;
	}

	void CheckAnswer() // ���� �´��� �Ǻ�
	{
		//��Ʈ����ũ �Ǻ�
		if (Player.a == Computer.x) {
			strike++;
		}

		if (Player.b == Computer.y) {
			strike++;
		}

		if (Player.c == Computer.z) {
			strike++;
		}

		//�� �Ǻ�
		if (Player.a == Computer.y || Player.a == Computer.z) {
			ball++;
		}
		if (Player.b == Computer.x || Player.b == Computer.z) {
			ball++;
		}
		if (Player.c == Computer.y || Player.c == Computer.x) {
			ball++;
		}

		Player.life--; // life ����
		//sprintf(gueAftPrint, "%d ��Ʈ����ũ, %d ��, ���� ��� : %d", strike, ball, Player.life);
	}

	void AssignMassage() // ���� �� ��¸޽��� �Է�
	{
		if (IsAnswer() == true) // ������ ����ٸ�
		{
			sprintf(gueAftPrint, "�¸��ϼ̽��ϴ�. �ٽ� �Ͻðڽ��ϱ�? [Y/N]");
			GameStatus = FINISH; // ���� ���� ����
		}
		else if (Player.life <= 0) // life�� 0 ���ϸ�
		{
			sprintf(gueAftPrint, "���� ����. �ٽ� �Ͻðڽ��ϱ�? [Y/N]");
			GameStatus = FINISH;
		}
		else
		{
			sprintf(gueAftPrint, "%d ��Ʈ����ũ, %d ��, ���� ��� : %d", strike, ball, Player.life);
		}
	}

	void ResetVari() // �Ϻ� ���� �ʱ�ȭ
	{
		// InputBox �ʱ�ȭ`
		for (int i = 0; i < 3; i++) 
		{
			InBox[i].num = -1;
		}

		// Player ���� �� �ʱ�ȭ
		Player.a = -1;
		Player.b = -1;
		Player.c = -1;
		
		// strike, ball �ʱ�ȭ
		strike = 0;
		ball = 0;
	}

	void StatusPrint() // GameStatus�� ���� ȭ�� ��� �� ���� ��ȭ
	{
		clock_t CurTime = clock(); // ���� �ð�

		switch (GameStatus)
		{
		case START:
			// ���� ���� �ʱ�ȭ
			sprintf(statPrint,
				"�� �� �� ��\n\n"
				"���ݺ��� ���ھ߱��� �����ϰڽ��ϴ�.\n\n"
				"���� ��Ģ\n\n"
				"������ �� �ڸ� ���� ���ߴ� �����Դϴ�.\n������ ���� �����ϰ� �� �ڸ� ���� �Է��ϸ�,\n"
				"���ڿ� �ڸ��� ���� ��� ��Ʈ����ũ\n"
				"���ڴ� �´µ� �ڸ��� Ʋ�� ��� ���Դϴ�.\n"
				"ex) ���� 123, �Է��� �� 132 -> 1 ��Ʈ����ũ 2��\n\n"
				"�Է¹�� : ���ڸ� �ϳ��� �Է��ϸ�, ���� �Է��� �Ŀ� [Enter]�� �����ϴ�.\n\n"
				"[Space Bar]Ű�� ������ �����մϴ�.");

			// ���
			ScreenPrint(10, 2, statPrint);
			break;

		case INIT:
			// ���� �ʱ�ȭ (void Init()���� ������)

			// Computer�� ���� ����
			SetAnswer();

			// ��� ����
			Player.life = 10;

			// strike, ball ���� ����
			strike = 0;
			ball = 0;

			// InputBox �ʱ�ȭ
			for (int i = 0; i < 3; i++)
			{
				InBox[i].num = -1;
				InBox[i].X = 10 + (4 * i);
				InBox[i].Y = 9;
			}

			// ���� ���� �ʱ�ȭ
			sprintf(gueAftPrint, "%d ��Ʈ����ũ, %d ��, ���� ��� : %d", strike, ball, Player.life);

			// ȭ�����
			if (CurTime - stat_OldTime < 3 * 1000) // 3�� ���� ���
			{
				sprintf(statPrint, "[��ǻ�� ���� ���� ��]");
				ScreenPrint(25, 8, statPrint);
			}
			else
			{
				GameStatus = RUNNING; // 3�� ��� ��, ���� ����.
				stat_OldTime = CurTime; // ������ ���� �ð� = ���� �ð�
			}

			break;

		case RUNNING:
			break;

		case FINISH:
			break;

		default:
			break;
		}
	}

	void KeyControl(int key) // Ű �Է� �� ����
	{

		if (GameStatus == START)
		{
			if (key == 32) // SPACE �Է� ��
				GameStatus = INIT;
		}

		if (GameStatus == RUNNING)
		{
			if (key == 13) // Enter �Է½�
			{
				enterFlag = true;
			}

			if ((key - 48) >= 1 && (key - 48) <= 9)
			{
				InputNumber(key - 48); // 1~9 ���ڸ� �Է�
			}
		}

		if (GameStatus == FINISH)
		{
			switch (key)
			{
			case 'Y': case 'y':
				GameStatus = INIT; // ���� �����
				break;

			case 'N': case 'n':
				sprintf(gueAftPrint, "���� ����. �������� [Q]�� ��������.");
				break;

			default:
				break;
			}
		}
	}

	// �����ӿ�ũ �Լ�

	void Init()
	{
		// GameStatus �ʱ�ȭ
		GameStatus = START;

		// Computer�� ���� ����
		SetAnswer();

		// ��� ����
		Player.life = 10;

		// strike, ball ���� ����
		strike = 0;
		ball = 0;

		// InputBox �ʱ�ȭ
		for (int i = 0; i < 3; i++)
		{
			InBox[i].num = -1;
			InBox[i].X = 10 + (4*i);
			InBox[i].Y = 9;
		}
	
		// ���� ���� �ʱ�ȭ -> StatusPrint()�� �̵�
		
	}

	void Update()
	{
		if (enterFlag == true) // Enter �Է��� ������
		{
			GuessAnswer(); // ���� ���� �Է�
			//(3�� �� �Է� + ���� �Է� �� ����) (���� �ʿ�)
			if (InBox[2].num != -1)
			{
				CheckAnswer(); // �������� �Ǻ�
				AssignMassage(); // ���� �� ��� �޽��� �Է�
				ResetVari(); // ���� �ʱ�ȭ
			}
			enterFlag = false; 
		}
	}

	void Render()
	{
		ScreenClear();

		char InBoxNum[5];
		char temp[5];

		/*
		if (GameStatus == START)
		{
			ScreenPrint(10, 2, startPrint);
		}
		*/
		StatusPrint(); // GameStatus�� ���� ���� ��� 

		if (GameStatus == RUNNING || GameStatus == FINISH)
		{
			sprintf(guidePrint, "���� �� ���� �Է��ϼ���. ���� ��� : %d \n", Player.life);
			ScreenPrint(10, 5, guidePrint);

			// �Է��� �� ���
			for (int i = 0; i < 3; i++)
			{
				if (InBox[i].num != -1) // ���ڰ� �ִ� �͸� ���
				{
					sprintf(InBoxNum, "%d", InBox[i].num);
					ScreenPrint(InBox[i].X, InBox[i].Y, InBoxNum);
				}
			}
			/*
			// �׽�Ʈ�� ���� ���
			sprintf(temp, "%d", Computer.x);
			ScreenPrint(10, 13, temp);
			sprintf(temp, "%d", Computer.y);
			ScreenPrint(10, 16, temp);
			sprintf(temp, "%d", Computer.z);
			ScreenPrint(10, 19, temp); 
			*/
			ScreenPrint(10, 10, gueAftPrint); // ���� �� �޽��� ���
		}

		ScreenFlipping();
	}

	void BaseBall() {
		Init();
		ScreenInit();

		int key;

		while (1)
		{
			// Ű�Է� �߻� �� ����
			if (_kbhit())
			{
				key = _getch();

				if (key == 'q' || key == 'Q')
					break;			

				KeyControl(key); // Key �Է� �� ����
			}

			Update();
			Render();
		}

	}

}