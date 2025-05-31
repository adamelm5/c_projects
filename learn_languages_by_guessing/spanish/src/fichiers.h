#ifndef FICHIERS_H
#define FICHIERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum type {
    A1_VERBS = 0,
    A2_VERBS,
    B1_VERBS,
    B2_VERBS,
    TYPES_NUMBER
};

enum fichiers {
    a1_verbs = 0,
    a2_verbs,
    b1_verbs,
    b2_verbs
};


char * type_to_string(enum type t);
enum type insert__type();
enum fichiers type_to_file(enum type t);
char * file_name(enum type f);
int lines__number(const char *nomFichier);
unsigned int random__line();
char* line__from_random_int(int n, const char* nomFichier);

#endif // FICHIERS_H