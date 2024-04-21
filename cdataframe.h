
#ifndef CDDATAFRAME_CDATAFRAME_H
#define CDDATAFRAME_CDATAFRAME_H
#include "column.h"
Colonne** creer_cdataframe_vide();
void remplissage_utilisateur_CDataframe(Colonne** CDataFrame);
void remplissage_dure(Colonne** CDataFrame);
void affichage_cdatatframe(Colonne** CDataFrame);
void affichage_cdatatframe_ligne_utilisateur(Colonne** CDataFrame);
void affichage_cdatatframe_colonne_utilisateur(Colonne** CDataFrame);
void ajouter_ligne_CDataframe(Colonne** CDataFrame, int valeur);
void supprimer_ligne_CDataframe(Colonne** CDataFrame);
void ajouter_colonne_CDataframe(Colonne** CDataFrame);
void supprimer_colonne_CDataframe(Colonne** CDataFrame);
void renommer_titre(Colonne** CDataFrame, int position);
int existence_valeur(Colonne** CDataFrame, int valeur);
void changement_valeur(Colonne** CDataFrame, int colonne, int ligne, int valeur);
void afficher_nom_colonne(Colonne** CDataFrame);
void afficher_nombre_ligne(Colonne** CDataFrame);
void afficher_nombre_colonne(Colonne** CDataFrame);

#endif //CDDATAFRAME_CDATAFRAME_H
