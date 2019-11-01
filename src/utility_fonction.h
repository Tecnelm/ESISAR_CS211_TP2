#include <stdio.h>
#include <stdlib.h>

void closeFile(FILE* file);
FILE* openFile(char* name, char* mode);
int  is_inside_table(char c,const char *table,int table_size);
int is_upper(char c);
int is_lower(char c);
