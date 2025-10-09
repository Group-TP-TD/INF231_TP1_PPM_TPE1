#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ppm_io.h"

// Ignore les commentaires et espaces dans un fichier PPM

static void ignorer_commentaires_et_espaces(FILE *f) {
    int c;
    do {
        while ((c = fgetc(f)) != EOF && isspace(c));
        if (c == '#') {
            while ((c = fgetc(f)) != EOF && c != '\n');
        } else {
            ungetc(c, f);
            break;
        }
        while (c != EOF);
    }
}

// Lit une image PPM (P3) et la charge en memoire.

ImagePPM* lirePPM(const char* nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    ImagePPM *image = (ImagePPM*) malloc(sizeof(ImagePPM));
    if (image == NULL) {
        perror("Erreur d'allocation memoire pour l'image");
        fclose(fichier);
        
        return NULL;
    }

    fscanf(fichier, "%2s", image->version);
    if (strcmp(image->version, "P3") != 0) {
        fprintf(stderr, "Erreur : format non pris en charge (P3 attendu)\n");
        free(image);
        fclose(fichier);
        return NULL;
    }

    image->pixels = (Pixel**) malloc(image->hauteur * sizeof(Pixel*));
    if (image->pixels == NULL) {
        perror("Erreur d'allocation lignes");
        free(image);
        fclose(fichier);
        return NULL;
    }

    for (int i = 0; i < image->hauteur; i++) {
        image->pixels[i] = (Pixel*) malloc (image->largeur * sizeof(Pixel));
        if (image->pixels[i] == NULL) {
            perror("Erreur d'allocation colonnes");
            for (int j = 0; j < i; j++) free(image->pixels[j]);
            free(image->pixels);
            free(image);
            fclose(fichier);
            return NULL;
        }
    }

    for (int i = 0; i < image->largeur; i++) {
        for (int j = 0; j < image-> largeur; j++) {
            if (fscanf(fichier, "%d %d %d", &image->pixels[i][j].r, &image->pixels[i][j].g, &image->pixels[i][j].b) != 3) {
                fprintf(stderr, "Erreur : donnees de pixel corrompues.\n");
                for (int k = 0; k < image->hauteur; k++) free(image->pixels[k]);
                free(image->pixels);
                free(image);
                fclose(fichier);

                return NULL;
            }
        }
    }

    fclose(fichier);
    return image;
}

// Ecrit une image PPM (P3) dans un fichier.

void ecrirePPM(const char* nom_fichier, const ImagePPM* image) {
    if (image == NULL || image->pixels == NULL) {
        fprintf(stderr, "Erreur : structure image invalide.\n");
        return;
    }

    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier de sortie");
        return;
    }

    fprintf(fichier, "P3\n");
    fprintf(fichier, "%d %d\n", image->largeur, image->hauteur);
    fprintf(fichier, "%d\n", image->max_val);

    for (int i = 0; i < image->hauteur; i++) {
        for (int j = 0; j < image->largeur; j++) {
            fprintf(fichier, "%d %d %d ", &image->pixels[i][j].r, &image->pixels[i][j].g, &image->pixels[i][j].b);
        }
        fprintf(fichier, "\n");
    }

    fclose(fichier);
    printf("Image sauvegardee dans '%s' .\n", nom_fichier );
}

// libere toute la memoire utilisee par une image

void libererImage(ImagePPM *image) {
    if (image == NULL) return;
    for (int i = 0; i < image->hauteur; i++) free(image->pixels[i]);
    free(image->pixels);
    free(image;)
}
