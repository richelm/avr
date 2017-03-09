#include <stdio.h>

int main() {
	unsigned int buffer[5] = {15,20,20,15,00};
	unsigned int i;
	unsigned int j;
	unsigned int n;
	
	i = 0;
	for (i = 0; i < 5; i++) {
		n = 1;
		for (j = 4; j < 255; j--) {
			printf("i: %d; n:%d; %d",buffer[i], n, (buffer[i] & n));
			if ((buffer[i] & n) > 0) 
				printf(" - 1\n");
			else
				printf(" - 0\n");
			n = n * 2;
		}
	}
		
	return 0;
}
