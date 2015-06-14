#include <vcd.h>
#include <stdlib.h>
#include <stdio.h>
int success=0;
int failure=0;
int main(int argc, char *argv)
{
	vcd_init();
	if (vcd_open("toto") == 0) {
		success++;
		printf("succeed to open <toto>\n");
	} else {
		printf("fail to open <toto>\n");
		failure++;
	}
	if (vcd_close() == 0) {
		printf("succeed to close <toto>\n");
		success++;
	} else {
		printf("fail to close <toto>\n");
		failure++;
	}
	if (vcd_open("titi") == 0) {
		printf("succeed to open <titi>\n");
		success++;
	} else {
		printf("fail to open <titi>\n");
		failure++;
	}
	if (vcd_close() == 0) {
		printf("succeed to close <titi>\n");
		success++;
	} else {
		failure++;
		printf("fail to close <titi>\n");
	}
	printf("success = %d\nfailure = %d\n",success,failure);
	if (failure ) { exit (1); } else { exit(0); };
	
	
}

