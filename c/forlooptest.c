#include <stdio.h>

// what is the difference between
// THIS:
// 		for (i = 0; i < 3; ++i)
// AND THIS:
// 		for (i = 0; i < 3; i++)

int main() {
	unsigned int i;
	
	printf("++i syntax\n");
	for (i = 0; i < 3; ++i) {
		printf("i: %d\n",i);
	}
	
	printf("i++ syntax\n");
	for (i = 0; i < 3; i++) {
		printf("i: %d\n",i);
	}
}
