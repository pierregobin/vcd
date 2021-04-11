# Value Change Dump
This is a small library for genrating VCD files that is under GNU General Public License.

Working with the library is simple.
```c
vcd_init();
if (vcd_open("var.vcd")) {
   printf("open failed\n");
   return 0;
}
vcd_timescale("1ps");
vcd_scope("logic");
vcd_wire("reset",1);
vcd_wire("clk",1);
vcd_wire("data",8);
vcd_wire("rx",1);
vcd_wire("tx",1);
vcd_upscope();
vcd_enddef();

for (int i=0;i<100;i++) {
   vcd_dump("rx","0");
   vcd_time(30UL + 100*i);
   vcd_dump("rx","1");
   vcd_time(30UL + 100*i);
}

if (vcd_close()) {
   printf("close failed\n");
}
```
