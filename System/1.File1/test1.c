#include <stdio.h>
#include <string.h>

int write_test() {
	FILE *file;
	file = fopen("/Users/dopamine100/Test/test", "w");
	if(file == NULL) {
		perror("fopen error\n");	
		return -1;
	}
	fputs("Hello\n", file);
	fclose(file);	

	return 0;
}

int read_test() {
	FILE * file;
	file = fopen("/Users/dopamine100/Test/test", "r");
	if(file == NULL) {
		perror("fopen error\n");
		return -1;
	}	

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	fgets(buffer, sizeof(buffer), file);
	printf("%s", buffer);	
	fclose(file);

	return 0;
}

int main(void) {
	if(write_test()) return -1;
	if(read_test()) return -1;

	return 0;	
}
