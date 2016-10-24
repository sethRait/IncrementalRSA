#include <stdio.h>
#include <strings.h>

int main() {
	int can_login = 0;
	char usr_input[10];
	char answer[10] = "tenchars10";
	gets(usr_input);
	if (strncmp(usr_input, answer, 10) == 0) {
		can_login = 1;
	}
	if (can_login) {
		printf("1");
	}
	else {
		printf("0");
	}
}
