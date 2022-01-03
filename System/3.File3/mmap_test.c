#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

struct person {
	char name[10];
	int age;
};

int write_test(struct person *p) {
	int fd;
	ssize_t ret;

	fd = open("test.txt",  O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1) {
		printf("open fail\n");
		return -1;
	}

	ret = write(fd, p, sizeof(struct person));
	if (ret == -1) {
		printf("write fail\n");
		close(fd);
	} else if (ret != sizeof(struct person)) {
		printf("write fail2\n");
		close(fd);
	}

	close(fd);
	return 0;
}

int read_test(void) {
	int fd;
	struct stat sb;
	struct person *p;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1) {
		printf("open fail\n");	
		return -1;
	}
	
	if (fstat(fd, &sb) == -1) {
		printf("stat fail\n");
		close(fd);
		return -1;
	}

	p = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		printf("mmap fail\n");
		close(fd);
		return -1;
	}
	
	for(int i=0; i<sb.st_size / sizeof(struct person); i++) {
		printf("%s %d\n", p[i].name, p[i].age);
	}
	munmap(p, sb.st_size);
	close(fd);
	return 0;
}

int main(void) {
	struct person persons[] = {
		{"Lee", 30},
		{"Kim", 40}
	};

	write_test(&persons[0]);
	write_test(&persons[1]);

	read_test();

	return 0;
}

