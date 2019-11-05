#include "bitmap.h"
#include "utility_fonction.h"


int decode_BMP(char* output_path,char* input_path);
int canDecodeBMP();
int getHeaderBMP(FILE* file, FichierEntete* fichierEntete, ImageEntete* imageEntete, CouleurPallete* couleurPallete);
int encodeImageBMP(char* sourcePath, char* outputPath, char* transporteurPath);