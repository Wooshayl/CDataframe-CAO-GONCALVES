
#include "cdataframe.h"
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Colonne** creer_cdataframe_vide(){
    Colonne** CDataFrame;
    CDataFrame = (Colonne **)malloc(100 * sizeof(Colonne *));
    for (int i = 0; i < 100; i++) {
        CDataFrame[i] = (Colonne *)malloc(sizeof(Colonne));
    }
    return CDataFrame;
}

int taille_logique_cdataframe(Colonne** CDataFrame){
    for (int i = 0; i < 100; ++i) {
        if(CDataFrame[i] = NULL){
            return i;
        }
    }
}
Colonne** remplissage_utilisateur_CDataframe(int taille){
    Colonne** CDataFrame = (Colonne**)malloc(taille*sizeof(Colonne*));
    // printf("Combien de colonnes voulez-vous ?");
    int nbr_col, nbr_lig_max=0;
    // scanf("%d", &nbr_col);
    getchar();
    for(int i =0; i < taille; i++) {
        printf("Quel titre voulez-vous pour la colonne %d : ", i);
        char titre[100];
        gets(titre);
        //scanf("%s", titre);
        Colonne *colonne = creer_colonne(titre);
        CDataFrame[i] = colonne;
       // printf("i: %d et titre : %s\n",i,CDataFrame[0]->titre);
    }
    //printf("%s\n",CDataFrame[0]->titre);
    //printf("%s\n",CDataFrame[1]->titre);
    for (int i = 0; i < taille; ++i) {
        printf("Combien de données voulez-vous dans la colonne %d ? ", i);
        int nbr_lig;
        scanf("%d", &nbr_lig);
        if(nbr_lig>nbr_lig_max) {
            nbr_lig_max = nbr_lig;
        }
        for (int j = 0; j < nbr_lig; ++j) {
            printf("Entrez une valeur : ");
            int valeur_ligne;
            scanf("%d", &valeur_ligne);
            inserer_valeur(CDataFrame[i], valeur_ligne);
        }
    }
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i]->taille_logique < nbr_lig_max){
            for (int j = CDataFrame[i]->taille_logique; j < nbr_lig_max; ++j) {
                inserer_valeur(CDataFrame[i],0);
            }
        }

    }
    return CDataFrame;
}

void remplissage_dure(Colonne** CDataFrame){
    Colonne *ma_colonne = creer_colonne("Ma colonne");
    inserer_valeur(ma_colonne, 52);
    inserer_valeur(ma_colonne, 44);
    inserer_valeur(ma_colonne, 15);
    inserer_valeur(ma_colonne, 69);
    Colonne *ma_colonne2 = creer_colonne("Ma colonne 2");
    inserer_valeur(ma_colonne2, 52);
    inserer_valeur(ma_colonne2, 44);
    inserer_valeur(ma_colonne2, 15);
    inserer_valeur(ma_colonne2, 69);
    CDataFrame[0] = ma_colonne;
    CDataFrame[1] = ma_colonne2;
}
void affichage_cdatatframe(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        if(CDataFrame[i] != NULL){
            printf("%s", CDataFrame[i]->titre);
            for (int j = 0; j < CDataFrame[i]->taille_logique; ++j) {
                printf("%d", CDataFrame[i]->donnees[j]);
            }
            printf("\n");
        }
    }
}
void affichage_cdatatframe_ligne_utilisateur(Colonne** CDataFrame){
    int valeur_ligne_utilisateur;
    printf("Jusqu'à quelles lignes voulez-vous ?");
    scanf("%d", &valeur_ligne_utilisateur);
    for (int i = 0; i < 100; ++i) {
        if(CDataFrame[i] != NULL){
            printf("%s", CDataFrame[i]->titre);
            for (int j = 0; j < valeur_ligne_utilisateur; ++j) {
                printf("%d", CDataFrame[i]->donnees[j]);
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
            printf("%s", CDataFrame[i]->titre);
            for (int j = 0; j < CDataFrame[i]->taille_logique; ++j) {
                printf("%d", CDataFrame[i]->donnees[j]);
            }
            printf("\n");
        }
    }

}
void ajouter_ligne_CDataframe(Colonne** CDataFrame, int valeur, int taille){
    for (int i = 0; i < taille; ++i) {
        inserer_valeur(CDataFrame[i], valeur);
    }
}
void supprimer_ligne_CDataframe(Colonne** CDataFrame){
    for (int i = 0; i < 100; ++i) {
        CDataFrame[i]->donnees[CDataFrame[i]->taille_logique] = 0;
    }
}
void ajouter_colonne_CDataframe(Colonne** CDataFrame){
    CDataFrame[taille_logique_cdataframe(CDataFrame)] = creer_colonne("Nouvelle colonne");
}
void supprimer_colonne_CDataframe(Colonne** CDataFrame){
    CDataFrame[taille_logique_cdataframe(CDataFrame)-1] = NULL;

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
int existence_valeur(Colonne** CDataFrame, int valeur){
    for (int i = 0; i < taille_logique_cdataframe(CDataFrame); ++i) {
        for (int j = 0; j < CDataFrame[i]->taille_logique; ++j) {
            if(CDataFrame[i]->donnees[j] == valeur)
            return 1;
        }
    }
    return 0;
}
void changement_valeur(Colonne** CDataFrame, int colonne, int ligne, int valeur){
    CDataFrame[colonne]->donnees[ligne] = valeur;
}
void afficher_nom_colonne(Colonne** CDataFrame, int taille){
    for (int i = 0; i < taille; ++i) {
        printf("%s\n",CDataFrame[i]->titre);
    }
}
void afficher_nombre_ligne(Colonne** CDataFrame){
    printf("%d", CDataFrame[0]->taille_logique);
}
void afficher_nombre_colonne(Colonne** CDataFrame){
    printf("%d", taille_logique_cdataframe(CDataFrame));
}
int nombre_cellule_x(Colonne** CDataFrame, int x){
    int cpt=0;
    for (int i = 0; i < 100; ++i) {
        if(CDataFrame[i] != NULL){
            for (int j = 0; j < CDataFrame[i]->taille_logique; ++j) {
                if(CDataFrame[i]->donnees[j] ==x)
                    cpt+=1;
            }
        }
    }
    return cpt;
}
int nombre_cellule_superieur_x(Colonne** CDataFrame, int x){
    int cpt=0;
    for (int i = 0; i < 100; ++i) {
        if(CDataFrame[i] != NULL){
            for (int j = 0; j < CDataFrame[i]->taille_logique; ++j) {
                if(CDataFrame[i]->donnees[j] > x)
                    cpt+=1;
            }
        }
    }
    return cpt;
}
int nombre_cellule_inferieur_x(Colonne** CDataFrame, int x){
    int cpt=0;
    for (int i = 0; i < 100; ++i) {
        if(CDataFrame[i] != NULL){
            for (int j = 0; j < CDataFrame[i]->taille_logique; ++j) {
                if(CDataFrame[i]->donnees[j] < x)
                    cpt+=1;
            }
        }
    }
    return cpt;
}
