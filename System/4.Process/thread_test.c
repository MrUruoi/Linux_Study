#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
	printf(" pthread id %p\n" ,pthread_self());
	return NULL;
}

int main(void) {
	pthread_t threads[2];
	int ret;

	ret = pthread_create(&threads[0], NULL, thread_func, NULL);
	if (ret) {
		printf("pthread_create fail...\n");
		return -1;
	}

	ret = pthread_create(&threads[1], NULL, thread_func, NULL);
	if (ret) {
		printf("pthread_create fail...\n");
		return -1;
	}

	if (pthread_join(threads[0], NULL)) {
		printf("pthread_join %p fail\n", threads[0]);
	}
	if (pthread_join(threads[1], NULL)) {
		printf("pthread_join %p fail\n", threads[1]);
	}

	return 0;
}
