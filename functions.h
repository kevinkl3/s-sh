#ifndef FUNCTIONS_H
#define FUNCITONS_H
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "param.h"
#define PATH_MAX       1024
#define HOST_NAME_MAX  128

/*Global Variables*/
char* currentPath;
char* currentUser;
char hostName[HOST_NAME_MAX];
extern char *yytext;

/*Prototypes*/
int ls(struct Param*);
int cd(struct Param*);
int makedir(struct Param*);
int potencia(int,int);
char* formatHuman(long,short);
void printError(char*);
#endif
