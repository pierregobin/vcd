/*
    This file is part of vcd.

    vcd is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    vcd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with vcd.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <glib.h>
#include <glib/gstdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <vcd.h>
#include <errno.h>
static GSList  *_gsl_signals;

static char * _filename;
static FILE  * _filehandle;

typedef struct s_signals {
	char *name;
	int length;
	int nickname;
	long int time;
	char *value;
} s_signal;


int vcd_init(void)
{
	_gsl_signals = NULL;
	return (0);
}

int vcd_open(char *filename)
{
	_filename = filename;
	if ((_filehandle=g_fopen(_filename,"w+")) == NULL) {
		printf("%s %i - NULL\n",__FUNCTION__,__LINE__);
		return EMFILE;
		
	}
	return 0;
}
int vcd_date(void)
{
	GTimeVal current_time;
	gchar * c_time_string;
	if (_filehandle == NULL) {
		printf("_filehandle is NULL\n");
		exit(0);
	}
	g_fprintf(_filehandle,"$date\n");
	g_get_current_time(&current_time);
	c_time_string = g_time_val_to_iso8601(&current_time);
	g_fprintf(_filehandle,"\t%s\n",c_time_string);
	g_fprintf(_filehandle,"$end\n");
	return(0);
}
int vcd_version(char *version)
{
	g_fprintf(_filehandle,"$version\n");
	g_fprintf(_filehandle,"\t%s\n",version);
	g_fprintf(_filehandle,"$end\n");
}
int vcd_comment(char *comment)
{
	g_fprintf(_filehandle,"$comment\n");
	g_fprintf(_filehandle,"\t%s\n",comment);
	g_fprintf(_filehandle,"$end\n");
}
int vcd_timescale(char *timescale)
{
	g_fprintf(_filehandle,"$timescale %s $end\n",timescale);
}
int vcd_scope(char *module)
{
	g_fprintf(_filehandle,"$scope module %s $end\n",module);
}
int vcd_upscope(void)
{
	g_fprintf(_filehandle,"$upscope $end\n");
}
int vcd_wire(char *name, int size)
{
}

int vcd_close(void)
{
	return (fclose(_filehandle));
}
int vcd_dump(char *name, char *value)
{
}
int vcd_time(long int time)
{
}


