#include "manip.h"
#include "fichiers.h"

int main(){
    srand(time(NULL));
    enum type t = insert__type();
    char * type_s = type_to_string(t);
    char * filename = file_name(t);
    char * element = random__element(filename);
    one__round(element, type_s);
    free(element);
}
