#include "fichiers.h"
#include "manip.h"


int lines__number(){
    FILE *fichier = fopen("txt/countries.txt", "r");
    char ligne[5];
    fgets(ligne, sizeof(ligne), fichier);
    int entier = atoi(ligne);
    fclose(fichier);
    return entier;
}

unsigned int random__line(){
    FILE* fichier = fopen("txt/countries.txt", "r");
    if (! fichier) printf(" nn hh\n");
    int n = 4*(aleatoire(lines__number()) + 1) + 1;
    return n;
}

char* country__from_random_int(int n){
    FILE* fichier = fopen("txt/countries.txt", "r");
    if (! fichier) printf(" nn hh\n");
    char ligne[70]; 
    int lines = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL){
        lines++;
        if (lines == n) {
            fclose(fichier); 
            ligne[strcspn(ligne, "\n")] = '\0';
            char* resultat = malloc(strlen(ligne) + 1);
            strcpy(resultat, ligne);
            //printf("Ligne trouvée : %s, ce mot a %lu lettres\n", resultat, strlen(resultat));
            return resultat;
        }
    }
    fclose(fichier);
    return NULL;
}

char* continent__from_random_int(int n){
    FILE* fichier = fopen("txt/countries.txt", "r");
    if (! fichier) printf(" nn hh\n");
    char ligne[70]; 
    int lines = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL){
        lines++;
        if (lines == n) {
            fclose(fichier); 
            ligne[strcspn(ligne, "\n")] = '\0';
            char* resultat = malloc(strlen(ligne) + 1) + 1;
            strcpy(resultat, ligne);
            //printf("Ligne trouvée : %s, ce mot a %lu lettres\n", resultat, strlen(resultat));
            return resultat;
        }
    }
    fclose(fichier);
    return NULL;
}

char* capital__from_random_int(int n){
    FILE* fichier = fopen("txt/countries.txt", "r");
    if (! fichier) printf(" nn hh\n");
    char ligne[70]; 
    int lines = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL){
        lines++;
        if (lines == n) {
            fclose(fichier); 
            ligne[strcspn(ligne, "\n")] = '\0';
            char* resultat = malloc(strlen(ligne) + 1) + 1;
            strcpy(resultat, ligne);
            //printf("Ligne trouvée : %s, ce mot a %lu lettres\n", resultat, strlen(resultat));
            return resultat;
        }
    }
    fclose(fichier);
    return NULL;
}