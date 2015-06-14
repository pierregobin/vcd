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
#define MAX_SIGNAL 20
static long unsigned int _vcd_time;
static char * _filename;
static FILE  * _filehandle;
static gboolean _print_vcd_time;

typedef struct s_signals {
	char *name; /* name of the signal */
	int size; /* size (number of bits) of the signal */
	int nickname; /* short name used in the dump file */
	long int time; /* last updated time */
	char value[128]; /* last value */
} s_signal;

static s_signal  _gsl_signals[MAX_SIGNAL];
static int _signal_number;
static int nickname;

int vcd_init(void)
{
	_signal_number = 0;
	_vcd_time = 0;
	nickname = 33;
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
	int i;
	if (_signal_number >= MAX_SIGNAL) return 1;
	_gsl_signals[_signal_number].name = name;
	_gsl_signals[_signal_number].size = size;
	_gsl_signals[_signal_number].nickname = nickname;
	nickname ++;
	for (i=0;i<size;i++) _gsl_signals[_signal_number].value[i] = "x";
	_signal_number++;
	g_fprintf(_filehandle,"$var wire %d %c %s $end\n",size,nickname,name);
	return(0);
	
}

int vcd_close(void)
{
	return (fclose(_filehandle));
}

int vcd_dump_vars(void)
{
	int i;
	g_fprintf(_filehandle,"$dumpvars\n");
	for (i=0; i<_signal_number;i++) {
		printf("[%d] %s\n",i,_gsl_signals[i].name);
		if (_gsl_signals[i].size == 1) {
			g_fprintf(_filehandle,"%s%s\n",_gsl_signals[i].nickname,_gsl_signals[i].value);
		} else {
			g_fprintf(_filehandle,"b%s%s #\n",_gsl_signals[i].nickname,_gsl_signals[i].value);
		}
	}
	g_fprintf(_filehandle,"$end\n");
}
int vcd_dump(char *name, char *value)
{
	int i;
	for (i=0; i<_signal_number;i++) {
		if (strcmp(name,_gsl_signals[i].name) == 0) break;
	}
	if (strcmp(value,_gsl_signals[i].value) != 0) {
		if (_print_vcd_time) {
			g_fprintf(_filehandle,"#%ld\n",_vcd_time);
			_print_vcd_time = FALSE;
		}
		strncpy(_gsl_signals[i].value,value,_gsl_signals[i].size);
		if (_gsl_signals[i].size == 1) {
			g_fprintf(_filehandle,"%s%s\n",_gsl_signals[i].nickname,_gsl_signals[i].value);
		} else {
			g_fprintf(_filehandle,"b%s%s #\n",_gsl_signals[i].nickname,_gsl_signals[i].value);
		}
	}
	return(0);
}
int vcd_time(long unsigned int time)
{
	if (time < _vcd_time) return 1;
	_vcd_time = time;
	_print_vcd_time = TRUE;
	return 0;
}


