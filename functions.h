#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "param.h"
#define PATH_MAX       1024
#define HOST_NAME_MAX  128
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*Global Variables*/
char* currentPath;
char* currentUser;
char hostName[HOST_NAME_MAX];
extern char *yytext;

/*Prototypes*/
int ls_r(const char*,struct Param* params);
int ls(struct Param*);
int cd(struct Param*);
int makedir(struct Param*);
int mv(struct Param*);
int rm(struct Param*);
int chgrp(struct Param*);
int potencia(int,int);
char* formatHuman(long,short);
void printError(const char*);
#endif
