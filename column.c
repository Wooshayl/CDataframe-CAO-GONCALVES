#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "column.h"



Colonne *creer_colonne(ENUM_TYPE type, char* titre){
    Colonne *nouvelle_colonne = (Colonne *)malloc(sizeof(Colonne));
    nouvelle_colonne->titre = (char*)malloc(strlen(titre)+1);
    strcpy(nouvelle_colonne->titre, titre);
    nouvelle_colonne->type_colonne = type;
    nouvelle_colonne->donnees = NULL;
    nouvelle_colonne->taille_physique = 256;
    nouvelle_colonne->taille_logique = 0;
    nouvelle_colonne->index = 0;
    nouvelle_colonne->valid_index = 0;
    nouvelle_colonne->sort_dir = 0;
    printf("nouvelle colonne addr: %x\n",nouvelle_colonne);
    return nouvelle_colonne;
}

int inserer_valeur(Colonne* colonne, void* valeur) {
    // Check if the column is full
    if (colonne->donnees == NULL){
        colonne->donnees = (COL_TYPE**) malloc(255*sizeof(COL_TYPE*));
    }
    
    colonne->donnees[colonne->taille_logique] = (COL_TYPE*)malloc(sizeof(COL_TYPE));

    if (colonne->index == NULL){
        colonne->index = (long long unsigned*) malloc(255* sizeof(long long unsigned));
    }
    colonne->index[colonne->taille_logique] = colonne->taille_logique;

    // Copy the value into the column based on the column type
    switch (colonne->type_colonne) {
        case UINT:
            colonne->donnees[colonne->taille_logique]->uint_value = *(unsigned int*)value;
            break;
        case INT:
            if (value == NULL){
                colonne->donnees[colonne->taille_logique]->int_value = 0;
                break;
            }
            colonne->donnees[colonne->taille_logique]->int_value = *(int*)value;
            break;
        case CHAR:
            if (value == NULL){
                colonne->donnees[colonne->taille_logique]->char_value = '\0';
                break;
            }
            colonne->donnees[colonne->taille_logique]->char_value = *(char*)value;
            break;
        case FLOAT:
            if (value == NULL){
                colonne->donnees[colonne->taille_logique]->float_value = 0;
                break;
            }
            colonne->donnees[colonne->taille_logique]->float_value = *(float*)value;
            break;
        case DOUBLE:
            if (value == NULL){
                colonne->donnees[colonne->taille_logique]->double_value = 0;
                break;
            }
            colonne->donnees[colonne->taille_logique]->double_value = *(double*)value;
            break;
        case STRING:
            if (value == NULL){
                colonne->donnees[colonne->taille_logique]->string_value = NULL;
                break;
            }
            colonne->donnees[colonne->taille_logique]->string_value = (char*)malloc(strlen((char*)value) + 1);
            strcpy(colonne->donnees[colonne->taille_logique]->string_value, (char*)value);

            break;
        case STRUCTURE:
            colonne->donnees[colonne->taille_logique]->struct_value = value;
            break;
        default:
            // Invalid column type
            return -1;
    }

    if (colonne->valid_index == 1){
        colonne->valid_index = 1;
    }else if (colonne->valid_index == -1){
        colonne->valid_index = -1;
    }else{
        colonne->valid_index = 0;
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
        printf("[%d]\t%s\t\t", i, str);
        //printf("colonne->index[%d] : %d\n",i,colonne->index[i]);
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

int partition_int(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    int pivot = col->donnees[col->index[droite]]->int_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->int_value <= pivot) : (col->donnees[col->index[j]]->int_value >= pivot)) {
            i = i + 1;
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
            //col->index[i], col->index[j] = col->index[j], col->index[i];
        }
    }
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    //col->index[i + 1], col->index[droite] = col->index[droite], col->index[i + 1];
    return (i + 1);
}



int partition_uint(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    unsigned int pivot = col->donnees[col->index[droite]]->uint_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->uint_value <= pivot) : (col->donnees[col->index[j]]->uint_value >= pivot)) {
            i = i + 1;
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
            //col->index[i], col->index[j] = col->index[j], col->index[i];
        }
    }
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    //col->index[i + 1], col->index[droite] = col->index[droite], col->index[i + 1];
    return (i + 1);
}

int partition_char(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    char pivot = col->donnees[col->index[droite]]->char_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->char_value <= pivot) : (col->donnees[col->index[j]]->char_value >= pivot)) {
            i = i + 1;
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
            //col->index[i], col->index[j] = col->index[j], col->index[i];
        }
    }
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    //col->index[i + 1], col->index[droite] = col->index[droite], col->index[i + 1];
    return (i + 1);
}

int partition_float(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    float pivot = col->donnees[col->index[droite]]->float_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->float_value <= pivot) : (col->donnees[col->index[j]]->float_value >= pivot)) {
            i = i + 1;
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
            //col->index[i], col->index[j] = col->index[j], col->index[i];
        }
    }
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    //col->index[i + 1], col->index[droite] = col->index[droite], col->index[i + 1];
    return (i + 1);
}

int partition_double(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    double pivot = col->donnees[col->index[droite]]->double_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->double_value <= pivot) : (col->donnees[col->index[j]]->double_value >= pivot)) {
            i = i + 1;
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
            //col->index[i], col->index[j] = col->index[j], col->index[i];
        }
    }
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    //col->index[i + 1], col->index[droite] = col->index[droite], col->index[i + 1];
    return (i + 1);
}

int partition_string(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    char* pivot = col->donnees[col->index[droite]]->string_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->string_value[0] <= pivot[0]) : (col->donnees[col->index[j]]->string_value[0] >= pivot[0])) {
            i = i + 1;
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
            //col->index[i], col->index[j] = col->index[j], col->index[i];
        }
    }
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    //col->index[i + 1], col->index[droite] = col->index[droite], col->index[i + 1];
    return (i + 1);
}

int partition(Colonne* col, int gauche, int droite, int sort_dir){
    switch (col->type_colonne){
        case INT:
            return partition_int(col,gauche,droite,sort_dir);
        case UINT:
            return partition_uint(col, gauche, droite, sort_dir);
        case CHAR:
            return partition_char(col, gauche, droite, sort_dir);
        case FLOAT:
            return partition_float(col, gauche, droite, sort_dir);
        case DOUBLE:
            return partition_double(col, gauche, droite, sort_dir);
        case STRING:
            return partition_string(col, gauche, droite, sort_dir);
        case STRUCTURE:
            break;
    }
}

void QuickSort(Colonne* col, int gauche, int droite, int sort_dir){
    printf("QUICKSORT SORT CALLED\n");
    if (gauche < droite){
        int pi = partition(col, gauche, droite, sort_dir);
        QuickSort(col, gauche, pi - 1, sort_dir);
        QuickSort(col, pi + 1, droite, sort_dir);
    }
    return;
}


void Tri_insertion(Colonne* col, int sort_dir) {
    printf("INSERTION SORT CALLED\n");
    switch (col->type_colonne) {
        case INT:
            for (int i = 1; i < col->taille_logique; i++) {
                COL_TYPE *k = col->donnees[col->index[i]];
                int j = i - 1;
                while (sort_dir == ASC ? ((j >= 0) && (col->donnees[col->index[j]]->int_value > k->int_value)) : (
                        (j >= 0) && (col->donnees[col->index[j]]->int_value < k->int_value))) {
                    col->index[j + 1] = col->index[j];
                    j = j - 1;
                }
                col->index[j + 1] = i;
            }
            col->valid_index = 1;
            break;
        case UINT:
            for (int i = 1; i < col->taille_logique; i++) {
                COL_TYPE *k = col->donnees[col->index[i]];
                int j = i - 1;
                while (sort_dir == ASC ? ((j >= 0) && (col->donnees[col->index[j]]->uint_value > k->uint_value)) : (
                        (j >= 0) && (col->donnees[col->index[j]]->uint_value < k->uint_value))) {
                    col->index[j + 1] = col->index[j];
                    j = j - 1;
                }
                col->index[j + 1] = i;
            }
            col->valid_index = 1;
            break;
        case CHAR:
            for (int i = 1; i < col->taille_logique; i++) {
                COL_TYPE *k = col->donnees[col->index[i]];
                int j = i - 1;
                while (sort_dir == ASC ? ((j >= 0) && (col->donnees[col->index[j]]->char_value > k->char_value)) : (
                        (j >= 0) && (col->donnees[col->index[j]]->char_value < k->char_value))) {
                    col->index[j + 1] = col->index[j];
                    j = j - 1;
                }
                col->index[j + 1] = i;
            }
            col->valid_index = 1;
            break;
        case FLOAT:
            for (int i = 1; i < col->taille_logique; i++) {
                COL_TYPE *k = col->donnees[col->index[i]];
                int j = i - 1;
                while (sort_dir == ASC ? ((j >= 0) && (col->donnees[col->index[j]]->float_value > k->float_value)) : (
                        (j >= 0) && (col->donnees[col->index[j]]->float_value < k->float_value))) {
                    col->index[j + 1] = col->index[j];
                    j = j - 1;
                }
                col->index[j + 1] = i;
            }
            col->valid_index = 1;
            break;
        case DOUBLE:
            for (int i = 1; i < col->taille_logique; i++) {
                COL_TYPE *k = col->donnees[col->index[i]];
                int j = i - 1;
                while (sort_dir == ASC ? ((j >= 0) && (col->donnees[col->index[j]]->double_value > k->double_value)) : (
                        (j >= 0) && (col->donnees[col->index[j]]->double_value < k->double_value))) {
                    col->index[j + 1] = col->index[j];
                    j = j - 1;
                }
                col->index[j + 1] = i;
            }
            col->valid_index = 1;
            break;
        case STRING:
            for (int i = 1; i < col->taille_logique; i++) {
                COL_TYPE *k = col->donnees[col->index[i]];
                int j = i - 1;
                while (sort_dir == ASC ? ((j >= 0) && (col->donnees[col->index[j]]->string_value[0] > k->string_value[0])) : (
                        (j >= 0) && (col->donnees[col->index[j]]->string_value[0] < k->string_value[0]))) {
                    col->index[j + 1] = col->index[j];
                    j = j - 1;
                }
                col->index[j + 1] = i;
            }
            col->valid_index = 1;
            break;
        case STRUCTURE:
            break;
    }
}
void sort(Colonne* col, int sort_dir){
    if (col->index == NULL){
        printf("La colonne n'a pas d'index!");
    }
    if (col->valid_index == 0){
        QuickSort(col, 0, col->taille_logique - 1, sort_dir);
        //Tri_insertion(col, sort_dir);
        col->valid_index = 1;
        return;
    }else if (col->valid_index == -1){
        Tri_insertion(col, sort_dir);
        col->valid_index = 1;
        return;
    } else if (col->valid_index == 1){
        printf("Déjà trié");
        return;
    } else {
        printf("Valeur invalide");
    }
}

void afficher_col_index(Colonne* colonne) {
    /*
    for (int i = 0; i < colonne->taille_logique; i++){
        printf("\t%d ", colonne->donnees[colonne->index[i]]->int_value);
    }
     */
    char str[100];
    printf("%s par index:\n", colonne->titre);
    for (int i = 0; i < colonne->taille_logique; i++){
        convertir_valeur(colonne,colonne->index[i],str,100);
        printf("[%d]\t%s\n", i, str);
    }
}

void efface_index(Colonne* col){
    //liberer memoire alloué
    free(col->index);
    //index = NULL
    col->index = NULL;
    //valid_index = 0;
    col->valid_index = 0;
}

int check_index(Colonne* col){
    if (col->index == NULL){
        return 0;
    }else if (col->valid_index == 0 || col->valid_index == -1){
        return -1;
    }else if (col->valid_index == 1){
        return 1;
    }
    printf("Erreur check_index");
    return 1337;
}


void update_index(Colonne *col){
    switch (col->type_colonne) {
        case INT:
            col->donnees[0]->int_value < col->donnees[col->taille_logique - 1]->int_value ? sort(col, ASC) : sort(col,DESC);
            return;
        case UINT:
            col->donnees[0]->uint_value < col->donnees[col->taille_logique - 1]->uint_value ? sort(col, ASC) : sort(col,DESC);
            return;
        case CHAR:
            col->donnees[0]->char_value < col->donnees[col->taille_logique - 1]->char_value ? sort(col, ASC) : sort(col,DESC);
            return;
        case FLOAT:
            col->donnees[0]->float_value < col->donnees[col->taille_logique - 1]->float_value ? sort(col, ASC) : sort(col, DESC);
            return;
        case DOUBLE:
            col->donnees[0]->double_value < col->donnees[col->taille_logique - 1]->double_value ? sort(col, ASC) : sort(col, DESC);
            return;
        case STRING:
            col->donnees[0]->string_value[0] < col->donnees[col->taille_logique - 1]->string_value[0] ? sort(col, ASC) : sort(col, DESC);
            return;
        case STRUCTURE:
            return;
    }
}

int recherche_valeur_dans_colonne(Colonne *col, void *val){
    switch (col->type_colonne) {
        case INT:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                int gauche = 0;
                int droite = col->taille_logique - 1;
                int milieu = 0;
                while (gauche<= droite){
                    int milieu = (gauche + droite) / 2;
                    if (col->donnees[col->index[milieu]]->int_value < *(int*)val){
                        gauche = milieu + 1;
                    } else if (col->donnees[col->index[milieu]]->int_value > *(int*)val){
                        droite = milieu - 1;
                    } else{
                        printf("\ntrouvé @%d\n", milieu);
                        return 1;
                    }
                }
                printf("\npas trouvé");
                return 0;
            }
            break;
        case UINT:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                int gauche = 0;
                int droite = col->taille_logique - 1;
                int milieu = 0;
                while (gauche<= droite){
                    int milieu = (gauche + droite) / 2;
                    if (col->donnees[col->index[milieu]]->uint_value < *(unsigned int*)val){
                        gauche = milieu + 1;
                    } else if (col->donnees[col->index[milieu]]->uint_value > *(unsigned int*)val){
                        droite = milieu - 1;
                    } else{
                        printf("\ntrouvé @%d\n", milieu);
                        return 1;
                    }
                }
                printf("\npas trouvé");
                return 0;
            }
            break;
        case CHAR:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                int gauche = 0;
                int droite = col->taille_logique - 1;
                int milieu = 0;
                while (gauche<= droite){
                    int milieu = (gauche + droite) / 2;
                    if (col->donnees[col->index[milieu]]->char_value < *(char*)val){
                        gauche = milieu + 1;
                    } else if (col->donnees[col->index[milieu]]->int_value > *(char*)val){
                        droite = milieu - 1;
                    } else{
                        printf("\ntrouvé @%d\n", milieu);
                        return 1;
                    }
                }
                printf("\npas trouvé");
                return 0;
            }
            break;
        case FLOAT:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                int gauche = 0;
                int droite = col->taille_logique - 1;
                int milieu = 0;
                while (gauche<= droite){
                    int milieu = (gauche + droite) / 2;
                    if (col->donnees[col->index[milieu]]->float_value < *(float*)val){
                        gauche = milieu + 1;
                    } else if (col->donnees[col->index[milieu]]->float_value > *(float*)val){
                        droite = milieu - 1;
                    } else{
                        printf("\ntrouvé @%d\n", milieu);
                        return 1;
                    }
                }
                printf("\npas trouvé");
                return 0;
            }
            break;
        case DOUBLE:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                int gauche = 0;
                int droite = col->taille_logique - 1;
                int milieu = 0;
                while (gauche<= droite){
                    int milieu = (gauche + droite) / 2;
                    if (col->donnees[col->index[milieu]]->double_value < *(double *)val){
                        gauche = milieu + 1;
                    } else if (col->donnees[col->index[milieu]]->double_value > *(double *)val){
                        droite = milieu - 1;
                    } else{
                        printf("\ntrouvé @%d\n", milieu);
                        return 1;
                    }
                }
                printf("\npas trouvé");
                return 0;
            }
            break;
        case STRING:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                int gauche = 0;
                int droite = col->taille_logique - 1;
                int milieu = 0;
                while (gauche<= droite){
                    int milieu = (gauche + droite) / 2;
                    if (col->donnees[col->index[milieu]]->string_value[0] < *(char*)val){
                        gauche = milieu + 1;
                    } else if (col->donnees[col->index[milieu]]->string_value[0] > *(char*)val){
                        droite = milieu - 1;
                    } else{
                        printf("\ntrouvé @%d\n", milieu);
                        return 1;
                    }
                }
                printf("\npas trouvé");
                return 0;
            }
            break;
        case STRUCTURE:
            break;
    }
}
