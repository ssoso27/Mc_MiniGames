#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int you;
int com;
int result;
int record[3] = { 0, };
char moves[5][50] = { "너랑 안해!", "가위", "바위", "보", "??!" };
char texts[5][50] = { "비겼습니다!", "플레이어가 이겼습니다!", "컴퓨터가 이겼습니다!", "잘못된 입력입니다..",
"게임을 종료합니다." };

int main() {
	srand(time(NULL));

	while (1) {
		printf("< 가위바위보 게임! >\n");
		printf("숫자를 입력해 주세요. (1)가위, (2)바위, (3)보, (0)그만하기 : ");

		you = -1;
		scanf_s("%d", &you);
		getchar();
		if (you<0 || you>3) you = 4;

		com = rand() % 3 + 1;

		printf("You : %s! / Computer : %s!\n", moves[you], moves[com]);

		if (you == 4) result = 3;
		else if (you == 0) result = 4;
		else {
			result = (3 + you - com) % 3;
			record[result]++;
		}

		printf("< %s %d승 %d무 %d패 >\n\n", texts[result], record[1], record[0], record[2]);

		if (you == 0) exit(0);
	}
}