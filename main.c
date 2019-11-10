#include "src/fonction_bitmap_steno.h"
#include "src/fonction_decode_question_I1.h"
#include "src/fonction_prep.h"
#include "src/menu.h"
int programme1 ();

int programme2 ();

int programme3 ();

int programme4 (int argc, char *argv[]);

int main (int argc, char *argv[]) {

	char *progName[] = {
			"Encode/decodeBMP",
			"Question Preparatoire Nombre",
			"Nombre impaire",
			"Transporteur texte",
			"EXIT"
	};
	int size = 5;
	int programme = menu(progName, size);

	switch (programme) {
		case 1:programme1();
			break;
		case 2: programme2();
			break;
		case 3: programme3();
			break;
		case 4:programme4(argc, argv);
			break;
		default:fprintf(stderr,"NO PROGRAMME SELECTED");break;
	}

	return EXIT_SUCCESS;
}

int programme1 () {

	///Decode the source file
	char *transporteur = "./Data/transporteur.bmp";
	char *output1 = "./Data/source.jpg";
	decode_BMP(output1, transporteur);

	///Encode the image with source and transporteur
	char *output = "./Data/encoded.bmp";
	char *origine = "./Data/originel.bmp";
	char *source = "./Data/source.jpg";
	encodeImageBMP(source, output, origine);

	///decode the image that we obptain
	char *out = "./Data/decoded.jpg";
	char *encoded = "./Data/encoded.bmp";
	decode_BMP(out, encoded);

	///compare the encoded image by the fonction and the base image together to see if they are the same
	compareBMP("./Data/transporteur.bmp", "./Data/encoded.bmp");
	return EXIT_SUCCESS;
}

int programme2 () {

	///code for the preparation question
	char *transporteur_path = "./Data/transporteur.txt";
	char *source_path = "./Data/source.txt";

	decodeFonction(source_path, transporteur_path);
	return EXIT_SUCCESS;
}

int programme3 () {

	get_nombre_impairs();
	return EXIT_SUCCESS;
}

int programme4 (int argc, char *argv[]) {

	int *data;
	if (argc == 1) {
		printf("No argument specified Program abord");
		return EXIT_FAILURE;
	}
	else {

		data = get_info_char(argv[argc - 1]);
	}
	aff_value(data, argv[argc - 1]);
	return EXIT_SUCCESS;

}