#include "manip.h"
#include <unistd.h>

// genère un nombre compris entre 0 et n-1 aléatoirement
// necessite débuter son main par ++|srand(time(NULL));
unsigned int aleatoire(unsigned int n){
    return rand() % n;
}

// compte le nombre d'un char dans une chaîne de char
// exemples : count("france", 'a') = 1
//            count("italie", 'I') = 2
size_t count(char c, char * s, int len){
    int count = 0;
    c = tolower(c);
    for (int i = 0; i < len; i++){
        if (tolower(s[i]) == c) count++;
    }
    return count;
}

// 1 si un char existe dans une chaîne de char, 0 sinon
int exists(char c, char* s, int len){
    return (count(c, s, len) != 0); 
}

// retourne la chaine de caractère issue du camouflement de 
// tous les char dans cette chaîne sauf 2 aléatoires
// exemple : france -> _ _a_ _e
char * new__random_char(char * s){

    size_t len = strlen(s);
    char * str = malloc( (len+1) * sizeof(char) );
    
    for (size_t i = 0; i < len; i++) str[i] = '_';
    for (size_t i = 0; i < len; i++){
        if (s[i] == ' ') str[i] = ' ';
    }

    str[len] = '\0';
    size_t a = aleatoire(len - 1);
    str[a] = s[a];
    size_t b = aleatoire(len - 1);
    if (len > 5){ 
        while( b == a ) b = aleatoire(len- 1);
        str[b] = s[b];
    }
    return str;
}

// affiche une chaîne de caractères espacés d'un seul espace
// exemple france -> f r a n c e
void  print__spaces_char(char * c, char x, int acts){
    for (size_t i = 0; i < strlen(c); i ++){

        if (acts == -1) printf("%c ", c[i]);
        else if (acts == 0){
            if (c[i] == x) printf("\033[31m%c\033[0m ", c[i]);
            if (c[i] != x) printf("%c ", c[i]);
        } 
    }
    printf("\n");
}

// 
int act(char * original, char * hiden, char c){
    int len = strlen(original);
    if (!exists(c, original, len)) return -1;
    for (int i = 0; i < len; i ++){
        if (tolower(original[i]) == tolower(c)) hiden[i] = original[i];
    }
    return 0;
}

// indique si le jeu est terminé ou pas encore
// le jeu est terminé si toute la chaîne hidden est révélée
// autrement dit aucun '_' n'y figure
int end__game(int i, char * hiden){
    if (i == -1) return -1;
    for (size_t i = 0; i < strlen(hiden); i ++){
        if (hiden[i] == '_') return -1;
    }
    return 0;
}

// boucle d'une manche
void one__round(char *original, char *definition) {
    char *hidden = new__random_char(original);
    int attempts = (strlen(original) > 6) ? 8 : 5;

    while (end__game(0, hidden) == -1 && attempts > 0) {
        // Réinitialisation du terminal (méthode multi-plateforme)
        #ifdef _WIN32
            system("cls");  // Pour Windows
        #else
            printf("\033[2J\033[H");  // ANSI: efface l'écran et repositionne le curseur
        #endif

        // Affichage du jeu
        printf("\n Adivine el verbo !\n\n");
        printf("%s\n\n", definition);
        printf("               ");
        print__spaces_char(hidden, '=', 0);
        printf("\n %d tentativas restantes. Escriba su letra : ", attempts);

        // Saisie utilisateur
        char c;
        scanf(" %c", &c);

        // Traitement
        int doing = act(original, hidden, c);
        if (doing == -1) {
            printf("\n SE AQUIVOCO :( \n");
            attempts--;
        } else {
            printf("\n               ");
            print__spaces_char(hidden, c, doing);
        }

        // Pause optionnelle pour la lisibilité
        usleep(2000000);  // 0.5s (nécessite <unistd.h>)
    }

    // Nettoyage final
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
    #endif

    // Résultat
    if (end__game(0, hidden) == 0) {
        printf("\n GANASTE ! El verbo era \033[32m%s\033[0m !\n", original);
    } else {
        printf("\n JUEGO PERDIDO, El verbo era : \033[32m%s\033[0m \n\n", original);
    }

    free(hidden);
}