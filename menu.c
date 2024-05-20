/*======================================================================================================================
                                CDataframe par Lilian CAO et Valentin GONCALVES
Ce fichier contient toutes fonctions pour pouvoir utiliser le menu et tester les fonctionnalités du projet.
======================================================================================================================*/

#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "colonne.h"
#include "cdataframe.h"

/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : option_affichage_dataframe
Cette fonction est un menu qui contient toutes les fonctions sur l'affichage.
Elle prend en paramètre le Dataframe et sa taille.
 Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void option_affichage_dataframe(Colonne** CDataFrame, int taille){
    int test;
    printf("Que voulez-vous faire :\n[1]Affichage de tout le Dataframe\n[2]Afficher les n premières lignes\n");
    printf("[3]Afficher les n premières colonnes\n");
    scanf("%d", &test);
    getchar();
    switch (test) {
        case 1:
            affichage_cdatatframe(CDataFrame, taille);

            menu_global(CDataFrame, taille);
        case 2:
            affichage_cdatatframe_ligne_utilisateur(CDataFrame, taille);
            menu_global(CDataFrame, taille);
        case 3:
            affichage_cdatatframe_colonne_utilisateur(CDataFrame);
            menu_global(CDataFrame, taille);
        default:
            printf("Ce choix n'est pas proposé, voulez-vous réessayer ?\n[1]Oui\t[2]Non\n");
            scanf("%d", &test);
            if(test==1)option_affichage_dataframe(CDataFrame, taille);
            else{
                printf("Au revoir.");
                break;
            }
            menu_global(CDataFrame, taille);
    }


}



/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : modification_Dataframe
Cette fonction est un menu qui contient toutes les fonctions sur la modification du Dataframe.
Elle prend en paramètre le Dataframe et sa taille.
 Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void modification_Dataframe(Colonne** CDataFrame, int taille){
    int test, position;
    char valeur[255];
    printf("Que voulez-vous faire :\n[1]Ajouter une ligne de valeurs au CDataframe\n");
    printf("[2]Supprimer la dernière ligne de valeurs du CDataframe\n");
    printf("[3] Ajouter une colonne au CDataframes\n");
    printf("[4] Supprimer une colonne du CDataframe\n");
    printf("[5] Renommer le titre d’une colonne du CDataframe\n");
    printf("[6] Vérifier l’existence d’une valeur (recherche) dans le CDataframe\n");
    printf("[7] Remplacer la valeur se trouvant dans une cellule du CDataframe\n");
    printf("[8] Afficher les noms des colonnes\n");
    scanf("%d", &test);
    getchar();
    switch (test) {
        case 1:
            ajouter_ligne_CDataframe(CDataFrame,taille);
            menu_global(CDataFrame, taille);
        case 2:
            supprimer_ligne_CDataframe(CDataFrame, taille);
            menu_global(CDataFrame, taille);
        case 3:
            ajouter_colonne_CDataframe(&CDataFrame, &taille);
            menu_global(CDataFrame, taille);
        case 4:
            //supprimer_colonne_CDataframe(CDataFrame);
            menu_global(CDataFrame, taille);
        case 5:
            printf("Quel est la position de la colonne que vous voulez renommer ?");
            scanf("%d", &position);
            getchar();
            renommer_titre(CDataFrame,position);
            menu_global(CDataFrame, taille);
        case 6:
            printf("Quelle est la valeur dont vous voulez vérifier l'existence ?");
            scanf("%s", valeur);
            if (existence_valeur(CDataFrame, valeur, taille))printf("Elle existe ! \n");
            else printf("Elle n'existe pas ! \n");
            menu_global(CDataFrame, taille);
        case 7:
            //changement_valeur(CDataFrame)
            menu_global(CDataFrame, taille);
        case 8:
            afficher_nom_colonne(CDataFrame,taille);
            menu_global(CDataFrame, taille);
        default:
            printf("Ce choix n'est pas proposé, voulez-vous réessayer ?\n[1]Oui\t[2]Non\n");
            scanf("%d", &test);
            if(test==1)modification_Dataframe(CDataFrame, taille);
            else{
                printf("Au revoir.");
                break;
            }
            menu_global(CDataFrame, taille);
    }
}



/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : analyse_statistique
Cette fonction est un menu qui contient toutes les fonctions sur les analyses statistiques du Dataframe.
Elle prend en paramètre le Dataframe et sa taille.
 Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void analyse_statistique(Colonne** CDataFrame, int taille){
    int test, cpt;
    char valeur[255];
    printf("Que voulez-vous faire :\n[1]Afficher le nombre de lignes\n");
    printf("[2]Afficher le nombre de colonnes\n");
    printf("[3] Nombre de cellules contenant une valeur égale à x\n");
    printf("[4] Nombre de cellules contenant une valeur supérieure à x\n");
    printf("[5] Nombre de cellules contenant une valeur inférieure à x\n");
    scanf("%d", &test);
    getchar();
    switch (test) {
        case 1:
            afficher_nombre_ligne(CDataFrame);
            menu_global(CDataFrame, taille);
        case 2:
            afficher_nombre_colonne(CDataFrame, taille);
            menu_global(CDataFrame, taille);
        case 3:
            printf("Quel est la valeur x que vous voulez comparer ?");
            scanf("%s", valeur);
            cpt = nombre_cellule_x(CDataFrame, valeur, taille);
            printf("Il y a %d valeur(s) égal à %s.",cpt, valeur);
            menu_global(CDataFrame, taille);
        case 4:printf("Quel est la valeur x que vous voulez comparer ?");
            scanf("%s", valeur);
            cpt = nombre_cellule_superieur_x(CDataFrame, valeur, taille);
            printf("Il y a %d valeur(s) supérieur à %s.",cpt, valeur);
            menu_global(CDataFrame, taille);
        case 5:
            printf("Quel est la valeur x que vous voulez comparer ?");
            scanf("%s", valeur);
            cpt = nombre_cellule_inferieur_x(CDataFrame, valeur, taille);
            printf("Il y a %d valeur(s) inférieur à %s.",cpt, valeur);
            menu_global(CDataFrame, taille);
        default:
            printf("Ce choix n'est pas proposé, voulez-vous réessayer ?\n[1]Oui\t[2]Non\n");
            scanf("%d", &test);
            if(test==1)analyse_statistique(CDataFrame, taille);
            else{
                printf("Au revoir.");
                break;
            }
            menu_global(CDataFrame, taille);
    }
}



/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : menu_global
Cette fonction est un menu qui contient les fonctions des autres sous menus.
Elle prend en paramètre le Dataframe et sa taille.
 Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void menu_global(Colonne** CDataFrame, int taille){
    int test;
    printf("Que voulez-vous faire :\n[1]Options d'affichage du dataframe\n");
    printf("[2]Options de modification du dataframe\n");
    printf("[3] Analyses et Statistiques sur le dataframe\n");
    printf("[4] Quitter l'application\n");
    scanf("%d", &test);
    getchar();
    switch (test) {
        case 1:
            option_affichage_dataframe(CDataFrame,taille);
            menu_global(CDataFrame, taille);
        case 2:
            modification_Dataframe(CDataFrame, taille);
            menu_global(CDataFrame, taille);
        case 3:
            analyse_statistique(CDataFrame, taille);
            menu_global(CDataFrame, taille);
        case 4:
            printf("Au revoir");
            exit(0);
        default:
            printf("Ce choix n'est pas proposé, voulez-vous réessayer ?\n[1]Oui\t[2]Non\n");
            scanf("%d", &test);
            if(test==1)menu_global(CDataFrame, taille);
            else{
                printf("Au revoir.");
                break;
            }
            menu_global(CDataFrame, taille);

    }
}
