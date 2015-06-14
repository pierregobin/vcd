#include <vcd.h>
#include <stdlib.h>
#include <stdio.h>
int success=0;
int failure=0;
GError **error;
int main(int argc, char *argv)
{
	int h;
	if (vcd_open("toto") == 0) {
		success++;
		printf("open succeeded\n");
	} else {
		printf("fail to open <toto>\n");
		failure++;
	}
	vcd_date();
	if (vcd_close(error) == TRUE) {
		success++;
		printf("close succeeded\n");
	} else {
		printf("fail to close <toto>\n");
		failure++;
	}
	if (failure ) { exit (1); } else { exit(0); };
	
	
}

