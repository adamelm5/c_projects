
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ROWS 10

// starts with an alphabet
int is_starter_verb(char * c);

// starts with '-'
int is_phrasal_verb(char * c);

char * phrasal_verb(char * phrase);

char * definition(char *phrase);

int number_of_starter_verbs(const char * filename);

// retourne une telle liste à partir du random ième verbe :
// ["- Get away with: To avoid punishment.", 
// "- Get down: To feel sad or depressed."]
char ** phrasal_verbs_lines(const char * filename, int random);

// la on parle vraiment en entiers non nuls, comme en francais
int line_of_verb(int n, char * filename);

int random_int(int n);

char *** matrix_from_list(char ** list);



// test
/*
int main(){
    srand(time(NULL));
    printf("%d\n", number_of_starter_verbs("../txt/phrasal_verbs.txt"));
    printf("%d\n", line_of_verb(2, "../txt/phrasal_verbs.txt"));
    int lines_num = number_of_starter_verbs("../txt/phrasal_verbs.txt");
    int random = random_int(lines_num);
    printf("%d\n", random);
    char ** list = phrasal_verbs_lines("../txt/phrasal_verbs.txt", random);
    for (int i = 0; i < MAX_ROWS; i++){
        if (list[i]) printf("%s\n", list[i]);
    }
    char *** sss = matrix_from_list(list);
    for (int i = 0; i < MAX_ROWS; i++){
        printf("%s\n%s\n", sss[i][0], sss[i][1]);
    } 
    return 0;
}*/