#include "column.h"
#include <stdlib.h>

Colonne *creer_colonne(char* titre){
    Colonne *nouvelle_colonne = (Colonne *)malloc(sizeof(Colonne));;
    nouvelle_colonne->titre = titre;
    nouvelle_colonne->donnees = NULL;
    nouvelle_colonne->taille_physique = 255;
    nouvelle_colonne->taille_logique = 0;
    return nouvelle_colonne;
}
int inserer_valeur(Colonne* colonne, int valeur){
    if(colonne == NULL){
        colonne->donnees = (int *) malloc(255 * sizeof(int));
        if (colonne->donnees == NULL) {
            return 0;
        }
        colonne->donnees[colonne->taille_logique] = valeur;
        colonne->taille_logique = 1;
        return 1;
    } else if(colonne->taille_logique >= colonne->taille_physique){
        colonne->taille_physique += REALOC_SIZE;
        colonne->donnees = (int *)realloc(colonne->donnees, colonne->taille_physique * sizeof(int));
        if (colonne->donnees == NULL) {
            return 0;
        }
        colonne->donnees[colonne->taille_logique] = valeur;
        colonne->taille_logique +=1;
        return 1;
    } else{
        colonne->donnees[colonne->taille_logique] = valeur;
        colonne->taille_logique +=1;
        return 1;
    }
}
