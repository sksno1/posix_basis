#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int err;

	char *str = "Standard Stream : Standard Out \n";

	printf("%s", str);
	
	err = close(STDOUT_FILENO);
	
	printf("ERR : %d \n", err);

	write(STDOUT_FILENO, str, strlen(str));
	printf("STDOUT_FILENO : %d \n", STDOUT_FILENO);
	
	return 0;
}
