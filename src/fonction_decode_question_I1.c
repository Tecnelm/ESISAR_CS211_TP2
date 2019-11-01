#include "fonction_decode_question_I1.h"
#include "folder_fonction.h"
#include "folder_fonction.c"


void decode_fonction(char* source_path,char* transporteur_path)
{
    FILE *transporteur;
    FILE *source;
    char caractere_temp;
    int counteur = 0;

    transporteur = openFile(transporteur_path,"r");
    source =openFile(source_path,"w");

    do {
        caractere_temp = fgetc(transporteur);
        if (caractere_temp >='A' && caractere_temp <='Z') { //[A-Z] <=> [65-91]
            fprintf(source, "1");
            counteur++;
        }
        else if (caractere_temp >='a' && caractere_temp <='z') {//[a-z] <=> [97-122]
            fprintf(source, "0");
            counteur++;
        }
        else
            continue;
        if(counteur >=40){
            counteur =0;
            fprintf(source,"\n");
        }
    } while (caractere_temp != EOF);
}