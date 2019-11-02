
typedef struct __attribute__((__packed__)) {
	unsigned short signature; 
	unsigned int tailleFichier; 
	unsigned int reserve; 
	unsigned int offset; 
} FichierEntete;

typedef struct __attribute__((__packed__)) {
	unsigned int tailleEntete;
	unsigned int largeur;
	unsigned int hauteur;
	unsigned short plan; 
	unsigned short profondeur; 
	unsigned int compression;
	unsigned int tailleImage;
	unsigned int resolutionHorizontale;
	unsigned int resolutionVerticale;
	unsigned int nombreCouleurs; 
	unsigned int nombreCouleursImportantes; 
} ImageEntete;

typedef struct __attribute__((__packed__)) {
	unsigned char B; 
	unsigned char V; 
	unsigned char R; 
	unsigned char reserve; 
} CouleurPallete;



