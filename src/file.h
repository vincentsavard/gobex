#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int get_file_size(FILE *handle);
int get_basename(const char *filename, char *basename2);
int create_directory(const char *name);
