#include "folder_fonction.h"


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
