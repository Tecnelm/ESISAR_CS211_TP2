#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#include "fonction_decode_question_I1.h"
#include "utility_fonction.h"

void decode_fonction(char* source_path,char* transporteur_path)
{
    FILE *transporteur;
    FILE *source;
    char character;
    int counter = 0;
    char buffer=0;

    transporteur = openFile(transporteur_path,"r");
    source = openFile(source_path,"w");

    do {
        character = (char)fgetc(transporteur);
        if(is_alpha(character))
        {
            if (counter == 8){
                counter = 0;
                //print_binary_char(buffer);
                fputc(buffer,source);
                buffer = 0;

            }
            if(is_upper(character)){
                buffer = (char)(buffer << 1);
                buffer++;
            }
            else {
                buffer = (char)(buffer << 1);
            }
            counter++;
        }

    } while (character != EOF);
    closeFile(transporteur);
    closeFile(source);
}
#pragma clang diagnostic pop