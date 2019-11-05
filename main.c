#include "src/fonction_bitmap_steno.h"

int main() {
    char *transporteur = "../Data/transporteur.bmp";
    char *output1 = "../Data/source.jpg";

    char *out = "../Data/decoded.jpg";
    char *encoded = "../Data/encoded.bmp";

    decode_BMP(output1, transporteur);

    char *output = "../Data/encoded.bmp";
    char *origine = "../Data/originel.bmp";
    char *source = "../Data/source.jpg";

    encodeImageBMP(source, output, origine);

    decode_BMP(out, encoded);

    compareBMP("../Data/transporteur.bmp","../Data/encoded.bmp");

    return 0;
}