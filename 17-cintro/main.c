#include <stdio.h>
#include <stdlib.h>
#include "simple.h"

int main() {
	int i = 0;
	while (i < 1000) {
		char *h = (char*)malloc(sizeof(char));
		*h = 'c';
		i++;
		free(h);
	}
	return 0;
}
