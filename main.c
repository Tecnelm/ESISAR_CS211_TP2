#include "src/fonction_bitmap_steno.h"

int main() {
    char* transporteur = "../Data/transporteur.bmp";
    char* output1 = "../Data/source.bmp";


    char* output = "../Data/encoded.bmp";
    char* origine = "../Data/originel.bmp";
    char* source = "../Data/source.bmp";

    //decode_BMP(output1,transporteur);

    encodeImageBMP(source, output, origine);

    return 0;
}