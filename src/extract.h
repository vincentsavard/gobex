#ifndef EXTRACT_H
#define EXTRACT_H

#define UNPACK_LE_INT(s) ((s[0]) | (s[1] << 8) | (s[2] << 16) | (s[3] << 24))

#define BUFFER_SIZE 4
#define FILE_NAME_SIZE 12

struct file_entry {
    char name[FILE_NAME_SIZE + 1];
    int pos;
    int size;
};

int extract_files_from_gob(const char *filename);
int find_files(const char *buffer, struct file_entry *entries, int num_files);
int extract_files(FILE *handle, const struct file_entry *entries, int num_files, const char *filename);
void print_files(const struct file_entry *entries, int num_files);
int unpack_int(const char *buffer);

#endif
