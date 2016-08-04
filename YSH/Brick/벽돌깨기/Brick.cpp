#include "Header.h"
#include "Brick.h"

	// 열거형 

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32
	};

	// 구조체

	// 전역 변수

	char *KeyInput[] = { "위", "아래", "좌", "우", "스페이스" }; // KeyInput[k_Index]
	int k_Index = -1;

	BALL Ball;
	BAR Bar;

	// 함수

	void BallDirect(int key)
	{
		int direction;
		direction = key - '0';
		if (direction >= 0 && direction <= 5)
		{
			Ball.Direction = (DIRECT) direction;
			Ball.IsReady = 0;
		}
	}

	void KeyControl(int key) // 키조작
	{
		clock_t CurTime = clock();
		
		if (CurTime - Bar.OldTime > Bar.MoveTime)
		{
			switch (key)
			{
			case UP:
				k_Index = 0;
				break;

			case DOWN:
				k_Index = 1;
				break;

			case LEFT:
				k_Index = 2;
				if (Bar.X[0] > 0)
				{
					Bar.X[0]--;
					Bar.X[1]--;
					Bar.X[2]--;
				}
				break;

			case RIGHT:
				k_Index = 3;
				if (Bar.X[2] < BOARD_WIDTH)
				{
					Bar.X[0]++;
					Bar.X[1]++;
					Bar.X[2]++;
				}
				break;

			case SPACE:
				k_Index = 4;
				(Ball.IsReady == 0) ? (Ball.IsReady = 1) : (Ball.IsReady = 0); // Ball.IsReady 바꿈 
				break;
			}
		}

		if (Ball.IsReady == 0)
			BallDirect(_getch()); // Ball의 방향을 정함
	}

	void BallMove(clock_t CurTime) // Ball의 이동
	{
		if (Ball.IsReady == 0) // 준비상태가 아니면
		{
			if (CurTime - Ball.OldTime > Ball.MoveTime) // 이동제한시간 경과
			{
				Ball.OldTime = CurTime;

				// 방향에 따른 좌표 변화 
				switch (Ball.Direction)
				{
				case TOP:
					Ball.Y--;
					break;

				case TOP_RIGHT:
					Ball.X++;
					Ball.Y--;
					break;

				case BOT_RIGHT:
					Ball.X++;
					Ball.Y++;
					break;

				case BOTTOM:
					Ball.Y++;
					break;

				case BOT_LEFT:
					Ball.X--;
					Ball.Y++;
					break;

				}
			}
			if (Ball.X < 0 || Ball.X >BOARD_WIDTH || Ball.Y < 0 || Ball.Y > BOARD_HEIGH) // 벽에 충돌
			{
				Ball.IsReady = 1;
				Ball.X = FirstX;
				Ball.Y = FirstY;
			}
		}
	}

	// 프레임워크 함수

	void Init()
	{
		// 공 초기화
		Ball.X = FirstX;
		Ball.Y = FirstY;
		Ball.Direction = TOP;
		Ball.OldTime = clock();
		Ball.IsReady = 1;
		Ball.MoveTime = 200;

		// 바 초기화
		Bar.X[0] = 30;
		Bar.X[1] = 32;
		Bar.X[2] = 34;
		Bar.Y = 20;
		Bar.Length = 3;
		Bar.OldTime = clock();
		Bar.MoveTime = 100;
	}

	void Update()
	{
		clock_t CurTime = clock(); // 현재 시각

		BallMove(CurTime);// 공 움직임
		
	}

	void Render()
	{
		ScreenClear();

		if (k_Index >= 0)
			ScreenPrint(10, 10, KeyInput[k_Index]);

		ScreenPrint(Ball.X, Ball.Y, "●"); // 공 표시
		for (int i = 0; i < Bar.Length; i++)
		{
			ScreenPrint(Bar.X[i], Bar.Y, "▣");
		}

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


			if (_kbhit())
			{
				key = _getch();

				if ((key == 'q') || (key == 'Q'))
					break;
				
				KeyControl(key);

			}
			Update();
			Render();
		}
	}
