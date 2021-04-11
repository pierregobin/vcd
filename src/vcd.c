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

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "vcd.h"
#include <errno.h>
#include <string.h>
#include <time.h>
#define MAX_SIGNAL 20
static long unsigned int _vcd_time;
static char * _filename;
static FILE  * _filehandle;
static char _print_vcd_time;

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

char* get_time_string()
{
    struct tm *tm;
    time_t t;
    char *str_time = (char *) malloc(100*sizeof(char));
    t = time(NULL);
    tm = localtime(&t);
    strftime(str_time, sizeof(str_time), "%H:%M:%S", tm);
    return str_time;
}

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
	if ((_filehandle=fopen(_filename,"w+")) == NULL) {
		printf("%s %i - NULL\n",__FUNCTION__,__LINE__);
		return EMFILE;
		
	}
	return 0;
}
int vcd_date(void)
{
	char * c_time_string;
	if (_filehandle == NULL) {
		printf("_filehandle is NULL\n");
		exit(0);
	}
	fprintf(_filehandle,"$date\n");
	c_time_string = get_time_string();
	fprintf(_filehandle,"\t%s\n",c_time_string);
	fprintf(_filehandle,"$end\n");
	return(0);
}
int vcd_version(char *version)
{
	fprintf(_filehandle,"$version\n");
	fprintf(_filehandle,"\t%s\n",version);
	fprintf(_filehandle,"$end\n");
}
int vcd_comment(char *comment)
{
	fprintf(_filehandle,"$comment\n");
	fprintf(_filehandle,"\t%s\n",comment);
	fprintf(_filehandle,"$end\n");
}
int vcd_timescale(char *timescale)
{
	fprintf(_filehandle,"$timescale %s $end\n",timescale);
}
int vcd_scope(char *module)
{
	fprintf(_filehandle,"$scope module %s $end\n",module);
}
int vcd_enddef(void)
{
	fprintf(_filehandle,"$enddefinitions $end\n");
}
int vcd_upscope(void)
{
	fprintf(_filehandle,"$upscope $end\n");
}
int vcd_wire(char *name, int size)
{
	int i;
	if (_signal_number >= MAX_SIGNAL) return 1;
	_gsl_signals[_signal_number].name = name;
	_gsl_signals[_signal_number].size = size;
	_gsl_signals[_signal_number].nickname = nickname;
	for (i=0;i<size;i++) _gsl_signals[_signal_number].value[i] = 'x';
	_gsl_signals[_signal_number].value[i]=0;
	fprintf(_filehandle,"$var wire %d %c %s $end\n",size,nickname,name);
	_signal_number++;
	nickname ++;
	return(0);
	
}

int vcd_close(void)
{
	return (fclose(_filehandle));
}

int vcd_dump_vars(void)
{
	int i;
	fprintf(_filehandle,"$dumpvars\n");
	for (i=0; i<_signal_number;i++) {
		if (_gsl_signals[i].size == 1) {
			fprintf(_filehandle,"%c%c\n",(int) _gsl_signals[i].value[0], _gsl_signals[i].nickname);
		} else {
			int j;
			fprintf(_filehandle,"b");
			/* for (j=_gsl_signals[i].size-1;j>=0;j--) { */
			for (j=0;j<_gsl_signals[i].size;j++) {
				fprintf(_filehandle,"%c",_gsl_signals[i].value[j]);
			}
			fprintf(_filehandle," %c\n",_gsl_signals[i].nickname);
		}
	}
	fprintf(_filehandle,"$end\n");
}
int vcd_dump(char *name, char *value)
{
	int i;
	for (i=0; i<_signal_number;i++) {
		if (strcmp(name,_gsl_signals[i].name) == 0) break;
	}
	if (strncmp(value,_gsl_signals[i].value,_gsl_signals[i].size) != 0) {
		if (_print_vcd_time) {
			fprintf(_filehandle,"#%ld\n",_vcd_time);
			_print_vcd_time = 0;
		}
		strncpy(_gsl_signals[i].value,value,_gsl_signals[i].size);
		if (_gsl_signals[i].size == 1) {
			fprintf(_filehandle,"%c%c\n",(int) _gsl_signals[i].value[0], _gsl_signals[i].nickname);
		} else {
			int j;
			fprintf(_filehandle,"b");
			for (j=0;j<_gsl_signals[i].size;j++) {
				fprintf(_filehandle,"%c",_gsl_signals[i].value[j]);
			}
			fprintf(_filehandle," %c\n",_gsl_signals[i].nickname);
		}
	}
	return(0);
}

int vcd_dump_from_int(char *name, int value)
{
	int i, size;
	char bin[128];
	char *binoff = bin;
	char hex[8];
	for (i=0; i<_signal_number;i++) {
		if (strcmp(name,_gsl_signals[i].name) == 0) break;
	}
	size = _gsl_signals[i].size;

	sprintf(hex,"%04x", value);
	vcd_hex2bin(hex, bin);

	binoff+=strlen(bin)-size; //moving the pointer to the place in the string we need move to the beginning 
	strcpy(bin, binoff);

	vcd_dump(name,bin);
}

int vcd_time(long unsigned int time)
{
	if (time < _vcd_time) return 1;
	_vcd_time = time;
	_print_vcd_time = 1;
	return 0;
}

int vcd_hex2bin(char *hex, char *bin)
{
	bin[0]=0;
	while(*hex)
    {
        switch(*hex)
        {
            case '0':
                strcat(bin, "0000");
                break;
            case '1':
                strcat(bin, "0001");
                break;
            case '2':
                strcat(bin, "0010");
                break;
            case '3':
                strcat(bin, "0011");
                break;
            case '4':
                strcat(bin, "0100");
                break;
            case '5':
                strcat(bin, "0101");
                break;
            case '6':
                strcat(bin, "0110");
                break;
            case '7':
                strcat(bin, "0111");
                break;
            case '8':
                strcat(bin, "1000");
                break;
            case '9':
                strcat(bin, "1001");
                break;
            case 'a':
            case 'A':
                strcat(bin, "1010");
                break;
            case 'b':
            case 'B':
                strcat(bin, "1011");
                break;
            case 'c':
            case 'C':
                strcat(bin, "1100");
                break;
            case 'd':
            case 'D':
                strcat(bin, "1101");
                break;
            case 'e':
            case 'E':
                strcat(bin, "1110");
                break;
            case 'f':
            case 'F':
                strcat(bin, "1111");
                break;
            default:
                printf("Invalid hexadecimal input.");
        }
		hex++;
    }
	return 0;
}
