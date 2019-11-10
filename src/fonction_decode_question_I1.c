#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include "fonction_decode_question_I1.h"
#include "utility_fonction.h"


void decodeFonction (char *source_path, char *transporteur_path) {

	FILE *transporteur;
	FILE *source;
	char character;
	int counter = 0;
	char buffer = 0; /// creation of a buffer to write in the source byte by byte

	transporteur = openFile(transporteur_path, "r");
	source = openFile(source_path, "w");

	do {
		character = (char) fgetc(transporteur); /// get the next char of transporteur
		if (is_alpha(character)) /// check if is alphanum
		{
			if (counter == 8) { /// if the buffer is full write it in the source folder
				counter = 0;
				fputc(buffer, source);
				buffer = 0;

			}
			/// add the right bit to the buffer
			if (is_upper(character)) {
				buffer = (char) (buffer << 1);
				buffer++;
			}
			else {
				buffer = (char) (buffer << 1);
			}
			counter++;
		}

	}
	while (character != EOF);
	closeFile(transporteur);
	closeFile(source);
}

