#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[])
{
	int fd;
	int len;
	char readBuf[BUFFER_SIZE];

	fd = open("test.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

	if(fd < 0)
	{
		printf("File Create Error \n");
		return -1;
	}
	
	printf("File Descriptor : %d \n", fd);

	memset(readBuf, 0x00, BUFFER_SIZE);

	len = read(fd, readBuf, BUFFER_SIZE);
	
	printf("Write Len : %d \n", len);
	
	if(len = -1)
	{
		printf("ERROR (%d) : %s \n",errno,  strerror(errno));
	}

	printf(" %s \n", readBuf);

	close(fd);

	return 0;
}
