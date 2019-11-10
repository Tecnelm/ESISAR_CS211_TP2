#include "bitmap.h"
#include "utility_fonction.h"


int decode_BMP (char *output_path, char *input_path);

int canEncodeBMP (long sizeSource, long sizeTrans);

int getHeaderBMP (FILE *file, FichierEntete *fichierEntete, ImageEntete *imageEntete, CouleurPallete *couleurPallete);

int encodeImageBMP (char *sourcePath, char *outputPath, char *transporteurPath);

void afficher_entete(FichierEntete fichierEntete, ImageEntete imageEntete ,CouleurPallete couleurPallete);