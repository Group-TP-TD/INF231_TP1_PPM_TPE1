#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "ppm_io.h"

// Fait varier la luminosite des pixels selon la couleur dominante
void appliquer_dominante(ImagePPM *img, char couleur, int valeur);

// Convertir une image en niveaux de gris
void convertir_en_gris(ImagePPM *img);

// Cree le negatif d'une image
void creer_negatif(ImagePPM *img);

// Afficher la taille d'une image (largeur x hauteur)
void afficher_taille(const ImagePPM *img);

// Decoupe une partie de l'image (lignes l1 a l2, colonnes c1 a c2)
ImagePPM* decouper_image(const ImagePPM *img, int l1, int l2, int c1, int c2);

// Applique un filtre median sur une image (option avancee)
void appliquer_filtre_median(ImagePPM *img);

#endif