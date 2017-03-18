#include <stdio.h>


int main() {
	unsigned int i;
	unsigned int j;
	unsigned int s;
	unsigned int bitmap[3] = {0x15,0x0A,0x1F};
	
	printf("mod test\n");
	for (i = 7; i > 0; i--) {
		printf("%d mod 2: %d\n",i,(i % 2));
	}
	
	j = 0;
	for (i = 20; i > 0; i--) {
		s = bitmap[j];
		printf("j: %d s: %x\n",j,s);
		j++;
		if (j > 2) {j = 0;}
	}

}
