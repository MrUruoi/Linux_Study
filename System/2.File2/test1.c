#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int write_test(void) {
	int fd;
	
	fd = open("test", O_WRONLY | O_CREAT, 0644);	
	// fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);	
	if(fd == -1) {
		return -1;	
	}
	dprintf(fd, "hoge\n");
	close(fd);

	return 0;
}

int append_test(void) {
	int fd;
	fd = open("test", O_WRONLY | O_APPEND);	

	dprintf(fd, "append...\n");
	close(fd);
	return 0;
}

int main(void) {
	write_test();
	append_test();
}
