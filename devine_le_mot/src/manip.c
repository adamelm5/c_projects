#include "manip.h"

// generates a random number between 0 and n-1
unsigned int aleatoire(unsigned int n){
    return rand() % n;
}

// gives the count of a specific letter in a string
// examples : count("france", 'a') = 1
//            count("italie", 'I') = 2
size_t count(char c, char * s, int len){
    int count = 0;
    c = tolower(c);
    for (int i = 0; i < len; i++){
        if (tolower(s[i]) == c) count++;
    }
    return count;
}

// checks if a letter exists in a string
int exists(char c, char* s, int len){
    return (count(c, s, len) != 0); 
}

// returns the string obtained from hiding all the letters
// except two random ones
// example : france -> _ _a_ _e
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

// displays a string with spaces between the letters
// example france -> f r a n c e
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

// if the char c exists in the word, it displays it in its hidden form
// and returns -1, otherwise it returns 0
// example : france, f__nce, r -> fr_nce, -1
//           france, f__nce, d -> f__nce, 0
int act(char * original, char * hiden, char c){
    int len = strlen(original);
    if (!exists(c, original, len)) return -1;
    for (int i = 0; i < len; i ++){
        if (tolower(original[i]) == tolower(c)) hiden[i] = original[i];
    }
    return 0;
}

// tells if the game is over, it ends if the hidden word
// doesn't contain any '_'
int end__game(int i, char * hiden){
    if (i == -1) return -1;
    for (size_t i = 0; i < strlen(hiden); i ++){
        if (hiden[i] == '_') return -1;
    }
    return 0;
}

// game loop
void one__round(char *original, char *type){
    char *hidden = new__random_char(original);

    int attempts = 6;
    if (strlen(original) > 6) attempts = 10;
    
    print__spaces_char(hidden, '=', 0);

    while (end__game(0, hidden) == -1 && attempts > 0){
        printf("\n %d remaining tries. Type your letter : ", attempts);
        char c;
        scanf(" %c", &c);

        int doing = act(original, hidden, c);
        if (doing == -1){
            printf("Wrong letter :( \n");
            attempts--;
        }

        printf("               ");
        print__spaces_char(hidden, c, doing);
    }

    if (end__game(0, hidden) == 0) printf("\n CONGRATS! The %s was \033[32m%s\033[0m !\n", type, original);
    else printf("\n Game lost, the %s was : \033[32m%s\033[0m \n\n", type, original);

    free(hidden);
}
