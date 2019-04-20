#include <stdio.h>  
#include <linux/rtc.h>  
#include <sys/ioctl.h>  
#include <sys/time.h>  
#include <sys/types.h>  
#include <sys/epoll.h>
#include <fcntl.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>

#define EPOLL_SIZE	16
#define BUF_SIZE	128

int add_epoll(int epollFd, int fd)
{

	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = fd;

	printf("FD : %d \n", fd);	
	epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event);
	
	return 0;
}


int main(int argc, char *argv[])
{
	char stdInBuf[BUF_SIZE];


	int epollFd = epoll_create(EPOLL_SIZE); 
	struct epoll_event* events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE); 
	
	add_epoll(epollFd, STDIN_FILENO);
	
	printf("start \n");
	while(1) 
	{ 
		int i;
		int event_count = epoll_wait(epollFd, events, EPOLL_SIZE, -1); 
		if( event_count == -1 ) 
		{
			printf("EVENT COUNT ERROR \n");
			  printf("ERROR (%d) : %s \n", errno, strerror(errno));

			break; 
		}

		for( i = 0 ; i < event_count; ++i ) 
		{ 
			if(events[i].data.fd == STDIN_FILENO)
			{
				printf("EVENT FD : %d \n", events[i].data.fd);
				memset(stdInBuf, 0x00, BUF_SIZE);
				read(STDIN_FILENO, stdInBuf, BUF_SIZE);
				printf("STDIN : %s \n", stdInBuf);
			}

		}
	} 

	return 0;
}
