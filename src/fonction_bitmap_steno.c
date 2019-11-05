#include "fonction_bitmap_steno.h"

int decode_BPM(char* output_path,char* input_path)
{
        FILE* input;
        FILE* output;
        ImageEntete imageEntete;
        FichierEntete fichierEntete;
        CouleurPallete couleurPallete;
        unsigned char* image;
        char buffer;
        int index;


        input = openFile(input_path,"r");
        output = openFile(output_path,"w");

    fread(&fichierEntete, sizeof(FichierEntete),1,input);
    if(fichierEntete.signature != 0x4D42){//0x4D42 "BM" en hexa
        fprintf(stderr,"ERROR WRONG FORMAT");
        return EXIT_FAILURE;
    }
    fread(&imageEntete, sizeof(ImageEntete),1,input);
    if(ftell(input) != fichierEntete.offset) // check if a pallette is present and get information if it's the case
        fread(&couleurPallete, sizeof(CouleurPallete),1,input);

    fseek(input,fichierEntete.offset,SEEK_SET);//set the position to the first byte of image

    if(couleurPallete.B == 0 && couleurPallete.V == 0 && couleurPallete.R == 0 ) {
        image = malloc(sizeof(char) * imageEntete.tailleImage);//alloc the right size of pixel
        fread(image,imageEntete.tailleImage,1,input);//fill image with all pixel value
        if (image == NULL) {
            fprintf(stderr, "ERROR MALLOC");
            closeFile(input);
            closeFile(output);
            return EXIT_FAILURE;
        }
        int buffer_counter =0;
        buffer = 0;
        for(index = 0 ; index <imageEntete.tailleImage ; index++) // NOLINT(bugprone-too-small-loop-variable)
        {
            if (buffer_counter == 8) { // if the buffer is full write it in the source folder
                buffer_counter = 0;
                fputc(buffer, output);
                buffer = 0;
            }
            buffer = (char)((buffer<<1)+(image[index]&0x1)); // NOLINT(hicpp-signed-bitwise,bugprone-narrowing-conversions)
            buffer_counter++;
        }
        free(image);
    }
    closeFile(input);
    closeFile(output);
}