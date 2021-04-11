#ifndef VCD_H_
#define VCD_H_

/* always return status */
int vcd_init(void);
int vcd_open(char *filename);
int vcd_date(void);
int vcd_version(char *version);
int vcd_comment(char *comment);
int vcd_timescale(char *timescale);
int vcd_scope(char *module);
int vcd_enddef(void);
int vcd_upscope(void);
int vcd_wire(char *name,int size);
int vcd_close();
int vcd_dump(char *name, char *value);
int vcd_dump_from_int(char *name, int value);
int vcd_time(long unsigned int time);

#endif /* VCD_H_ */

