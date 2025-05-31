#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum sign {
    ntg = 0,
    X,
    Y
};

struct tile {
    enum sign sign;
    unsigned int position;
};

struct tile board[9];

// initializes the boards positions
void initialize_board() {
    for (size_t i = 0; i < 9; i++) {
        board[i].position = i;
        board[i].sign = ntg;
    }
}

// returns the number of empty tiles
unsigned int free_tiles_number() {
    unsigned int count = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i].sign == ntg) count++;
    }
    return count;
}

// returns the opposite sign X->O, O->X, ntg->ntg
enum sign opposite_sign(enum sign s) {
    if (s == 1) return 2;
    if (s == 2) return 1;
    return s;
}

// places a sign in a tile
int put__sign(struct tile *t, enum sign s) {
    if (t->sign != ntg) return 0; 
    t->sign = s;
    return 1;
}

// returns 1 with a probability of (wins-1)/wins
int bernoulli(int wins) {
    return (rand() % wins != 0);
}

// returns a random empty position 
unsigned int random_position() {
    unsigned int pos = rand() % 9;
    while (board[pos].sign != ntg) pos = rand() % 9;
    return pos;
}

// checks if it's a winning position for a sign
int is_a_win_move(struct tile t, enum sign s) {
    if (t.sign != ntg) return 0; 

    int pos = t.position;
    if (pos == 0 && ((board[1].sign == s && board[2].sign == s) ||
                     (board[3].sign == s && board[6].sign == s) ||
                     (board[4].sign == s && board[8].sign == s))) return 1;
    if (pos == 1 && ((board[0].sign == s && board[2].sign == s) ||
                     (board[4].sign == s && board[7].sign == s))) return 1;
    if (pos == 2 && ((board[1].sign == s && board[0].sign == s) ||
                     (board[5].sign == s && board[8].sign == s) ||
                     (board[4].sign == s && board[6].sign == s))) return 1;
    if (pos == 3 && ((board[0].sign == s && board[6].sign == s) ||
                     (board[4].sign == s && board[5].sign == s))) return 1;
    if (pos == 4 && ((board[0].sign == s && board[8].sign == s) ||
                     (board[1].sign == s && board[7].sign == s) ||
                     (board[2].sign == s && board[6].sign == s) ||
                     (board[3].sign == s && board[5].sign == s))) return 1;
    if (pos == 5 && ((board[2].sign == s && board[8].sign == s) ||
                     (board[3].sign == s && board[4].sign == s))) return 1;
    if (pos == 6 && ((board[0].sign == s && board[3].sign == s) ||
                     (board[7].sign == s && board[8].sign == s) ||
                     (board[4].sign == s && board[2].sign == s))) return 1;
    if (pos == 7 && ((board[1].sign == s && board[4].sign == s) ||
                     (board[6].sign == s && board[8].sign == s))) return 1;
    if (pos == 8 && ((board[0].sign == s && board[4].sign == s) ||
                     (board[2].sign == s && board[5].sign == s) ||
                     (board[6].sign == s && board[7].sign == s))) return 1;
    return 0;
}

// returns the tile that allows winning
struct tile *winning_move(enum sign s) {
    for (size_t i = 0; i < 9; i++) {
        if (is_a_win_move(board[i], s)) return &board[i];
    }
    return NULL;
}

// tells if a tile is dangerous (allows the opponent to win int the next move)
int is_dangerous_for(struct tile t, enum sign s) {
    return (t.sign == ntg && is_a_win_move(t, opposite_sign(s)));
}

// returns a dangerous tile
struct tile *dangerous__tile(enum sign s) {
    for (size_t i = 0; i < 9; i++) {
        if (is_dangerous_for(board[i], s)) return &board[i];
    }
    return NULL;
}

// displays the board of the game
void afficher_board() {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        if (board[i].sign == 1) 
            printf(" \033[35mX\033[0m ");
        else if (board[i].sign == 2) 
            printf(" \033[34mO\033[0m ");
        else 
            printf(" \033[31m%d\033[0m ", board[i].position);

        if (i % 3 != 2) 
            printf("|");
        if (i % 3 == 2 && i != 8) 
            printf("\n---+---+---\n");
    }
    printf("\n\n");
}


// computers turn, the higher the difficulty is, the smarter the computer is
int computer__turn(enum sign s, int difficulty) {

    printf("Computer's turn : \n\n");
    int pp = bernoulli(difficulty);
    struct tile *pos;

    // if smart :
    if (pp) {
        // if a winning position exists, take it 
        pos = winning_move(s);
        // if a dangerous position exists, occupy it 
        if (!pos) pos = dangerous__tile(s);
        // if center empty, take it
        pos = &board[4];
        // if no danger take a random position
        if (!pos) pos = &board[random_position()];
    } else { // if not smart : 
        // random position
        pos = &board[random_position()];
    }

    // if is a win : the player lost
    if (is_a_win_move(*pos, s)){
        put__sign(pos, s);
        printf("You lost !\n");
        return 0;
    }

    // fill the tile
    put__sign(pos, s);

    // if no more tiles are empty, game over
    if (free_tiles_number() == 0) {
        printf("Game over, no more free tiles available\n");
        return 0;
    }

    return 1;
}

// human's turn
int human__turn(enum sign s){
    printf("Your turn : \n");
    printf("Select a valid position (0-8): ");
    unsigned int p;
    while (scanf("%u", &p) != 1 || p > 8 || board[p].sign != ntg){
        printf("\nInvalid position, select another position (0-8): ");
        while (getchar() != '\n'); 
    }

    if (is_a_win_move(board[p], s)){
        put__sign(&board[p], s);
        printf("You won !\n");
        afficher_board();
        return 0;
    }

    put__sign(&board[p], s);

    if (free_tiles_number() == 0){
        printf("Game over, no more free tiles available\n");
        return 0;
    }

    return 1;
}

// game loop
void game(int prob){
    srand(time(NULL));
    enum sign human = (rand() % 2) + 1;
    enum sign machine = opposite_sign(human);

    printf("You are %c, computer is %c\n", (human == 1) ? 'X' : 'O', (machine == 1) ? 'X' : 'O');
    afficher_board();
    while (1){
        if (!human__turn(human)) break;
        afficher_board();
        if (!computer__turn(machine, prob)) break;
        afficher_board();
    }
}


// main function
int main(){
    initialize_board();
    game(10);
    return 0;
}