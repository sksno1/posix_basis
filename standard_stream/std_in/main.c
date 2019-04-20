#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>

#define BUF_SIZE 128

int main(int argc, char *argv[])
{

	int len;
	char buf[BUF_SIZE];
	
	printf("scanf() input \n");
	memset(buf, 0x00, BUF_SIZE);
	scanf("%s", buf);
	printf("scanf() : %s \n", buf);

	printf("STDIN input \n");
	memset(buf, 0x00, BUF_SIZE);
	len = read(STDIN_FILENO, buf, BUF_SIZE);
	
	printf("LEN :%d STD_IN : %s \n", len, buf);

	printf("STDIN_FILENO : %d \n", STDIN_FILENO);
	
	return 0;
}
