#ifndef PPM_IO_H
#define PPM_IO_H

// Structure d'un pixel

typedef struct {
    int r, g, b;
} Pixel;

// Structure d'une image PPM (P3)

typedef struct {
    char version[3];
    int largeur;     // nombre de colonnes
    int hauteur;     // nombre de lignes 
    int max_val;     // valeur maximale (255)
    Pixel **pixels;  // matrice [hauteur][largeur] de pixels
} ImagePPM;

// Prototypes des fonctions d'E/S

ImagePPM* lirePPM(const char* nom_fichier);
void ecrirePPM(const char* nom_fichier, const ImagePPM* image);
void libererImage(ImagePPM* image);

#endif