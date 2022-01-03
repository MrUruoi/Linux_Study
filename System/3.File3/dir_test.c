#include <stdio.h>
#include <dirent.h>

#define STROF(x) \
	((x) == DT_DIR	? "DT_DIR" :\
	(x) == DT_REG	? "DT_REG" :\
	(x) == DT_LNK	? "DT_LNK" :\
	"else..")

int main(void) {
	DIR *dp;
	struct dirent *entry;

	dp = opendir(".");
	if(dp == NULL) return -1;
	
	while((entry = readdir(dp))) {
		
		printf("%s %s\n", entry->d_name, STROF(entry->d_type)); 
	}

	closedir(dp);

	return 0;	
}
