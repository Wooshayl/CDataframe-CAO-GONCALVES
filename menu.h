/*======================================================================================================================
                                CDataframe par Lilian CAO et Valentin GONCALVES
Ce fichier contient les prototypes des fonctions pour le menu.
======================================================================================================================*/

#ifndef CDDATAFRAME_MENU_H
#define CDDATAFRAME_MENU_H
#include "colonne.h"
void option_affichage_dataframe(Colonne** CDataFrame, int taille);
void modification_Dataframe(Colonne** CDataFrame, int taille);
void analyse_statistique(Colonne** CDataFrame, int taille);
void menu_global(Colonne** CDataFrame, int taille);

#endif //CDDATAFRAME_MENU_H
