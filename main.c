#include <stdio.h>
#include <stdlib.h>
#include "colonne.h"
#include "cdataframe.h"

int main() {
    //Creation d'une CDataFrame:
    printf("Combien de colonnes voulez-vous ?");
    int taille=0;
    scanf("%d", &taille);
    Colonne** Exemple_CDataFrame1 = remplissage_utilisateur_CDataframe(taille);

    //Affichage des deux CDataFrame
    affichage_cdatatframe(Exemple_CDataFrame1, taille);
    //affichage_cdatatframe(Exemple_CDataFrame2);
    printf("-----------------------fin\n");
    //----Modifications----
    ajouter_ligne_CDataframe(Exemple_CDataFrame1, 5, taille);
    affichage_cdatatframe(Exemple_CDataFrame1, taille);
    renommer_titre(Exemple_CDataFrame1, 0);
    affichage_cdatatframe(Exemple_CDataFrame1, taille);

    //Afficher infos:
    afficher_nombre_ligne(Exemple_CDataFrame1);
    printf("ok c bon baka");
    afficher_nom_colonne(Exemple_CDataFrame1, taille);
}
