#include "functions.h"
#include <sys/types.h>
#include <sys/stat.h>
#define false 0
#define true 1
#define KB 1024
#define MB 1024*1024
#define GB 1024*1024*1024
  /*SH Functions*/

  /*ls command*/
  int ls(struct Param* params){
    struct dirent *pDirent;
    DIR *pDir;

    /*OPTIONS*/
    short ALL = false;
    short RECURSIVE = false;
    short LARGE = false;
    short HUMAN = false;
    short INODE = false;

    //setup options
    struct Param* p = params;
    while(p != NULL){
        if(strcmp(p->value,"-a")==0){
          ALL = true;
        }

        if(strcmp(p->value,"-R")==0){
          RECURSIVE = true;
        }

        if(strcmp(p->value,"-l")==0){
          LARGE = true;
        }

        if(strcmp(p->value,"-h")==0){
          HUMAN = true;
        }

        if(strcmp(p->value,"-i")==0){
          INODE = true;
        }
        p = p->next;
    }

    if(currentPath == NULL){
      currentPath = (char*)malloc(3);
      sprintf(currentPath,"./");
    }
    pDir = opendir (currentPath);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", currentPath);
        return 1;
    }

    if(LARGE==true){
      printf("Links\tInode\tSize\t\tName\n");
    }
    while ((pDirent = readdir(pDir)) != NULL) {
        if(pDirent->d_name[0] != '.' || ALL == true){
          if(LARGE == false)
            printf ("%s\n", pDirent->d_name);
          else{
            struct stat* fileInfo = malloc(sizeof(struct stat));
            int strSz = strlen(currentPath) + strlen(pDirent->d_name);
            char* fname = (char*)malloc(strSz);
            sprintf(fname,"%s%s",currentPath,pDirent->d_name);
            if(stat(fname,fileInfo)==0){
              printf("%d\t%d\t%s\t%s\n",
                fileInfo->st_nlink,
                fileInfo->st_ino,
                formatHuman(fileInfo->st_size,HUMAN),
                pDirent->d_name
              );
            }else{
              printf("abs: %s",fname );
              printf ("%d %d %s\n",  pDirent->d_fileno, pDirent->d_reclen, pDirent->d_name);
            }
          }
        }

    }
    closedir (pDir);
    return 0;
  }


  int makedir(struct Param* params){
    if(params == NULL){
      printError("mkdir esperaba un parametro.");
      return 1;
    }
    char* newDirName = params->value;
    //si no es ruta absoluta
    if(newDirName[0] != '/'){
        newDirName = (char*)malloc(strlen(params->value)+strlen(currentPath));
        sprintf(newDirName,"%s%s",currentPath,params->value);
    }

    struct stat* dirStat = malloc(sizeof(struct stat));
    if(stat(newDirName,dirStat) == -1){
      //create
      printf("no existe");
    }else{
      printError("El directorio ya existe!");
    }
  }


  int cd(struct Param* params){
    //validation
    if(params == NULL){
      printf("cd esperaba un parametro.");
      return 1;
    }

    char* pDirName = params->value;

    if(currentPath == NULL || 0){
      currentPath = (char*)malloc(3);
      sprintf(currentPath,"./");
    }

    DIR* pDir;
    char targetDir[PATH_MAX];
    sprintf(targetDir,"%s%s",currentPath,pDirName);

    pDir = opendir ( targetDir);
    if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", targetDir);
            return 1;
    }

    closedir (pDir);
    char actualpath [PATH_MAX+1];
    char* ptr;
    ptr = realpath(targetDir,actualpath);
    free(currentPath);
    currentPath = malloc((strlen(ptr)+1)*sizeof(char));
    strcpy(currentPath,ptr);
    strcat(currentPath,"/");
    printf("changed to dir: %s \n",currentPath);

    return 0;
  }

  int potencia(int a, int b){
      return b <= 0 ? 1 : a * potencia(a,b-1);
  }

  char* formatHuman(long bytes,short flag){
    char* cantidad = malloc(16*sizeof(char));
    if(flag == false){
      sprintf(cantidad,"%d",bytes);
      return cantidad;
    }

    if(bytes > GB){
      long gigas = bytes/GB;
      bytes -= gigas*GB;
      long megas = bytes/MB;
      sprintf(cantidad,"%d.%dG",gigas,megas);
      return cantidad;
    }else if(bytes > MB){
      long megas = bytes/MB;
      bytes -= megas*MB;
      long kilos = bytes/KB;
      sprintf(cantidad,"%d.%dM",megas,kilos);
      return cantidad;
    }else if(bytes > KB){
      long kilos = bytes/KB;
      bytes -= kilos*KB;
      sprintf(cantidad,"%d.%dK",kilos,bytes);
      return cantidad;
    }
    sprintf(cantidad,"%dB",bytes);
    return cantidad;

  }

  void printError(char* msg){
    printf("\x1b[33m%s\n\x1b[0m",msg);
  }
