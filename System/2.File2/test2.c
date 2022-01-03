#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct person {
	char name[10];
	int age;
};

int write_test(struct person *p) {
	int fd;
	fd = open("test", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if(fd == -1) return -1;
	
	ssize_t ret = write(fd, p, sizeof(struct person));
	if(ret == -1) {
		close(fd);
		return -1;
	} else if(ret != sizeof(struct person)) {
		close(fd);
		return -1;	
	}
	
	close(fd);
	return 0;
}

int read_test(void) {
	int fd;
	ssize_t ret;
	struct person p;

	fd = open("test", O_RDONLY);
	if(fd == -1) return -1;

	do {
		ret = read(fd, &p, sizeof(struct person));
		if(ret == -1) {
			close(fd);
			return -1;
		}else if(ret == 0) {
			break;
		}  else if(ret != sizeof(struct person)) {
			close(fd);
			return -1;
		}
		printf("%s %d\n", p.name, p.age);
	} while(1);

	return 0;
}

int main(void) {
	struct person persons[] = {
		{"Lee", 30},
		{"Kim", 25}
	};
	
	write_test(&persons[0]);
	write_test(&persons[1]);

	read_test();

	return 0;
}

