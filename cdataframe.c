
#include "cdataframe.h"
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int taille_logique_cdataframe(Colonne** CDataFrame){
    for (int i = 0; i < 100; ++i) {
        if(CDataFrame[i] = NULL){
            return i;
        }
    }
}

Colonne** remplissage_utilisateur_CDataframe(int taille){
    Colonne** CDataFrame = (Colonne**)malloc(taille*sizeof(Colonne*));
    int nbr_col, nbr_lig_max=0;
    getchar();
    int* liste_choix_types = (int*) malloc(sizeof(int)*taille);
    for(int i =0; i < taille; i++) {
        printf("Quel titre voulez-vous pour la colonne %d : ", i);
        char titre[100];
        gets(titre);
        printf("Choisissez le type de votre colonne :\n[1]Entier Naturel [2]Entier Relatif [3]Charactère [4]Floatant [5]Double [6]Chaine de caractère : ");
        int choix_type;
        scanf("%d", &choix_type);
        getchar();
        liste_choix_types[i] = choix_type;
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

       // printf("i: %d et titre : %s\n",i,CDataFrame[0]->titre);
    }
    //printf("%s\n",CDataFrame[0]->titre);
    //printf("%s\n",CDataFrame[1]->titre);
    for (int i = 0; i < taille; ++i) {
        printf("Combien de données voulez-vous dans la colonne %d ? ", i);
        int nbr_lig;
        scanf("%d", &nbr_lig);
        getchar();
        if(nbr_lig>nbr_lig_max) {
            nbr_lig_max = nbr_lig;
        }
        switch (liste_choix_types[i]) {
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
void affichage_cdatatframe(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            //printf("%s", CDataFrame[i]->titre);
            afficher_colonne(CDataFrame[i]);
            printf("\n");
        }
    }
}

void affichage_cdatatframe_ligne_utilisateur(Colonne** CDataFrame, int taille){
    int valeur_ligne_utilisateur;
    char str[100];
    printf("Jusqu'à quelles lignes voulez-vous ?");
    scanf("%d", &valeur_ligne_utilisateur);
    for (int i = 0; i < taille; ++i) {
        if(valeur_ligne_utilisateur > CDataFrame[i]->taille_logique)return;
        if(CDataFrame[i] != NULL){
            printf("%s", CDataFrame[i]->titre);
            for (int j = 0; j < valeur_ligne_utilisateur; ++j) {
                convertir_valeur(CDataFrame[i],j,str, 100);//Checker ligne utilisateur > taille logique de la colonne
                printf("[%d]\t%s\t\t", j, str);
            }
            printf("\n");
        }
    }
}


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

void ajouter_ligne_CDataframe(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        switch (CDataFrame[i]->type_colonne) {
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

void supprimer_ligne_CDataframe(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        free(CDataFrame[i]->donnees[CDataFrame[i]->taille_logique] );
        CDataFrame[i]->taille_logique--;
    }
}

void ajouter_colonne_CDataframe(Colonne*** CDataFrame, int * taille) {
    Colonne ** NouveauCDataFrame = (Colonne**) realloc(*CDataFrame, (*taille + 1)*sizeof(Colonne*));
    if (NouveauCDataFrame == NULL) {
        printf("Allocation échoué\n");
        free(*CDataFrame);
        return;
    }
    printf("Quel titre voulez-vous pour la nouvelle colonne : ");
    char titre[100];
    gets(titre);
    printf("Choisissez le type de votre colonne :\n[1]Entier Naturel [2]Entier Relatif [3]Charactère [4]Floatant [5]Double [6]Chaine de caractère : ");
    int choix_type;
    scanf("%d", & choix_type);
    getchar();

    switch (choix_type) {
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
    if (nbr_lig > nbr_lig_max) {
        for (int i = 0; i < nbr_lig - nbr_lig_max; ++i) {
            ajouter_ligne_CDataframe(*CDataFrame, (*taille)-1);
        }
    }
}

void supprimer_colonne_CDataframe(Colonne*** CDataFrame, int* taille){
    *CDataFrame[*taille - 1] = NULL;
    Colonne ** NouveauCDataFrame = (Colonne**) realloc(*CDataFrame, (*taille - 1)*sizeof(Colonne*))
    *CDataFrame = NouveauCDataFrame
    *taille = *taille - 1
}

void renommer_titre(Colonne** CDataFrame, int position){
    printf("Chosir un nouveau titre : ");
    char nouveau_titre[100];
    fflush(stdout);
    fflush(stdin);
    gets(nouveau_titre);
    CDataFrame[position]->titre = (char*)realloc(CDataFrame[position]->titre, strlen(nouveau_titre)+1);
    strcpy(CDataFrame[position]->titre, nouveau_titre);
}

int existence_valeur(Colonne** CDataFrame,  void* valeur, int taille){
    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < CDataFrame[i]->taille_logique; ++j) {
            if(CDataFrame[i]->donnees[j] == valeur)
            return 1;
        }
    }
    return 0;
}

void changement_valeur(Colonne** CDataFrame, int colonne, int ligne, int valeur){
    CDataFrame[colonne]->donnees[ligne] = &valeur;//je sais pas
}

void afficher_nom_colonne(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        printf("%s\n",CDataFrame[i]->titre);
    }
}

void afficher_nombre_ligne(Colonne** CDataFrame){
    printf("%d\n", CDataFrame[0]->taille_logique);
}

void afficher_nombre_colonne(Colonne** CDataFrame,int taille){
    printf("%d\n", taille);
}
int nombre_cellule_x(Colonne** CDataFrame, void* x, int taille){
    int cpt=0;
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            cpt += nombre_occurence_valeur(CDataFrame[i], x);
        }
    }
    return cpt;
}
int nombre_cellule_superieur_x(Colonne** CDataFrame, void* x, int taille){
    int cpt=0;
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            cpt += nombre_occurence_superieur(CDataFrame[i], x);
        }
    }
    return cpt;
}
int nombre_cellule_inferieur_x(Colonne** CDataFrame, void* x,int taille){
    int cpt=0;
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            cpt += nombre_occurence_inferieur(CDataFrame[i], x);
        }
    }
    return cpt;
}
