
#include <stdio.h>  
#include <linux/rtc.h>  
#include <sys/ioctl.h>  
#include <sys/time.h>  
#include <sys/types.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <errno.h> 
#include <string.h>

#define DEV_RTC "/dev/rtc"

int main(int argc, char* argv[])
{
	int fd;
	int err;
	int cnt = 0;
	unsigned long rtcData;  
	
	fd = open(DEV_RTC, O_RDONLY);  

	if (fd == -1) {  
        	printf("ERROR (%d) : %s \n", errno, strerror(errno));  
        	exit(errno);  
    	}  
	
	err = ioctl(fd, RTC_UIE_ON, 0);
    	
	if (err == -1) {
        	printf("ERROR (%d) : %s \n", errno, strerror(errno));  
        	exit(errno);
    	}
	
	while(1)
	{

		read(fd, &rtcData, sizeof(unsigned long));
		printf("TIMER %d \n", cnt++);
	}

	return 0;
}
