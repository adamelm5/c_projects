#ifndef FICHIERS_H
#define FICHIERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum type {
    COUNTRIES = 0,
    CITIES = 1,
    ANIMALS = 2,
    TYPES_NUMBER
};

enum fichiers {
    pays = 0,
    cities,
    animals
};


char * type_to_string(enum type t);
enum type insert__type();
enum fichiers type_to_file(enum type t);
char * file_name(enum type f);
int lines__number(const char *nomFichier);
char* random__element(const char* nomFichier);

#endif // FICHIERS_H