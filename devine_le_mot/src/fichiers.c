#include "fichiers.h"
#include "manip.h"

/* function that returns the type as a string */
char * type_to_string(enum type t){
    switch (t) {
        case (COUNTRIES) : return "country";
        case (CITIES) : return "city";
        case (ANIMALS) : return "animal";
        default : return NULL;
    }
}

/* function responsible for the user choice, it returns the type */
enum type insert__type(){
    printf("\n                     Guess the word !\n\n");
    printf("Select the type you want to guess : \n");
    for (enum type t = 0; t < TYPES_NUMBER; t++) printf("  %s : %d \n", type_to_string(t), t);

    printf("Your choice : ");
    enum type d;
    int result = scanf("%d", (int *)&d);

    while (result != 1 || d >= TYPES_NUMBER || d < 0){
        printf("Try a valid choice between 0 and %d !\nYour choice : ", TYPES_NUMBER - 1);
        result = scanf("%d", (int *)&d);
    }
    printf("\nGuess the %s : \n", type_to_string(d));
    return d;
}

/* function that returns the choice's type as a string */
enum fichiers type_to_file(enum type t) {
    switch (t) {
        case COUNTRIES: return pays;
        case CITIES: return cities;
        case ANIMALS: return animals;
        default: return pays; 
    }
}

/* function that returns the file name */
char *file_name(enum type f) {
    switch (f) {
        case pays: return "txt/pays.txt";
        case cities: return "txt/city.txt";
        case animals: return "txt/animals.txt";
        default: return NULL;
    }
}

/* function that returns the first line of a file, it represents the 
   number of lines in a file */
int lines__number(const char *nomFichier){
    FILE *fichier = fopen(nomFichier, "r");
    char ligne[5];
    fgets(ligne, sizeof(ligne), fichier);
    int entier = atoi(ligne);
    fclose(fichier);
    return entier;
}

/* function that returns a random word from a file */
char* random__element(const char* nomFichier){
    FILE* fichier = fopen(nomFichier, "r");
    // printf("Nom du fichier : %s\n", nomFichier);
    if (! fichier) fprintf(stderr, "ERROR : can't open a file\n");
    int n = aleatoire(lines__number(nomFichier)) + 1;
    char ligne[30]; 
    int lines = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL){
        lines++;
        if (lines == n) {
            fclose(fichier); 
            ligne[strcspn(ligne, "\n")] = '\0';
            char* resultat = malloc(strlen(ligne) + 1);
            strcpy(resultat, ligne);
            // printf("Ligne trouvée : %s, ce mot a %lu lettres\n", resultat, strlen(resultat));
            return resultat;
        }
    }
    fclose(fichier);
    return NULL;
}
