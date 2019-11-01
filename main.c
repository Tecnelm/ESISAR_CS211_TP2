#include <stdio.h>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main() {
    FILE *fd;
    FILE *fw;
    int caracteretemp;
    int conteur = 0;

    fd = fopen("/home/toma/CLionProjects/ESISAR_CS211_TP2/Data/transporteur.txt", "r");
    fw = fopen("/home/toma/CLionProjects/ESISAR_CS211_TP2/Data/source.txt", "w");

    if (fd == NULL) {
        fprintf(stderr, "erreur ouverture %s/n", "transporteur.txt");
        perror("");
        return EXIT_FAILURE;
    }
    if (fw == NULL) {
        fprintf(stderr, "erreur ouverture %s/n", "source.txt");
        perror("");
        return EXIT_FAILURE;
    }

    do {

        caracteretemp = fgetc(fd);
        //if(caracteretemp == 'i')
        if (caracteretemp >=65 && caracteretemp <=91) { //[A-Z] <=> [65-91]
            fprintf(fw, "1");
            conteur++;
        }
        else if (caracteretemp >=97 && caracteretemp <=122) {//[a-z] <=> [97-122]
            fprintf(fw, "0");
            conteur++;
        }
        else
            continue;
        if(conteur >=40){
            conteur =0;
            fprintf(fw,"\n");
        }
    } while (caracteretemp != EOF);
    return EXIT_SUCCESS;
}
