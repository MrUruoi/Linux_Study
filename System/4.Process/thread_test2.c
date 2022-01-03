#include <stdio.h>
#include <pthread.h>

int shared = 0;
pthread_mutex_t mutex;

void *thread_func(void *arg) {
	unsigned int i;

	pthread_mutex_lock(&mutex);
	for (i=0; i<100000; i++) {
		shared++;
	}
	for (i=0; i<100000; i++) {
		shared--;
	}
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(void) {
	pthread_t threads[2];
	int ret;
	
	if (pthread_mutex_init(&mutex, NULL)) {
		printf("pthread_mutex_init fail\n");
		return -1;
	}

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

	printf("shared %d\n", shared);

	return 0;
}
