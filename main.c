#include "src/fonction_prep.h"

//#include "src/fonction_prep.c"

int main(int argc, char *argv[]) {
    int *data;
#ifdef TEST
    const char* folder_path = "/home/clement/CLionProjects/ESISAR_CS211_TP2/Data/transporteur.txt";
    data = get_info_char(folder_path);
    aff_value(data,folder_path);

    const char* folder_path2 = "/home/clement/CLionProjects/ESISAR_CS211_TP2/Data/transporteur.txt";
    data = get_info_char(folder_path2);
    aff_value(data,folder_path2);
#else
    get_nombre_impairs();
    if (argc == 1) {
        printf("No argument specified Program abord");
    } else {

        data = get_info_char(argv[argc - 1]);
    }
        aff_value(data,argv[argc - 1]);
#endif


    return 0;
}


