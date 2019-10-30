#include "fonction_prep.h"
#include <stdio.h>
#include <stdlib.h>
void get_nombre_impairs(void)
{
    const char *folder_name = "nombres_impairs.txt";
    const char *mode = "w";
    FILE* folder ;
    int number = 0;
    int number_counter = 0;
    folder = fopen(folder_name,mode);


    if(folder == NULL)
    {
        fprintf(stderr,"ERROR OPENING FOLDER");
        exit(1);
    }
    while(number_counter !=100)
    {
        if(number%2 !=0)
        {
            number_counter++;
            fprintf(folder,"%d\n",number);
        }
        number++;
    }
    if(fclose(folder)== EOF)
    {
        fprintf(stderr,"ERROR CLOSING FOLDER");
        exit(1);
    }
}
