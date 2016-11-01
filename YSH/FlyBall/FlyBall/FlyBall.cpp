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


// 상수
const int PlayerFirstX = 10; // 플레이어의 시작 X좌표
const int PlayerFirstY = 6; // 플레이어의 시작 Y좌표
const int MaxBlockCount = 512; // Map에 들어가는 최대 Block 수
const int MAXMAPNUM = 8; // 최대 Map 수

						 // 전역 변수
int MapIndex; // 현재 Map의 Index

			  // 구조체 변수
BLOCK Block[MaxBlockCount];
BOARD Board;
PLAYER Player;
PORTAL Portal[4]; // 상, 우, 하, 좌
GOAL Goal;
STARTP StartP;

// 배열
bool IsBlock[Board.Height][Board.Width / 2] = { false, }; // Block 생성 위치 판별

// 함수
// Start, Goal 지점 Map 세팅
void SetStartGoal()
{
	srand((unsigned)time(NULL));

	StartP.whereMap = rand() % MAXMAPNUM;

	do
	{
		Goal.whereMap = rand() % MAXMAPNUM;
	} while (StartP.whereMap == Goal.whereMap);

}

// 이전 Map 정보 리셋
void MapReset()
{
	// Player 리셋
	Player.X = PlayerFirstX;
	Player.Y = PlayerFirstY;
	Player.Direction = M_RIGHT;
	Player.OldTime = clock();
	Player.IsReady = 1;

	// Block 리셋
	for (int i = 0; i < Board.Height; i++)
	{
		for (int j = 0; j < Board.Width / 2; j++)
		{
			IsBlock[i][j] = false;
		}
	}

	// Portal 리셋
	for (int i = 0; i < 4; i++)
	{
		Portal[i].IsEnable = false;
	}

	// Goal 리셋
	Goal.IsEnable = false;
}

// Portal 활성화 및 설정
void SetPortal(int i)
{
	switch (i)
	{
	case 0: // ↑
		Portal[i].IsEnable = true; // 포탈 활성화
		Portal[i].nextMap = MapIndex - 1; // 이동 맵 결정
		break;

	case 1: // →
		Portal[i].IsEnable = true; // 포탈 활성화
		Portal[i].nextMap = MapIndex + 2; // 이동 맵 결정
		break;

	case 2: // ↓
		Portal[i].IsEnable = true; // 포탈 활성화
		Portal[i].nextMap = MapIndex + 1; // 이동 맵 결정
		break;

	case 3: // ←
		Portal[i].IsEnable = true; // 포탈 활성화
		Portal[i].nextMap = MapIndex - 2; // 이동 맵 결정
		break;

	default:
		break;
	}
}

// Block 좌표 대입
void AssignCoord(int k)
{
	for (int i = 0; i < Board.Height; i++) // i행
	{
		for (int j = 0; j < Board.Width / 2; j++) // j열
		{
			if (IsBlock[i][j] == true) // MapMake()에 의해 생성된 블럭 자리
			{
				// Block 좌표 초기화
				Block[k].X = Board.leftX + (j * 2) + 1;
				Block[k].Y = Board.topY + i + 1;

				// 블럭 자리 false
				IsBlock[i][j] = false;

				// k번째 Block 좌표 초기화 종료
				return;
			} // if문 end
		} // for j end
	} // for i end
}

// Block Map 생성
void MapMake(int index)
{
	// Map 종류에 따라 다르게 생성
	switch (index)
	{
	case 0: // Map0
			// bool IsBlock[][] 에 true 넣을거 [14][31]
		for (int i = 2; i <= 31; i++) { IsBlock[0][i] = true; } // 0
		for (int i = 4; i <= 10; i++) { IsBlock[1][i] = true; }	//1
		for (int i = 21; i <= 27; i++) { IsBlock[1][i] = true; }//1
		for (int i = 14; i <= 18; i++) { IsBlock[2][i] = true; }//2
		for (int i = 17; i <= 24; i++) { IsBlock[3][i] = true; }//3		
		for (int i = 0; i <= 13; i++) { IsBlock[4][i] = true; }// 4
		for (int i = 24; i <= 29; i++) { IsBlock[5][i] = true; }//5
		for (int i = 0; i <= 9; i++) { IsBlock[6][i] = true; }//6
		for (int i = 19; i <= 21; i++) { IsBlock[6][i] = true; }//6
		for (int i = 0; i <= 11; i++) { IsBlock[7][i] = true; }//7
		for (int i = 16; i <= 28; i++) { IsBlock[7][i] = true; }//7
		for (int i = 0; i <= 12; i++) { IsBlock[8][i] = true; }//8
		for (int i = 24; i <= 29; i++) { IsBlock[8][i] = true; }//8
		for (int i = 17; i <= 19; i++) { IsBlock[9][i] = true; }//9
		for (int i = 26; i <= 31; i++) { IsBlock[9][i] = true; }//9
		for (int i = 10; i <= 14; i++) { IsBlock[10][i] = true; }//10
		for (int i = 24; i <= 28; i++) { IsBlock[10][i] = true; }//10
		for (int i = 1; i <= 6; i++) { IsBlock[11][i] = true; }//11
		for (int i = 11; i <= 18; i++) { IsBlock[11][i] = true; }//11
		for (int i = 5; i <= 7; i++) { IsBlock[12][i] = true; }//12
		for (int i = 17; i <= 22; i++) { IsBlock[12][i] = true; }//12
		for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14
																// 포탈 설정 
		SetPortal(1);
		SetPortal(2);

		break;


	case 1: //Map1
			// bool IsBlock[][] 에 true 넣을거 [14][31]
		for (int i = 2; i <= 10; i++) { IsBlock[0][i] = true; } // 0
		for (int i = 21; i <= 31; i++) { IsBlock[0][i] = true; } //0
		for (int i = 5; i <= 8; i++) { IsBlock[1][i] = true; }//1
		for (int i = 17; i <= 19; i++) { IsBlock[1][i] = true; }//1
		for (int i = 2; i <= 3; i++) { IsBlock[2][i] = true; }//2
		for (int i = 11; i <= 29; i++) { IsBlock[2][i] = true; }//2
		for (int i = 11; i <= 29; i++) { IsBlock[3][i] = true; }//3		
		for (int i = 0; i <= 8; i++) { IsBlock[4][i] = true; }// 4
		for (int i = 12; i <= 26; i++) { IsBlock[5][i] = true; }//5
		for (int i = 0; i <= 9; i++) { IsBlock[6][i] = true; }//6
		for (int i = 14; i <= 27; i++) { IsBlock[6][i] = true; }//6
		for (int i = 0; i <= 9; i++) { IsBlock[7][i] = true; }//7
		for (int i = 0; i <= 9; i++) { IsBlock[8][i] = true; }//8
		for (int i = 15; i <= 29; i++) { IsBlock[8][i] = true; }//8
		for (int i = 0; i <= 12; i++) { IsBlock[9][i] = true; }//9
		for (int i = 24; i <= 30; i++) { IsBlock[9][i] = true; }//9
		for (int i = 2; i <= 14; i++) { IsBlock[10][i] = true; }//10
		for (int i = 24; i <= 30; i++) { IsBlock[10][i] = true; }//10
		for (int i = 3; i <= 15; i++) { IsBlock[11][i] = true; }//11
		for (int i = 18; i <= 31; i++) { IsBlock[11][i] = true; }//11
		for (int i = 5; i <= 7; i++) { IsBlock[12][i] = true; }//12
		for (int i = 4; i <= 7; i++) { IsBlock[13][i] = true; }//13
		for (int i = 19; i <= 23; i++) { IsBlock[13][i] = true; }//13
		for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14

																// 포탈 설정 
		SetPortal(0);
		SetPortal(1);

		break;


	case 2: //Map2
			// bool IsBlock[][] 에 true 넣을거 [14][31]
		for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
		for (int i = 14; i <= 17; i++) { IsBlock[1][i] = true; }//1
		for (int i = 14; i <= 17; i++) { IsBlock[2][i] = true; }//2
		for (int i = 0; i <= 11; i++) { IsBlock[3][i] = true; }//3
		for (int i = 14; i <= 17; i++) { IsBlock[3][i] = true; }//3
		for (int i = 14; i <= 17; i++) { IsBlock[4][i] = true; }//4
		for (int i = 14; i <= 17; i++) { IsBlock[5][i] = true; }//5
		for (int i = 21; i <= 31; i++) { IsBlock[6][i] = true; }//6
		for (int i = 12; i <= 18; i++) { IsBlock[7][i] = true; }//1
		for (int i = 0; i <= 9; i++) { IsBlock[8][i] = true; }//8
		for (int i = 14; i <= 17; i++) { IsBlock[9][i] = true; }//9
		for (int i = 14; i <= 20; i++) { IsBlock[10][i] = true; }//10
		for (int i = 10; i <= 24; i++) { IsBlock[11][i] = true; }//11
		for (int i = 14; i <= 27; i++) { IsBlock[12][i] = true; }//12
		for (int i = 14; i <= 17; i++) { IsBlock[13][i] = true; }//13
		for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14

																// 포탈 설정 (IsEnable, nextMap)
		SetPortal(1);
		SetPortal(2);
		SetPortal(3);

		break;


	case 3: //Map3
			// bool IsBlock[][] 에 true 넣을거 [14][31]
			//0
		for (int i = 6; i <= 9; i++) { IsBlock[0][i] = true; }
		for (int i = 16; i <= 19; i++) { IsBlock[0][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[0][i] = true; }
			//1
		for (int i = 6; i <= 9; i++) { IsBlock[1][i] = true; }
		for (int i = 16; i <= 19; i++) { IsBlock[1][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[1][i] = true; }
			//2
		for (int i = 6; i <= 9; i++) { IsBlock[2][i] = true; }
		for (int i = 16; i <= 19; i++) { IsBlock[2][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[2][i] = true; }
			//3
		for (int i = 0; i <= 3; i++) { IsBlock[3][i] = true; }
		for (int i = 6; i <= 13; i++) { IsBlock[3][i] = true; }
		for (int i = 16; i <= 19; i++) { IsBlock[3][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[3][i] = true; }
			//4
		for (int i = 16; i <= 19; i++) { IsBlock[4][i] = true; }
		for (int i = 22; i <= 28; i++) { IsBlock[4][i] = true; }
			//5
		for (int i = 16; i <= 19; i++) { IsBlock[5][i] = true; }
		for (int i = 22; i <= 28; i++) { IsBlock[5][i] = true; }
			//6
		for (int i = 12; i <= 19; i++) { IsBlock[6][i] = true; }
			//7
		for (int i = 0; i <= 9; i++) { IsBlock[7][i] = true; }
			//8
		for (int i = 23; i <= 28; i++) { IsBlock[8][i] = true; }
			//9
		for (int i = 6; i <= 9; i++) { IsBlock[9][i] = true; }
		for (int i = 22; i <= 28; i++) { IsBlock[9][i] = true; }
			//10
		for (int i = 6; i <= 9; i++) { IsBlock[10][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[10][i] = true; }
			//11
		for (int i = 6; i <= 9; i++) { IsBlock[11][i] = true; }
		for (int i = 16; i <= 19; i++) { IsBlock[11][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[11][i] = true; }
			//12
		for (int i = 6; i <= 9; i++) { IsBlock[12][i] = true; }
		for (int i = 16; i <= 19; i++) { IsBlock[12][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[12][i] = true; }
			//13
		for (int i = 6; i <= 9; i++) { IsBlock[13][i] = true; }
		for (int i = 16; i <= 19; i++) { IsBlock[13][i] = true; }
		for (int i = 25; i <= 28; i++) { IsBlock[13][i] = true; }
			//14
		for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }

																// 포탈 설정 (IsEnable, nextMap)
		SetPortal(0);
		SetPortal(1);
		SetPortal(3);

		break;


	case 4: //Map4
			// bool IsBlock[][] 에 true 넣을거 [14][31]
		for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
		for (int i = 10; i <= 31; i++) { IsBlock[1][i] = true; }//1
		for (int i = 10; i <= 31; i++) { IsBlock[2][i] = true; }//2
		for (int i = 0; i <= 7; i++) { IsBlock[3][i] = true; }//3
		for (int i = 10; i <= 31; i++) { IsBlock[3][i] = true; }//3
		for (int i = 10; i <= 31; i++) { IsBlock[4][i] = true; }//4
		for (int i = 10; i <= 31; i++) { IsBlock[5][i] = true; }//5
		for (int i = 3; i <= 31; i++) { IsBlock[6][i] = true; }//6
		for (int i = 6; i <= 10; i++) { IsBlock[7][i] = true; }//7
		for (int i = 0; i <= 3; i++) { IsBlock[8][i] = true; }//8
		for (int i = 6; i <= 10; i++) { IsBlock[8][i] = true; }//8
		for (int i = 6; i <= 10; i++) { IsBlock[9][i] = true; }//9
		for (int i = 15; i <= 29; i++) { IsBlock[9][i] = true; }//9
		for (int i = 6; i <= 10; i++) { IsBlock[10][i] = true; }//10
		for (int i = 15; i <= 24; i++) { IsBlock[10][i] = true; }//10
		for (int i = 3; i <= 8; i++) { IsBlock[11][i] = true; }//11
		for (int i = 13; i <= 24; i++) { IsBlock[11][i] = true; }//11
		for (int i = 15; i <= 24; i++) { IsBlock[12][i] = true; }//12
		for (int i = 27; i <= 31; i++) { IsBlock[12][i] = true; }//12
		for (int i = 15; i <= 24; i++) { IsBlock[13][i] = true; }//13
		for (int i = 3; i <= 10; i++) { IsBlock[14][i] = true; }//14
		for (int i = 15; i <= 24; i++) { IsBlock[14][i] = true; }//14

																 // 포탈 설정 (IsEnable, nextMap)
		SetPortal(2);
		SetPortal(3);

		break;


	case 5: //Map5
			// bool IsBlock[][] 에 true 넣을거 [14][31]
		for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
		for (int i = 8; i <= 10; i++) { IsBlock[1][i] = true; }//1
		for (int i = 21; i <= 25; i++) { IsBlock[1][i] = true; }//1
		for (int i = 8; i <= 10; i++) { IsBlock[2][i] = true; }//2
		for (int i = 21; i <= 25; i++) { IsBlock[2][i] = true; }//2
		for (int i = 0; i <= 5; i++) { IsBlock[3][i] = true; }//3
		for (int i = 8; i <= 10; i++) { IsBlock[3][i] = true; }//3
		for (int i = 16; i <= 18; i++) { IsBlock[3][i] = true; }//3
		for (int i = 8; i <= 10; i++) { IsBlock[4][i] = true; }//4
		for (int i = 13; i <= 18; i++) { IsBlock[4][i] = true; }//4
		for (int i = 8; i <= 10; i++) { IsBlock[5][i] = true; }//5
		for (int i = 16; i <= 21; i++) { IsBlock[5][i] = true; }//5
		for (int i = 8; i <= 10; i++) { IsBlock[6][i] = true; }//6
		for (int i = 16; i <= 28; i++) { IsBlock[6][i] = true; }//6
		for (int i = 3; i <= 13; i++) { IsBlock[7][i] = true; }//7
		for (int i = 16; i <= 21; i++) { IsBlock[7][i] = true; }//7
		for (int i = 8; i <= 10; i++) { IsBlock[8][i] = true; }//8
		for (int i = 16; i <= 21; i++) { IsBlock[8][i] = true; }//8
		for (int i = 8; i <= 10; i++) { IsBlock[9][i] = true; }//9
		for (int i = 16; i <= 21; i++) { IsBlock[9][i] = true; }//8
		for (int i = 26; i <= 31; i++) { IsBlock[9][i] = true; }//9
		for (int i = 0; i <= 5; i++) { IsBlock[10][i] = true; }//10
		for (int i = 8; i <= 10; i++) { IsBlock[10][i] = true; }//10
		for (int i = 13; i <= 21; i++) { IsBlock[10][i] = true; }//10
		for (int i = 8; i <= 10; i++) { IsBlock[11][i] = true; }//11
		for (int i = 16; i <= 24; i++) { IsBlock[11][i] = true; }//11
		for (int i = 16; i <= 21; i++) { IsBlock[12][i] = true; }//12
		for (int i = 26; i <= 29; i++) { IsBlock[12][i] = true; }//12
		for (int i = 16; i <= 21; i++) { IsBlock[13][i] = true; }//13
		for (int i = 26; i <= 29; i++) { IsBlock[13][i] = true; }//13
		for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14

																// 포탈 설정 (IsEnable, nextMap)
		SetPortal(0);
		SetPortal(3);

		break;

	case 6: //Map6
			// bool IsBlock[][] 에 true 넣을거 [14][31]
		for (int i = 0; i <= 6; i++) { IsBlock[0][i] = true; }//0
		for (int i = 18; i <= 31; i++) { IsBlock[0][i] = true; }//0
		for (int i = 4; i <= 7; i++) { IsBlock[1][i] = true; }//1
		for (int i = 19; i <= 31; i++) { IsBlock[1][i] = true; }//1
		for (int i = 5; i <= 8; i++) { IsBlock[2][i] = true; }//2
		for (int i = 6; i <= 9; i++) { IsBlock[3][i] = true; }//3
		for (int i = 2; i <= 5; i++) { IsBlock[5][i] = true; }//5
		for (int i = 11; i <= 13; i++) { IsBlock[5][i] = true; }//5
		for (int i = 1; i <= 4; i++) { IsBlock[6][i] = true; }//6
		for (int i = 11; i <= 13; i++) { IsBlock[6][i] = true; }//6
		for (int i = 0; i <= 13; i++) { IsBlock[7][i] = true; }//7
		for (int i = 17; i <= 31; i++) { IsBlock[7][i] = true; }//7
		for (int i = 0; i <= 13; i++) { IsBlock[8][i] = true; }//8
		for (int i = 17; i <= 31; i++) { IsBlock[8][i] = true; }//8
		for (int i = 10; i <= 12; i++) { IsBlock[9][i] = true; }//9
		for (int i = 10; i <= 12; i++) { IsBlock[10][i] = true; }//10
		for (int i = 10; i <= 12; i++) { IsBlock[11][i] = true; }//11
		for (int i = 0; i <= 31; i++) { IsBlock[14][i] = true; }//14
		SetPortal(1);
		SetPortal(2);
		break;
	case 7: //Map7
			// bool IsBlock[][] 에 true 넣을거 [14][31]
		for (int i = 0; i <= 31; i++) { IsBlock[0][i] = true; }//0
		for (int i = 7; i <= 12; i++) { IsBlock[1][i] = true; }//1
		for (int i = 20; i <= 25; i++) { IsBlock[1][i] = true; }//1
		for (int i = 15; i <= 17; i++) { IsBlock[2][i] = true; }//2
		for (int i = 2; i <= 4; i++) { IsBlock[3][i] = true; }//3
		for (int i = 20; i <= 25; i++) { IsBlock[4][i] = true; }//4
		for (int i = 7; i <= 12; i++) { IsBlock[5][i] = true; }//5
		for (int i = 15; i <= 17; i++) { IsBlock[5][i] = true; }//5
		for (int i = 2; i <= 4; i++) { IsBlock[7][i] = true; }//7
		for (int i = 20; i <= 25; i++) { IsBlock[7][i] = true; }//7
		for (int i = 15; i <= 17; i++) { IsBlock[8][i] = true; }//8
		for (int i = 7; i <= 12; i++) { IsBlock[9][i] = true; }//9
		for (int i = 20; i <= 25; i++) { IsBlock[10][i] = true; }//10
		for (int i = 2; i <= 4; i++) { IsBlock[11][i] = true; }//11
		for (int i = 15; i <= 17; i++) { IsBlock[11][i] = true; }//11
		for (int i = 7; i <= 12; i++) { IsBlock[13][i] = true; }//13
		for (int i = 20; i <= 25; i++) { IsBlock[13][i] = true; }//13
		for (int i = 0; i <= 31; i++) {	IsBlock[14][i] = true;}//14
		SetPortal(0);
		SetPortal(1);
		break;
	default:
		break;
	}

}

// index에 맞는 Map Block 생성
void CreateBlock(int MapIndex)
{
	MapReset(); // 이전 맵 리셋

	if (MapIndex == Goal.whereMap) // Goal Map 이면
		Goal.IsEnable = true; // Goal 활성화

	MapMake(MapIndex); // 맵 생성
	for (int i = 0; i < MaxBlockCount; i++)
	{
		AssignCoord(i); // 좌표 부여
	}
}

// 충돌 체크
int Collision(int x, int y)
{
	int count = 0;

	// Player와 Portal[i]의 충돌
	for (int i = 0; i < 4; i++)
	{
		if (Portal[i].IsEnable == false) // 유효하지 않은 포탈이면
			continue;

		if (Portal[i].Y == y) // y 또는 y+1이 동일
		{
			if (Portal[i].X == x || Portal[i].X == (x + 1) ||
				(Portal[i].X + 1) == x || (Portal[i].X + 1) == (x + 1)) // x 또는 x+1이 동일
			{
				// 충돌 시 반응
				// Portal[i].nextMap에 따른 맵 이동
				MapIndex = Portal[i].nextMap;
				CreateBlock(MapIndex);

				return 1; // 충돌 O
			}
		}
	}
	// Player과 Block의 충돌
	for (int i = 0; i < MaxBlockCount; i++)
	{
		if (Block[i].Y == y) // y 또는 y+1이 동일
		{
			if (Block[i].X == x || Block[i].X == (x + 1) ||
				(Block[i].X + 1) == x || (Block[i].X + 1) == (x + 1)) // x 또는 x+1이 동일
			{
				// Player 상태 초기화
				Player.X = PlayerFirstX;
				Player.Y = PlayerFirstY;
				Player.Direction = M_RIGHT;
				Player.OldTime = clock();
				Player.IsReady = 1;

				// 충돌 시 반응
				Player.Life--; // Life 감소

				count++; // 충돌체크
			}
		}
	}

	if (count > 0)
		return 1;

	// Player와 벽의 충돌
	if (y < Board.topY + 1 || x > Board.rightX - 1 || y > Board.bottomY - 1 || x < Board.leftX + 1)
	{
		// 충돌 시 반응
		Player.Life--; // Life 감소

					   // Player 상태 초기화
		Player.X = PlayerFirstX;
		Player.Y = PlayerFirstY;
		Player.Direction = M_RIGHT;
		Player.OldTime = clock();
		Player.IsReady = 1;

		return 1; // 충돌 O
	}

	return 0; // 충돌 X
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
			case M_TOP:
				if (Collision(Player.X, Player.Y - 1) == 0) // 이동할 좌표에서 충돌이 안 일어나면 
				{
					Player.Y--; // 이동한다
				}
				// 충돌이 일어났을 경우, Collision에서 충돌 처리
				break;

			case M_RIGHT:
				if (Collision(Player.X + 2, Player.Y) == 0)
				{
					Player.X += 2;
				}
				break;

			case M_BOTTOM:
				if (Collision(Player.X, Player.Y + 1) == 0)
				{
					Player.Y++;
				}
				break;
				
			case M_LEFT:
				if (Collision(Player.X - 2, Player.Y) == 0)
				{
					Player.X -= 2;
				}
				break;

			default:
				break;

			}
		}
		if (Player.X < 0 || Player.X >BOARD_WIDTH || Player.Y < 0 || Player.Y > BOARD_HEIGH) // 벽에 충돌
		{
			Player.IsReady = 1;
			Player.Direction = M_RIGHT;
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
		direction = M_TOP;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '6': // →
		direction = M_RIGHT;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '2': // ↓
		direction = M_BOTTOM;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '4': // ←
		direction = M_LEFT;
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
	Board.topY = 4;
	Board.bottomY = Board.topY + Board.Height;
	Board.leftX = 8;
	Board.rightX = Board.leftX + Board.Width;

	// Portal 초기화
	// 상
	Portal[0].X = 35;
	Portal[0].Y = 6;
	// 우
	Portal[1].X = 70;
	Portal[1].Y = 10;
	// 하
	Portal[2].X = 35;
	Portal[2].Y = 18;
	// 좌
	Portal[3].X = 10;
	Portal[3].Y = 10;

	for (int i = 0; i < 4; i++)
	{
		Portal[i].IsEnable = false; // 모든 Portal 비활성화
	}

	// Start, Goal 지점 초기화
	Goal.X = 70;
	Goal.Y = 18;
	SetStartGoal();

	// Map 초기화
	MapIndex = StartP.whereMap;
	CreateBlock(MapIndex);


	// Player 초기화
	Player.X = PlayerFirstX;
	Player.Y = PlayerFirstY;
	Player.Life = 3;
	Player.Direction = M_RIGHT;
	Player.OldTime = clock();
	Player.IsReady = 1;
	Player.MoveTime = 170;
}

void Update()
{
	clock_t CurTime = clock(); // 현재 시각

	PlayerMove(CurTime);
}

void Render()
{
	ScreenClear();

	// 상단바 출력
	char TheTopBar[81];
	sprintf(TheTopBar, "현 스테이지 : %d | Life : %d  \t\t    [Map%d]", 1, /*Stage.Level + 1,*/ Player.Life, MapIndex);
	ScreenPrint(17, 2, TheTopBar);

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

	// Start, Goal 출력
	ScreenPrint(PlayerFirstX, PlayerFirstY, "S");
	ScreenPrint(Goal.X, Goal.Y, "G");

	// Player 출력
	ScreenPrint(Player.X, Player.Y, "●");

	// Block 출력
	for (int i = 0; i < MaxBlockCount; i++)
	{
		if (Block[i].X == 0 && Block[i].Y == 0) continue; // 좌표가 주어지지 않은 Block 표시 X
		ScreenPrint(Block[i].X, Block[i].Y, "■");
	}

	// Portal 출력
	for (int i = 0; i < 4; i++)
	{
		if (Portal[i].IsEnable == false) // 유효하지 않은 포탈이면
			continue;

		ScreenPrint(Portal[i].X, Portal[i].Y, "★");
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
