#include<stdarg.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define MAXLINE 4096

static void err_doit(int, int, const char *, va_list);

void err_quit(const char *fmt, ...)
{
	fputs(fmt, stderr);
	exit(-1);
}


void err_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);

}


static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char buf[MAXLINE];

	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}