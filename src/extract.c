#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extract.h"
#include "file.h"
#include "error.h"

const char gob_header_string[] = "GOB\n";

int extract_files_from_gob(const char *filename) {
    FILE *handle = 0;
    char *buffer = 0;
    int file_description_pos = 0, gob_file_size = 0, num_files = 0, bytes_read = 0;
    struct file_entry *entries = 0;

    handle = fopen(filename, "rb");
    check(handle, "gobex: file '%s' does not exist.\n", filename);

    buffer = (char *)malloc(sizeof(unsigned char) * BUFFER_SIZE);
    check(buffer, "gobex: out of memory");

    bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, handle);
    check(!(bytes_read == 0), "gobex: invalid file (incorrect header)\n");

    // verify if the file is a valid gob file
    check(!strcmp(buffer, gob_header_string), "gobex: invalid file (incorrect header)\n");

    // read the position of the file descriptions
    bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, handle);
    check(!(bytes_read == 0), "gobex: invalid file (incorrect header)\n");
    file_description_pos = unpack_int(buffer);

    // read the number of files in the archive
    fseek(handle, file_description_pos, SEEK_SET);
    bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, handle);
    check(!(bytes_read == 0), "gobex: empty archive\n");
    num_files = unpack_int(buffer);
    free(buffer);

    // read file descriptions
    gob_file_size = get_file_size(handle);
    buffer = (char *)malloc(sizeof(char) * (gob_file_size - file_description_pos));
    check(buffer, "gobex: out of memory");

    fread(buffer, sizeof(char), (gob_file_size - file_description_pos), handle);
    check(!(bytes_read == 0), "gobex: empty archive\n");

    entries = (struct file_entry *)malloc(sizeof(struct file_entry) * num_files);
    check(buffer, "gobex: out of memory");
    find_files(buffer, entries, num_files);

    char *basename = (char *)malloc(sizeof(char) * strlen(filename));
    get_basename(filename, basename);
    create_directory(basename);
    extract_files(handle, entries, num_files, basename);

    free(entries);
    free(buffer);
    fclose(handle);

    return 1;

 error:
    if (buffer) free(buffer);
    if (entries) free(entries);
    return 0;
}

int find_files(const char *buffer, struct file_entry *entries, int num_files) {
    struct file_entry current_entry;

    for (int i = 0; i < num_files; i++, buffer += 21) {
	current_entry.pos = unpack_int(buffer);
	current_entry.size = unpack_int(buffer + 4);
	strcpy(current_entry.name, buffer + 8);
	entries[i] = current_entry;
    }

    return 1;
}

int extract_files(FILE *handle, const struct file_entry *entries, int num_files, const char *directory) {
    char *buffer = 0, *new_file_name = 0;
    FILE *new_file = 0;

    for (int i = 0; i < num_files; i++) {
	buffer = (char *)malloc(sizeof(char) * entries[i].size);
	new_file_name = (char *)malloc(sizeof(char) * (strlen(directory) + strlen(entries[i].name) + 2));
	fseek(handle, entries[i].pos, SEEK_SET);
	fread(buffer, sizeof(char), entries[i].size, handle);
	sprintf(new_file_name, "%s/%s", directory, entries[i].name);
	new_file = fopen(new_file_name, "wb");
	fwrite(buffer, sizeof(char), entries[i].size, new_file);
	fclose(new_file);
	free(new_file_name);
	free(buffer);
    }

    return 1;
}

void print_files(const struct file_entry *entries, int num_files) {
    for (int i = 0; i < num_files; i++) {
	printf("%s: (%d, %d)\n", entries[i].name, entries[i].pos, entries[i].size);
    }
}

int unpack_int(const char *buffer) {
    unsigned char *new_buffer = (unsigned char *)buffer;
    return UNPACK_LE_INT(new_buffer);
}
