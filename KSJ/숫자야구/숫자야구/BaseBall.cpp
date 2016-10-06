#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

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

void main() {
	//오프닝 화면 만들기(게임설명)
	

	printf("숫 자 야 구\n\n");
	printf("지금부터 숫자야구를 시작하겠습니다.\n\n");
	printf("게임 규칙\n\n");
	printf("정해진 세 자리 수를 맞추는 게임입니다.\n정해진 수를 예측하고 세 자리 수를 입력하면,\n");
	printf("숫자와 자리가 맞을 경우 스트라이크\n");
	printf("숫자는 맞는데 자리가 틀릴 경우 볼입니다.\n");
	printf("ex) 정답 123, 입력한 값 132 -> 1 스트라이크 2볼\n\n");
	printf("입력방법 : 숫자를 하나씩 입력하며 space bar나 enter키로 각각의 수를 구분한다.\n\n");

	printf("enter키를 누르면 시작합니다.");
	getchar();

	system("cls");


	//게임 화면

	int x, y, z; // 컴퓨터가 생각한 정답
	
	int life = 10;

	int temp=0; // 스트라이크=temp=3 마지막에 승리하셨습니다 출력

	srand((unsigned)time(NULL)); // rand 함수를 쓰기 위함

	// 컴퓨터의 숫자 지정
	x = (rand() % 9) + 1; // 숫자 1~9까지만 사용할 거 - 난수의 9에 대한 나머지 0~8 -> 1~9
	
	y = (rand() % 9) + 1;
	if (y == x) {

		y = (rand() % 9) + 1;

	}// 다른 수 나올 때까지 반복

	z = (rand() % 9) + 1;
	while (z == x || z == y) {

		z = (rand() % 9) + 1;

	}//x,y 둘과 다르게

	// 화면 출력
	printf("%d %d %d", x, y, z); // 코딩 중에만 테스트용으로 사용

	printf("숫자 세 개를 입력하세요. 남은 목숨 : %d \n",life);

	// 사용자 숫자 입력
	int a, b, c;

	//----------------------for문 시작

	for (life = 9; life != -1; life--) {



		scanf("%d", &a);
		scanf("%d", &b);
		scanf("%d", &c);
		//scanf("%d, %d, %d",&a, &b, &c);
		/*
		while (1)
		{
			if ((a != b) && (b != c) && (c != a))
				break;

			printf("다른 숫자 3개로 다시 입력하세요");
			scanf("%d, %d, %d", &a, &b, &c);
		}*/

		while (a == b || b == c || c == a) {
			printf("다른 숫자 3개로 다시 입력하세요 \n");
			/*scanf("%d", &a);
			scanf("%d", &b);
			scanf("%d", &c);*/ //-------------------------------------------왜 scanf를 나눠써야만 무한루프 안 되고 정상적으로 돌아가는지 질문하기
			scanf("%d %d %d", &a, &b, &c); //------------------------------얘는 무한루프 돼요ㅠㅠ

			/*
			--------------------------------------------------------------scanf("%d, %d, %d", &a, &b, &c) ""안의 ,가 문제임.
																			 tip! - 입력할때, 1, 2, 3으로 쉼표 섞어쓰면 입력까지는 괜찮음.
																				  - 판정은 어떨지 아직 확인 안해봤음.
			*/
		}

		// 숫자 맞는지 판별

		//스트라이크 판별
		
		int strike = 0;
		int ball = 0;


		if (a == x) {

			strike++;

		}

		if (b == y) {

			strike++;

		}

		if (c == z) {

			strike++;

		}

		//볼 판별
		if (a == y || a == z) {

			ball++;

		}
		if (b == x || b == z) {

			ball++;

		}
		if (c == y || c == x) {

			ball++;

		}

		printf("%d 스트라이크, %d 볼, 남은 목숨 : %d \n", strike, ball,life);

		if (strike == 3) {
			temp = 3;
			break;
		}

	}

	//루프 돌리기 

	if ( temp!= 3) {
		printf("게임오버 \n");
	}
	if (temp == 3) {
		printf("승리하셨습니다. \n");
	}


	//while (strike != 3){}
	//for문을 써보자


	














	getchar();
	getchar();
	
}
