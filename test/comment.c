#include "vcd.h"
#include <stdlib.h>
#include <stdio.h>
int success=0;
int failure=0;
int main(int argc, char *argv[])
{
	int h;
	vcd_init();
	if (vcd_open("comment.vcd") == 0) {
		success++;
		printf("open succeeded\n");
	} else {
		printf("fail to open <toto>\n");
		failure++;
	}
	vcd_comment("hello");
	if (vcd_close() == 0) {
		success++;
		printf("close succeeded\n");
	} else {
		printf("fail to close <toto>\n");
		failure++;
	}
	if (failure ) { exit (1); } else { exit(0); };
	
	
}

