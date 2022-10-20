// this is a program generate hole file
#include<include/errors.h>
#include<unistd.h>
#include<fcntl.h>

#define SEEK_OFFSET 30010

char buf1[] = "ABCDEFG123";
char buf2[] = "abcdefg123";

int main(void)
{
	int fd;

	size_t sbuf1 = sizeof(buf1);
	size_t sbuf2 = sizeof(buf2);

	printf("buf1 size %lu\n:", sbuf1);

	if ((fd = creat("file.hole", 0644)) < 0)
		err_quit("create error\n");
	
	if (write(fd, buf1, sbuf1) != sbuf1)
		err_quit("write failed\n");

	if (lseek(fd, SEEK_OFFSET, SEEK_CUR) == -1)
		err_quit("lseek error\n");

	if (write(fd, buf2, sbuf2) != sbuf2)
		err_quit("write failed\n");
	
	exit(0);
}