/*======================================================================================================================
                                CDataframe par Lilian CAO et Valentin GONCALVES
Ce fichier contient les prototyeps des fonctions de 'colonne.c'.
======================================================================================================================*/
#ifndef CDDATAFRAME_COLONNE_H
#define CDDATAFRAME_COLONNE_H
#define REALOC_SIZE 256
#define ASC 0
#define DESC 1

enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE ;



typedef struct {
    char *titre;
    ENUM_TYPE type_colonne;
    COL_TYPE **donnees;
    unsigned int taille_physique;
    unsigned int taille_logique;
    unsigned long long int* index;
    int valid_index;
    int sort_dir;
}Colonne;

/*
*/
Colonne *creer_colonne(ENUM_TYPE type, char* titre);
int inserer_valeur(Colonne* colonne, void* valeur);
void supprimer_colonne(Colonne **colonne);
void convertir_valeur(Colonne *col, unsigned long long int position, char *str, int taille_logique);
void afficher_colonne(Colonne* colonne);
int nombre_occurence_valeur(Colonne* colonne, void* valeur);
char* retourne_valeur_a_x(Colonne* colonne, int x);
int nombre_occurence_superieur(Colonne* colonne, void* valeur);
int nombre_occurence_inferieur(Colonne* colonne, void* valeur);
void sort(Colonne* col, int sort_dir);
void afficher_col_index(Colonne* colonne);
void efface_index(Colonne* col);
int check_index(Colonne* col);
void update_index(Colonne *col);
int recherche_valeur_dans_colonne(Colonne *col, void *val);
#endif //CDDATAFRAME_COLONNE_H
