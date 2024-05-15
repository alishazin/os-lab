#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

int main() {

	DIR *dir_ptr;
	struct dirent *read_dir;
	char path[30];

	printf("Enter directoy to open: ");
	scanf("%30s", path);

	dir_ptr = opendir(path);
	if (dir_ptr == NULL) {
		printf("Couldn't open the folder '%s'\n", path);
		return 1;
	}

	read_dir = readdir(dir_ptr);
	printf("type\tinode\t\tname\n");
	while (read_dir != NULL) {
	
		if (read_dir->d_type == DT_DIR)
			printf("DIR:\t");
		else if (read_dir->d_type == DT_REG)
			printf("FILE:\t");
		else if (read_dir->d_type == DT_LNK)
			printf("LINK:\t");

		printf("%ld\t%s\n", read_dir->d_ino, read_dir->d_name);
			
		// hard link is DT_REG
		// soft link is DT_LNK 

		read_dir = readdir(dir_ptr);

	}

	if (closedir(dir_ptr) == -1) {
		printf("Couldn't close the folder '%s'\n", path);
		return 1;
	}

	return 0;
}
