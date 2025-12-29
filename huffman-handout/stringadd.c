#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	char* a = strdup("dafkjaklfj");
	char* b = strdup("asdfj23437423798");
	char* result = malloc(strlen(a) + strlen(b) + 1);
	strcpy(result, a);
	strcat(result, b);
	printf("%s\n", result);
	free(result);
	free(a);
	free(b);
	return 0;
}
