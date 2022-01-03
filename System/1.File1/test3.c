#include <stdio.h>

struct person {
	char name[20];
	int age;
};

int write_test(void) {
	struct person lee = {
		.name = "Lee",
		.age = 30	
	};
	struct person kim = {
		.name = "Kim",
		.age = 28	
	};

	FILE *fp = NULL;
	fp = fopen("test", "w");
	if(fp == NULL) return -1;

	if( fwrite(&lee, sizeof(struct person), 1, fp) != 1) goto err;	
	if( fwrite(&kim, sizeof(struct person), 1, fp) != 1) goto err;	

	fclose(fp);

	return 0;

err:
	if(fp) fclose(fp);
	return -1;
}

int read_test(void) {
	struct person persons[2];

	FILE *fp;
	fp = fopen("test", "r");
	if(fp == NULL) return -1;

	if( fread(persons, sizeof(struct person), 2, fp) != 2 ) {
		fclose(fp);
		return -1;
	}

	fclose(fp);
	for(int i=0; i<2; i++) {
		printf("%s %d\n", persons[i].name, persons[i].age);
	}

	return 0;

}

int main(void) {
	write_test();	
	read_test();
	return 0;
}
