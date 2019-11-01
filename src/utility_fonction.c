#include "utility_fonction.h"


FILE* openFile(char* name, char* mode)
{
    FILE* fd;
    fd = fopen(name, mode);

    if (fd == NULL) {
        fprintf(stderr, "ERROR OPENING FOLDER : %s\n", name);
        perror("");
        exit(EXIT_FAILURE);
    }

    return fd;
}

void closeFile(FILE* file)
{
    if (fclose(file) == EOF) {
        fprintf(stderr, "\"ERROR CLOSE FOLDER \n");
        perror("");
        exit(EXIT_FAILURE);
    }
}

int is_inside_table(char c, const char *table, int table_size) {
    int result = 0;
    int index = 0;
    do {
        if (c == table[index]) {
            result = 1;
        }
    } while ((c != table[index]) && ++index < table_size);
    return result;
}

int is_upper(char c) {
    return (c >= 'A' && c <= 'Z');
}

int is_lower(char c) {
    return (c >= 'a' && c <= 'z');
}
