#include <stdio.h>

int main(int argc, char** argv)
{
	int i = 0;
	while(i++ < 1000000000);
	
	printf("%s\n", argv[1]);

	return 0;
}