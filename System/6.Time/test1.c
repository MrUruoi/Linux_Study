#include <stdio.h>
#include <time.h>

int main(void) {
	time_t now;
	struct tm * current_tm;	
	
	now = time(NULL);
	printf("%ld\n", now);

	current_tm = localtime(&now);
	if (!current_tm) {
		printf("localtime fail...\n");
		return -1;
	}
	printf("%d %d %d %d %d %d\n", 
		current_tm->tm_year + 1900,
		current_tm->tm_mon + 1,
		current_tm->tm_mday,
		current_tm->tm_hour,
		current_tm->tm_min,
		current_tm->tm_sec);
		
	return 0;
}
