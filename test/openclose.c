#include <vcd.h>
#include <stdlib.h>
#include <stdio.h>
int success=0;
int failure=0;
GError **error;
int main(int argc, char *argv)
{
	int h;
	if (vcd_open("toto",&h) == 0) {
		success++;
		if (h == 0)  {success++;} else {
		   printf("bad handler (0 expected: %d)\n",h);
                   failure++;};
	} else {
		printf("fail to open <toto>\n");
		failure++;
	}
	if (vcd_open("titi",&h) == 0) {
		success++;
		if (h == 1)  {success++;} else {
		   printf("bad handler (1 expected: %d)\n",h);
		failure++;
        	}
	} else {
		printf("fail to open <titi>\n");
		failure++;
	}
	if (vcd_close(0, error) == 0) {
		success++;
	} else {
		printf("fail to close 0\n");
		failure++;
	}
	if (vcd_close(1, error) == 0) {
		success++;
	} else {
		printf("fail to close 1\n");
		failure++;
	}
	if (failure ) { exit (1); } else { exit(0); };
	
	
}

