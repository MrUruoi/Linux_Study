#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/errno.h>

int main(void) {
	int ret;
	char buf[128];
	int fd;
	int flag;

	// Blocking
	memset(buf, 0, sizeof(buf));
	ret = read(STDIN_FILENO, buf, sizeof(buf));
	printf("%s %d\n", buf, ret);

	flag = fcntl(fd, F_GETFL);
	if (flag == -1) {
		printf("F_GETFL fail...\n");
		return -1;
	}

	ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
	if (flag == -1) {
		printf("F_SETFL fail...\n");
		return -1;
	}

	// Non-Blocking
	memset(buf, 0, sizeof(buf));
	ret = read(STDIN_FILENO, buf, sizeof(buf));
	printf("%s %d\n", buf, ret);
	if (ret == -1) {
		printf("%d %s\n", errno, strerror(errno));
	}

	return 0;
}
