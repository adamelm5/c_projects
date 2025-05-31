#ifndef MANIP_H
#define MANIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> 
#include <ctype.h> 


unsigned int aleatoire(unsigned int n);
size_t count(char c, char * s, int len);
int exists(char c, char* s, int len);
char * new__random_char(char * s);
void  print__spaces_char(char * c, char x, int acts);
int act(char * original, char * hiden, char c);
int end__game(int i, char * hiden);

void one__round(char *original, char *type);

#endif // MANIP_H