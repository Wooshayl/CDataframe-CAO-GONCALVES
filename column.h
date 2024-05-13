
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
void supprimer_colonne(Colonne **colonne);
void print_col(Colonne* colonne);
int nombre_occurence_valeur(Colonne* colonne, int valeur);
int retourne_valeur_a_x(Colonne* colonne, int x);
int nombre_occurence_superieur(Colonne* colonne, int valeur);
int nombre_occurence_inferieur(Colonne* colonne, int valeur);
#endif //CDDATAFRAME_COLUMN_H
