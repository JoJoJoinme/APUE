// open with O_APPEND flag only, read from anywhere is ok, but write would be failed with errno:9, bad file descriptor
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<malloc.h>
#include<include/errors.h>

int write_content(int fd)
{
	char *s = "abcdefghi";
	#define WR_BUF 64
	int val = 0;
	val = write(fd, s, WR_BUF);
	if (val == -1)
	{
		err_sys("write failed with errno\n");
	}
}

int print_content(int fd)
{
	#define BUFSIZE 128
	char buf[BUFSIZE];
	int val = 0, offset = 0;
	// 从头开始读
	offset = lseek(fd, 0, SEEK_SET);
	if (offset == -1)
	{
		err_sys("offset SEEK_SET is wrong with errorno: %d\n", errno);
	}



	while((val = read(fd, buf, BUFSIZE)) != 0)
	{
		printf("%s",buf);
		memset(buf, 0, BUFSIZE);
		
	}
	printf("\n");
}


int main()
{
	const char *path = "./3-6.input";

	int fd = open(path, O_APPEND);
	if (fd == -1)
	{
		err_sys("open path: %s failed with errorno:%d\n", path, errno);
	}

	int offset = 0;
	offset = lseek(fd, 0, SEEK_CUR);
	if (offset == -1)
	{
		err_sys("offset is wrong with errorno: %d\n", errno);
	}

	printf("the end of file offset is:%d\n", offset);

	printf("original content\n");
	print_content(fd);
	
	printf("leek at the front\n");
	offset = lseek(fd, 0, SEEK_SET);
	if (offset == -1)
	{
		err_sys("offset SEEK_SET is wrong with errorno: %d\n", errno);
	}

	write_content(fd);
	print_content(fd);

	printf("leek at the end\n");
	offset = lseek(fd, 0, SEEK_END);
	if (offset == -1)
	{
		err_sys("offset SEEK_END is wrong with errorno: %d\n", errno);
	}
	printf("current offset is:%d\n", offset);
	write_content(fd);
	print_content(fd);
}