#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
}Colonne;

typedef struct {
    int x,y;
} point;

Colonne *creer_colonne(ENUM_TYPE type, char* titre){
    Colonne *nouvelle_colonne = (Colonne *)malloc(sizeof(Colonne));
    nouvelle_colonne->titre = (char*)malloc(strlen(titre)+1);
    strcpy(nouvelle_colonne->titre, titre);
    nouvelle_colonne->type_colonne = type;
    nouvelle_colonne->donnees = NULL;
    nouvelle_colonne->taille_physique = 256;
    nouvelle_colonne->taille_logique = 0;
    nouvelle_colonne->index = NULL;
    printf("nouvelle colonne addr: %x\n",nouvelle_colonne);
    return nouvelle_colonne;
}

int inserer_valeur(Colonne* colonne, void* valeur) {

    if (colonne->donnees == NULL){
        colonne->donnees = (COL_TYPE**) malloc(255*sizeof(COL_TYPE*));
    }

    colonne->donnees[colonne->taille_logique] = (COL_TYPE*)malloc(sizeof(COL_TYPE));



    switch (colonne->type_colonne) {
        case UINT:
            colonne->donnees[colonne->taille_logique]->uint_value = *(unsigned int*)valeur;
            break;
        case INT:
            if (valeur == NULL){
                colonne->donnees[colonne->taille_logique]->int_value = 0;
                break;
            }
            colonne->donnees[colonne->taille_logique]->int_value = *(int*)valeur;
            break;
        case CHAR:
            if (valeur == NULL){
                colonne->donnees[colonne->taille_logique]->char_value = '\0';
                break;
            }
            colonne->donnees[colonne->taille_logique]->char_value = *(char*)valeur;
            break;
        case FLOAT:
            colonne->donnees[colonne->taille_logique]->float_value = *(float*)valeur;
            break;
        case DOUBLE:
            colonne->donnees[colonne->taille_logique]->double_value = *(double*)valeur;
            break;
        case STRING:
            colonne->donnees[colonne->taille_logique]->string_value = (char*)malloc(strlen((char*)valeur) + 1);
            strcpy(colonne->donnees[colonne->taille_logique]->string_value, (char*)valeur);

            break;
        case STRUCTURE:
            colonne->donnees[colonne->taille_logique]->struct_value = valeur;
            break;
        default:
            // Invalid column type
            return -1;
    }

    // Increment the logical size of the column
    colonne->taille_logique++;

    return 0;
}

void convertir_valeur(Colonne *col, unsigned long long int position, char *str, int taille_logique){
    if(col->donnees != NULL) {
        switch (col->type_colonne) {
            case INT:
                snprintf(str, taille_logique, "%d", *((int *) col->donnees[position]));
                break;
            case UINT:
                snprintf(str, taille_logique, "%d", *((unsigned int *) col->donnees[position]));
                break;
            case CHAR:
                if (col->donnees[position]->char_value == '\0'){
                    strcpy(str, "NULL");
                    break;
                }
                snprintf(str, taille_logique, "%c", *((char *) col->donnees[position]));
                break;
            case FLOAT:
                snprintf(str, taille_logique, "%f", *((float *) col->donnees[position]));
                break;
            case DOUBLE:
                snprintf(str, taille_logique, "%lf", *((double *) col->donnees[position]));
                break;
            case STRING:
                snprintf(str, taille_logique, "%s", col->donnees[position]->string_value);
                //printf("%s",col->donnees[position]->string_value);
                break;
            case STRUCTURE:
                snprintf(str, taille_logique, "%p", col->donnees[position]->struct_value);
                break;
            default:
                return;
        }
    }
}


void afficher_colonne(Colonne* colonne){
    char str[100];
    printf("%s\n", colonne->titre);
    for (int i = 0; i < colonne->taille_logique; i++){
        convertir_valeur(colonne,i,str,100);
        printf("[%d]\t%s\n", i, str);
    }

}

int nombre_occurence_valeur(Colonne* colonne, void* value) {
    int cpt = 0;
    char str[100];
    char char_temp[100];

    if (colonne == NULL || colonne->donnees == NULL) {
        return 0;
    }
    switch (colonne->type_colonne) {
        case INT:
            snprintf(char_temp, sizeof(char_temp), "%d", *(int *)value);
            break;
        case UINT:
            snprintf(char_temp, sizeof(char_temp), "%u", *(unsigned int *)value);
            break;
        case CHAR:
            snprintf(char_temp, sizeof(char_temp), "%c", *(char *)value);
            break;
        case FLOAT:
            snprintf(char_temp, sizeof(char_temp), "%f", *(float *)value);
            break;
        case DOUBLE:
            snprintf(char_temp, sizeof(char_temp), "%lf", *(double *)value);
            break;
        case STRING:
            snprintf(char_temp, sizeof(char_temp), "%s", (char *)value);
            break;
        default:
            return 0;
    }
    for(int i = 0; i < colonne->taille_logique; ++i) {
        convertir_valeur(colonne, i, str, sizeof(str));
        if (strcmp(str, char_temp) == 0) {
            cpt++;
        }
    }

    return cpt;
}



char* retourne_valeur_a_x(Colonne* colonne, int x) {
    if (x >= colonne->taille_logique || x < 0) {
        return NULL;
    }
    char* valeur = malloc(100 * sizeof(char));
    if (valeur == NULL) {
        return NULL;
    }
    convertir_valeur(colonne, x, valeur, 100);
    return valeur;
}


int nombre_occurence_superieur(Colonne* colonne, void* valeur) {
    int cpt = 0;
    if (colonne == NULL || colonne->donnees == NULL) {
        return 0;
    }

    switch (colonne->type_colonne) {
        case INT:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(int *) colonne->donnees[i] > *((int *) valeur)) cpt++;
            }
            break;
        case UINT:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(unsigned int*) colonne->donnees[i] > *((unsigned int*) valeur)) cpt++;
            }
            break;
        case FLOAT:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(float *) colonne->donnees[i] > *((float *) valeur)) cpt++;
            }
            break;
        case DOUBLE:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(double *) colonne->donnees[i] > *((double *) valeur)) cpt++;
            }
            break;
        case CHAR:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                char char_temp[100];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) > 0) cpt++;
            }
            break;
        case STRING:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                char char_temp[100];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) > 0) cpt++;
            }
            break;
        default:
            return 0;
    }

    return cpt;

}

int nombre_occurence_inferieur(Colonne* colonne, void* valeur) {
    int cpt = 0;
    if (colonne == NULL || colonne->donnees == NULL) {
        return 0;
    }

    switch (colonne->type_colonne) {
        case INT:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(int *) colonne->donnees[i] < *((int *) valeur)) cpt++;
            }
            break;
        case UINT:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(unsigned int*) colonne->donnees[i] < *((unsigned int*) valeur)) cpt++;
            }
            break;
        case FLOAT:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(float *) colonne->donnees[i] < *((float *) valeur)) cpt++;
            }
            break;
        case DOUBLE:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                if (*(double *) colonne->donnees[i] < *((double *) valeur)) cpt++;
            }
            break;
        case CHAR:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                char char_temp[100];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) < 0) cpt++;
            }
            break;
        case STRING:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                char char_temp[100];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) < 0) cpt++;
            }
            break;
        default:
            return 0;
    }

    return cpt;

}
