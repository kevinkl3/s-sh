#include <stdlib.h>
#include <string.h>
#ifndef PARAM_H
#define PARAM_H
  struct Param* newParam(char*,struct Param*);

  struct Param{
    char* value;
    struct Param* next;
  };
#endif
