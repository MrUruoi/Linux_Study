#include <stdio.h>
#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	int fd;
	int ops;

	if (argc < 2) {
		printf("usage: %s (ex|sh)\n", argv[0]);
		exit(-1);
	}

	if (!strcmp(argv[1], "sh")) ops = LOCK_SH;
	else if (!strcmp(argv[1], "ex")) ops = LOCK_EX;
	else printf("usage: %s (ex|sh)\n", argv[0]);

	fd = open("text.txt", O_RDWR | O_CREAT, 0644);
	if (fd < 0 ) {
		printf("open fail");
		return -1;
	}
	
	// if (flock(fd, ops) != 0) {
	// 	printf("flock fail\n");
	// 	return -1;
	// }
	if (flock(fd, ops | LOCK_NB) != 0) {
		printf("%d %s\n", errno, strerror(errno));
		return -1;
	}
	printf("lock...");
	getc(stdin);	// for test

	if (flock(fd, LOCK_UN)) {
		printf("LOCK_UN fail");
	}
	
	close(fd);

	return 0;
}

