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

// ====================================
// Fonctions avancees
// ====================================

ImagePPM* decouper_image(const ImagePPM *img, int l1, int l2, int c1, int c2) {
    // TODO: a implementer par membre 4
    return NULL;
}

void appliquer_filtre_median(ImagePPM *img) {
    // TODO: a implementer par membre 4
}