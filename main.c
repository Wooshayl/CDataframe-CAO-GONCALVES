/*======================================================================================================================
                                CDataframe par Lilian CAO et Valentin GONCALVES
Ce fichier permet de mettre en relation tout les autres fichiers pour une utilisation efficace du programme.
======================================================================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "colonne.h"
#include "cdataframe.h"
#include "menu.h"


int main() {
    int test, taille_cdataframe;
    printf("Bienvue dans le Cdataframe CAO/GONCALVES !\n");
    printf("Cette application vous permettra de stocker et de manipuler des données.\n");
    printf("Combien de colonnes voulez-vous ?\n");
    scanf("%d", &taille_cdataframe);
    Colonne **Cdataframe = remplissage_utilisateur_CDataframe(taille_cdataframe);
    menu_global(Cdataframe, taille_cdataframe);


    return 0;
}
