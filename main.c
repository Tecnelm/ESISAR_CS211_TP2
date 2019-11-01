#include "src/fonction_decode_question_I1.h"
#include "src/utility_fonction.h"

int main() {

    char *transporteur_path ="../Data/transporteur.txt";
    char *source_path ="../Data/source.txt";
    decode_fonction(source_path,transporteur_path);
    return EXIT_SUCCESS;
}
