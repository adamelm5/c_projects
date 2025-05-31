#include "../phrasal_verbs.h"
#include "../manip.h"
#include "../fichiers.h"


char * line_from_int

int random_line(int n){
    int a = rand()%n;
    line = line_from_int();
    while (!is_phrasal_verb(line)){
        a = rand()%n;
    }
}

char ** verb_prep(char * whole_verb){
    int count1 = 0;
    while (whole_verb[count1 != " "]) count1++;
    int count2 = 0;
    while (whole_verb[count1 + count1 != "\0"]) count2++;
    char * verb = malloc(sizeof(char) * count1);
    char * prep = malloc(sizeof(char) * count2);
    
}











// boucle d'une manche
void one__round(char *verb, char * prop){
    char *hidden = new__random_char(original);

    int attempts = 6;
    if (strlen(original) > 6) attempts = 10;
    

    printf("\n Adivinhe o verbo !\n\n");
    printf("%s\n", definition);
    print__spaces_char(hidden, '=', 0);

    while (end__game(0, hidden) == -1 && attempts > 0){
        printf("\n %d tentativas restantes. Digite sua letra : ", attempts);
        char c;
        scanf(" %c", &c);

        int doing = act(original, hidden, c);
        if (doing == -1){
            printf(" ERROU :( \n");
            attempts--;
        }

        printf("               ");
        print__spaces_char(hidden, c, doing);
    }

    if (end__game(0, hidden) == 0) printf("\n ACERTOU ! O verbo é \033[32m%s\033[0m !\n", original);
    else printf("\n Game lost, the word was : \033[32m%s\033[0m \n\n", original);

    free(hidden);
}

int main(){
    exercice1()
}