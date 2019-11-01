#include "src/fonction_decode_question_I1.h"
#include "src/fonction_decode_question_I1.c"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main() {
    char *transporteur_path ="../Data/transporteur.txt";
    char *source_path ="../Data/source.txt";
    decode_fonction(source_path,transporteur_path);
    return EXIT_SUCCESS;
}
