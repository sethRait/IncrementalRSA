#include <stdio.h>
#include <strings.h>

int main() {
	int can_login = 0;
	char usr_input[12];
	char answer[12] = "twelvechars!";
	gets(usr_input);
	if (strncmp(usr_input, answer, 12) == 0) {
		can_login = 1;
	}
	if (can_login) {
		printf("1");
	}
	else {
		printf("0");
	}
}
