#include <string.h>
#include <stdio.h>

int main() {
	char s[10];

	int n = 33215;

	// puts n to s 
	snprintf(s, 10, "%d", n);
	
	printf("s[10] : %s\n", s);

	return 0;
}
