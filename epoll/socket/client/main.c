#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT	15412

int main(int argc, char *argv[])
{
	int fd;
	int len;
	struct  sockaddr_in addr;
	char *msg = "UDP Client Message\n";

	fd = socket(PF_INET, SOCK_DGRAM, 0);
	
	if(fd < 0)
        {
                printf("UDP Socket Error \n");
                return -1;
        }


	memset(&addr, 0x00, sizeof(struct sockaddr_in));
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        addr.sin_port = htons(PORT);
	
	len = sendto(fd, msg, strlen(msg), 0,(struct sockaddr *)&addr, sizeof(addr));

	printf("sendto len : %d \n", len);
	
	return 0;

}
