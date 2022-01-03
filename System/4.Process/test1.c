#include <stdio.h>
#include <unistd.h>

void test_func(void) {
	printf("test_func %d\n", getpid());
}
int main(void) {
	pid_t pid;

	printf("origin - ppid: %d pid: %d\n", getppid(), getpid());

	pid = fork();
	if (pid == 0 ) {
		// child
		printf("child - pid: %d\n", getpid());
	} else if (pid > 0) {
		// parent
		printf("parent - pid: %d\n", getpid());
	}

	test_func();

	return 0;
}
