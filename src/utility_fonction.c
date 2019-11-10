#include "utility_fonction.h"
#include "bitmap.h"


FILE *openFile (char *name, char *mode) {

	FILE *fd;
	fd = fopen(name, mode);

	if (fd == NULL) {
		fprintf(stderr, "ERROR OPENING FOLDER : %s\n", name);
		perror("");
		exit(EXIT_FAILURE);
	}

	return fd;
}

void closeFile (FILE *file) {

	if (fclose(file) == EOF) {
		fprintf(stderr, "\"ERROR CLOSE FOLDER \n");
		perror("");
		exit(EXIT_FAILURE);
	}
}

int isInsideTable (char c, const char *table, int table_size) {///compare each element of a table and return if the parmeter is present

	int result = 0;
	int index = 0;
	do {
		if (c == table[index]) {
			result = 1;
		}
	}
	while ((c != table[index]) && ++index < table_size);
	return result;
}

void isInsideTest () {

	int size = 5;
	char chaine[] = {'a', 'b', 'a', 'd', 'e'};
	char compare[] = {'a', 'e', 'i', 'o', 'u', 'y'};
	int n = sizeof(compare) / sizeof(char);
	int index;
	for (index = 0; index < size; index++) {
		int temp = isInsideTable(chaine[index], compare, n);
		printf("char n* %d : %d\n", index, temp);
	}
}

int is_upper (char c) {

	return (c >= 'A' && c <= 'Z');
}

int is_lower (char c) {

	return (c >= 'a' && c <= 'z');
}

int is_alpha (char c) {

	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void print_binary_char (char c, char lastchar) {

	int i;
	for (i = 7; i >= 0; i--) {
		printf("%d", c >> i & 1); /// get the bit and print it
	}

	printf("%c", lastchar);
}

int convert_String_hexa (const char *string) { /// convert a char*, format in HEXA to an integer "FF" -> 255

	unsigned int stringlen = strlen(string);
	int result = 0;
	int value;
	unsigned int index;

	for (index = 0; index < stringlen; index++) {
		result *= 16;
		switch (string[index]) {
			case '0':value = 0;
				break;
			case '1':value = 1;
				break;
			case '2':value = 2;
				break;
			case '3':value = 3;
				break;
			case '4':value = 4;
				break;
			case '5':value = 5;
				break;
			case '6':value = 6;
				break;
			case '7':value = 7;
				break;
			case '8':value = 8;
				break;
			case '9':value = 9;
				break;
			case 'A':value = 10;
				break;
			case 'B':value = 11;
				break;
			case 'C':value = 12;
				break;
			case 'D':value = 13;
				break;
			case 'E':value = 14;
				break;
			case 'F':value = 15;
				break;
			default:return -1;
		}
		result += value;
	}
	return result;
}

int compareBMP (char *pathFile1, char *pathFile2) {

	FILE *file1 = openFile(pathFile1, "r"); /// open file
	FILE *file2 = openFile(pathFile2, "r");

	char *image1Byte;/// list of byte for the image one and two
	char *image2Byte;

	long index;
	long size;

	FichierEntete fichierEntete1, fichierEntete2;

	fread(&fichierEntete1, sizeof(FichierEntete), 1, file1);/// read the entete to know the size of the image
	fread(&fichierEntete2, sizeof(FichierEntete), 1, file2);

	fseek(file2, 0, SEEK_END);/// go to the end of the file to know the size of the data
	fseek(file1, 0, SEEK_END);

	size = ftell(file1) == ftell(file2) ? ftell(file2) : 0;

	if (size == 0) {
		printf("SIZE NULL OR DIFFERENT");
		closeFile(file1);
		closeFile(file2);
		return EXIT_FAILURE;
	}

	image1Byte = malloc(size);
	image2Byte = malloc(size);

	if (image1Byte == NULL || image2Byte == NULL) {
		fprintf(stderr, "ERROR MEMORY ALLOCATION");
		closeFile(file1);
		closeFile(file2);
		free(image1Byte);
		free(image2Byte);
		return 0;
	}

	fseek(file1, 0, SEEK_SET);
	fseek(file2, 0, SEEK_SET);
	fread(image1Byte, size, 1, file1);
	fread(image2Byte, size, 1, file2);

	for (index = 0; index < size; index++) {/// compare each byte together
		if (image1Byte[index] != image2Byte[index]) {
			printf("ERROR BYTE n° %ld\n", index);
			closeFile(file1);
			closeFile(file2);
			free(image1Byte);
			free(image2Byte);
			return EXIT_FAILURE;
		}
	}
	printf("SUCESS BOTH FOLDER ARE SAME");
	closeFile(file1);
	closeFile(file2);
	free(image1Byte);
	free(image2Byte);
	return EXIT_SUCCESS;
}

void resetBuffer () {

	int c;
	while ((c = getchar()) != EOF && c != '\n');
}

