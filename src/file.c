#include "file.h"

int get_file_size(FILE *handle) {
    int cursor_pos = ftell(handle), file_size = 0;
    fseek(handle, 0, SEEK_END);
    file_size = ftell(handle);
    fseek(handle, cursor_pos, SEEK_SET);
    return file_size;
}

int get_basename(const char *filename, char *basename) {
    char c;

    do {
	c = *filename;

	if (c == '.') break;
	*basename = c;
	basename++;
    } while (filename++);

    return 1;
}

int create_directory(const char *name) {
    struct stat st = {0};

    if (stat(name, &st) == -1) {
	mkdir(name, 0700);
	return 1;
    }
    return 0;
}
