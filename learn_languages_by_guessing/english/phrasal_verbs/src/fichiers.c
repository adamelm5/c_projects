#include "fichiers.h"
#include "manip.h"

char * type_to_string(enum type t){
    switch (t) {
        case (A1_VERBS) : return "A1_verbs";
        case (A2_VERBS) : return "A2_verbs";
        case (B1_VERBS) : return "B1_verbs";
        case (B2_VERBS) : return "B2_verbs";
        default : return NULL;
    }
}

enum type insert__type(){
    printf("\n                     Advinhe o verbo !\n\n");
    printf("Escolha o seu nivel : \n");
    for (enum type t = 0; t < TYPES_NUMBER; t++) printf("  %s : %d \n", type_to_string(t), t);

    printf("Sua escolha : ");
    enum type d;
    int result = scanf("%d", (int *)&d);

    while (result != 1 || d >= TYPES_NUMBER || d < 0){
        printf("Tente uma escolha válida entre 0 e %d !\nSua escolha : ", TYPES_NUMBER - 1);
        result = scanf("%d", (int *)&d);
    }
    printf("\nAdvinhe o verbo %s : \n", type_to_string(d));
    return d;
}


enum fichiers type_to_file(enum type t) {
    switch (t) {
        case A1_VERBS: return a1_verbs;
        case A2_VERBS: return a2_verbs;
        case B1_VERBS: return b1_verbs;
        case B2_VERBS: return b2_verbs;
        default: return b1_verbs; 
    }
}

char *file_name(enum type f) {
    switch (f) {
        case A1_VERBS: return "../txt/a1_verbs.txt";
        case A2_VERBS: return "../txt/a2_verbs.txt";
        case B1_VERBS: return "../txt/b1_verbs.txt";
        case B2_VERBS: return "../txt/b2_verbs.txt";
        default: return NULL;
    }
}

// se trouve toujours dans la 1ere ligne 
int lines__number(const char *nomFichier){
    FILE *fichier = fopen(nomFichier, "r");
    char ligne[5];
    fgets(ligne, sizeof(ligne), fichier);
    int entier = atoi(ligne);
    fclose(fichier);
    return entier;
}

unsigned int random__line(const char* nomFichier){
    FILE* fichier = fopen("../txt/countries.txt", "r");
    int n = 3*(aleatoire(lines__number(nomFichier)) + 1) + 1;
    return n;
}

char* line__from_random_int(int n, const char* nomFichier){
    FILE* fichier = fopen(nomFichier, "r");
    char ligne[200]; 
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
