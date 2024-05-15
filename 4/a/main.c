#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		printf("source and target are required args\n");
		return 1;
	}

	char *s_path = argv[1];
	char *t_path = argv[2];

	char ch;
	FILE *s_f, *t_f;

	s_f = fopen(s_path, "r");
	if (s_f == NULL) {
		printf("couldn't open the file '%s'\n", s_path);
		return 1;
	}
	
	t_f = fopen(t_path, "w");
	if (t_f == NULL) {
		printf("couldn't open the file '%s'\n", t_path);
		fclose(s_f);
		return 1;
	}

	while ((ch=fgetc(s_f)) != EOF) {
		fputc(ch, t_f);
	}

	printf("Copied from '%s' to '%s'\n", s_path, t_path);
	fclose(s_f);
	fclose(t_f);

	return 0;
}
