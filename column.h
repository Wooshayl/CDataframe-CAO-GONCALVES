
#ifndef CDDATAFRAME_COLUMN_H
#define CDDATAFRAME_COLUMN_H
#define REALOC_SIZE 256

typedef struct {
    char *titre;
    int *donnees;
    int taille_physique;
    int taille_logique;
}Colonne;

Colonne *creer_colonne(char* titre);
int inserer_valeur(Colonne* colonne, int valeur);


#endif //CDDATAFRAME_COLUMN_H
