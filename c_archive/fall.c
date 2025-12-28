#include <stdio.h>
#include <stdlib.h>

void check_parity(int x) {
	switch (x % 2) {
		case 0:
			printf("x is even!\n");
		default:
			printf("x is odd!\n");
	}
}

int main(int argc, char** args) {
	check_parity(atoi(args[1]));
	return 0;
}
