#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_io.h"
#include "operations.h"

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
/*
  Fonce ou eclaircit les pixels ayant une couleur dominante donnee.
  img image a modifier
  couleur 'R', 'G' ou 'B'
  valeur intensite (+ pour foncer, - pour eclaircir)
*/

// Fonctions de base

void appliquer_dominante(ImagePPM *img, char couleur, int valeur) {
    if (!img || !img->pixels) return;

    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel *p = &img->pixels[i][j];
            int r = p->r, g = p->g, b = p->b;
            int max_val = (r > g && r > b) ? 'R' : (g > b ? 'G' : 'B');

            if (toupper(couleur) == max_val) {
                p->r = CLAMP(p->r + valeur, 0, img->max_val);
                p->g = CLAMP(p->g + valeur, 0, img->max_val);
                p->b = CLAMP(p->b + valeur, 0, img->max_val);
            }
        }
    }
}

// Convertit une image couleur en niveaux de gris

void convertir_en_gris(ImagePPM *img) {
    if (!img || !img->pixels) return;

    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel *p = &img->pixels[i][j];
            int gris = (p->r + p->g + p->b) / 3;
            p->r = p->g = p->b = gris;
        }
    }
}

//  Cree le negatif d'une image (inverse les couleurs).

void creer_negatif(ImagePPM *img) {
    if (!img || !img->pixels) return;

    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel *p = &img->pixels[i][j];
            p->r = img->max_val - p->r;
            p->g = img->max_val - p->g;
            p->b = img->max_val - p->b;
        }
    }
}

// Afficher la taille d'une image. 
void afficher_taille(const ImagePPM *img) {
    if (!img) return;
    printf("%d x %d\n", img->largeur, img->hauteur);
}

// Fonctions avancees

ImagePPM* decouper_image(const ImagePPM *img, int l1, int l2, int c1, int c2) {
   (!img || !img->pixels) return NULL;

   // Bornes correctes
   if (l1 < 0) l1 = 0;
   if (c1 < 0) c1 = 0;
   if (l2 > img->hauteur) l2 = img->hauteur;
   if (c2 > img->largeur) c2 = img->largeur;

   if (l1 >= l2 || c1 >= c2) {
    fprintf(stderr, "Erreur : dimensions invalides pour le decoupage.\n");
    return NULL;

   }

   int new_hauteur = l2 - l1;
   int new_largeur = c2 - c1;

   ImagePPM *decoupe = (ImagePPM*) malloc(sizeof(ImagePPM));
   if (!decoupe) {
    perror("Erreur d'allocation memoire pour la decoupe");
    return NULL;

   }

   // Copie des metadonnees
   snprintf(decoupe->version, 3, "%s", img->version);
   decoupe->largeur = new_largeur;
   decoupe->hauteur = new_hauteur;
   decoupe->max_val = img->max_val;

   // Allocation memoire de la matrice
   decoupe->largeur = (Pixel**) malloc(new_hauteur * sizeof(Pixel*));
   if (!decoupe->pixels) {
    perror("Erreur d'allocation lignes decoupe");
    free(decoupe);
    return NULL;
   }

   for (int i = 0; i < new_hauteur; i++) {
    decoupe->pixels[i] = (Pixel*) malloc(new_largeur * sizeof(Pixel));
    if (!decoupe->pixels[i]) {
        perror("Erreur d'allocation colonnes decoupe");
        for (int j = 0; j < i; j++) free(decoupe->pixels[j]);
        free(decoupe->pixels);
        free(decoupe);
        return NULL;
    }

    // Copie ligne par ligne
    for (int j = 0; j < new_largeur; j++) {
        decoupe->pixels[i][j] = img->pixels[l1 + i][c1 + j];
    }
   }
   return decoupe;

}


//  Fonction utilitaire : médiane d’un tableau de 9 valeurs ----------
static int median9(int *values) {
    // Tri par bulle simple
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 - i; j++) {
            if (values[j] > values[j + 1]) {
                int tmp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = tmp;
            }
        }
    }
    return values[4]; // valeur médiane
}

/**
 *  Applique un filtre médian 3x3 à l’image donnée.
 *  img ImagePPM à filtrer (modifiée en place)
 */
void appliquer_filtre_median(ImagePPM *img) {
    if (!img || !img->pixels) return;

    int h = img->hauteur;
    int w = img->largeur;

    // Crée une copie pour ne pas altérer les données pendant le filtrage
    Pixel **copie = (Pixel **)malloc(h * sizeof(Pixel *));
    for (int i = 0; i < h; i++) {
        copie[i] = (Pixel *)malloc(w * sizeof(Pixel));
        for (int j = 0; j < w; j++) {
            copie[i][j] = img->pixels[i][j];
        }
    }

    // Parcours de tous les pixels
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int r[9], g[9], b[9], count = 0;

            // voisinage 3×3
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int ny = y + dy;
                    int nx = x + dx;

                    if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
                        Pixel p = copie[ny][nx];
                        r[count] = p.r;
                        g[count] = p.g;
                        b[count] = p.b;
                    } else {
                        // bord : répéter le pixel courant
                        Pixel p = copie[y][x];
                        r[count] = p.r;
                        g[count] = p.g;
                        b[count] = p.b;
                    }
                    count++;
                }
            }

            img->pixels[y][x].r = median9(r);
            img->pixels[y][x].g = median9(g);
            img->pixels[y][x].b = median9(b);
        }
    }

    // Libération de la copie
    for (int i = 0; i < h; i++) free(copie[i]);
    free(copie);
}
