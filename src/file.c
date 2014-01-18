#include "file.h"

int get_file_size(FILE *handle) {
    int cursor_pos = ftell(handle), file_size = 0;
    fseek(handle, 0, SEEK_END);
    file_size = ftell(handle);
    fseek(handle, cursor_pos, SEEK_SET);
    return file_size;
}
