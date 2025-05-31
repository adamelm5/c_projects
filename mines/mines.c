#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_X 10
#define MAX_Y 10

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define MAGENTA "\x1b[35m"

struct position {
    unsigned int x; 
    unsigned int y;
};

struct tile {
    struct position position;
    unsigned int is_explosive;
    unsigned int hidden;
    unsigned int mines_nearby;
    unsigned int is_marqued;
};

struct tile board[MAX_X][MAX_Y];

/* creates and returns a position struct */
struct position p(unsigned int x, unsigned int y){
    struct position p;
    p.x = x;
    p.y = y;
    return p;
}

/* checks if a position is valid 
   MAX_X < x, y <MAX_Y */
int is_valid_position(int x, int y){
    return (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y);
}

/* returns the number of explosive neighbours of a tile */
unsigned int explosive_neighbours(struct tile t){
    unsigned int tab[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, 
                              {0, -1},           {0, 1}, 
                              {1, -1},  {1, 0},  {1, 1}};
    unsigned int count = 0;
    for (int e = 0; e < 8; e++){
        if (is_valid_position( t.position.x + tab[e][0], t.position.y + tab[e][1] ) 
            && board[t.position.x + tab[e][0]][t.position.y + tab[e][1]].is_explosive) count++;
    }
    return count;
}

/* returns the number of hidden neighbours of a tile */
unsigned int hidden_neighbours(struct tile t){
    unsigned int tab[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, 
                              {0, -1},           {0, 1}, 
                              {1, -1},  {1, 0},  {1, 1}};
    unsigned int count;
    for (int e = 0; e < 8; e++){
        if (is_valid_position( t.position.x + tab[e][0], t.position.y + tab[e][1] ) 
            && board[t.position.x + tab[e][0]][t.position.y + tab[e][1]].hidden) count++;
    }
    return count;
}

/* initializes the board of the game : 
    every tile gets its position
    mines are placed randomly
    every tile gets the number of mines nearby
    non explosive tiles are revealed randomly
*/
void initialise_board(unsigned int num_mines, unsigned int num_revealed) {
    srand(time(NULL));

    // initialize the board
    for (int x = 0; x < MAX_X; x++) {
        for (int y = 0; y < MAX_Y; y++) {
            board[x][y].position = p(x, y);
            board[x][y].is_explosive = 0;
            board[x][y].hidden = 1;
            board[x][y].mines_nearby = 0;
        }
    }

    // mines are placed randomly
    for (unsigned int i = 0; i < num_mines; i++) {
        int x = rand() % MAX_X;
        int y = rand() % MAX_Y;
        while (board[x][y].is_explosive){
            x = rand() % MAX_X;
            y = rand() % MAX_Y;
        }
        board[x][y].is_explosive = 1;
    }

    // count the number of explosive neighbours
    for (int x = 0; x < MAX_X; x++) {
        for (int y = 0; y < MAX_Y; y++) {
            board[x][y].mines_nearby = explosive_neighbours(board[x][y]);
        }
    }

    // reveal non mined tiles randomly
    for (unsigned int i = 0; i < num_revealed; i++) {
        int x = rand() % MAX_X;
        int y = rand() % MAX_Y;
        while (board[x][y].is_explosive || !board[x][y].hidden){
            x = rand() % MAX_X;
            y = rand() % MAX_Y;
        }
        board[x][y].hidden = 0;
    }
}

// Function to display the board
void afficher_board(unsigned int a, unsigned int b) {

    printf("    ");
    for (int y = 0; y < MAX_Y; y++) {
        printf(" %2d  ", y);
    }
    printf("\n");


    printf("    ╔");
    for (int y = 0; y < MAX_Y; y++) {
        printf("════");
        if (y < MAX_Y - 1) printf("╦");
    }
    printf("╗\n");


    for (int x = 0; x < MAX_X; x++) {

        printf("%2d  ║", x);

        for (int y = 0; y < MAX_Y; y++) {
            if (board[x][y].hidden) {
                if (board[x][y].is_marqued) printf(" 🟥 ║");
                else printf(" ⬜ ║");
            } else if (board[x][y].is_explosive) {
                printf(" 💣 ║");
            } else {
                if (board[x][y].mines_nearby) printf(" %d  ║", board[x][y].mines_nearby);
                else printf("    ║");
            }
        }
        printf("\n");


        if (x < MAX_X - 1) {
            printf("    ╠");
            for (int y = 0; y < MAX_Y; y++) {
                printf("════");
                if (y < MAX_Y - 1) printf("╬");
            }
            if (x == 1 && a) printf("╣       nombre de mines : %d\n", a);
            if (x == 2 && b) printf("╣       nombre de cases cachées : %d\n", b);
            if ((x != 2 || !b) && (x != 1 || !a)) printf("╣\n");
        }
    }


    printf("    ╚");
    for (int y = 0; y < MAX_Y; y++) {
        printf("════");
        if (y < MAX_Y - 1) printf("╩");
    }
    printf("╝\n ");
}

// function allowing the player to interact with the game, asks the position
// to choose and the option to mark or reveal the tile
// returns 1 if the chosen position to reveal is explosive
int deminer() {
    char e[50];
    char m;

    printf("Entrez les coordonnées de la case (ex: 42 m pour marquer, 42 d pour déminer): ");
    scanf("%s %c", e, &m);

    if (!(strlen(e) == 2 && isdigit(e[0]) && isdigit(e[1]))) {
        printf("\nVeuillez entrer une coordonnée valide (deux chiffres) !\n\n");
        return 2;
    }

    unsigned int x = e[1] - '0';
    unsigned int y = e[0] - '0';
    printf("x : %d, y : %d\n", x, y);

    if (!is_valid_position(x, y)) {
        printf("\nPosition invalide ! Veuillez choisir des coordonnées entre 0 et %d.\n\n", MAX_X - 1);
        return 2;
    }

    if (m == 'm') {
        if (!board[x][y].hidden) {
            printf("\nCette case n'est pas cachée, inutile de la marquer ;)\n\n");
            return 2;
        }
        board[x][y].is_marqued = !board[x][y].is_marqued;
        return 2;
    }

    if (m != 'd') {
        printf("\nVeuillez ajouter 'm' ou 'd' après votre position choisie (ex: 42 d).\n\n");
        return 2;
    }

    if (board[x][y].is_marqued) {
        printf("\nPosition marquée ! Veuillez démarquer avant de déminer.\n\n");
        return 2;
    }

    if (!board[x][y].hidden) {
        printf("\nCette case est déjà révélée !\n\n");
        return 2;
    }

    board[x][y].hidden = 0;

    if (board[x][y].is_explosive)
        return 0;
    return 1;
}


/* function that prints a string inside a box with a color */
void cadrer(const char *p, const char *color) {

    int length = strlen(p);

    printf("%s                     ╔", color);
    for (int i = 0; i < length + 2; i++) printf("═");
    printf("╗\n");

    printf("                     ║       %s%s       ║\n", color, p);

    printf("%s                     ╚", color);
    for (int i = 0; i < length + 2; i++) printf("═");
    printf("╝\n\x1b[0m");
}

/* main function : game loop */
int main(){
    printf("\n");
    cadrer("💣💣💣  BIENVENU AU JEU DEMINER  💣💣💣", MAGENTA);
    unsigned int num_mines = MAX_X*MAX_Y/5;
    unsigned int num_revealed = MAX_X*MAX_Y/3; 
    initialise_board(num_mines, num_revealed);
    unsigned int hidden_tiles = MAX_X*MAX_Y - num_revealed;
    afficher_board(num_mines, hidden_tiles);
    int a = 1;
    while(a){
        a = deminer();
        if (a == 1) hidden_tiles --;
        afficher_board(num_mines, hidden_tiles);
        if (hidden_tiles == num_mines){
            break;
        }
    }
    for (int x = 0; x < MAX_X; x++) {
        for (int y = 0; y < MAX_Y; y++) {
            board[x][y].hidden = 0;
            board[x][y].mines_nearby = 0;
        }
    }

    if(!a){
        printf("\n");
        afficher_board(num_mines, 0);
        printf("\n");
        cadrer("  💣💣💣 VOUS AVEZ PERDU ! 💣💣💣  ", RED);  
        printf("\n");  
    }
    else {
        printf("\n");  
        cadrer("  🏆🏆🏆 VOUS AVEZ GAGNE ! 🏆🏆🏆  ", GREEN);
        printf("\n");  
    }

    return 0;
}