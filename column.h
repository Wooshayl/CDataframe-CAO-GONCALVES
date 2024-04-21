
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
void print_col(Colonne* colonne);
int retourne_valeur_a_x(Colonne* colonne, int x);
int inserer_valeur(Colonne* colonne, int valeur);


#endif //CDDATAFRAME_COLUMN_H
