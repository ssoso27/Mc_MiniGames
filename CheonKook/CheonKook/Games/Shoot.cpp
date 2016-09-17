#include "Header.h"
#include "Shoot.h"

namespace SB_Shoot
{

	// typedef 시리즈
	enum ControlKeys
	{
		SPACE = 32,
		LEFT = 75,
		RIGHT = 77
	};


	GameState p_GameState = START; // 최초의 상태 : START
	int p_Goal, p_Stage = -1, p_GameStartTime; // GoalIn? , 현 스테이지, 게임 시작 시간

	char StateString[500]; // 게임 상태 저장
	clock_t p_OldTime; // 게임 상태 전이를 위한 이동 시각 저장

	StageInfo p_StageInfo[] = { { 2, 1000 * 20, 2, 20, 3, 300,2}, {10, 1000 * 30, 2, 20, 5, 300,2 } ,{ 15, 1000 * 30, 2, 20, 5, 300,2 } };
	EFFECT Effect;
	GOAL Goal;
	BALL Ball;
	PLAYER Player;
	char strPlayer[] = { "|__●__|" }; //캐릭터
	int Length; // 주인공 캐릭터 길이
	int BallCount = 0; // 총 넣은 공의 갯수
	int GoalIn; // GoalIn 했는가?
	clock_t p_LimitTime; // 제한 시간
	int p_GoalCount; // 목표 골인 개수

	// 초기화
	void Init() {

		//StageInfo. 스테이지 구성요소
		if (p_Stage == -1) // 게임 첫 실행
			p_Stage = 0;

		p_LimitTime = p_StageInfo[p_Stage].LimitTime; // 제한 시간 설정
		p_GoalCount = p_StageInfo[p_Stage].GoalBall; // 목표 골인 개수

		//플레이어
		Player.CenterX = 3; //주인공 X 중심 좌표
		Player.CenterY = 15; //주인공 Y 중심 좌표 
		Player.MoveX = 20; // 주인공 이동 X좌표 초기화
		Player.Y = Player.MoveY = 22; // 주인공 이도 Y좌표 초기화
		Player.X = Player.MoveX - Player.CenterX; //주인공 캐릭터 출력 좌표
		Length = strlen(strPlayer); //주인공 전체 길이

		//공
		Ball.ReadyB = 1;
		Ball.bMoveX = Player.MoveX;
		Ball.bMoveY = Player.MoveY - 1;
		Ball.MoveTime = 100;

		//골대 (수정)
		int gLength, i;

		Goal.gMoveX = p_StageInfo[p_Stage].GD_X;
		Goal.gMoveY = p_StageInfo[p_Stage].GD_Y;
		Goal.gLength = p_StageInfo[p_Stage].GD_Length; // 골대 길이 = gLength * 2 + 1 
		Goal.MoveTime = p_StageInfo[p_Stage].GD_MoveTime;
		Goal.OldTime = clock();
		Goal.gDistance = p_StageInfo[p_Stage].GD_Dist;
		gLength = Goal.gLength * 2 + 1; // 배열의 최대 길이
		for (i = 0; i < gLength; i++) {
			Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
		}

		//세레머니
		Effect.StayTime = 3000; // 세레머니 화면 3초

		//
		p_OldTime = clock();
	}
	// 데이터 갱신
	void Update()
	{
		clock_t CurTime = clock();
		int gLength = Goal.gLength * 2 + 1;
		int i;



		if ((CurTime - Goal.OldTime) > Goal.MoveTime)
		{
			Goal.OldTime = CurTime;
			if (Goal.gMoveX + Goal.gDistance >= 0 && ((Goal.gLineX[gLength - 1] + 3) + Goal.gDistance) <= 79)
			{
				Goal.gMoveX += Goal.gDistance;
				for (i = 0; i < gLength; i++)
				{
					Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
				}
			}
			else {
				Goal.gDistance = Goal.gDistance * (-1); // 방향바꾸기 
			}
		}

		if (Ball.ReadyB == 0) //공이동중 
		{
			if ((CurTime - Ball.OldTime) > Ball.MoveTime) {
				if (Ball.bMoveY - 1 > 0) {
					Ball.bMoveY--;
					Ball.OldTime = CurTime;

					//골대의라인과 충돌 
					if (Ball.bMoveX >= Goal.gLineX[0] && Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1]) {
						if (Ball.bMoveY <= Goal.gMoveY) {//공 초기화 
							Ball.ReadyB = 1;
							Ball.bMoveX = Player.MoveX;
							Ball.bMoveY = Player.MoveY - 1;
							BallCount++; //득점
							GoalIn = 1;
							Effect.StartTime = clock();
						}
						//골대 충돌 
					}
					else if ((Ball.bMoveX >= Goal.gLineX[0] - 2 && Ball.bMoveX <= Goal.gLineX[0] - 1) || (Ball.bMoveX + 1 >= Goal.gLineX[0] - 2) && (Ball.bMoveX + 1 <= Goal.gLineX[0] - 1) || (Ball.bMoveX >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX <= Goal.gLineX[gLength - 1] + 3) || (Ball.bMoveX + 1 >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1] + 3)) {
						if (Ball.bMoveY <= Goal.gMoveY) {
							Ball.ReadyB = 1;
							Ball.bMoveX = Player.MoveX;
							Ball.bMoveY = Player.MoveY - 1;
						}
					}
				}
				else {
					Ball.ReadyB = 1;
					Ball.bMoveX = Player.MoveX;
					Ball.bMoveY = Player.MoveY - 1;
				}
			}
		}
		else {
			Ball.bMoveX = Player.MoveX;
		}

		//세레머니
		if (GoalIn == 1)
		{
			if ((CurTime - Effect.StartTime) > Effect.StayTime)
				GoalIn = 0;
		}

		//
		switch (p_GameState)
		{
		case START: // 게임 시작 화면

			sprintf(StateString, "\t  [슛골인 게임] \n\n"
				"\t\t===================================\n\n"
				"\t\t공을 던져 골대에 넣는 게임입니다.\n"
				"\t\t각 스테이지마다 제한 시간과 목표 점수가 \n"
				"\t\t있습니다.\n"
				"\t\t제한 시간과 목표 점수는 게임 실행 전,\n"
				"\t\t또는 실행 중에 제시 됩니다.\n\n"
				"\t\t===================================\n\n"
				"\t\t\t  - 조 작 법 -\n\n"
				"\t\t이동 : 방향키 | 공 던지기 : SPACE BAR\n\n"
				"\t\t-----------------------------------\n"
				"\t\t게임 시작 : SPACE BAR | 게임 종료 : q\n\n\n\n\n");

			break;

		case INIT: // case 초기화
			if (p_Stage != -1)
			{
				sprintf(StateString, "%s", "게임 및 사운드 초기화");
				if (CurTime - p_OldTime > 3000) // 게임 상태 전이?
				{
					p_OldTime = CurTime;
					BallCount = 0;
					p_GameState = READY; // READY 상태로 넘어감
				}
				else // 시간이 안 됐음.
				{ // INIT 창 띄움
					sprintf(StateString, "[INIT] 게임 스테이지 초기화");

					if (CurTime - p_OldTime > 3000) // 창 띄운 후, 상태 전이?
					{
						p_OldTime = CurTime;
					}
				}
			}
			break;

		case READY: // READY 상태
			sprintf(StateString, "[READY] %d 스테이지 \n \t\t\t\t\t\t목표 Goal : %d\n \t\t\t\t\t\t제한 시간 : %d초", p_Stage, p_GoalCount, p_LimitTime / 1000);
			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
				p_GameState = RUNNING;
				p_GameStartTime = CurTime;
			}
			break;

		case RUNNING: // RUNNING 상태
			if (CurTime - p_GameStartTime > p_StageInfo[p_Stage].LimitTime) // 제한시간 LimitTime을 넘김
			{
				p_GameState = STOP; // STOP 상태로 넘어감 -> 판별
			}
			else
			{
				sprintf(StateString, "[RUNNING] 제한 시간 : %d초. 현재 시간 : %d", p_StageInfo[p_Stage].LimitTime / 1000, (CurTime - p_GameStartTime) / 1000); // 문구 출력
			}
			break;
		case STOP: // STOP 상태. 성공/실패 판정
			if (BallCount >= p_GoalCount)
			{
				p_GameState = SUCCESS;
			}
			else
			{
				p_GameState = FAILED;
			}
			break;
		case SUCCESS: // SUCCESS 상태. 미션 성공
			if (p_Stage < 3)
			{
				sprintf(StateString, "스테이지 %d 미션 성공. 다음 단계? (Y/N)", p_Stage);
			}
			else // 모든 스테이지 클리어
			{
				sprintf(StateString, "모든 스테이지 클리어 \n");
			}

			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
			}
			break;
		case FAILED: // FAILED 상태. 미션 실패
			sprintf(StateString, "스테이지 %d 미션 실패.\n"
				"\t\t아무 키나 누르면, 결과창이 나옵니다.", p_Stage); // Y,N 입력. Stage 레벨 그대로.
			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
			}
			break;
		case RESULT: // RESULT 상태. 게임 결과
			sprintf(StateString, "[게임 결과 화면]\n\n\t\t\t가장 최근 스테이지에서 넣은 공 수 : %d\n\t\t\t최종 스테이지 : %d", BallCount, p_Stage);
			if (CurTime - p_OldTime > 3000)
			{
				p_OldTime = CurTime;
			}
			break;
		}
	}
	// 출력
	void Render()
	{
		char string[100] = { 0 };
		ScreenClear();
		int gLength, i;
		// 출력 시작

		if (p_GameState == RUNNING)
		{

			// 좌우에 벽을 만듬 (클리핑) 

			if (Player.X < 0)
				ScreenPrint(0, Player.MoveY, &strPlayer[Player.X * (-1)]);
			else if (Player.MoveX + (Length - Player.MoveX + Player.CenterX + 1) > 79)
			{
				strncat(string, strPlayer, Length - ((Player.MoveX + Player.CenterX + 1) - 79));
				ScreenPrint(Player.X, Player.Y, string);
			}
			else {
				ScreenPrint(Player.X, Player.Y, strPlayer);
			}

			ScreenPrint(Ball.bMoveX, Ball.bMoveY, "◎");
			sprintf(string, "주인공 이동좌표 : %d, %d              점 수 : %d/%d               초기화 : R 버튼 ", Player.MoveX, Player.Y, BallCount, p_GoalCount);
			ScreenPrint(0, 0, string);


			//골대 출력 

			ScreenPrint(Goal.gMoveX, Goal.gMoveY, "ㅁ");
			gLength = Goal.gLength * 2 + 1;

			for (i = 0; i < gLength; i++)
				ScreenPrint(Goal.gLineX[i], Goal.gMoveY, "ㅡ");

			ScreenPrint(Goal.gLineX[gLength - 1] + 2, Goal.gMoveY, "ㅁ");

			//세레머니 출력

			if (GoalIn == 1)
			{
				//ScreenClear();
				//GoalCere(10,5);
				ScreenPrint(50, 5, "** G O A L  I N **");
			}

		}
		// 상태 출력
		ScreenPrint(20, 10, StateString);

		//출력 끝


		ScreenFlipping();
	}

	//해제

	void Release()
	{
	}


	void Shoot()
	{
		int Key, Remain;

		ScreenInit();
		Init(); // 초기화

		while (1) //무한반복 
		{
			if (_kbhit()) // 키 입력?
			{
				Key = _getch();
				if (p_GameState == RESULT) // RESULT 키입력 -> 종료
					break;

				// RESULT 상태가 아닐 시

				if (Key == 'q' || Key == 'Q')
				{
					p_Stage = -1;
					break;
				}

				// START 상태에서의 키 조작
				if (p_GameState == START)
				{
					if (Key == SPACE)
						p_GameState = INIT;
				}

				// SUCCESS 상태에서의 키 조작
				if (p_GameState == SUCCESS)
				{
					p_OldTime = clock();
					switch (Key)
					{
					case 'Y': case 'y':
						if (p_Stage < 2) 
						{
							++p_Stage;
							p_GameState = INIT;
						}
						else // 모든 게임 클리어
						{
							p_GameState = RESULT;
						}

						break;
					case 'N': case 'n':
						p_GameState = RESULT;
						break;
					}
				}
				// FAILED 상태에서의 키 조작
				if (p_GameState == FAILED)
				{
					p_GameState = RESULT;
					p_OldTime = clock();
					p_Stage--;

					getchar();
				}
				/*
				if (p_GameState == FAILED || p_GameState==SUCCESS)
				{
					switch (Key)
					{
					case 'Y': case 'y':
						if (p_GameState == SUCCESS)
						{
							++p_Stage; // 미션성공 + 게임진행 원할 시, 스테이지 레벨 증가
							p_GameState = INIT;
						}
						if (p_GameState==FAILED)
							p_GameState = RESULT;
						p_OldTime = clock();
						break;
					case 'N': case 'n':
						if (p_GameState == FAILED)
						{
							p_Stage--; // 게임결과창을 위한 --
						}
						p_GameState = RESULT;
						p_OldTime = clock();
						break;
					}
				}
				*/
				switch (Key)
				{
					// S F Y
				case 'S': case 's':
					p_Goal = 1;
					break;
				case 'F': case 'f':
					p_Goal = 0;
					break;

					// 플레이어 캐릭터 조작
				case LEFT:
					if (Player.MoveX > 0) {
						Player.MoveX--;
						Remain = Length - (Player.CenterX + 1); // 남은길이 = 전체 길이 - (중심좌표 + 1)
						if (Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX < 0)
							Player.MoveX--;
						Player.X = Player.MoveX - Player.CenterX;
					}
					break;
				case RIGHT:
					if (Player.MoveX + 1 < 79) {
						Player.MoveX++;
						Remain = Length - (Player.CenterX + 1);
						if (Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX < 0)
							Player.MoveX++;
						Player.X = Player.MoveX - Player.CenterX;
					}
					break;
				case SPACE:
					if (Ball.ReadyB)
					{
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						Ball.OldTime = clock();
						Ball.ReadyB = 0;
					}

					break;
				case 'r':
					if (BallCount != 0)
					{
						BallCount = 0;
						Ball.ReadyB = 1;
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						p_GameState = INIT;
					}
					break;
				}
			}

			Update();//데이터 갱신 
			Render(); //화면 출력 

		}

	}
}