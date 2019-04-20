#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

	char *str = "Standard Stream : Standard Error \n";

	printf("%s", str);
	write(STDERR_FILENO, str, strlen(str));
	printf("STDERR_FILENO : %d \n", STDERR_FILENO);

	return 0;
}
