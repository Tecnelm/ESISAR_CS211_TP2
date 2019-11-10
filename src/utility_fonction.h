#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void closeFile (FILE *file);

FILE *openFile (char *name, char *mode);

int isInsideTable (char c, const char *table, int table_size);

void isInsideTest ();

int is_upper (char c);

int is_lower (char c);

int is_alpha (char c);

void print_binary_char (char character, char lastchar);

int convert_String_hexa (const char *string);

int compareBMP (char *pathFile1, char *pathFile2);

void resetBuffer ();