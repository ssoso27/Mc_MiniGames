#include "Header.h"
#include "Screen.h"
#include "BaseBall.h"

/*
//숫자 야구 만들기
// 숫자 야구란?
// 스트라이크 : 숫자와 자리를 맞추면
// 볼 : 숫자는 맞는데 자리가 틀리면

// 주의 : 같은 숫자가 나오면 안됨

//숫자 야구
/*  진행순서
게임방법, 안내 - 나중에 만들고

-게임 시작
컴 - 랜덤한 숫자 생각, 화면에는 _ _ _ 숫자를 입력하세요.
	 숫자 입력 받음.
반복
(
사람 - 숫자 입력
컴 - 스트라이크를 먼저 확인
	 스트라이크 제외하고 볼 확인
	 각각 결과 출력
	 숫자를 입력하세요.
)

*/

//namespace SJ_BaseBall
//{
	// 전역 변수
	//char startPrint[400]; // 시작 화면 표시용 문자열
	char statPrint[400]; // StatusPrint()에서 사용 문자열. 게임 상태 등을 표현.
	char gueAftPrint[100]; // 추측 후 출력 메시지
	char guidePrint[100]; // 현재 상태 안내 메시지

	int strike; // strike 개수
	int ball; // ball 개수

	bool enterFlag;

	clock_t stat_OldTime = clock(); // StatusPrint 에서 문구 출력용. 마지막 실행 시각.

	// 구조체 & 열거형 변수
	COMPUTER Computer;
	PLAYER Player;
	INBOX InBox[3];
	GAMESTATUS GameStatus;

	// 함수
	void SetAnswer() // Computer의 정답 설정
	{
		srand((unsigned)time(NULL)); // rand 함수를 쓰기 위함

									 // 컴퓨터의 숫자 지정
		Computer.x = (rand() % 9) + 1; // 숫자 1~9까지만 사용할 거 - 난수의 9에 대한 나머지 0~8 -> 1~9

		Computer.y = (rand() % 9) + 1;
		if (Computer.y == Computer.x) {

			Computer.y = (rand() % 9) + 1;

		}// 다른 수 나올 때까지 반복
		Computer.z = (rand() % 9) + 1;
		while (Computer.z == Computer.x || Computer.z == Computer.y) {

			Computer.z = (rand() % 9) + 1;

		}//x,y 둘과 다르게
	}

	void InputNumber(int key) // InputBox에 key 입력
	{
		for (int i = 0; i < 3; i++)
		{
			if (InBox[i].num == -1) // InBox[i]에 숫자가 없으면
			{
				InBox[i].num = key; // 숫자 입력하고
				break; // for문 종료
			}
		}
	}

	void GuessAnswer() // Player의 정답 추측
	{
		Player.a = InBox[0].num;
		Player.b = InBox[1].num;
		Player.c = InBox[2].num;
	}

	bool IsAnswer() // 정답을 맞췄는지 판별
	{
		if (strike == 3)
		{
			return true;
		}

		return false;
	}

	void CheckAnswer() // 숫자 맞는지 판별
	{
		//스트라이크 판별
		if (Player.a == Computer.x) {
			strike++;
		}

		if (Player.b == Computer.y) {
			strike++;
		}

		if (Player.c == Computer.z) {
			strike++;
		}

		//볼 판별
		if (Player.a == Computer.y || Player.a == Computer.z) {
			ball++;
		}
		if (Player.b == Computer.x || Player.b == Computer.z) {
			ball++;
		}
		if (Player.c == Computer.y || Player.c == Computer.x) {
			ball++;
		}

		Player.life--; // life 감소
		//sprintf(gueAftPrint, "%d 스트라이크, %d 볼, 남은 목숨 : %d", strike, ball, Player.life);
	}

	void AssignMassage() // 추측 후 출력메시지 입력
	{
		if (IsAnswer() == true) // 정답을 맞췄다면
		{
			sprintf(gueAftPrint, "승리하셨습니다. 다시 하시겠습니까? [Y/N]");
			GameStatus = FINISH; // 게임 상태 변경
		}
		else if (Player.life <= 0) // life가 0 이하면
		{
			sprintf(gueAftPrint, "게임 오버. 다시 하시겠습니까? [Y/N]");
			GameStatus = FINISH;
		}
		else
		{
			sprintf(gueAftPrint, "%d 스트라이크, %d 볼, 남은 목숨 : %d", strike, ball, Player.life);
		}
	}

	void ResetVari() // 일부 변수 초기화
	{
		// InputBox 초기화`
		for (int i = 0; i < 3; i++) 
		{
			InBox[i].num = -1;
		}

		// Player 추측 답 초기화
		Player.a = -1;
		Player.b = -1;
		Player.c = -1;
		
		// strike, ball 초기화
		strike = 0;
		ball = 0;
	}

	void StatusPrint() // GameStatus에 따른 화면 출력 및 상태 변화
	{
		clock_t CurTime = clock(); // 현재 시각

		switch (GameStatus)
		{
		case START:
			// 시작 문구 초기화
			sprintf(statPrint,
				"숫 자 야 구\n\n"
				"지금부터 숫자야구를 시작하겠습니다.\n\n"
				"게임 규칙\n\n"
				"정해진 세 자리 수를 맞추는 게임입니다.\n정해진 수를 예측하고 세 자리 수를 입력하면,\n"
				"숫자와 자리가 맞을 경우 스트라이크\n"
				"숫자는 맞는데 자리가 틀릴 경우 볼입니다.\n"
				"ex) 정답 123, 입력한 값 132 -> 1 스트라이크 2볼\n\n"
				"입력방법 : 숫자를 하나씩 입력하며, 전부 입력한 후엔 [Enter]를 누릅니다.\n\n"
				"[Space Bar]키를 누르면 시작합니다.");

			// 출력
			ScreenPrint(10, 2, statPrint);
			break;

		case INIT:
			// 게임 초기화 (void Init()에서 따왔음)

			// Computer의 정답 설정
			SetAnswer();

			// 목숨 설정
			Player.life = 10;

			// strike, ball 개수 설정
			strike = 0;
			ball = 0;

			// InputBox 초기화
			for (int i = 0; i < 3; i++)
			{
				InBox[i].num = -1;
				InBox[i].X = 10 + (4 * i);
				InBox[i].Y = 9;
			}

			// 추측 문구 초기화
			sprintf(gueAftPrint, "%d 스트라이크, %d 볼, 남은 목숨 : %d", strike, ball, Player.life);

			// 화면출력
			if (CurTime - stat_OldTime < 3 * 1000) // 3초 동안 출력
			{
				sprintf(statPrint, "[컴퓨터 숫자 세팅 중]");
				ScreenPrint(25, 8, statPrint);
			}
			else
			{
				GameStatus = RUNNING; // 3초 출력 후, 게임 시작.
				stat_OldTime = CurTime; // 마지막 실행 시각 = 현재 시각
			}

			break;

		case RUNNING:
			break;

		case FINISH:
			break;
		}
	}

	void KeyControl(int key) // 키 입력 시 수행
	{

		if (GameStatus == START)
		{
			if (key == 32) // SPACE 입력 시
				GameStatus = INIT;
		}

		if (GameStatus == RUNNING)
		{
			if (key == 13) // Enter 입력시
			{
				enterFlag = true;
			}

			if ((key - 48) >= 1 && (key - 48) <= 9)
			{
				InputNumber(key - 48); // 1~9 숫자만 입력
			}
		}

		if (GameStatus == FINISH)
		{
			switch (key)
			{
			case 'Y': case 'y':
				GameStatus = INIT; // 게임 재시작
				break;

			case 'N': case 'n':
				sprintf(gueAftPrint, "게임 종료. 나가려면 [Q]를 누르세요.");
				break;

			default:
				break;
			}
		}
	}

	// 프레임워크 함수

	void Init()
	{
		// GameStatus 초기화
		GameStatus = START;

		// Computer의 정답 설정
		SetAnswer();

		// 목숨 설정
		Player.life = 10;

		// strike, ball 개수 설정
		strike = 0;
		ball = 0;

		// InputBox 초기화
		for (int i = 0; i < 3; i++)
		{
			InBox[i].num = -1;
			InBox[i].X = 10 + (4*i);
			InBox[i].Y = 9;
		}
	
		// 시작 문구 초기화 -> StatusPrint()로 이동
		
	}

	void Update()
	{
		if (enterFlag == true) // Enter 입력이 있으면
		{
			GuessAnswer(); // 추측 정답 입력
			//(3개 다 입력 + 엔터 입력 시 수행) (수정 필요)
			if (InBox[2].num != -1)
			{
				CheckAnswer(); // 정답인지 판별
				AssignMassage(); // 추측 후 출력 메시지 입력
				ResetVari(); // 변수 초기화
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
		StatusPrint(); // GameStatus에 따른 문구 출력 

		if (GameStatus == RUNNING || GameStatus == FINISH)
		{
			sprintf(guidePrint, "숫자 세 개를 입력하세요. 남은 목숨 : %d \n", Player.life);
			ScreenPrint(10, 5, guidePrint);

			// 입력한 수 출력
			for (int i = 0; i < 3; i++)
			{
				if (InBox[i].num != -1) // 숫자가 있는 것만 출력
				{
					sprintf(InBoxNum, "%d", InBox[i].num);
					ScreenPrint(InBox[i].X, InBox[i].Y, InBoxNum);
				}
			}

			// 테스트용 정답 출력
			sprintf(temp, "%d", Computer.x);
			ScreenPrint(10, 13, temp);
			sprintf(temp, "%d", Computer.y);
			ScreenPrint(10, 16, temp);
			sprintf(temp, "%d", Computer.z);
			ScreenPrint(10, 19, temp); 

			ScreenPrint(10, 10, gueAftPrint); // 추측 후 메시지 출력
		}

		ScreenFlipping();
	}

	//BaseBall
	void main() {
		Init();
		ScreenInit();

		int key;

		while (1)
		{
			// 키입력 발생 시 수행
			if (_kbhit())
			{
				key = _getch();

				if (key == 'q' || key == 'Q')
					break;			

				KeyControl(key); // Key 입력 시 수행
			}

			Update();
			Render();
		}

	}

//}