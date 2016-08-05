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
BLOCK Block[30];

int WallStateTable[4][6] = { // 벽과의 충돌 시 상태 변화 테이블
	{3, 2, -1, -1, -1, 4},
	{-1, 5, 4, -1, -1, -1},
	{-1, -1, 1, 0, 5, -1},
	{-1, -1, -1, -1, 2, 1}
};
int BlockStateTable[6] = { 3, 2, 1, 0, 5, 4 }; // 블럭과의 충돌 시 상태 변화 테이블
 
// 함수

int Collision(int x, int y) // 충돌 체크
{
	int count = 0; // 블럭 충돌 개수

	// Bar와의 충돌

	for (int i = 0; i < Bar.Length; i++)
	{
		if (y == Bar.Y)
		{
			if ((x >= Bar.X[0] && x <= Bar.X[2] + 1) ||
				((x + 1) >= Bar.X[0] && (x + 1) <= Bar.X[2] + 1))
			{
				Ball.Direction = (DIRECT) BlockStateTable[Ball.Direction];
				return 1;
			}
		}
	}

	// 블럭과의 충돌

	for (int i = 0; i < BLOCK_COUNT; i++)
	{
		if (Block[i].Life > 0) // Life가 남은 Block에 한해서
		{
			if (Block[i].Y == y) // y가 동일
			{
				if (Block[i].X == x || Block[i].X == (x + 1) ||
					(Block[i].X + 1) == x || (Block[i].X + 1) == (x + 1)) // x 또는 x+1이 동일
				{
					Ball.Direction = (DIRECT) BlockStateTable[Ball.Direction];
					Block[i].Life--;
					count++;
				}
			}
		}
	}
	
	if (count > 0)
		return 1;

	// 벽과의 충돌

	// ↑ ([0])
	if (y < 0)
	{
		Ball.Direction = (DIRECT) WallStateTable[0][Ball.Direction];
		return 1; // 충돌 O
	}
	
	// → ([1])
	if (x > BOARD_WIDTH)
	{
		Ball.Direction = (DIRECT)WallStateTable[1][Ball.Direction];
		return 1;
	}
	
	// ↓ ([2])
	if (y > BOARD_HEIGH)
	{
		Ball.Direction = (DIRECT)WallStateTable[2][Ball.Direction];
		return 1;
	}

	// ← ([3])
	if (x < 0)
	{
		Ball.Direction = (DIRECT)WallStateTable[3][Ball.Direction];
		return 1;
	}

	return 0; // 충돌 X
}

int OverlapBlock(int End, int x, int y) // 중복Block 존재? 
{
	for (int i = 0; i < End; i++)
	{
		if (Block[i].Y == y) // y동일
		{
			if (Block[i].X == x || (Block[i].X + 1) == x
				|| Block[i].X == (x + 1) || (Block[i].X + 1) == (x + 1)) // x동일
				return 1; // 중복 있음
		}
	} // 중복 검사 종료
	return 0; // 중복 없음
}

	void SetBlock(int BlockCount)
	{
		int x, y, i;
		srand((unsigned)time(NULL));
		for (int i = 0; i < BlockCount; i++)
		{
			Block[i].Life = 1; // Block[i]의 Life 지정

			while (1)
			{
				x = rand() % BOARD_WIDTH; // 0 <= x < 가로길이
				y = rand() % BOARD_HEIGH; // 0 <= y < 세로길이

				if (OverlapBlock(i, x, y) == 0) // 0~i번 까지의 블럭 중 중복이 없으면
				{
					Block[i].X = x;
					Block[i].Y = y;
					break;
				}
			} // while 문 끝
		} // for문 끝
	}

	void KeyControl(int key) // 키조작
	{
		clock_t CurTime = clock();
		int direction;
		
		if (CurTime - Bar.OldTime > Bar.MoveTime) // Ball 이동제한시간 경과 시 
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
				//(Ball.IsReady == 1) ? (Ball.IsReady = 0) : (Ball.IsReady = 1); // Ball.IsReady 바꿈 
				if (Ball.IsReady == 1) 
				{
					Ball.OldTime = clock();
					Ball.IsReady = 0; // 준비 O -> 준비 X
				}
				else
				{
					Init(); // 준비X -> 게임 초기화 
				}

				break;

			case '0': case '1': case '2': case '3': case '4': case '5': // Ball 방향 변경 
				direction = key - '0';
				Ball.IsReady = 1;
				Ball.X = Bar.X[1];
				Ball.Y = Bar.Y - 1;
				Ball.Direction = (DIRECT) direction;
				Ball.OldTime = clock();
				break;
			}
		}

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
					if (Collision(Ball.X, Ball.Y -1 ) == 0) // 이동할 좌표에서 충돌이 안 일어나면 
					{
						Ball.Y--; // 이동한다
					}
					// 충돌이 일어났을 경우, Collision에서 Ball.Direction이 변경된다.
					break;

				case TOP_RIGHT:
					if (Collision(Ball.X + 1, Ball.Y - 1) == 0)
					{
						Ball.X++;
						Ball.Y--;
					}
					break;

				case BOT_RIGHT:
					if (Collision(Ball.X + 1, Ball.Y + 1)== 0)
					{
						Ball.X++;
						Ball.Y++;
					}
					break;

				case BOTTOM:
					if (Collision(Ball.X, Ball.Y + 1) == 0)
					{
						Ball.Y++;
					}
					break;

				case BOT_LEFT:
					if (Collision(Ball.X - 1, Ball.Y + 1) == 0)
					{
						Ball.X--;
						Ball.Y++;
					}
					break;

				case TOP_LEFT:
					if (Collision(Ball.X - 1, Ball.Y - 1) == 0)
					{
						Ball.X--;
						Ball.Y--;
					}
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
		Ball.MoveTime = 100;

		// Block 생성
		SetBlock(BLOCK_COUNT);

	}

	void Update()
	{
		clock_t CurTime = clock(); // 현재 시각

		BallMove(CurTime);// 공 움직임
		
	}

	void Render()
	{
		ScreenClear();

		ScreenPrint(Ball.X, Ball.Y, "●"); // Ball 표시

		for (int i = 0; i < Bar.Length; i++) // Bar 표시
		{
			ScreenPrint(Bar.X[i], Bar.Y, "▣");
		}

		for (int i = 0; i < BLOCK_COUNT; i++) // Block 표시
		{
			if (Block[i].Life > 0) // Life가 남아있으면
				ScreenPrint(Block[i].X, Block[i].Y, "■"); 
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
