/*======================================================================================================================
                                CDataframe par Lilian CAO et Valentin GONCALVES
Ce fichier contient les prototyeps des fonctions de 'cdataframe.c'.
======================================================================================================================*/

#ifndef CDDATAFRAME_CDATAFRAME_H
#define CDDATAFRAME_CDATAFRAME_H
#include "colonne.h"
Colonne** creer_cdataframe_vide();
Colonne** remplissage_utilisateur_CDataframe(int taille);
void remplissage_dure(Colonne** CDataFrame);
void affichage_cdatatframe(Colonne** CDataFrame, int taille);
void affichage_cdatatframe_ligne_utilisateur(Colonne** CDataFrame, int taille);
void affichage_cdatatframe_colonne_utilisateur(Colonne** CDataFrame);
void ajouter_ligne_CDataframe(Colonne** CDataFrame, int taille);
void supprimer_ligne_CDataframe(Colonne** CDataFrame, int taille);
void ajouter_colonne_CDataframe(Colonne*** CDataFrame, int * taille);
void supprimer_colonne_CDataframe(Colonne*** CDataFrame, int* taille);
void renommer_titre(Colonne** CDataFrame, int position);
int existence_valeur(Colonne** CDataFrame,  char * valeur, int taille);
void changement_valeur(Colonne** CDataFrame, int colonne, int ligne, COL_TYPE * valeur);
void afficher_nom_colonne(Colonne** CDataFrame, int taille);
void afficher_nombre_ligne(Colonne** CDataFrame);
void afficher_nombre_colonne(Colonne** CDataFrame,int taille);
int nombre_cellule_x(Colonne** CDataFrame, void* x, int taille);
int nombre_cellule_superieur_x(Colonne** CDataFrame, void* x, int taille);
int nombre_cellule_inferieur_x(Colonne** CDataFrame, void* x,int taille);
#endif //CDDATAFRAME_CDATAFRAME_H
