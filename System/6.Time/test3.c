#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

void print_cur_time(void) {
	time_t now;
	struct tm *cur_tm;

	now = time(NULL);
	printf("%ld\n", now);

	cur_tm = localtime(&now);
	if (!cur_tm) {
		printf("localtime fail...\n");
		return;
	}
	printf("%d %d %d %d %d %d\n", 
		cur_tm->tm_year + 1900,
		cur_tm->tm_mon + 1,
		cur_tm->tm_mday,
		cur_tm->tm_hour,
		cur_tm->tm_min,
		cur_tm->tm_sec);
}

void sigalarm_handler(int signum) {
	printf("sigalarm_handler...\n");
	print_cur_time();
}

int main(void) {
	struct itimerval ival;	

	signal(SIGALRM, sigalarm_handler);
	print_cur_time();

	ival.it_value.tv_sec = 3;
	ival.it_value.tv_usec = 0;
	ival.it_interval.tv_sec = 1;
	ival.it_interval.tv_usec = 0;
	if (setitimer(ITIMER_REAL, &ival, NULL) != 0) {
		printf("setitimer fail...\n");
		return -1;
	}

	while(1) {
		sleep(2);
	}

	return 0;
}
