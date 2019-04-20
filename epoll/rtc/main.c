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
#define DEV_RTC		"/dev/rtc"
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
	int rtcFd;
	int err;
	int cnt = 0;
	char stdInBuf[BUF_SIZE];


	int epollFd = epoll_create(EPOLL_SIZE); 
	struct epoll_event* events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE); 
	
	add_epoll(epollFd, STDIN_FILENO);
	
	rtcFd = open(DEV_RTC, O_RDONLY);

	if(rtcFd == -1)
	{
		printf("RTC FD ERROR (%d) : %s \n", errno, strerror(errno));
		exit(errno);
	}
	err = ioctl(rtcFd, RTC_UIE_ON, 0);

	if(err < 0)
	{
		printf("RTC IOCTL ERROR (%d) : %s \n", errno, strerror(errno));
		exit(errno);
	}
	
	add_epoll(epollFd, rtcFd);

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
			}else if(events[i].data.fd == rtcFd)
			{
				unsigned long rtcData;
				read(rtcFd, &rtcData, sizeof(unsigned long));
				printf("TIMER : %d \n", cnt++);		
			}

		}
	} 

	return 0;
}
