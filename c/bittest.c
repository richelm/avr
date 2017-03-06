#include <stdio.h>

int main() {
	unsigned int i;
	unsigned int j;
	unsigned int A;
	unsigned int B;
	unsigned int C;
	
	A = 2;
	B = 3;
	C = 4;
	
	j = 0x3F;
	for (i = 7; i > 0; i--) {
		j &= ~((1 << A) | (1 << B) | (1 << C));
		j |= (i <<2);
		printf("%d : %d : %x\n",i,j,j);
	}
	
	return 0;
}
