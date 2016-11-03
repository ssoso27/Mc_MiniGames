#include "Header.h"

namespace SH_Intro
{
	const int printStr = 24; // ������ �� ��� ���ڿ� ����
	const int strCount = 48; // ���ڿ� ����
	int startIndex; // ��� ���� �� 
	char IntroPrint[strCount][85]; // �Ұ� ����
	bool upFlag = true; // ȭ���� �ö󰡴°�?
	clock_t OldTime;
	clock_t PrintTime;
	clock_t G_OldTime = clock(); // ���� ����ӵ� ����

	void Init()
	{
		// clock_t �ʱ�ȭ
		OldTime = clock();
		PrintTime = 1 * 1000;

		// ��� ���� ��
		startIndex = 0;

		// 1������
		for (int i = 0; i < printStr; i++)
		{
			sprintf(IntroPrint[i], " \n");
		}

		// 2������ (24 ~ 47��) // ������� ����
		sprintf(IntroPrint[24], "                               ������");
		sprintf(IntroPrint[25], "");
		sprintf(IntroPrint[26], "                       ����������     ������");
		sprintf(IntroPrint[27], "");
		sprintf(IntroPrint[28], "                       ��������       �����");
		sprintf(IntroPrint[29], "");
		sprintf(IntroPrint[30], "                       �����׸�ã��   �����");
		sprintf(IntroPrint[31], "");
		sprintf(IntroPrint[32], "                       ȭ��ǥ���ϱ�   �����");
		sprintf(IntroPrint[33], "");
		sprintf(IntroPrint[34], "                       ������         ��¹�");
		sprintf(IntroPrint[35], "");
		sprintf(IntroPrint[36], "                       ���ھ߱�       �����");
		sprintf(IntroPrint[37], "");
		sprintf(IntroPrint[38], "");
		sprintf(IntroPrint[39], "                          ������ �ֽ� �е�");
		sprintf(IntroPrint[40], "");
		sprintf(IntroPrint[41], "                              ��̿���");
		sprintf(IntroPrint[42], "");
		sprintf(IntroPrint[43], "                              �̹�����");
		sprintf(IntroPrint[44], "");
		sprintf(IntroPrint[45], "                            ������ħ �а�");



		sprintf(IntroPrint[47], "                                END");
	}

	void Render()
	{
		clock_t CurTime = clock();
		int j = 0;

		ScreenClear();


		for (int i = startIndex; i < startIndex + printStr - 1; i++, j++)
		{
			ScreenPrint(15, j, IntroPrint[i]); // (15,j) ������ ��� // ������� ����
		}

		if (upFlag == true)
		{
			if (CurTime - OldTime > PrintTime) // ���� �ö󰡴� �ð� : 2��
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