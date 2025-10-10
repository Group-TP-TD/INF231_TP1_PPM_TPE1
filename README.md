# INF231_TP1_PPM_TPE1
Projet de traitement d’images PPM (INF231 - Université de Yaoundé 1)
L’objectif de ce projet est de concevoir, en langage C, une application permettant de lire, manipuler et sauvegarder des images au format PPM (Portable PixMap – version P3).

L’application s’exécute en ligne de commande (CLI) et permet d’appliquer plusieurs traitements sur les images :
Afficher la taille d’une image,
Convertir en niveaux de gris,
Créer le négatif d’une image,
Modifier la luminosité d’une couleur dominante (rouge, vert ou bleu),
Découper une partie d’une image,
Appliquer un filtre médian (suppression de bruit).

Le projet a ete diviser en 5 pour les 5 membres du groupe
Membre 1 NGUEFACK TIOGUIM ULRICH BRYAN
**Charger de l'interface principale main.c**
- Création de la boucle principale de la CLI.
- Gestion des commandes utilisateur.
- Intégration des fonctions de traitement.
- Formatage des messages de succès et d’erreur

Membre 2 KIADJEU NGOUMEZON LADIE DIANA
Charger du module ppm_io.c / ppm_io.h
- Lecture et écriture des images PPM.
- Définition de la structure ImagePPM.
- Gestion des erreurs de fichiers.
- Nettoyage mémoire (libererImage).

Membre 3 DOMSU NIMATCHA LYDIE ESTHER
Charger du module operations.c / operations.h
- Fonctions de base : gris, négatif, dominante, taille.
- Intégration avec la structure ImagePPM.
- Gestion de la saturation et des bornes (0–255).

Membre 4 AYIMELE MOGHELA URIE JIZREEL 
Charger du module fonctions avancées : découpe & filtre médian
- Implémentation de decouper_image().
- Implémentation de appliquer_filtre_median().
- Tests unitaires pour vérifier la cohérence

Membre 5 LIENOU KAMGANG STEPHY LAURE
Charger du module interface utilisateur (CLI) et intégration finale
- Création du menu interactif (while principal).
- Appels vers les fonctions des autres modules.
- Messages d’erreurs clairs et formatés.
- Vérifications d’arguments et chemins d’accès.

Structure du projet
INF231_TP_PPM/
│
├── src/                        # Code source
│   ├── main.c                  # Interface utilisateur (CLI)
│   ├── ppm_io.c / ppm_io.h     # Lecture / écriture d’images PPM
│   ├── operations.c / operations.h # Fonctions de traitement d’image
│   ├── utils.c / utils.h       # Fonctions utilitaires (futures extensions)
│
├── images/                     # Dossier des fichiers PPM (entrée/sortie)
│   ├── test.ppm
│   ├── test_gris.ppm
│   ├── test_neg.ppm
│
├── README.md                   # Documentation du projet
└── ppmviewer                   # Exécutable généré après compilation

Compilation
La compilation est faites manuelement 
gcc src/*.c -o ppmviewer

Exécution
./ppmviewer

| Commande                            | Description                           | Exemple                       |                                                |                            |
| ----------------------------------- | ------------------------------------- | ----------------------------- | ---------------------------------------------- | -------------------------- |
| `size <fichier>`                    | Affiche la taille de l’image.         | `size images/test.ppm`        |                                                |                            |
| `gris <fichier>`                    | Crée une version en niveaux de gris.  | `gris images/test.ppm`        |                                                |                            |
| `neg <fichier>`                     | Crée le négatif de l’image.           | `neg images/test.ppm`         |                                                |                            |
| `dom <R                             | G                                     | B> <valeur> <fichier>`        | Modifie la luminosité d’une couleur dominante. | `dom R 30 images/test.ppm` |
| `cut <fichier> <l1> <l2> <c1> <c2>` | Découpe une sous-image rectangulaire. | `cut images/test.ppm 0 2 0 2` |                                                |                            |
| `fil <fichier>`                     | Applique un filtre médian.            | `fil images/test.ppm`         |                                                |                            |
| `quit`                              | Quitte le programme.                  | —                             |                


Organisation de développement

Phase 1 — Création de la structure du projet
Création des dossiers src/ et images/
Définition de la structure ImagePPM et des prototypes dans operations.h

Phase 2 — Implémentation modulaire
Chaque membre travaille sur un fichier spécifique dans src/
Compilation séparée des modules
Tests unitaires indépendants pour chaque opération

Phase 3 — Intégration
Le membre 5  relie toutes les fonctions dans main.c
Mise au point de la CLI avec gestion des erreurs et messages utilisateurs

Phase 4 — Tests finaux
Création de plusieurs fichiers .ppm dans images/
Test de toutes les commandes (gris, neg, dom, cut, fil)
Vérification de la cohérence des résultats

Consignes pour exécuter correctement le projet
Se placer dans la racine du projet.
Compiler avec gcc src/*.c -o ppmviewer
Créer un fichier PPM dans images/
Lancer ./ppmviewer
Taper les commandes de test (une à la fois)
Vérifier les nouveaux fichiers créés dans images/

Tous les modules sont indépendants et peuvent être testés séparément.
Le projet respecte une structure modulaire claire, favorisant la réutilisation et la maintenance.
Les erreurs sont gérées proprement (fichier introuvable, indices invalides, mémoire libérée).
