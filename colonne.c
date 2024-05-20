
/*======================================================================================================================
                                CDataframe par Lilian CAO et Valentin GONCALVES
Ce fichier contient toutex les fonctions qui permettent de gérer le fonctionnement des colonnes dans le CDataframe.
 Il est donc essentiel pour le bon fonctionnement du projet et assure gestion des données.
======================================================================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colonne.h"

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : creer_colonne
 La fonction creer_colonne a pour but de générer une colonne du type souhaité par l'utilisateur.
 Elle prend en paramètre le type voulut pour cette colonne et le titre que l'utilisateur souhaite pour cette colonne.
 Cette fonction renvoit un une colonne pointeur du type struct Colonne qui contient tout ce qui est nécessaire pour une
 colonne, tout ces paramètres sont d'ailleur initialisé dans cette fonction.
----------------------------------------------------------------------------------------------------------------------*/

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
    return nouvelle_colonne;
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : inserer_valeur
La fonction inserer_valeur a pour but comme sont nom l'indique d'insérer une valeur dans uen colonne.
 Elle prend en paramètre un pointeur colonne de type colonne et un pointeur valeur de type void pour que la valeur
 puisse être de n'importe quel type.
 Cette fonction renvoit un entier (-1 ou 0) celon la réussite de l'insertion de la valeur.
----------------------------------------------------------------------------------------------------------------------*/


int inserer_valeur(Colonne* colonne, void* valeur) {
    //Initialise la colonne si ce n'est pas deja fait.
    if (colonne->donnees == NULL){
        colonne->donnees = (COL_TYPE**) malloc(255*sizeof(COL_TYPE*));
    }
    // Alloue de la mémoire pour la valeur
    colonne->donnees[colonne->taille_logique] = (COL_TYPE*)malloc(sizeof(COL_TYPE));

    if (colonne->index == NULL){
        colonne->index = (long long unsigned*) malloc(255* sizeof(long long unsigned));
    }
    colonne->index[colonne->taille_logique] = colonne->taille_logique;

    //Switch pour savoir quel est le type de la valeur et pouvoir la caster dans le bon type
    //Vérifie pour chaque type si la valeur est NULL
    switch (colonne->type_colonne) {
        case UINT:
            if (valeur == NULL){
                colonne->donnees[colonne->taille_logique]->int_value = 0;
                break;
            }
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
            if (valeur == NULL){
                colonne->donnees[colonne->taille_logique]->float_value = 0;
                break;
            }
            colonne->donnees[colonne->taille_logique]->float_value = *(float*)valeur;
            break;
        case DOUBLE:
            if (valeur == NULL){
                colonne->donnees[colonne->taille_logique]->double_value = 0;
                break;
            }
            colonne->donnees[colonne->taille_logique]->double_value = *(double*)valeur;
            break;
        case STRING:
            if (valeur == NULL){
                colonne->donnees[colonne->taille_logique]->string_value = NULL;
                break;
            }
            colonne->donnees[colonne->taille_logique]->string_value = (char*)malloc(strlen((char*)valeur) + 1);
            strcpy(colonne->donnees[colonne->taille_logique]->string_value, (char*)valeur);

            break;
        case STRUCTURE:
            colonne->donnees[colonne->taille_logique]->struct_value = valeur;
            break;
        default:
            return -1;
    }

    //Applique le bon index
    if (colonne->valid_index == 1){ //si trié alors partiellement trié
        colonne->valid_index = -1;
    }else if (colonne->valid_index == -1){ //si partiellement trié alors non trié
        colonne->valid_index = 0;
    }else{
        colonne->valid_index = 0;   //sinon ça reste pas trié
    }
    colonne->taille_logique++;

    return 0;
}


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : convertir_valeur
La fonction convertir valeur a pour but de convertir une valeur en chaine de caractère. Cela permet de faciliter la
 gestion de donnés dans la suite du projet.
 La fonction prend en paramètre un pointeur colonne de type Colonne, la position de la valeur à changer, un pointeur
 d'une chaine de caractère pour pouvoir y mettre la valeur convertit et la taille logique de cette chaine de caractères.
 La fonction ne renvoit rien car la chaine de caractère est allouée dynamiquement, elle est donc accescible.
----------------------------------------------------------------------------------------------------------------------*/


void convertir_valeur(Colonne *col, unsigned long long int position, char *str, int taille_logique){
    if(col->donnees != NULL) {
        //Switch pour transformer chaques valeurs en chaine de caractères avec la fonction snprintf
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


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : afficher_colonne
Comme son nom l'indique, cette fonction a pour but d'afficher le contenu d'une colonne peut importe son type.
 Elle prend en paramètre un pointeur colonne de la colonne à afficher.
 Elle ne renvoit rien puisqu'elle affiche déjà la colonne dans la fonction.
----------------------------------------------------------------------------------------------------------------------*/



void afficher_colonne(Colonne* colonne){
    //La fonction affiche le titre de la colonne avant de la parcourir pour convertir chaque valeur et l'afficher.
    char str[256];
    printf("%s\n", colonne->titre);
    for (int i = 0; i < colonne->taille_logique; i++){
        convertir_valeur(colonne,i,str,256);
        printf("[%d]\t%s\t\t", i, str);
    }
    printf("\n");
}


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : nombre_occurence_valeur
Cette fonction cherche le nombre de fois qu'une valeur donnée est présente dans une colonne.
 Elle prend en paramètre la valeur à chercher et la colonne dans laquelle il faut chercher.
 Elle renvoit le nombre de fois que la valeur a été trouvé.
----------------------------------------------------------------------------------------------------------------------*/


int nombre_occurence_valeur(Colonne* colonne, void* valeur) {
    int cpt = 0;
    char str[256];
    char char_temp[256];
    //Vérifie que la colonne n'est pas null
    if (colonne == NULL || colonne->donnees == NULL) {
        return 0;
    }
    // Fait un switch pour convertir la valeur donné en chaine de caractère.
    switch (colonne->type_colonne) {
        case INT:
            snprintf(char_temp, sizeof(char_temp), "%d", *(int *)valeur);
            break;
        case UINT:
            snprintf(char_temp, sizeof(char_temp), "%u", *(unsigned int *)valeur);
            break;
        case CHAR:
            snprintf(char_temp, sizeof(char_temp), "%c", *(char *)valeur);
            break;
        case FLOAT:
            snprintf(char_temp, sizeof(char_temp), "%f", *(float *)valeur);
            break;
        case DOUBLE:
            snprintf(char_temp, sizeof(char_temp), "%lf", *(double *)valeur);
            break;
        case STRING:
            snprintf(char_temp, sizeof(char_temp), "%s", (char *)valeur);
            break;
        default:
            return 0;
    }
    //Convertit chaque valeur de la colonne et la compare avec la valeur donnée.
    for(int i = 0; i < colonne->taille_logique; ++i) {
        convertir_valeur(colonne, i, str, sizeof(str));
        if (strcmp(str, char_temp) == 0) {
            cpt++;
        }
    }

    return cpt;
}


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : retourner_valeur_a_x
Cette fonction renvoit la valeur présente à la position x d'une colonne, avec x donné par l'utilisateur.
La fonction prend en paramètre la colonne et la position demandé par l'utilisateur.
 Elle renvoit la valeur présente à cette position sous la forme d'une chaine de caractères.
----------------------------------------------------------------------------------------------------------------------*/


char* retourne_valeur_a_x(Colonne* colonne, int x) {
    //Vérifie que la postion x est présente dans la colonne
    if (x >= colonne->taille_logique || x < 0) {
        return NULL;
    }
    //Alloue de la mémoire pour la chaine de caractère
    char* valeur = malloc(256 * sizeof(char));
    if (valeur == NULL) {
        return NULL;
    }
    //Converti la valeur présente à la position et la retourne
    convertir_valeur(colonne, x, valeur, 256);
    return valeur;
}


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : nombre_occurence_supérieur
Cette fonction cherche le nombre de valeur supérieur à la valeur donnée par l'utilisateur dans cette colonne.
 Elle prend en paramètre la valeur avec laquelle il faut comparer et la colonne dans laquelle il faut chercher.
 Elle renvoit le nombre de valeurs supérieur à la valeur donnée.
----------------------------------------------------------------------------------------------------------------------*/



int nombre_occurence_superieur(Colonne* colonne, void* valeur) {
    int cpt = 0;
    //Regarde si la colonne est Null et arrete la fonction si c'est le cas
    if (colonne == NULL || colonne->donnees == NULL) {
        return 0;
    }
    //Fait un switch pour comparer avec le type de la colonne
    switch (colonne->type_colonne) {
        //Pour chaque cas fait une boucle pour comparer chaque valeur de la colonne avec la valeur donnée par
        //l'utilisateur en la castant avec le bon type, on rajoute 1 au compteur si la condition est vérifié.
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
                char char_temp[256];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) > 0) cpt++;
            }
            break;
        case STRING:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                char char_temp[256];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) > 0) cpt++;
            }
            break;
        default:
            return 0;
    }

    return cpt;

}


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : nombre_occurence_inférieur
Cette fonction cherche le nombre de valeur inférieur à la valeur donnée par l'utilisateur dans cette colonne.
 Elle prend en paramètre la valeur avec laquelle il faut comparer et la colonne dans laquelle il faut chercher.
 Elle renvoit le nombre de valeurs inférieur à la valeur donnée.
----------------------------------------------------------------------------------------------------------------------*/


int nombre_occurence_inferieur(Colonne* colonne, void* valeur) {
    int cpt = 0;
    //Regarde si la colonne est Null et arrete la fonction si c'est le cas
    if (colonne == NULL || colonne->donnees == NULL) {
        return 0;
    }
    //Fait un switch pour comparer avec le type de la colonne
    switch (colonne->type_colonne) {
        //Pour chaque cas fait une boucle pour comparer chaque valeur de la colonne avec la valeur donnée par
        //l'utilisateur en la castant avec le bon type, on rajoute 1 au compteur si la condition est vérifié.
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
                char char_temp[256];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) < 0) cpt++;
            }
            break;
        case STRING:
            for (int i = 0; i < colonne->taille_logique; ++i) {
                char char_temp[256];
                snprintf(char_temp, sizeof(char_temp), "%c", *(char *)colonne->donnees[i]);
                if (strcmp(char_temp, (char *) valeur) < 0) cpt++;
            }
            break;
        default:
            return 0;
    }

    return cpt;
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : partition_int
La fonction a pour but de partitionner une colonne de entiers relatifs pour l'algorithme de tri rapide.
La focntion prend en paramètre la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
Elle retiurne l'indice de pivot après partitionnement.
----------------------------------------------------------------------------------------------------------------------*/
int partition_int(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    int pivot = col->donnees[col->index[droite]]->int_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        // Vérification de la condition pour le tri selon sort_dir
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->int_value <= pivot) : (col->donnees[col->index[j]]->int_value >= pivot)) {
            i = i + 1;
            // Échange des index
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }
    // Placement du pivot à sa position correcte
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    return (i + 1);
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : partition_uint
La fonction a pour but de partitionner une colonne de entiers naturels pour l'algorithme de tri rapide.
La focntion prend en paramètre la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
Elle retiurne l'indice de pivot après partitionnement.
----------------------------------------------------------------------------------------------------------------------*/
int partition_uint(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    unsigned int pivot = col->donnees[col->index[droite]]->uint_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        // Vérification de la condition pour le tri selon sort_dir
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->uint_value <= pivot) : (col->donnees[col->index[j]]->uint_value >= pivot)) {
            i = i + 1;
            // Échange des index
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }
    // Placement du pivot à sa position correcte
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    return (i + 1);
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : partition_char
La fonction a pour but de partitionner une colonne de caracttères pour l'algorithme de tri rapide.
La focntion prend en paramètre la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
Elle retiurne l'indice de pivot après partitionnement.
----------------------------------------------------------------------------------------------------------------------*/
int partition_char(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    char pivot = col->donnees[col->index[droite]]->char_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        // Vérification de la condition pour le tri selon sort_dir
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->char_value <= pivot) : (col->donnees[col->index[j]]->char_value >= pivot)) {
            i = i + 1;
            // Échange des index
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }
    // Placement du pivot à sa position correcte
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    return (i + 1);
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : partition_float
La fonction a pour but de partitionner une colonne de floatant pour l'algorithme de tri rapide.
La focntion prend en paramètre la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
Elle retiurne l'indice de pivot après partitionnement.
----------------------------------------------------------------------------------------------------------------------*/
int partition_float(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    float pivot = col->donnees[col->index[droite]]->float_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        // Vérification de la condition pour le tri selon sort_dir
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->float_value <= pivot) : (col->donnees[col->index[j]]->float_value >= pivot)) {
            i = i + 1;
            // Échange des index
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }
    // Placement du pivot à sa position correcte
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    return (i + 1);
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : partition_double
La fonction a pour but de partitionner une colonne de doubles pour l'algorithme de tri rapide.
La focntion prend en paramètre la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
Elle retiurne l'indice de pivot après partitionnement.
----------------------------------------------------------------------------------------------------------------------*/
int partition_double(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    double pivot = col->donnees[col->index[droite]]->double_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        // Vérification de la condition pour le tri selon sort_dir
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->double_value <= pivot) : (col->donnees[col->index[j]]->double_value >= pivot)) {
            i = i + 1;
            // Échange des index
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }
    // Placement du pivot à sa position correcte
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    return (i + 1);
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : partition_string
La fonction a pour but de partitionner une colonne de chaînes de caractères pour l'algorithme de tri rapide.
La focntion prend en paramètre la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
Elle retiurne l'indice de pivot après partitionnement.
----------------------------------------------------------------------------------------------------------------------*/
int partition_string(Colonne* col, int gauche, int droite, int sort_dir){
    int i = gauche - 1;
    char* pivot = col->donnees[col->index[droite]]->string_value;
    int temp = 0;
    for (int j = gauche; j < droite; j++){
        // Vérification de la condition pour le tri selon sort_dir
        if (sort_dir == ASC ? (col->donnees[col->index[j]]->string_value[0] <= pivot[0]) : (col->donnees[col->index[j]]->string_value[0] >= pivot[0])) {
            i = i + 1;
            // Échange des index
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }
    // Placement du pivot à sa position correcte
    temp = col->index[i + 1];
    col->index[i + 1] = col->index[droite];
    col->index[droite] = temp;
    return (i + 1);
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : partition
La fonction à pour but d'appeler la fonction de partitionnement appropriée selon le type de données de la colonne.
La focntion prend en paramètre la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
La fonction renvoit -1 s'il y a un mauvais type
----------------------------------------------------------------------------------------------------------------------*/
int partition(Colonne* col, int gauche, int droite, int sort_dir) {
    switch (col->type_colonne) {
        case INT:
            return partition_int(col, gauche, droite, sort_dir);
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
        default:
            // Erreur si le type n'est pas supporté
            return -1;
    }
}


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : QuickSort
la fonction a pour but d'effectuer un tri rapide (QuickSort) sur une colonne du Cdataframe.
Elle prend en compte la colonne à trier, l'indice de début, l'indice de fin et la direction du tri.
Elle ne renvoit rien puisqu'elle a pour but de trier le tableau.
----------------------------------------------------------------------------------------------------------------------*/
void QuickSort(Colonne* col, int gauche, int droite, int sort_dir){
    printf("QUICKSORT SORT CALLED\n");
    if (gauche < droite){
        // Partitionnement de la colonne et obtention de l'indice de pivot
        int pi = partition(col, gauche, droite, sort_dir);
        // Appels récursifs pour les sous-tableaux
        QuickSort(col, gauche, pi - 1, sort_dir);
        QuickSort(col, pi + 1, droite, sort_dir);
    }
    return;
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : Tri_insertion
La fonction a pour but d'effectuer un tri par insertion sur une colonne d'un tableau.
Elle prend en comptela colonne à trier et la direction du tri.
Elle ne renvoit rien puisqu'elle a pour but de trier le tableau.
----------------------------------------------------------------------------------------------------------------------*/
void Tri_insertion(Colonne* col, int sort_dir) {
    printf("INSERTION SORT CALLED\n");
    switch (col->type_colonne) {
        case INT:
            for (int i = 1; i < col->taille_logique; i++) {
                COL_TYPE *k = col->donnees[col->index[i]];
                int j = i - 1;
                // Tri par insertion pour les valeurs entières
                while (sort_dir == ASC ? ((j >= 0) && (col->donnees[col->index[j]]->int_value > k->int_value)) : (
                        (j >= 0) && (col->donnees[col->index[j]]->int_value < k->int_value))) {
                    col->index[j + 1] = col->index[j];
                    j = j - 1;
                }
                col->index[j + 1] = i;
            }
            col->valid_index = 1;
            break;
            // Cas pour les autres types de colonnes
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

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : sort
la fonction a pour but de trier une colonne d'un tableau en utilisant QuickSort ou le tri par insertion
 selon l'état de l'index.
Elle prend en compte la colonne à trier et la direction du tri.
Elle ne renvoit rien puisqu'elle a pour but de trier le tableau.
----------------------------------------------------------------------------------------------------------------------*/
void sort(Colonne* col, int sort_dir){
    if (col->index == NULL){
        printf("La colonne n'a pas d'index!");
    }
    if (col->valid_index == 0){
        QuickSort(col, 0, col->taille_logique - 1, sort_dir);
        col->valid_index = 1;
        return;
    }else if (col->valid_index == -1){
        Tri_insertion(col, sort_dir);
        col->valid_index = 1;
        return;
    } else if (col->valid_index == 1){
        printf("Déjà trié\n");
        return;
    } else {
        printf("Valeur invalide");
        return;
    }
}



/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : afficher_col_index
La fonction a pour but d'afficher les valeurs d'une colonne triées selon l'index.
Elle prend en paramètre la colonne à afficher.
Elle ne renvoit aucune donné puisqu'elle affiche le tableau.
----------------------------------------------------------------------------------------------------------------------*/


void afficher_col_index(Colonne* colonne) {
    char str[100];
    printf("%s par index:\n", colonne->titre);
    for (int i = 0; i < colonne->taille_logique; i++){
        convertir_valeur(colonne,colonne->index[i],str,100);
        printf("[%d]\t%s\n", i, str);
    }
}


/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : efface_index
La fonction a pour but d'effacer l'index d'une colonne et réinitialiser son état.
Elle prend en paramètre la colonne dont l'index doit être effacé.
Elle ne renvoit aucunes informations puisqu'elle se contente d'effacer l'index.
----------------------------------------------------------------------------------------------------------------------*/
void efface_index(Colonne* col){
    // Libérer la mémoire allouée pour l'index
    free(col->index);
    col->index = NULL;
    col->valid_index = 0;
}

/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : check_index
La focntion a pour but de vérifier l'état de l'index d'une colonne.
Elle prend en compte comme paramètre la colonne à vérifier.
Elle renvoit un entier représentant l'état de l'index (0 : pas d'index, -1 : index non valide, 1 : index valide).
----------------------------------------------------------------------------------------------------------------------*/
int check_index(Colonne* col){
    if (col->index == NULL){
        printf("Pas d'index!");
        return 0;
    }else if (col->valid_index == 0 || col->valid_index == -1){
        printf("Index non trié!");
        return -1;
    }else if (col->valid_index == 1){
        printf("Index trié");
        return 1;
    }
    printf("Erreur check_index");
    return 1337;
}



/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : update_index
La fonction a pour but de mettre à jour l'index d'une colonne en fonction de ses valeurs.
Elle prend en paramètre la colonne à mettre à jour.
Elle ne renvoit rien et se contente de mettre à jour dynamiquement.
----------------------------------------------------------------------------------------------------------------------*/
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



/*----------------------------------------------------------------------------------------------------------------------
                                             FONCTION : recherche_valeur_dans_colonne
Elle a pour but de rechercher une valeur dans une colonne triée en utilisant la recherche binaire.
Elle prend en compte la colonne où il faut chercheret la valeur à rechercher.
Elle renvoit un entier, 1 si la valeur est trouvé et 0 si ce n'est pas le cas.
----------------------------------------------------------------------------------------------------------------------*/
int recherche_valeur_dans_colonne(Colonne *col, void *val){
    switch (col->type_colonne) {
        case INT:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                // Recherche binaire pour les valeurs entières
                int gauche = 0;
                int droite = col->taille_logique - 1;
                while (gauche <= droite){
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
            // Cas pour les autres types de colonnes
        case UINT:
            if (col->valid_index == 0){
                printf("\nColonne n'est pas trié\n");
                return 0;
            } else {
                int gauche = 0;
                int droite = col->taille_logique - 1;
                while (gauche <= droite){
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
                while (gauche <= droite){
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
                while (gauche <= droite){
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
                while (gauche <= droite){
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
                while (gauche <= droite){
                    int milieu = (gauche + droite) / 2;
                    if (col->donnees[col->index[milieu]]->string_value[0] < *(char*)val){
                        gauche = milieu + 1;
                    } else if (col->donnees[col->index[milieu]]->string_value[0] > *(char*)val){
                        droite = milieu - 1;
                    } else{
                        printf("\ntrouvé à l'index : %d\n", milieu);
                        return 1;
                    }
                }
                printf("\nvaleur pas trouvé");
                return 0;
            }
        case STRUCTURE:
            break;
    }
}
