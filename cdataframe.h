
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

#endif //CDDATAFRAME_CDATAFRAME_H
