#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	struct stat statbuf;

	if(argc < 2) {
		printf("usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(stat(argv[1], &statbuf)) {
		printf("fail\n");
	 	exit(EXIT_FAILURE);
	}	

	printf("%lld\n", statbuf.st_size);
	if(S_ISDIR(statbuf.st_mode)) printf("DIR\n");
	if(S_ISREG(statbuf.st_mode)) printf("REG\n");

	return 0;
}
