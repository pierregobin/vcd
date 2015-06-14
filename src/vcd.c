
#include <glib.h>

typedef struct s_vcd_handlers
{
	char *filename;
	
} s_vcd_handler;

static s_vcd_handler _vcd_handler[];

int vcd_init(void)
{
}

int vcd_open(char *filename)
{
}
int vcd_date(int vcd_handler, char *date_field)
{
}
int vcd_version(int vcd_handler, char *version)
{
}
int vcd_comment(int vcd_handler, char *comment)
{
}
int vcd_timescale(int vcd_handler, char *timescale)
{
}
int vcd_scope(int vcd_handler, char *module)
{
}
int vcd_upscope(int vcd_handler)
{
}
int vcd_wire(int vcd_handler, int size, char *name)
{
}
int vcd_close(int vcd_handler)
{
}
int vcd_dump(int vcd_handler, char *name, char *value)
{
}
int vcd_time(int vcd_handler, int time)
{
}


