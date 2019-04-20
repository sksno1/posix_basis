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
	char *writeWords = "READ ONLY \n";

	fd = open("test.txt", O_CREAT|O_RDWR, S_IRUSR);

	if(fd < 0)
	{
		printf("File Create Error \n");
		return -1;
	}
	
	printf("File Descriptor : %d \n", fd);

	len = write(fd, writeWords, strlen(writeWords));
	
	printf("Write Len : %d \n", len);
	
	if(len = -1)
	{
		printf("ERROR (%d) : %s \n",errno,  strerror(errno));
	}
	close(fd);

	return 0;
}
