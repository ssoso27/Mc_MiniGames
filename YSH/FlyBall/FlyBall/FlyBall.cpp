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
const int PlayerFirstX = 8;
const int PlayerFirstY = 4;
const int MaxBlockCount = 30;

// 구조체 변수
BLOCK Block[MaxBlockCount];
BOARD Board;


// 배열
bool IsBlock[Board.Height / 2][Board.Width / 2] = { false, }; // Block 생성 위치 판별 [20][8]

// 함수

// Block 좌표 대입
void AssignCoord(int k)
{
	for (int i = 0; i < Board.Height / 2; i++) // i행
	{
		for (int j = 0; j < Board.Width / 2; j++) // j열
		{
			if (IsBlock[i][j] == true)
			{
				Block[k].X = Board.leftX + (j * 2) + 1;
				Block[k].Y = Board.topY + (i * 2) + 1;
				IsBlock[i][j] = false;

				break;
			} // if문 end
		} // for j end
	} // for i end
} 

// Block Map 생성
void MapMake()
{
	// bool IsBlock[][] 에 true 넣을거 [7][19]
	IsBlock[7][19] = true;
}

// Block 생성
void CreateBlock()
{
	MapMake();
	for (int i = 0; i < MaxBlockCount; i++)
	{
		AssignCoord(i);
	}
}

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
			Player.X = PlayerFirstX;
			Player.Y = PlayerFirstY;
		}
	}
	else // 준비 상태면
	{
		Player.X = PlayerFirstX;
		Player.Y = PlayerFirstY;
	}
}

// 키조작
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
	// Board 초기화
	Board.topY = 2;
	Board.bottomY = Board.topY + Board.Height;
	Board.leftX = 6;
	Board.rightX = Board.leftX + Board.Width;

	// Block 초기화
	CreateBlock();

	// Player 초기화
	Player.X = PlayerFirstX;
	Player.Y = PlayerFirstY;
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

	// Board 출력
	// 각모서리
	ScreenPrint(Board.leftX, Board.topY, "┌"); // 좌측 상단
	ScreenPrint(Board.rightX, Board.topY, "┐"); // 우측 상단
	ScreenPrint(Board.leftX, Board.bottomY, "└"); // 좌측 하단
	ScreenPrint(Board.rightX, Board.bottomY, "┘"); // 우측 하단

												   // 위아래벽
	for (int i = Board.leftX + 2; i < Board.rightX; i++)
	{
		ScreenPrint(i, Board.topY, "-");
		ScreenPrint(i, Board.bottomY, "-");
	}
	// 좌우벽
	for (int i = Board.topY + 1; i < Board.bottomY; i++)
	{
		ScreenPrint(Board.leftX, i, "│");
		ScreenPrint(Board.rightX, i, "│");
	}

	//ScreenPrint(Player.X, Player.Y, "●");

	//for (int i = 0; i < MaxBlockCount; i++)
	{
		ScreenPrint(Block[0].X, Block[0].Y, "■");
	}

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