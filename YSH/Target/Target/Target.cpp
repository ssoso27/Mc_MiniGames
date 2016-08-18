#include "Header.h"
#include "Target.h"

// 프레임워크 함수

void Init()
{

}

void Update()
{

}

void Render()
{
	ScreenClear();

	ScreenFlipping();
}

void Release()
{

}

void main()
{
	int key;

	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit)
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;
		}

		Update();
		Render();
	}

	Release();
}