#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void green() {printf("\033[0;32m");}
void reset() {printf("\033[0m");}

int main() {

	DIR *dir_ptr;
	struct dirent *read_dir;

	dir_ptr = opendir(".");
	if (dir_ptr == NULL) {
		printf("couldn't open cwd");
		return 1;
	}

	read_dir = readdir(dir_ptr);
	while (read_dir != NULL) {
		if (read_dir->d_type == DT_DIR) {
			green();printf("%s    ", read_dir->d_name);
		} else if (read_dir->d_type == DT_REG) {
			printf("%s    ", read_dir->d_name);
		}
		reset();
		read_dir = readdir(dir_ptr);
			
	}

	printf("\n");

	if (closedir(dir_ptr) == -1) {
		printf("couldn't close cwd");
		return 1;
	}

	return 1;
}
