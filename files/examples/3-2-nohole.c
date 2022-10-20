// this is a program generate hole file
#include<include/errors.h>
#include<unistd.h>
#include<string.h>
#include<malloc.h>
#include<fcntl.h>

#define SEEK_OFFSET 30010

char buf1[] = "ABCDEFG123";
char buf2[] = "abcdefg123";

char no_hole[SEEK_OFFSET] = {1};

int main(void)
{
	int fd;

	size_t sbuf1 = sizeof(buf1);
	size_t sbuf2 = sizeof(buf2);

	printf("buf1 size %lu\n:", sbuf1);

	char *ml_p = malloc(SEEK_OFFSET);
	memset(ml_p, 1, SEEK_OFFSET);

	if ((fd = creat("file.nohole", 0644)) < 0)
		err_quit("create error\n");
	
	if (write(fd, buf1, sbuf1) != sbuf1)
		err_quit("write failed\n");

	// if (write(fd, no_hole, SEEK_OFFSET) != SEEK_OFFSET)
	// 	err_quit("write failed\n");

	if (write(fd, ml_p, SEEK_OFFSET) != SEEK_OFFSET)
		err_quit("write failed\n");


	if (write(fd, buf2, sbuf2) != sbuf2)
		err_quit("write failed\n");
	
	exit(0);
}