#include "manip.h"
#include "fichiers.h"


int main(){
    srand(time(NULL));
    enum type type = insert__type();
    char * filename = file_name(type);
    int n = random__line(filename);
    char * word = line__from_random_int(n, filename);
    char * definition = line__from_random_int(n+1, filename);
    one__round(word, definition);
}
