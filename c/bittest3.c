#include <stdio.h>

int main() {
	unsigned char buffer[5] = {15,20,20,15,00};
	unsigned int i;
	unsigned int j;
	
	
	i = 5;
	j = 2;
	printf("i: %d; j:%d; %d\n",i, j, (i & (1 <<j)));
	
	j = 1;
	printf("i: %d; j:%d; %d\n",i, j, (i & (1 <<j)));

	j = 0;
	printf("i: %d; j:%d; %d\n",i, j, (i & (1 <<j)));
		
	return 0;
}
