#include <stdio.h>
#include <string.h>

#define MAXLEN	15	/* max message length */

main()
{
	int		i;
	int		j;
	int		col;
	char	mesg[] = "ABC";
	int		lidx;
	static	int	letters[27][5] = {
		{0x7F,0x7F,0x7F,0x7F,0x7F},	// space
		{0x03,0x75,0x76,0x75,0x03}, //A
		{0x00,0x36,0x36,0x36,0x49}, //B
		{0x41,0x3E,0x3E,0x3E,0x5D}, //C
		{0x00,0x3E,0x3E,0x3E,0x41}, //D
		{0x00,0x36,0x36,0x3E,0x3E}, //E
		{0x00,0x76,0x76,0x7E,0x7E}, //F
		{0x41,0x3E,0x2E,0x2E,0x4D}, //G
		{0x00,0x77,0x77,0x77,0x00}, //H
		{0x3E,0x3E,0x00,0x3E,0x3E}, //I
		{0x5E,0x3E,0x00,0x7E,0x7E}, //J
		{0x00,0x77,0x6B,0x5D,0x3E}, //K
		{0x00,0x3F,0x3F,0x3F,0x3F}, //L
		{0x00,0x7D,0x7B,0x7D,0x00}, //M
		{0x00,0x7B,0x77,0x6F,0x00}, //N
		{0x41,0x3E,0x3E,0x3E,0x41}, //O
		{0x00,0x76,0x76,0x76,0x79}, //P
		{0x41,0x3E,0x3E,0x5E,0x21}, //Q
		{0x00,0x76,0x66,0x56,0x39}, //R
		{0x59,0x36,0x36,0x36,0x4D}, //S
		{0x7E,0x7E,0x00,0x7E,0x7E}, //T
		{0x40,0x3F,0x3F,0x3F,0x40}, //U
		{0x60,0x5F,0x3F,0x5F,0x60}, //V
		{0x00,0x5F,0x6F,0x5F,0x00}, //W
		{0x1C,0x6B,0x77,0x6B,0x1C}, //X
		{0x7E,0x7D,0x03,0x7D,0x7E}, //Y
		{0x1E,0x2E,0x36,0x3A,0x3C}	//Z
	};

	//strcpy(mesg,"AB");
	
	for (i = 0; (i < MAXLEN && mesg[i] != 0); ++i) {
		lidx = mesg[i];
		if (lidx == 32)
			lidx = 0;
		else
			lidx = lidx - 64;
		
		printf("%d : ",lidx);
		col = 1;
		for (j = 0; j < 5; ++j) {
			printf("%d;",col);
			printf("%x ",letters[lidx][j]);
			col = col * 2;
		}
		printf("\n");
	}
	
}
