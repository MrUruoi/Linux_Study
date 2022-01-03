#include <stdio.h>
#include <unistd.h>

int main(void) {

	if(link("test.txt", "hard.txt")) return -1;

	if(symlink("test.txt", "soft.txt")) return -1;

	return 0;
}
