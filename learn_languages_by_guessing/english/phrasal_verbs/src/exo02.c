#include "../phrasal_verbs.h"


int longest_verb(char *** matrix){
    int max = 0;
    for (int i = 0; i < MAX_ROWS; i ++){
        if(matrix[i][0] && strlen(matrix[i][0]) > max) max = strlen(matrix[i][0]);
    }
    return max;
}

int longest_def(char *** matrix){
    int max = 0;
    for (int i = 0; i < MAX_ROWS; i ++){
        if(matrix[i][1] && strlen(matrix[i][1]) > max) max = strlen(matrix[i][1]);
    }
    return max;
}

void print_equal_content1(int len, char * c){
    for (int i = 0; i < len - strlen(c); i ++) printf(" ");
    printf(" %s", c);
}
void print_equal_content2(int len, char * c, int color){
    if (color == 0) printf(" %s", c);
    if (color == 1) printf("\x1b[31m %s\x1b[0m", c); //rouge
    if (color == 2) printf("\x1b[32m %s\x1b[0m", c); //vert
    for (int i = 0; i < len - strlen(c); i ++) printf(" ");

}

void print_separative(int i){
    if (i < 10) printf(" ║  %d ✦------------✦ %c ║", i, 'a'+i);
    else printf(" ║ %d ✦------------✦ %c ║", i, 'a'+i);
}

int * shuffle_list(int len){
    int *list = malloc(sizeof(int) * len);
    for (int i = 0; i < len ; i ++) list[i] = i;
    for (int i = len-1; i >0; i --){
        int tmp = list[i];
        int ran = random_int(i);
        list[i] = list[ran];
        list[ran] = tmp;
    }
    return list;
}

int num_of_lines(char *** matrix){
    int count = 0;
    for (int i = 0; i < MAX_ROWS; i++){
        if (matrix[i][0]) count ++;
    }
    return count;
}

char ***shuffle(char ***matrix) {
    int lines_num = num_of_lines(matrix);
    int *shuffled_indices = shuffle_list(lines_num);
    if (!shuffled_indices) return NULL;

    char ***new_matrix = malloc(MAX_ROWS * sizeof(char **));

    for (int i = 0; i < MAX_ROWS; i++) {
        new_matrix[i] = malloc(2 * sizeof(char *));
        if (!matrix[i][0]) {
            new_matrix[i][0] = NULL;
            new_matrix[i][1] = NULL;
            continue;
        }
        int shuffled_index = shuffled_indices[i];
        new_matrix[i][0] = strdup(matrix[i][0]);
        new_matrix[i][1] = strdup(matrix[shuffled_index][1]);
    }

    //free(shuffled_indices);
    return new_matrix;
}


void print_table(char *** matrix, int * color){
    int len_verb = longest_verb(matrix);
    int len_def = longest_def(matrix);
    printf("╔");
    for (int i = 0; i < len_verb + 2; i ++) printf("═");
    printf("╦");
    for (int i = 0; i < 21; i ++) printf("═");
    printf("╦");
    for (int i = 0; i < len_def + 2; i ++) printf("═");
    printf("╗\n");
    for (int i = 0; i < MAX_ROWS; i ++){
        if (!matrix[i][0]) continue;
        printf("║");
        print_equal_content1(len_verb, matrix[i][0]);
        print_separative(i);
        print_equal_content2(len_def, matrix[i][1], color[i]);
        printf(" ║");
        printf("\n");
    }
    printf("╚");
    for (int i = 0; i < len_verb + 2; i ++) printf("═");
    printf("╩");
    for (int i = 0; i < 21; i ++) printf("═");
    printf("╩");
    for (int i = 0; i < len_def + 2; i ++) printf("═");

    printf("╝\n");

}

void switch_defs(char *** matrix, int a, int b){
    char * tmp;
    tmp = strdup(matrix[a][1]);
    strcpy(matrix[a][1], matrix[b][1]);
    matrix[b][1] = strdup(tmp);
}

int number_of_correct_answers(char *** original, char *** response){
    int count = 0;
    for (int i = 0; i < MAX_ROWS; i ++){
        if (original[i][1] && !strcmp(original[i][1], response[i][1])) count++;
    }
    return count;
}

int char_to_int(char c){
    if (c == 'a') return 0;
    return 1 + char_to_int(c - 1);
}

int * color_list(){
    int * list = malloc(sizeof(int) * MAX_ROWS);
    for (int i = 0; i < MAX_ROWS; i ++) list[i] = 0;
    return list;
}

void fill_list(int * list, int a, int color){
    list[a] = color;
}

void free_list(int * list, int a){
    list[a] = 0;
}

void color_final_list(char *** original, char *** response, int * list){
    for (int i = 0; i < MAX_ROWS; i ++){
        if (original[i][1] && !strcmp(original[i][1], response[i][1])) list[i] = 2;
        else list[i] = 1;
    }
}

int count_non_null_lines(char *** matrix){
    int count = 0;
    for (int i = 0; i < MAX_ROWS; i ++){
        if (matrix[i][0]) count ++;
    }
    return count;
}

// link def to verb 
void exercice2(){

    //ne pas oublier srand(...)
    int lines_num = number_of_starter_verbs("../txt/phrasal_verbs.txt");
    int random = random_int(lines_num);
    char ** list = phrasal_verbs_lines("../txt/phrasal_verbs.txt", random);
    char *** original = matrix_from_list(list);
    printf("Exercice : \nLink evry verb to its definition.\n");
    char *** response = shuffle(original);
    int *color = color_list();
    int rouge = 1;
    int vert = 2;
    print_table(response, color);
    int e = 1;
    char m;
    int lines_number = count_non_null_lines(original);
    while (1){
        printf("Write a response as (number)(letter) to switch the lines, type 0a one you've done :");
        scanf("%u%c", &e, &m);
        while(e >= lines_number || char_to_int(m) >= lines_number ){
            printf("Unvalid arguments. Write your response as (number)(letter), type 0a one you've done :");
            scanf("%u%c", &e, &m);
        }
        if (e == 0 && m == 'a') break;
        switch_defs(response, e, char_to_int(m));
        fill_list(color, e, rouge);
        fill_list(color, char_to_int(m), rouge);
        print_table(response, color);
        free_list(color, e);
        free_list(color, char_to_int(m));
    }
    int correct_answers = number_of_correct_answers(original, response);
    printf("\nYour final response :\n");
    color_final_list(original, response, color);
    print_table(response, color);
    for (int i = 0; i < MAX_ROWS; i ++) fill_list(color, i, vert);
    printf("expected response :\n");
    print_table(original, color);
    char* col_c = (correct_answers == lines_number) ? "\x1b[32m" : "\x1b[31m";
    printf("\nYour final result :  %s %d / %d \n\n", col_c, correct_answers, lines_number);
}


int main(){
    srand(time(NULL));
    exercice2();
    return 0;
}