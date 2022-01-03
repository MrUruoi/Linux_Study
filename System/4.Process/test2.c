#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void test_func(void) {
	printf("test_func %d\n", getpid());
}
int main(void) {
	pid_t pid;
	int exit_status;

	printf("origin - ppid: %d pid: %d\n", getppid(), getpid());

	pid = fork();
	if (pid == 0 ) {
		// child
		printf("child - pid: %d\n", getpid());
		if (execl("/bin/ls", "ls", "-al", NULL) == -1) {
			printf("execl fail...\n");
			return -1;
		}
	} else if (pid > 0) {
		// parent
		printf("parent - pid: %d\n", getpid());
	}

	test_func();

	pid = wait(&exit_status);
	if (WIFEXITED(exit_status)) {
		printf("child %d returns %d\n", pid, WEXITSTATUS(exit_status));
	} else {
		printf("child %d ??", pid);
	}

	return 0;
}
