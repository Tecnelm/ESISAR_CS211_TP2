#include "fonction_bitmap_steno.h"

int decode_BMP(char *output_path, char *input_path) {
    FILE *input;
    FILE *output;
    ImageEntete imageEntete;
    FichierEntete fichierEntete;
    CouleurPallete couleurPallete;
    unsigned char *image;
    char buffer;
    int index;


    input = openFile(input_path, "r");
    output = openFile(output_path, "w");

    getHeaderBMP(input, &fichierEntete, &imageEntete, &couleurPallete);

    if (fichierEntete.signature != 0x4D42) {//0x4D42 "BM" en hexa
        fprintf(stderr, "ERROR WRONG FORMAT");
        return EXIT_FAILURE;
    }
    fseek(input, fichierEntete.offset,SEEK_SET);
    if (couleurPallete.B == 0 && couleurPallete.V == 0 && couleurPallete.R == 0) {
        image = malloc(sizeof(char) * imageEntete.tailleImage);//alloc the right size of pixel
        fread(image, imageEntete.tailleImage, 1, input);//fill image with all pixel value
        if (image == NULL) {
            fprintf(stderr, "ERROR MALLOC");
            closeFile(input);
            closeFile(output);
            return EXIT_FAILURE;
        }
        int buffer_counter = 0;
        buffer = 0;
        for (index = 0; index < imageEntete.tailleImage; index++) // NOLINT(bugprone-too-small-loop-variable)
        {
            if (buffer_counter == 8) { // if the buffer is full write it in the source folder
                buffer_counter = 0;
                fputc(buffer, output);
                buffer = 0;
            }
            buffer = (char) ((buffer << 1) +
                             (image[index] & 0x1)); // NOLINT(hicpp-signed-bitwise,bugprone-narrowing-conversions)
            buffer_counter++;
        }
        free(image);
    }
    closeFile(input);
    closeFile(output);
}

int getHeaderBMP(FILE *file, FichierEntete *fichierEntete, ImageEntete *imageEntete, CouleurPallete *couleurPallete) {

    if(file == NULL)
    {
        fprintf(stderr,"ERROR NO FILE AVAILABLE");
        return EXIT_FAILURE;
    }
    fread(fichierEntete, sizeof(FichierEntete), 1, file);
    fread(imageEntete, sizeof(ImageEntete), 1, file);
    if (ftell(file) != (*fichierEntete).offset) // check if a pallette is present and get information if it's the case
        fread(&couleurPallete, sizeof(CouleurPallete), 1, file);

    return EXIT_SUCCESS;
}

int encodeImageBMP(char *sourcePath, char *outputPath, char *transporteurPath) {
    ImageEntete imageEntete;
    FichierEntete fichierEntete;
    CouleurPallete couleurPallete;

    FILE* transporteur = openFile(transporteurPath, "r");
    FILE* source = openFile(sourcePath,"r");
    FILE* output = openFile(outputPath,"w");

    unsigned char bufferSource;
    unsigned char temp;
    int index;
    unsigned long sourceSize, indexS;
    char *dataByte, *imageByte;



    getHeaderBMP(transporteur , &fichierEntete, &imageEntete, &couleurPallete);
    fwrite(&fichierEntete, sizeof(FichierEntete),1,output);
    fwrite(&imageEntete, sizeof(ImageEntete),1,output);

    fseek(transporteur,fichierEntete.offset,SEEK_SET);
    fseek(source,0,SEEK_END);
    sourceSize = ftell(source);
    fseek(source,0,SEEK_SET);

    if (!(couleurPallete.B == 0 && couleurPallete.V == 0 && couleurPallete.R == 0))
        fwrite(&couleurPallete, sizeof(couleurPallete),1,output);

    if(!canDecodeBMP())
        return EXIT_FAILURE;

    imageByte = malloc(sizeof(char)*imageEntete.tailleImage);
    dataByte = malloc(sizeof(char)*sourceSize);

    if(imageByte == NULL || dataByte == NULL ){
        fprintf(stderr,"IMPOSSIBLE ALLOCATE MEMORY");
        return EXIT_FAILURE;
    }

    fread(imageByte, sizeof(char)*imageEntete.tailleImage,1,transporteur);
    fread(dataByte, sizeof(char)*sourceSize,1,source);


    for(indexS =0 ; indexS<sourceSize ; indexS++)
    {
        bufferSource = dataByte[indexS];
        for(index = 7 ; index>= 0 ; index --) // need correction of value;
        {
            temp = imageByte[(7-index)+indexS*8];
            temp = (bufferSource>>index & 1)  ? temp|1 : temp & 0xFE;

            fputc(temp,output);
        }
    }
    closeFile(output);
    closeFile(transporteur);
    closeFile(source);
}

int canDecodeBMP()
{
    return 1;
}

