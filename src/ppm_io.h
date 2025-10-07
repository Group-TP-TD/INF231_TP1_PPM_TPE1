typedef struct {
    int largeur;
    int hauteur;
    int max_val;
    unsigned char *pixels;  // ou un tableau [hauteur][largeur][3]
} ImagePPM;
