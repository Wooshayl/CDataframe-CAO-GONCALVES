/*======================================================================================================================
                                CDataframe par Lilian CAO et Valentin GONCALVES
Ce fichier s'occupe de la gestion du CDataframe, il fait appel aux fonctions présentes dans colonne.c et les utilise
 àbon escient afin d'avoir un Dataframe fonctionnel pouvant stocker et traiter tout type de donnée.
======================================================================================================================*/


#include "cdataframe.h"
#include "colonne.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : remplissage_utilisateur_CDataframe
Cette fonction permet à l'utilisateur de remplir le dataframe et donc de pouvoir par la suite utiliser toutes ses
 fonctionnalitées.
 Il prend en paramètre la taille voulut par l'utilisateur.
 Il renvoit le Dataframe si l'exécution est bonne et un entier si ce n'est pas le cas.
----------------------------------------------------------------------------------------------------------------------*/


Colonne** remplissage_utilisateur_CDataframe(int taille){
    Colonne** CDataFrame = (Colonne**)malloc(taille*sizeof(Colonne*));
    int nbr_col, nbr_lig_max=0;
    getchar();
    //Créé une liste pour contenir le type de chaque colonne
    int* liste_choix_types = (int*) malloc(sizeof(int)*taille);
    //On fait une boucle pour crée autant de colonne que l'utilisateur a demandé
    for(int i =0; i < taille; i++) {
        printf("Quel titre voulez-vous pour la colonne %d : ", i);
        char titre[100];
        gets(titre);
        printf("Choisissez le type de votre colonne :\n[1]Entier Naturel [2]Entier Relatif [3]Charactère [4]Floatant [5]Double [6]Chaine de caractère : ");
        int choix_type;
        scanf("%d", &choix_type);
        getchar();
        liste_choix_types[i] = choix_type;
        //On fait un switch qui permet de créer une colonne celon le type choisit par l'utilisateur
        switch (choix_type) {
            case 1:
            {Colonne *colonne = creer_colonne(UINT, titre);
                CDataFrame[i] = colonne;
                break;}
            case 2:
            {Colonne *colonne = creer_colonne(INT, titre);
                CDataFrame[i] = colonne;
                break;}
            case 3:
            {Colonne *colonne = creer_colonne(CHAR, titre);
                CDataFrame[i] = colonne;
                break;}
            case 4:
            {Colonne *colonne = creer_colonne(FLOAT, titre);
                CDataFrame[i] = colonne;
                break;}
            case 5:
            {Colonne *colonne = creer_colonne(DOUBLE, titre);
                CDataFrame[i] = colonne;
                break;}
            case 6:
            {Colonne *colonne = creer_colonne(STRING, titre);
                CDataFrame[i] = colonne;
                break;}
            default:
                printf("Ce type n'existe pas.\n");
                return 0;

        }


    }
    for (int i = 0; i < taille; ++i) {
        printf("Combien de données voulez-vous dans la colonne %d ? ", i);
        int nbr_lig;
        scanf("%d", &nbr_lig);
        getchar();
        if(nbr_lig>nbr_lig_max) {
            nbr_lig_max = nbr_lig;
        }
        switch (liste_choix_types[i]) {
            //On fait un deuxième switch pour que l'utilisateur remplisse le Cdataframe avec les valeurs de son choix
            case 1:
            {for (int j = 0; j < nbr_lig; ++j) {
                    printf("Entrez une valeur : ");
                    unsigned int valeur_ligne;
                    scanf("%ud", &valeur_ligne);
                    getchar();
                    inserer_valeur(CDataFrame[i], &valeur_ligne);
                }
                break;}
            case 2:
            {for (int j = 0; j < nbr_lig; ++j) {
                    printf("Entrez une valeur : ");
                    int valeur_ligne;
                    scanf("%d", &valeur_ligne);
                    getchar();
                    inserer_valeur(CDataFrame[i], &valeur_ligne);
                }
                break;}
            case 3:
            {for (int j = 0; j < nbr_lig; ++j) {
                    printf("Entrez une valeur : ");
                    char valeur_ligne;
                    scanf("%c", &valeur_ligne);
                    getchar();
                    inserer_valeur(CDataFrame[i], &valeur_ligne);
                }
                break;}
            case 4:
            {for (int j = 0; j < nbr_lig; ++j) {
                    printf("Entrez une valeur : ");
                    float valeur_ligne;
                    scanf("%f", &valeur_ligne);
                    getchar();
                    inserer_valeur(CDataFrame[i], &valeur_ligne);
                }
                break;}
            case 5:
            {for (int j = 0; j < nbr_lig; ++j) {
                    printf("Entrez une valeur : ");
                    double valeur_ligne;
                    scanf("%lf", &valeur_ligne);
                    getchar();
                    inserer_valeur(CDataFrame[i], &valeur_ligne);
                }
                break;}
            case 6:
            {for (int j = 0; j < nbr_lig; ++j) {
                    printf("Entrez une valeur : ");
                    char buff[256];
                    gets(buff);
                    char *valeur_ligne=(char*) malloc(strlen(buff)+1);
                    strcpy(valeur_ligne, buff);
                    inserer_valeur(CDataFrame[i], valeur_ligne);
                }
                break;}
            default:
                return 0;

        }
    }
    //On fait une dernière boucle pour que chaque colonne est le même nombre de lignes en remplissant avec des NULL
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i]->taille_logique < nbr_lig_max){
            for (int j = CDataFrame[i]->taille_logique; j < nbr_lig_max; ++j) {
                void* valeur_nul=NULL;
                inserer_valeur(CDataFrame[i],valeur_nul);
            }
        }

    }
    return CDataFrame;
}



/*----------------------------------------------------------------------------------------------------------------------
                                          FONCTION : remplissage_dure
Cette fonction remplit simplement un Cdataframe en dure.
 Elle prend en paramètre le Dataframe qu'il faut remplir.
 ELle ne renvoit rien pusiqu'elle le remplit dynamiquement
----------------------------------------------------------------------------------------------------------------------*/


void remplissage_dure(Colonne** CDataFrame){
    Colonne *ma_colonne = creer_colonne(INT,"Ma colonne");
    int a=1, b=2, c=3, d=5;
    inserer_valeur(ma_colonne, &a);
    inserer_valeur(ma_colonne, &b);
    inserer_valeur(ma_colonne, &c);
    inserer_valeur(ma_colonne, &d);
    float a1=1.1, b2=2.2, c3=3.3, d4=5.4;
    Colonne *ma_colonne2 = creer_colonne(FLOAT,"Ma colonne 2");
    inserer_valeur(ma_colonne2, &a1);
    inserer_valeur(ma_colonne2, &b2);
    inserer_valeur(ma_colonne2, &c3);
    inserer_valeur(ma_colonne2, &d4);
    CDataFrame[0] = ma_colonne;
    CDataFrame[1] = ma_colonne2;
}



/*----------------------------------------------------------------------------------------------------------------------
                                          FONCTION : affichage_cdatatframe
Cette fonction a simplement pour but d'afficher un Cdataframe.
 Elle prend en paramètre le Cdataframe à afficher et la taille de ce Dataframe.
 Elle ne renvoit rien puisque son but est d'afficher.
----------------------------------------------------------------------------------------------------------------------*/
void affichage_cdatatframe(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        //Vérifie s'il n'est pas nul
        if(CDataFrame[i] != NULL){
            afficher_colonne(CDataFrame[i]);
            printf("\n");
        }
    }
}


/*----------------------------------------------------------------------------------------------------------------------
                                FONCTION : affichage_cdatatframe_ligne_utilisateur
Cette fonction a pour but d'afficher les n premières lignes du dataframe avec n choisit par l'utilisateur.
Elle prend en paramètre le Dataframe à afficher et sa taille.
Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void affichage_cdatatframe_ligne_utilisateur(Colonne** CDataFrame, int taille){
    int valeur_ligne_utilisateur;
    char str[256];
    printf("Jusqu'à quelles lignes voulez-vous ?");
    scanf("%d", &valeur_ligne_utilisateur);
    for (int i = 0; i < taille; ++i) {
        //Vérifie qu'il n'y ai pas d'erreurs de taille.
        if(valeur_ligne_utilisateur > CDataFrame[i]->taille_logique)return;
        if(CDataFrame[i] != NULL){
            printf("%s", CDataFrame[i]->titre);
            for (int j = 0; j < valeur_ligne_utilisateur; ++j) {
                convertir_valeur(CDataFrame[i],j,str, 256);
                printf("[%d]\t%s\t\t", j, str);
            }
            printf("\n");
        }
    }
}


/*----------------------------------------------------------------------------------------------------------------------
                                FONCTION : affichage_cdatatframe_colonne_utilisateur
Cette fonction a pour but d'afficher les n premières colonnes du dataframe avec n choisit par l'utilisateur.
Elle prend en paramètre le Dataframe à afficher.
Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void affichage_cdatatframe_colonne_utilisateur(Colonne** CDataFrame){
    int valeur_colonne_utilisateur;
    printf("Jusqu'à quelles colonnes voulez-vous ?");
    scanf("%d", &valeur_colonne_utilisateur);
    for (int i = 0; i < valeur_colonne_utilisateur; ++i) {
        if(CDataFrame[i] != NULL){
            afficher_colonne(CDataFrame[i]);
            printf("\n");
        }
    }

}


/*----------------------------------------------------------------------------------------------------------------------
                                FONCTION : ajouter_ligne_CDataframe
Cette fonction permet à l'utilisateur d'ajouter une ligne dans le Cdataframe et de remplir chaque colonnes avec les
 valeurs de son choix.
 Elle prend en paramètre le Dataframe et sa taille.
 Elle ne renvoit rien pusiqu'elle modifie dynamiquement.
----------------------------------------------------------------------------------------------------------------------*/
void ajouter_ligne_CDataframe(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        switch (CDataFrame[i]->type_colonne) {
            //Switch pour remplir chaque colonne avec le bon type
            case UINT:{
                unsigned int valeur_temporaire;
                printf("||Colonne de type ENTIER NATUREL||\tInsérez une valeur : ");
                scanf("%ud", &valeur_temporaire);
                getchar();
                inserer_valeur(CDataFrame[i],&valeur_temporaire);
                break;
            }
            case INT:{
                int valeur_temporaire;
                printf("||Colonne de type ENTIER RELATIF||\tInsérez une valeur : ");
                scanf("%d", &valeur_temporaire);
                getchar();
                inserer_valeur(CDataFrame[i],&valeur_temporaire);
                break;
            }
            case CHAR:{
                char valeur_temporaire;
                printf("||Colonne de type CARACTERE||\tInsérez une valeur : ");
                scanf("%c", &valeur_temporaire);
                getchar();
                inserer_valeur(CDataFrame[i],&valeur_temporaire);
                break;
            }
            case FLOAT:{
                float valeur_temporaire;
                printf("||Colonne de type FLOAT||\tInsérez une valeur : ");
                scanf("%f", &valeur_temporaire);
                getchar();
                inserer_valeur(CDataFrame[i],&valeur_temporaire);
                break;
            }
            case DOUBLE:{
                double valeur_temporaire;
                printf("||Colonne de type DOUBLE||\tInsérez une valeur : ");
                scanf("%lf", &valeur_temporaire);
                getchar();
                inserer_valeur(CDataFrame[i],&valeur_temporaire);
                break;
            }
            case STRING:{
                printf("||Colonne de type CHAINE DE CARACTERES||\tInsérez une valeur : ");
                char buff[256];
                gets(buff);
                char *valeur_temporaire=(char*) malloc(strlen(buff)+1);
                strcpy(valeur_temporaire, buff);
                inserer_valeur(CDataFrame[i], valeur_temporaire);
                break;
            }

        }
    }
}


/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : supprimer_ligne_CDataframe
Cette fonction supprime une ligne du CDataframe.
 Elle prend en paramètre le Cdataframe et sa taille.
 Elle ne renvoit rien puisqu'elle modifie dynamiquement.
----------------------------------------------------------------------------------------------------------------------*/
void supprimer_ligne_CDataframe(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        //libère la mémoire de la ligne et décrémente la taille logique
        free(CDataFrame[i]->donnees[CDataFrame[i]->taille_logique] );
        CDataFrame[i]->taille_logique--;
    }
}



/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : ajouter_colonne_CDataframe
Cette fonction permet à l'utilisateur d'ajouter une colonne dans le Cdataframe et de remplir chaque colonnes avec les
 valeurs de son choix.
 Elle prend en paramètre le Dataframe et sa taille.
 Elle ne renvoit rien pusiqu'elle modifie dynamiquement.
----------------------------------------------------------------------------------------------------------------------*/
void ajouter_colonne_CDataframe(Colonne*** CDataFrame, int * taille) {
    //On réallout la taille du Dataframe avec les vérifications nécessaires
    Colonne ** NouveauCDataFrame = (Colonne**) realloc(*CDataFrame, (*taille + 1)*sizeof(Colonne*));
    if (NouveauCDataFrame == NULL) {
        printf("Allocation échoué\n");
        free(*CDataFrame);
        return;
    }
    //On remplit cette nouvelle colonne avec le titre demandé
    printf("Quel titre voulez-vous pour la nouvelle colonne : ");
    char titre[100];
    gets(titre);
    printf("Choisissez le type de votre colonne :\n[1]Entier Naturel [2]Entier Relatif [3]Charactère [4]Floatant [5]Double [6]Chaine de caractère : ");
    int choix_type;
    scanf("%d", & choix_type);
    getchar();

    switch (choix_type) {
        //switch celon le type demandé
        case 1: {
            *CDataFrame = NouveauCDataFrame;
            (*CDataFrame)[ * taille] = creer_colonne(UINT, titre);
            * taille = * taille + 1;
            break;
        }
        case 2: {
            *CDataFrame = NouveauCDataFrame;
            (*CDataFrame)[ * taille] = creer_colonne(INT, titre);
            * taille = * taille + 1;
            break;
        }
        case 3: {
            *CDataFrame = NouveauCDataFrame;
            (*CDataFrame)[ * taille] = creer_colonne(CHAR, titre);
            * taille = * taille + 1;
            break;
        }
        case 4: {
            *CDataFrame = NouveauCDataFrame;
            (*CDataFrame)[ * taille] = creer_colonne(FLOAT, titre);
            * taille = * taille + 1;
            break;
        }
        case 5: {
            *CDataFrame = NouveauCDataFrame;
            (*CDataFrame)[ * taille] = creer_colonne(DOUBLE, titre);
            * taille = * taille + 1;
            break;
        }
        case 6: {
            *CDataFrame = NouveauCDataFrame;
            (*CDataFrame)[ * taille] = creer_colonne(STRING, titre);
            * taille = * taille + 1;
            break;
        }
        default:
            printf("Ce type n'existe pas.\n");
    }
    //On demande maintenant à l'utilisateur de remplir avec les valeurs de son choix
    int nbr_lig_max =(*CDataFrame)[0]->taille_logique;
    printf("Combien de données voulez-vous dans nouvelle colonne ? ");
    int nbr_lig;
    scanf("%d", & nbr_lig);
    getchar();

    switch (choix_type) {
        case 1: {
            for (int j = 0; j < nbr_lig; ++j) {
                printf("Entrez une valeur : ");
                unsigned int valeur_ligne;
                scanf("%ud", & valeur_ligne);
                getchar();
                inserer_valeur((*CDataFrame)[ * taille-1], & valeur_ligne);
            }
            break;
        }
        case 2: {
            for (int j = 0; j < nbr_lig; ++j) {
                printf("Entrez une valeur : ");
                int valeur_ligne;
                scanf("%d", & valeur_ligne);
                getchar();
                inserer_valeur((*CDataFrame)[ *taille-1], & valeur_ligne);
            }
            break;
        }
        case 3: {
            for (int j = 0; j < nbr_lig; ++j) {
                printf("Entrez une valeur : ");
                char valeur_ligne;
                scanf("%c", & valeur_ligne);
                getchar();
                inserer_valeur((*CDataFrame)[ *taille-1], & valeur_ligne);
            }
            break;
        }
        case 4: {
            for (int j = 0; j < nbr_lig; ++j) {
                printf("Entrez une valeur : ");
                float valeur_ligne;
                scanf("%f", & valeur_ligne);
                getchar();
                inserer_valeur((*CDataFrame)[  *taille-1], & valeur_ligne);
            }
            break;
        }
        case 5: {
            for (int j = 0; j < nbr_lig; ++j) {
                printf("Entrez une valeur : ");
                double valeur_ligne;
                scanf("%lf", & valeur_ligne);
                getchar();
                inserer_valeur((*CDataFrame)[ *taille-1], & valeur_ligne);
            }
            break;
        }
        case 6: {
            for (int j = 0; j < nbr_lig; ++j) {
                printf("Entrez une valeur : ");
                char buff[256];
                gets(buff);
                char * valeur_ligne = (char * ) malloc(strlen(buff) + 1);
                strcpy(valeur_ligne, buff);
                inserer_valeur((*CDataFrame)[ *taille-1], valeur_ligne);
            }
            break;
        }
        default:
            return;
    }
    //On fait une dernière vérification pour que chaque colonne est le même nombre de ligne en utilisant la fonction
    //ajouter_ligne_CDataframe si nécessaire
    if (nbr_lig > nbr_lig_max) {
        for (int i = 0; i < nbr_lig - nbr_lig_max; ++i) {
            ajouter_ligne_CDataframe(*CDataFrame, (*taille)-1);
        }
    }
}


/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : supprimer_colonne_CDataframe
Cette fonction supprime une colonne du CDataframe.
 Elle prend en paramètre le Cdataframe et sa taille.
 Elle ne renvoit rien puisqu'elle modifie dynamiquement.
----------------------------------------------------------------------------------------------------------------------*/
void supprimer_colonne_CDataframe(Colonne*** CDataFrame, int* taille){
    (*CDataFrame)[*taille-1] = NULL;
    free((*CDataFrame)[*taille-1]);
    *taille = *taille-1;
}


/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : renommer_titre
Cette fonction renomme une colonne du CDataframe.
 Elle prend en paramètre le Cdataframe et la position de la colonne qu'il faut renommer.
 Elle ne renvoit rien puisqu'elle modifie dynamiquement.
----------------------------------------------------------------------------------------------------------------------*/
void renommer_titre(Colonne** CDataFrame, int position){
    printf("Chosir un nouveau titre : ");
    char nouveau_titre[100];
    fflush(stdout);
    fflush(stdin);
    gets(nouveau_titre);
    CDataFrame[position]->titre = (char*)realloc(CDataFrame[position]->titre, strlen(nouveau_titre)+1);
    strcpy(CDataFrame[position]->titre, nouveau_titre);
}




/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : existence_valeur
Cette fonction vérifie l'existence d'une valeur dans le Dataframe
Elle prend comme argument, CDataFrame, la valeur qu'on cherche et la taille
----------------------------------------------------------------------------------------------------------------------*/
int existence_valeur(Colonne** CDataFrame,  char * valeur, int taille){
    char test[256];
    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < CDataFrame[i]->taille_logique; ++j){
            convertir_valeur(CDataFrame[i],j,test,256);
            //printf("\nAAA %s AAA\n",test);
            if (strcmp(test,valeur) == 0){
                //printf("YAYAYA");
                return 1;
            }
        }
    }

    return 0;
}


/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : changement_valeur
Cette fonction à pour role de changer une valeur à une position précise dans le Dataframe.
----------------------------------------------------------------------------------------------------------------------*/
void changement_valeur(Colonne** CDataFrame, int colonne, int ligne, COL_TYPE * valeur){
    switch(CDataFrame[colonne]->type_colonne){
        case UINT:
            CDataFrame[colonne]->donnees[ligne]->uint_value = valeur->uint_value;
            break;
        case INT:
            CDataFrame[colonne]->donnees[ligne]->int_value = valeur->int_value;
            break;
        case CHAR:
            CDataFrame[colonne]->donnees[ligne]->char_value = valeur->char_value;
            break;
        case FLOAT:
            CDataFrame[colonne]->donnees[ligne]->float_value = valeur->float_value;
            break;
        case DOUBLE:
            CDataFrame[colonne]->donnees[ligne]->double_value = valeur->double_value;
            break;
        case STRING:
            strcpy(CDataFrame[colonne]->donnees[ligne]->string_value, valeur->string_value);
            break;
        default:
            break;
    }
    return;
}




/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : afficher_nom_colonne
La fonction a pour but d'afficher le nom de toutes les colonnes.
 Elle prend en paramètre le Cdataframe et sa taille.
 Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void afficher_nom_colonne(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        printf("%s\n",CDataFrame[i]->titre);
    }
}

/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : afficher_nombre_ligne
Cette fonction a pour but d'afficher le nombre de lignes du Dataframe
 Elle prend en paramètre le Cdataframe.
 Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/


void afficher_nombre_ligne(Colonne** CDataFrame){
    printf("%d\n", CDataFrame[0]->taille_logique);
}



/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : afficher_nombre_colonne
Cette fonction a pour but d'afficher le nombre de colonnes du Dataframe
 Elle prend en paramètre le Cdataframe et sa taille.
 Elle ne renvoit rien puisque c'est une fonction d'affichage.
----------------------------------------------------------------------------------------------------------------------*/
void afficher_nombre_colonne(Colonne** CDataFrame,int taille){
    printf("%d\n", taille);
}


/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : nombre_cellule_x
Cette fonction a pour but de donner le nombre de cellule du Cdataframe qui ont une valeur égal à x, avec x qui est une
 valeur d'un type quelconque donné par l'utilisateur.
  Elle prend en paramètre le Cdataframe, sa taille et une valeur chosit par l'utilisateur.
----------------------------------------------------------------------------------------------------------------------*/
int nombre_cellule_x(Colonne** CDataFrame, void* x, int taille){
    int cpt=0;
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            cpt += nombre_occurence_valeur(CDataFrame[i], x);
        }
    }
    return cpt;
}



/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : nombre_cellule_superieur_x
Cette fonction a pour but de donner le nombre de cellule du Cdataframe qui ont une valeur supérieur à x, avec x qui est
 une valeur d'un type quelconque donné par l'utilisateur.
  Elle prend en paramètre le Cdataframe, sa taille et une valeur chosit par l'utilisateur.
----------------------------------------------------------------------------------------------------------------------*/
int nombre_cellule_superieur_x(Colonne** CDataFrame, void* x, int taille){
    int cpt=0;
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            cpt += nombre_occurence_superieur(CDataFrame[i], x);
        }
    }
    return cpt;
}



/*----------------------------------------------------------------------------------------------------------------------
                                    FONCTION : nombre_cellule_inferieur_x
Cette fonction a pour but de donner le nombre de cellule du Cdataframe qui ont une valeur inferieur à x, avec x qui est
 une valeur d'un type quelconque donné par l'utilisateur.
  Elle prend en paramètre le Cdataframe, sa taille et une valeur chosit par l'utilisateur.
----------------------------------------------------------------------------------------------------------------------*/
int nombre_cellule_inferieur_x(Colonne** CDataFrame, void* x,int taille){
    int cpt=0;
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            cpt += nombre_occurence_inferieur(CDataFrame[i], x);
        }
    }
    return cpt;
}
