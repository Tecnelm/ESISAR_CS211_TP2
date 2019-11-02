#include "fonction_bitmap_decode.h"

void decode_BPM(char* output_path,char* input_path)
{
        FILE* input;
        FILE* output;
        ImageEntete imageEntete;
        FichierEntete fichierEntete;


        input = openFile(input_path,"r");
        output = openFile(output_path,"w");

        fread(&fichierEntete, sizeof(FichierEntete),1,input);
        if(fichierEntete.signature == 0x4D42)//0x4D42 "BM" en hexa ;

        closeFile(input);
        closeFile(output);
}