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
    printf("[4] Supprimer la dernière colonne du CDataframe\n");
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
            supprimer_colonne_CDataframe(&CDataFrame, &taille);
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
            getchar();
            if (existence_valeur(CDataFrame, valeur, taille))printf("Elle existe ! %d\n", existence_valeur(CDataFrame, valeur, taille));
            else printf("Elle n'existe pas ! \n");
            menu_global(CDataFrame, taille);
        case 7:{
            int ligne_c7=0,colonne_c7=0;
            COL_TYPE valeur_c7;
            valeur_c7.int_value = 0;
            char* string_uti;
            printf("Choisissez une colonne:\n");
            scanf("%d", &colonne_c7);
            getchar();
            printf("Choisissez une ligne:\n");
            scanf("%d", &ligne_c7);
            getchar();
            switch (CDataFrame[colonne_c7]->type_colonne){
                case UINT:
                    printf("Attention, colonne de type Entier Naturel!");
                    printf("\nChoisissez une valeur qui correspond au type de la colonne:\n");
                    scanf("%d", &(valeur_c7.uint_value));
                    getchar();
                    break;
                case INT:
                    printf("Attention, colonne de type Entier Relatif!");
                    printf("\nChoisissez une valeur qui correspond au type de la colonne:\n");
                    scanf("%d", &(valeur_c7.int_value));
                    getchar();
                    break;
                case CHAR:
                    printf("Attention, colonne de type Caractère");
                    printf("\nChoisissez une valeur qui correspond au type de la colonne:\n");
                    scanf("%c", &(valeur_c7.char_value));
                    getchar();
                    break;
                case FLOAT:
                    printf("Attention, colonne de type Flottant");
                    printf("\nChoisissez une valeur qui correspond au type de la colonne:\n");
                    scanf("%f", &(valeur_c7.float_value));
                    getchar();
                    break;
                case DOUBLE:
                    printf("Attention, colonne de type Double");
                    printf("\nChoisissez une valeur qui correspond au type de la colonne:\n");
                    scanf("%lf", &(valeur_c7.double_value));
                    getchar();
                    break;
                case STRING:
                    printf("Attention, colonne de type Chaine de Caractère");
                    gets(string_uti);
                    break;
                default:
                    printf("Erreur 1");
                    exit(1);
            }
            changement_valeur(CDataFrame,colonne_c7,ligne_c7,&valeur_c7);
            menu_global(CDataFrame, taille);}
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
void tri_menu(Colonne** CDataFrame, int taille) {
    int test;
    printf("Que voulez-vous faire :\n[1] Afficher le Dataframe par index\n");
    printf("[2] Trier tout le Dataframe par ordre croissant\n");
    printf("[3] Trier tout le Dataframe par ordre décroissant\n");
    printf("[4] Trier seulement 1 colonne au choix \n");
    printf("[5] Mettre à jour index d'une colonne\n");
    printf("[6] Effacer l'index d'une colonne\n");
    printf("[7] Check l'index d'une colonne au choix\n");
    scanf("%d", &test);
    getchar();
    switch (test) {
        case 1: {
            int ok = 1;
            for (int i = 0; i < taille; i++) {
                if (CDataFrame[i]->index == NULL || CDataFrame[i]->valid_index != 1){
                    printf("Le Dataframe n'est pas trié et ne peux pas etre afficher par l'index\n");
                    ok = 0;
                    break;
                }
            }
            if (ok == 1) {
                for (int i = 0; i < taille; i++) {
                    afficher_col_index(CDataFrame[i]);
                }
            }
            menu_global(CDataFrame, taille);
        }
        case 2:
            for (int i = 0; i < taille; i++){
                sort(CDataFrame[i],ASC);
            }
            menu_global(CDataFrame, taille);
        case 3:
            for (int i = 0; i < taille; i++){
                sort(CDataFrame[i],DESC);
            }
            menu_global(CDataFrame, taille);
        case 4: {
            int choix_ordre=0, choix_colonne=0;
            printf("De quelle ordre voulez vous triez? (0 = croissant, 1 = décroissant)\n");
            scanf("%d", &choix_ordre);
            getchar();
            printf("Quelle colonne voulez vous trier?\n");
            scanf("%d ", &choix_colonne);
            getchar();
            sort(CDataFrame[choix_colonne], choix_ordre);
            menu_global(CDataFrame, taille);
        }
        case 5:
            for (int i = 0; i < taille; i++) {
                update_index(CDataFrame[i]);
            }
            menu_global(CDataFrame, taille);
        case 6:{
            int choix_eff=0;
            printf("De quelle ordre voulez vous effacer l'index?\n");
            scanf("%d", &choix_eff);
            efface_index(CDataFrame[choix_eff]);
            menu_global(CDataFrame, taille);
        }
        case 7: {
            int choix_check = 0;
            printf("De quelle colonne voulez vous verifier l'index?\n");
            scanf("%d", &choix_check);
            check_index(CDataFrame[choix_check]);
            menu_global(CDataFrame, taille);
        }
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
    printf("[2] Options de modification du dataframe\n");
    printf("[3] Analyses et Statistiques sur le dataframe\n");
    printf("[4] Options de Tri sur le dataframe\n");
    printf("[5] Quitter l'application\n");
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
            tri_menu(CDataFrame, taille);
            menu_global(CDataFrame, taille);
        case 5:
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
