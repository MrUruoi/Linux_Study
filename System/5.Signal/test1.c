#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void test_handler(int signum) {
	printf("%d handler...\n", signum);
}
int main(void) {
	sigset_t set;
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_SETMASK, &set, NULL);

	signal(SIGTERM, test_handler); 
	printf("while...\n");
	while(1) {
		sleep(2);
	}
	return 0;
}
