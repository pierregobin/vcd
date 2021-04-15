#include "vcd.h"
#include <stdlib.h>
#include <stdio.h>
int success=0;
int failure=0;
long int _time = 0;
void increment(void)
{
	int i;
	int seed;
	seed = 1;
	for (i=1;i<8;i++) {
		vcd_time(30UL + 100*i);
		vcd_dump_from_int("data",seed);
		seed = (seed << 1);
	}
}
void square(void)
{
	int i;
	for (i=0;i<100;i++) {
		vcd_dump("rx","0");
		vcd_time(3000UL + 100*i);
		vcd_dump("rx","1");
		vcd_time(3050UL + 100*i);
		vcd_dump_from_int("data",i);
	}
}
int main(int argc, char *argv)
{
	int h;
	vcd_init();
	if (vcd_open("dumpvarint.vcd") == 0) {
		success++;
		printf("open succeeded\n");
	} else {
		printf("fail to open <toto>\n");
		failure++;
	}
	vcd_timescale("1ns");
	vcd_scope("logic");
	vcd_wire("data",8);
	vcd_wire("data_str",8);
	vcd_wire("data_valid",1);
	vcd_wire("en",1);
	vcd_wire("rx",1);
	vcd_wire("tx",1);
	vcd_wire("empty",1);
	vcd_wire("underrun",1);
	vcd_upscope();
	vcd_enddef();
	vcd_dump_vars();
	vcd_time(10UL);
	vcd_dump_from_int("rx",1);
	vcd_dump("data_str","00000000");
	vcd_time(20UL);
	vcd_dump_from_int("data",0);
	vcd_dump("data_str","00000001");
	vcd_dump_from_int("rx",0);
	vcd_dump_from_int("tx",0);
	vcd_time(30UL);
	vcd_dump_from_int("tx",1);
	vcd_dump_from_int("data",44);
	vcd_dump("data_str","10000000");
	increment();
	square();

	if (vcd_close() == 0) {
		success++;
		printf("close succeeded\n");
	} else {
		printf("fail to close <toto>\n");
		failure++;
	}
	if (failure ) { exit (1); } else { exit(0); };
	
	
}

