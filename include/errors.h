#include<stdio.h>
#include<stdlib.h>

void err_quit(char *fmt)
{
	fputs(fmt, stderr);
	exit(-1);
}

