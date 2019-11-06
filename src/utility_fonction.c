#include "utility_fonction.h"
#include "bitmap.h"


FILE* openFile(char* name, char* mode){

    FILE* fd;
    fd = fopen(name, mode);

    if (fd == NULL) {
        fprintf(stderr, "ERROR OPENING FOLDER : %s\n", name);
        perror("");
        exit(EXIT_FAILURE);
    }

    return fd;
}

void closeFile(FILE* file){

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

int is_alpha(char c){
    return (c>='A' && c<='Z')|| (c>='a' && c<='z');
}

void print_binary_char(char c, char lastchar){
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", c>>i & 1);
    }


    printf("%c",lastchar);
}
char* convert_char_strHexa(char* string){

}

int convert_String_hexa(const char* string){
    int stringlen = strlen(string);
    int result = 0;
    int value;
    int index;

    for(index = 0 ; index <stringlen; index++)
    {
        result *= 16;
        switch (string[index]){
            case '0':value = 0;break;
            case '1':value = 1;break;
            case '2':value = 2;break;
            case '3':value = 3;break;
            case '4':value = 4;break;
            case '5':value = 5;break;
            case '6':value = 6;break;
            case '7':value = 7;break;
            case '8':value = 8;break;
            case '9':value = 9;break;
            case 'A':value = 10;break;
            case 'B':value = 11;break;
            case 'C':value = 12;break;
            case 'D':value = 13;break;
            case 'E':value = 14;break;
            case 'F':value = 15;break;
            default: return -1;
        }
        result += value;
    }
    return result;
}

int compareBMP(char* pathFile1, char* pathFile2)
{
    FILE* file1 = openFile(pathFile1,"r");
    FILE* file2 = openFile(pathFile2,"r");

    char *image1Byte;
    char *image2Byte;

    long index;

    FichierEntete fichierEntete1, fichierEntete2;

    fread(&fichierEntete1, sizeof(FichierEntete),1,file1);
    fread(&fichierEntete2, sizeof(FichierEntete),1,file2);

    if(fichierEntete1.signature != fichierEntete2.signature || fichierEntete1.tailleFichier != fichierEntete2.tailleFichier)
    {
        printf("NOT SAME SIGNATURE OR SIZE");
        closeFile(file1);
        closeFile(file2);
        return 0;
    }

    image1Byte = malloc(fichierEntete1.tailleFichier);
    image2Byte = malloc(fichierEntete1.tailleFichier);

    if(image1Byte == NULL || image2Byte == NULL)
    {
        fprintf(stderr,"ERROR MEMORY ALLOCATION");
        closeFile(file1);
        closeFile(file2);
        free(image1Byte);
        free(image2Byte);
        return 0;
    }

    fseek(file1,0,SEEK_SET);
    fseek(file2,0,SEEK_SET);
    fread(image1Byte,fichierEntete1.tailleFichier,1,file1);
    fread(image2Byte,fichierEntete1.tailleFichier,1,file2);

    for(index = 0; index < fichierEntete1.tailleFichier ; index++){
        if(image1Byte[index] != image2Byte[index]) {
            printf("ERROR BYTE n° %d\n",index);
            int i;
            for ( i = index; i <fichierEntete1.tailleFichier+fichierEntete1.offset ; ++i) {
                print_binary_char(image1Byte[index], '\t');
                print_binary_char(image2Byte[index], '\n');
            }
            closeFile(file1);
            closeFile(file2);
            free(image1Byte);
            free(image2Byte);
            return 0;
        }
    }
    printf("Both folder are same");
    closeFile(file1);
    closeFile(file2);
    free(image1Byte);
    free(image2Byte);
    return 1;
}