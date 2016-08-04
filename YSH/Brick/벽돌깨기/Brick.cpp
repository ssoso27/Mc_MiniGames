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
		int direction;
		
		if (CurTime - Bar.OldTime > Bar.MoveTime)
		{
			switch (key)
			{
			case LEFT:
				Bar.OldTime = clock();
				if (Bar.X[0] > 0)
				{
					Bar.X[0]--;
					Bar.X[1]--;
					Bar.X[2]--;
				}
				break;

			case RIGHT:
				Bar.OldTime = clock();
				if (Bar.X[2] < BOARD_WIDTH)
				{
					Bar.X[0]++;
					Bar.X[1]++;
					Bar.X[2]++;
				}
				break;

			case SPACE:
				(Ball.IsReady == 1) ? (Ball.IsReady = 0) : (Ball.IsReady = 1); // Ball.IsReady 바꿈 
				Bar.OldTime = clock();
				break;

			case '0': case '1': case '2': case '3': case '4': case '5':
				direction = key - '0';
				Ball.IsReady = 1;
				Ball.X = Bar.X[1];
				Ball.Y = Bar.Y - 1;
				Ball.Direction = (DIRECT) direction;
				Ball.OldTime = clock();
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

				case TOP_LEFT:
					Ball.X--;
					Ball.Y--;
					break;

				}
			}
			if (Ball.X < 0 || Ball.X >BOARD_WIDTH || Ball.Y < 0 || Ball.Y > BOARD_HEIGH) // 벽에 충돌
			{
				Ball.IsReady = 1;
				Ball.Direction = TOP;
				Ball.X = Bar.X[1];
				Ball.Y = Bar.Y - 1;
			}
		}
		else // 준비 상태면
		{
			Ball.X = Bar.X[1];
			Ball.Y = Bar.Y - 1;
		}
	}

	// 프레임워크 함수

	void Init()
	{

		// 바 초기화
		Bar.X[0] = 30;
		Bar.X[1] = 32;
		Bar.X[2] = 34;
		Bar.Y = 20;
		Bar.Length = 3;
		Bar.OldTime = clock();
		Bar.MoveTime = 100;

		// 공 초기화
		Ball.X = Bar.X[1];
		Ball.Y = Bar.Y-1;
		Ball.Direction = TOP;
		Ball.OldTime = clock();
		Ball.IsReady = 1;
		Ball.MoveTime = 200;

	}

	void Update()
	{
		clock_t CurTime = clock(); // 현재 시각

		BallMove(CurTime);// 공 움직임
		
	}

	void Render()
	{
		ScreenClear();

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
