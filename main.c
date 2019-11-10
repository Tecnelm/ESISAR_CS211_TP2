#include "src/fonction_bitmap_steno.h"
#include "src/fonction_decode_question_I1.h"

int main() {

	///code for the preparation question
    /*char *transporteur_path ="../Data/transporteur.txt";
    char *source_path ="../Data/source.txt";


    decode_fonction(source_path,transporteur_path);
    return EXIT_SUCCESS;
	 */

	///Decode the source file
    char *transporteur = "../Data/transporteur.bmp";
    char *output1 = "../Data/source.jpg";
	decode_BMP(output1, transporteur);

	///Encode the image with source and transporteur
	char *output = "../Data/encoded.bmp";
	char *origine = "../Data/originel.bmp";
	char *source = "../Data/source.jpg";
	encodeImageBMP(source, output, origine);

	///decode the image that we obptain
	char *out = "../Data/decoded.jpg";
	char *encoded = "../Data/encoded.bmp";
	decode_BMP(out, encoded);

	///compare the encoded image by the fonction and the base image together to see if they are the same
    compareBMP("../Data/transporteur.bmp","../Data/encoded.bmp");

    return EXIT_SUCCESS;

}