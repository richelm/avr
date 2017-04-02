#define MAXLEN	12

#include <stdio.h>


int main() {
	unsigned int i;
	unsigned int j;
	unsigned int s;
	unsigned int bitmap[MAXLEN] = {0x15,0x0A,0x1F,0x0F,0x06};
	
	printf("mod test\n");
	j = 0;
	for (i = 0; i < 20; i++) {
		printf("%d \n",j);
		j = (j+1) % MAXLEN;
	}
}
