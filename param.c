#include "param.h"

struct Param* newParam(char* val,struct Param* next){
  struct Param* nParam = (struct Param*)malloc(sizeof(struct Param));
  //strcpy(nParam->value,val);
  nParam->value = (char*)malloc( (strlen(val))*sizeof(char) );
  strcpy(nParam->value,val);
  nParam->next = next;
  return nParam;
}

void deleteParam(struct Param* param){
  struct Param* p;
  do{
    p = param->next;
    free(param);
    param = p;
  }while(param != NULL);
}
