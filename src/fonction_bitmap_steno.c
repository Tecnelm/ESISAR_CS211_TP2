#include "fonction_bitmap_steno.h"


int decode_BMP (char *output_path, char *input_path) {

	FILE *input;
	FILE *output;
	ImageEntete imageEntete;
	FichierEntete fichierEntete;
	CouleurPallete couleurPallete;
	unsigned char *image;
	unsigned char buffer;
	unsigned int index;


	input = openFile(input_path, "r");
	output = openFile(output_path, "w");

	getHeaderBMP(input, &fichierEntete, &imageEntete, &couleurPallete);

	afficherEntete(fichierEntete, imageEntete, couleurPallete);

	if (fichierEntete.signature != 0x4D42) {///0x4D42 "BM" en hexa
		fprintf(stderr, "ERROR WRONG FORMAT");
		return EXIT_FAILURE;
	}

	fseek(input, fichierEntete.offset, SEEK_SET);///set the position to the first byte of image
	if (couleurPallete.B == 0 && couleurPallete.V == 0 && couleurPallete.R == 0) {
		image = malloc(sizeof(char) * imageEntete.tailleImage);///allocate the right size of pixel
		fread(image, imageEntete.tailleImage, 1, input);///fill image with all pixel value
		if (image == NULL) {
			fprintf(stderr, "ERROR MALLOC");
			closeFile(input);
			closeFile(output);
			return EXIT_FAILURE;
		}
		int buffer_counter = 0;
		buffer = 0;
		for (index = 0; index < imageEntete.tailleImage; index++) {
			if (buffer_counter == 8) { /// if the buffer is full write it in the source folder
				buffer_counter = 0;
				fputc(buffer, output);
				buffer = 0;
			}
			buffer = (unsigned char) ((buffer << 1) +
									  (image[index] & 0x1));
			buffer_counter++;
		}
		free(image);
	}
	closeFile(input);
	closeFile(output);
	return EXIT_SUCCESS;
}

///
/// \param file file to get Header
/// \param fichierEntete structure of bitmap
/// \param imageEntete  strucuture of bitmap
/// \param couleurPallete strucuture of bitmap
/// \return value of succes or fail
int getHeaderBMP (FILE *file, FichierEntete *fichierEntete, ImageEntete *imageEntete, CouleurPallete *couleurPallete) {

	if (file == NULL) {
		fprintf(stderr, "ERROR NO FILE AVAILABLE");
		return EXIT_FAILURE;
	}
	fread(fichierEntete, sizeof(FichierEntete), 1, file);///read in the main folder the bit of folder header
	fread(imageEntete, sizeof(ImageEntete), 1, file);

	if (ftell(file) != (*fichierEntete).offset) { /// check if a pallet is present and get information if it's the case
		fread(&couleurPallete, sizeof(CouleurPallete), 1, file);
	}
	else {/// if the pallet isn't present initialize  the value to 0 use later
		couleurPallete->B = 0;
		couleurPallete->V = 0;
		couleurPallete->R = 0;
		couleurPallete->reserve = 0;
	}

	return EXIT_SUCCESS;
}


int encodeImageBMP (char *sourcePath, char *outputPath, char *transporteurPath) {

	ImageEntete imageEntete;
	FichierEntete fichierEntete;
	CouleurPallete couleurPallete;


	FILE *transporteur = openFile(transporteurPath, "rb"); /// open folder in binary read mode
	FILE *source = openFile(sourcePath, "rb");
	FILE *output = openFile(outputPath, "w"); /// open folder in write mode

	unsigned char bufferSource; /// buffer use later to build the char to put in the new folder
	unsigned char temp; /// temp char
	int index;
	unsigned long sourceSize, indexS;
	char *dataByte, *imageByte;


	getHeaderBMP(transporteur, &fichierEntete, &imageEntete, &couleurPallete);
	///write the header in the new folder

	fwrite(&fichierEntete, sizeof(FichierEntete), 1, output);
	fwrite(&imageEntete, sizeof(ImageEntete), 1, output);

	/// get the size of the source folder
	fseek(source, 0, SEEK_END);
	sourceSize = ftell(source);
	fseek(source, 0, SEEK_SET);
	///the value are 0 if couleur pallette isn't present
	if (!(couleurPallete.B == 0 && couleurPallete.V == 0 && couleurPallete.R == 0)) {
		fwrite(&couleurPallete, sizeof(couleurPallete), 1, output); /// write data to the output if the pallet is present
	}

	if (!canEncodeBMP(sourceSize, fichierEntete.tailleFichier)) {
		fprintf(stderr, "NOT ENOUGH BYTE TO ENCODE SOURCE");
		return EXIT_FAILURE;
	}

	fseek(transporteur, fichierEntete.offset, SEEK_SET); ///set the position to the start of imageByte
	fseek(output, fichierEntete.offset, SEEK_SET);

	imageByte = malloc(sizeof(char) * imageEntete.tailleImage); /// Allocate table to stock the byte of image and date
	dataByte = malloc(sizeof(char) * sourceSize);

	if (imageByte == NULL || dataByte == NULL) {
		fprintf(stderr, "IMPOSSIBLE ALLOCATE MEMORY");
		free(imageByte);
		free(dataByte);
		return EXIT_FAILURE;
	}

	fread(imageByte, sizeof(char) * imageEntete.tailleImage, 1, transporteur);
	fread(dataByte, sizeof(char) * sourceSize, 1, source);

	/// run through source data
	for (indexS = 0; indexS < sourceSize; indexS++) {
		bufferSource = dataByte[indexS];

		for (index = 7; index >= 0; index--) {
			temp = imageByte[(7 - index) + indexS * 8];
			temp = (bufferSource >> index & 1) ? temp | 1 : temp &
															0xFE; /// change the first bit of the image byte in fonction of the bit of the source
			fputc(temp, output);
		}
	}
	for (indexS *= 8; indexS <
					  imageEntete.tailleImage; indexS++) {/// if the source haven't the right number of byte end to copy the transporteur file (byte not codded)
		fputc(imageByte[indexS], output);
	}


	free(imageByte);
	free(dataByte);
	closeFile(output);
	closeFile(transporteur);
	closeFile(source);
	return EXIT_SUCCESS;
}

int canEncodeBMP (unsigned long sizeSource, unsigned long sizeTrans) {

	return sizeSource * 8 <= sizeTrans;
}


void afficherEntete (FichierEntete fichierEntete, ImageEntete imageEntete, CouleurPallete couleurPallete) {

	/// FichierEntete print
	printf("signature : %hd\n", fichierEntete.signature);
	printf("taille fichier : %d\n", fichierEntete.tailleFichier);
	printf("reserve : %d\n", fichierEntete.reserve);
	printf("offset : %d\n", fichierEntete.offset);

	/// Image entete print
	printf("tailleEntete : %d\n", imageEntete.tailleEntete);
	printf("largeur : %d\n", imageEntete.largeur);
	printf("hauteur : %d\n", imageEntete.hauteur);
	printf("plan : %hd\n", imageEntete.plan);
	printf("profondeur : %d\n", imageEntete.profondeur);
	printf("compression : %d\n", imageEntete.compression);
	printf("tailleImage : %d\n", imageEntete.tailleImage);
	printf("resolutionHorizontale : %d\n", imageEntete.resolutionHorizontale);
	printf("resolutionVerticale : %d\n", imageEntete.resolutionVerticale);
	printf("nombreCouleurs : %d\n", imageEntete.nombreCouleurs);
	printf("resolutionHorizontale : %d\n", imageEntete.resolutionHorizontale);
	printf("nombreCouleursImportantes : %d\n", imageEntete.nombreCouleursImportantes);

	/// Courleur Palette print
	printf("B : %hd\n", couleurPallete.B);
	printf("V : %hd\n", couleurPallete.V);
	printf("R : %hd\n", couleurPallete.R);
	printf("reserve : %hd\n", couleurPallete.reserve);

}


