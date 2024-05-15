#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 1024

void green() {printf("\033[0;32m");}
void reset() {printf("\033[0m");}

int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("pattern and filepath are required\n");
		return 1;;
	}

	char *pattern = argv[1];
	char *path = argv[2];

	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		printf("couldn't open '%s'\n", path);
		return 1;
	}

	char line[LINE_LENGTH];
	int matched = 0;
	int line_num = 0;

	while (fgets(line, LINE_LENGTH, fp) != NULL) {
		line_num++;
		if (strstr(line, pattern) != NULL) {
			matched = 1;
			green();printf("%d", line_num);reset();
			printf(":%s", line);
		}
	}

	if (matched == 0) {
		printf("No matches found!\n");
	}

	fclose(fp);

	return 0;
}
