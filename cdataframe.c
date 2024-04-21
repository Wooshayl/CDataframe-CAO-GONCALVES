
#include "cdataframe.h"
#include "column.h"
#include <stdio.h>
#include <stdlib.h>

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
