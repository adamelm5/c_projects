
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "phrasal_verbs.h"

// is *c a verb ? starts with an alphabet
int is_starter_verb(char * c){
    char e = tolower(c[0]);
    return isalpha(e);
}

// is *c a phrasal verb ? starts with '-'
int is_phrasal_verb(char * c){
    return (c[0] == '-');
}

// from a such line : 
// "- Set in: To begin and continue."
// extracts    "Set in"
char * phrasal_verb(char * phrase){

    char *debut = strchr(phrase, '-') + 1; //nvl fct decouverte strchr
    char *fin = strchr(phrase, ':');

    if (debut != NULL && fin != NULL && debut < fin){
        debut++;
        int longueur = fin - debut;
        char *resultat = (char *)malloc((longueur + 1) * sizeof(char));
        strncpy(resultat, debut, longueur);
        resultat[longueur] = '\0'; 
        return resultat;
    }
}

// from a such line : 
// "- Set in: To begin and continue."
// extracts    "To begin and continue"
char * definition(char *phrase){

    char *debut = strchr(phrase, ':') +1 ;
    char *fin = strchr(phrase, '.');

    if (debut != NULL && fin != NULL && debut < fin){
        debut++;
        int longueur = fin - debut;
        char *resultat = (char *)malloc((longueur + 1) * sizeof(char));
        strncpy(resultat, debut, longueur);
        resultat[longueur] = '\0'; 
        return resultat;
    }
}

// counts the starter verbs in a file
int number_of_starter_verbs(const char * filename){

    FILE *fichier = fopen(filename, "r");

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fichier) != NULL) {
        if (is_starter_verb(line)) count++;
    }

    fclose(fichier);
    return count;
}

// retourne une telle liste à partir du random ième verbe :
// ["- Get away with: To avoid punishment.", 
// "- Get down: To feel sad or depressed."]
char **phrasal_verbs_lines(const char *filename, int random) {
    
    FILE *fichier = fopen(filename, "r");
    char **lines = malloc(MAX_ROWS * sizeof(char *));

    char line[256];
    int n = random + 1;
    int index = 0;

    while (fgets(line, sizeof(line), fichier)) {
        if (n && is_phrasal_verb(line)) continue;
        if (is_starter_verb(line)) n--;
        if (n == 0 && is_phrasal_verb(line)){
            lines[index] = malloc(strlen(line) + 1);            
            strcpy(lines[index], line);
            index++;
        }
    }

    for (int i = index; i < MAX_ROWS; i++) lines[i] = NULL;
    fclose(fichier);
    return lines;
}

// la on parle vraiment en entiers non nuls, comme en francais
int line_of_verb(int n, char * filename){

    FILE *fichier = fopen(filename, "r");

    int count = 0;
    int count2 = 0;
    char line[256];

    while (fgets(line, sizeof(line), fichier) != NULL && count != n) {
        if (is_starter_verb(line)) count++;
        count2++;
    }

    fclose(fichier);
    return count2;
}

int random_int(int n){
    return rand() % n;
}

char *** matrix_from_list(char ** list){
    char ***matrix = malloc(MAX_ROWS * sizeof(char **));
    for (size_t i = 0; i < MAX_ROWS; i++) {
        matrix[i] = malloc(2 * sizeof(char *));
        if (list[i] == NULL) {
            matrix[i][0] = NULL;
            matrix[i][1] = NULL;
        } else {
            matrix[i][0] = phrasal_verb(list[i]);
            matrix[i][1] = definition(list[i]);
        }
    }
    return matrix;
}
