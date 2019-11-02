#include "src/fonction_bitmap_decode.h"

int main() {
    char* input="../Data/transporteur.bmp";
    char* output="../Data/source.bmp";
    decode_BPM(output,input);

    return 0;
}