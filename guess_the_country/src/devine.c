#include "manip.h"
#include "fichiers.h"


int main(){
    srand(time(NULL));
    printf("Welcome to guess the country !\n");
    printf("Are you good enought at geography ? let's see then !\n\n");
    int n = random__line();
    char * country = country__from_random_int(n);
    char * capital = capital__from_random_int(n+2);
    char * continent = continent__from_random_int(n+1);
    one__round(country, continent, capital);
}
