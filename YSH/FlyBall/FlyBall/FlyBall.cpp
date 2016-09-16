#include "Header.h"
#include "Screen.h"
#include "FlyBall.h"

// 구조체 변수 & 열거형
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	//LEFT = 75,
	//RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

PLAYER Player;

// 전역 변수
// 상수
const int FirstX = 2;
const int FirstY = 2;

// 함수
// Player의 이동
void PlayerMove(clock_t CurTime)
{
	if (Player.IsReady == 0) // 준비상태가 아니면
	{
		if (CurTime - Player.OldTime > Player.MoveTime) // 이동제한시간 경과
		{
			Player.OldTime = CurTime;

			// 방향에 따른 좌표 변화 
			switch (Player.Direction)
			{
			case TOP:
				//if (Collision(Player.X, Player.Y - 1) == 0) // 이동할 좌표에서 충돌이 안 일어나면 
				{
					Player.Y--; // 이동한다
				}
				// 충돌이 일어났을 경우, Collision에서 Player.Direction이 변경된다.
				break;

			case TOP_RIGHT:
				//if (Collision(Player.X + 1, Player.Y - 1) == 0)
				{
					Player.X++;
					Player.Y--;
				}
				break;
				
			case RIGHT:
				Player.X += 2;
				break;

			case BOT_RIGHT:
				//if (Collision(Player.X + 1, Player.Y + 1) == 0)
				{
					Player.X++;
					Player.Y++;
				}
				break;

			case BOTTOM:
				//if (Collision(Player.X, Player.Y + 1) == 0)
				{
					Player.Y++;
				}
				break;

			case BOT_LEFT:
				//if (Collision(Player.X - 1, Player.Y + 1) == 0)
				{
					Player.X--;
					Player.Y++;
				}
				break;

			case LEFT:
				Player.X -= 2;
				break;

			case TOP_LEFT:
				//if (Collision(Player.X - 1, Player.Y - 1) == 0)
				{
					Player.X--;
					Player.Y--;
				}
				break;

			}
		}
		if (Player.X < 0 || Player.X >BOARD_WIDTH || Player.Y < 0 || Player.Y > BOARD_HEIGH) // 벽에 충돌
		{
			Player.IsReady = 1;
			Player.Direction = RIGHT;
			Player.X = FirstX;
			Player.Y = FirstY;
		}
	}
	else // 준비 상태면
	{
		Player.X = FirstX;
		Player.Y = FirstY;
	}
}

void KeyControl(int key)
{
	int direction;

	switch (key)
	{
	case SPACE:
		//(Player.IsReady == 1) ? (Player.IsReady = 0) : (Player.IsReady = 1); // Player.IsReady 바꿈 
		if (Player.IsReady == 1)
		{
			Player.OldTime = clock();
			Player.IsReady = 0; // 준비 O -> 준비 X
		}
		break;

	case '8': // ↑
		direction = 0;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '9': // ↗
		direction = 1;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '6': // →
		direction = 2;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '3': // ↘
		direction = 3;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '2': // ↓
		direction = 4;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '1': // ↙
		direction = 5;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '4': // ←
		direction = 6;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '7': // ↖
		direction = 7;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	default:
		break;
	}
}

// 프레임워크 함수
void Init()
{
	Player.X = FirstX;
	Player.Y = FirstY;
	Player.Direction = RIGHT;
	Player.OldTime = clock();
	Player.IsReady = 1;
	Player.MoveTime = 130;
}

void Update()
{
	clock_t CurTime = clock(); // 현재 시각

	PlayerMove(CurTime);
}

void Render()
{
	ScreenClear();

	ScreenPrint(Player.X, Player.Y, "●");

	ScreenFlipping();
}

void main()
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

			KeyControl(key);

		}

		Update();
		Render();
	}
}