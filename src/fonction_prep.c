#include "fonction_prep.h"


void get_nombre_impairs (void) {

	const char *folder_name = "nombres_impairs.txt";
	const char *mode = "w";
	FILE *folder;
	int number = 0;
	int number_counter = 0;
	folder = fopen(folder_name, mode);


	if (folder == NULL) {
		fprintf(stderr, "ERROR OPENING FOLDER");
		exit(1);
	}
	while (number_counter != 100) {
		if (number % 2 != 0) {
			number_counter++;
			fprintf(folder, "%d\n", number);
		}
		number++;
	}
	if (fclose(folder) == EOF) {
		fprintf(stderr, "ERROR CLOSING FOLDER");
		exit(1);
	}
}

int *get_info_char (const char *folder_name) {

	static int info_char[3];
	int vowell = 0, maj = 0, min = 0;
	char compare[] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U', 'y', 'Y'};
	int n = sizeof(compare) / sizeof(char);
	char c;
	FILE *folder = fopen(folder_name, "r");
	if (folder == NULL) {
		fprintf(stderr, "OPEN FOLDER %s FAILURE", folder_name);
		exit(EXIT_FAILURE);
	}
	while (EOF != (c = getc(folder))) {
		if (isInsideTable(c, compare, n)) {
			vowell++;
			if (is_upper(c)) {
				maj++;
			}
			else if (is_lower(c)) {
				min++;
			}
		}

	}
	if (EOF == fclose(folder)) {
		fprintf(stderr, "Failure close folder %s", folder_name);
		exit(EXIT_FAILURE);
	}
	info_char[0] = vowell;
	info_char[1] = maj;
	info_char[2] = min;

	return info_char;
}


int is_upper (char c) {

	return (c >= 'A' && c <= 'Z');
}

int is_lower (char c) {

	return (c >= 'a' && c <= 'z');
}

void aff_value (int *table, const char *folder_name) {

	printf("information from: \n\t%s\n", folder_name);
	printf("il y a %d voyelle(s)\n", table[0]);
	printf("il y a %d majuscule(s)\n", table[1]);
	printf("il y a %d minuscule(s)\n", table[2]);
}


