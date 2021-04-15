#include "vcd.h"
#include <stdlib.h>
#include <stdio.h>
int success=0;
int failure=0;
int main(int argc, char *argv)
{
	int h;
	vcd_init();
	if (vcd_open("var.vcd") == 0) {
		success++;
		printf("open succeeded\n");
	} else {
		printf("fail to open <toto>\n");
		failure++;
	}
	vcd_timescale("1ps");
	vcd_scope("logic");
	vcd_wire("data",8);
	vcd_wire("data_valid",1);
	vcd_wire("en",1);
	vcd_wire("rx",1);
	vcd_wire("tx",1);
	vcd_wire("empty",1);
	vcd_wire("underrun",1);
	vcd_upscope();
	vcd_enddef();
	if (vcd_close() == 0) {
		success++;
		printf("close succeeded\n");
	} else {
		printf("fail to close <toto>\n");
		failure++;
	}
	if (failure ) { exit (1); } else { exit(0); };
	
	
}

