#include <stdio.h>
#include <stdlib.h>
#include "extract.h"

const char gobex_usage_string[] = "gobex <file>";

int main(int argc, char **argv) {
    if (argc == 1) {
	printf("usage: %s\n", gobex_usage_string);
	exit(1);
    } else if (argc > 2) {
	fprintf(stderr, "gobex: only one file at a time is supported\n");
	exit(1);
    }

    extract_files_from_gob(argv[1]);

    return 0;
}
