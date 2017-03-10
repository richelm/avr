#include <stdio.h>

int main() {
	const unsigned char buffer[7] = {00,00,15,20,20,15,00}; // A
	unsigned int r;
	unsigned int bufidx;
	

	for (bufidx = 0; bufidx < 7; ++bufidx) {
		printf("buffer[%d]: %d ",bufidx, buffer[bufidx]);
		for (r = 0; r < 5; ++r) {
			if ((buffer[bufidx] & (1 << r)) > 0) {
				printf("%d ", (1 << r+1));
			}
			else {
				printf("0");
			}
		}
		printf("\n");
	}
		
	return 0;
}
