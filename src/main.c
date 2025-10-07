#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "ppm_io.h"

// =================================
// Declarations des fonctions
//==================================
void commande_size();
void commande_gris();
void commande_neg();
void commande_dom();
void commande_cut();
void commande_fil();

// ================================
// Fomction principale 
// ================================

int main() {
    char commande[50];
    printf("Application de traitement d'images PPM  TPE1. \n");


    while (1) {
        printf("ppmviewer > ");
        scanf("%s", commande);

        if (strcmp(commande, "quit") == 0) {
            printf("Fermeture du programme...\n");
            break;
        }

        else if (strcmp(commande, "size") == 0) commande_size();
        else if (strcmp(commande, "gris") == 0) commande_gris();
        else if (strcmp(commande, "neg") == 0) commande_neg();
        else if (strcmp(commande, "dom") == 0) commande_dom();
        else if (strcmp(commande, "cut") == 0) commande_cut();
        else if (strcmp(commande, "fil") == 0) commande_fil();
        else {
            printf("Commande inconnue : %s\n", commande);
            printf("Commandes disponibles : dom, gris, neg, cut, fil, size, quit\n");
        }
    }

    return 0;
}

void commande_size() {
    char nomFichier[100];
    scanf("%s", nomFichier);

    ImagePPM *img = lirePPM(nomFichier);
    if (img == NULL) {
        printf("Erreur : fichier introuvable. \n");
        return;
    }

    afficher_taille(img);
    libererImage(img);
}

void commande_gris() {
    char nomFichier[100];
    scanf("%s", nomFichier);

    ImagePPM *img = lirePPM(nomFichier);
    if (img == NULL) {
        printf("Erreur : fichier introuvable. \n");
        return;
    }

    convertir_en_gris(img);

    char nouveauNom[120];
    sprintf(nouveauNom, "%s_gris.ppm", nomFichier);
    ecrirePPM(nouveauNom, img);
    printf("Operation effectuee ; %s cree. \n", nouveauNom);

    libererImage;
}

void commande_neg() {
    char src[100], dest[100];
    scanf("%s %s", src, dest);

    ImagePPM *img = lirePPM(src);
    if (img == NULL) {
        printf("Erreur : fichier introuvable. \n");
        return;
    }

    creer_negatif(img);
    ecrirePPM(dest, img);
    printf("Operation effectuee ; %s cree.  \n", dest);


    libererImage(img);
}

void commande_dom() {
    char couleur;
    int val;
    char nomFichier[100];
    scanf(" %c %d %s", &couleur, &val, nomFichier);

    ImagePPM *img = lirePPM(nomFichier);
    if (img == NULL) {
        printf("Erreur : fichier introuvable. \n");
        return;
    }

    appliquer_dominante(img, couleur, val);

    char nouveauNom[120];
    sprintf(nouveauNom, "%s_dom.ppm", nomFichier);
    ecrirePPM(nouveauNom, img);
    printf("Operation effectuee ; %s cree. \n", nouveauNom);

    libererImage(img);
}

void commande_cut() {
    char src[100], dest[100];
    int l1, l2, c1, c2;
    scanf("%s %d %d %d %d %s", src, &l1, &l2, &c1, &c2, dest);

    ImagePPM *img = lirePPM(src);
    if (img == NULL) {
        printf("Erreur : fichier introuvable. \n");
        return;
    }

    ImagePPM *decoupe = decouper_image(img, l1, l2, c1, c2);
    if (decoupe == NULL) {
        printf("Erreur : parametres de decoupe invalides. \n");
        libererImage(img);

        return;
    }

    ecrirePPM(dest, decoupe);
    printf("Operation effectuee ; %s cree. \n", dest);

    libererImage(img);
    libererImage(decoupe);
}

void commande_fil() {
    char src[100], dest[100];
    scanf("%s %s", src, dest);

    ImagePPM *img = lirePPM(src);
    if (img == NULL) {
        printf("Erreur : fichier introuvable. \n");
        return;
    }

    appliquer_filtre_median(img);
    ecrirePPM(dest, img);
    printf("Operation effectuee ; %s cree. \n", dest);

    libererImage(img);
}