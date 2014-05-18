#include "functions.h"
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#define false 0
#define true 1
#define KB 1024
#define MB 1024*1024
#define GB 1024*1024*1024
  /*SH Functions*/

  int ls(struct Param* params){
    if(currentPath == NULL){
      currentPath = (char*)malloc(3);
      sprintf(currentPath,"./");
    }
    return ls_r(currentPath,params);
  }

  /*ls command*/
  int ls_r(const char* directory,struct Param* params){
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
    pDir = opendir (directory);
    if (pDir == NULL) {
        printf ("No se puede abrir el directorio '%s'\n", directory);
        return 1;
    }

    if(LARGE==true){
      printf("Links\tInode\tSize\t\tName\n");
    }
    struct stat* fileInfo = malloc(sizeof(struct stat));
    int strSz,ok;
    while ((pDirent = readdir(pDir)) != NULL) {
        strSz = strlen(directory) + strlen(pDirent->d_name) + 1;
        char* fname = (char*)malloc(strSz);
        sprintf(fname,"%s%s",directory,pDirent->d_name);
        ok = stat(fname,fileInfo);

        if(pDirent->d_name[0] != '.' || ALL == true){
          if(LARGE == false)
            printf ("%s\n", pDirent->d_name);
          else{
            if(ok==0){
                printf("%d\t%d\t%s\t%s\n",
                fileInfo->st_nlink,
                (int)fileInfo->st_ino,
                formatHuman(fileInfo->st_size,HUMAN),
                pDirent->d_name
              );
            }else{
              printf ("abs: - %s -\t - %d -\t - %s -\n", fname, (int)pDirent->d_fileno, pDirent->d_name);
            }
          }
        }

        if(RECURSIVE == true && pDirent->d_name[0] != '.'){
          if(ok == 0){
            if(S_ISDIR(fileInfo->st_mode)){
                char* dirRecursive = malloc(strlen(fname)+2);
                sprintf(dirRecursive,"%s/",fname);
                printf("Archivos en %s:\n",dirRecursive);
                ls_r(dirRecursive,params);
                free(dirRecursive);
            }
          }
        }
        free(fname);
    }
    free(fileInfo);



    closedir (pDir);
    //deleteParam(params);
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
      //printf("no existe");
      mkdir(newDirName, 0700);
    }else{
      printError("El directorio ya existe!");
      return -1;
    }
    return 0;
  }


  int cd(struct Param* params){
    //validation
    if(params == NULL){
      printError("cd esperaba un parametro.");
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
            printf("No se puede abrir el directorio '%s'\n", targetDir);
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

  int mv(struct Param* params){
    if(params == NULL){
      printError("mv esperaba 2 argumentos.");
      return -1;
    }
    if(params->next == NULL){
      printError("mv esperaba 2 argumentos.");
      return -1;
    }
    char* from = params->value;
    char* to = params->next->value;
    int salida = rename(from,to);
    if(salida == -1){
      switch(errno){
        case EACCES:{
          printError("Error, permiso de escritura denegado.");
          break;
        }
        case ENOTEMPTY:
        case EEXIST:{
          printError("Error, el directorio de destino ya existe y no esta vacio.");
          break;
        }
        default:{
          printf("Error desconocido %d",errno);
        }
      }

      return -1;
    }
    return 0;
  }

  int rm(struct Param* params){
    if(params == NULL){
      printError("rm esperaba 1 argumento.\nUso: rm nombre_de_archivo");
    }

    int salida;
    do{
      salida = remove(params->value);
      if(salida == -1){
        printf("Error eliminando el archivo %s.\n",params->value);
      }
      params = params->next;
    }while(params != NULL);
    return 0;
  }


  int potencia(int a, int b){
      return b <= 0 ? 1 : a * potencia(a,b-1);
  }

  char* formatHuman(long bytes,short flag){
    char* cantidad = malloc(16*sizeof(char));
    if(flag == false){
      sprintf(cantidad,"%ld",bytes);
      return cantidad;
    }

    if(bytes > GB){
      long gigas = bytes/GB;
      bytes -= gigas*GB;
      long megas = bytes/MB;
      sprintf(cantidad,"%ld.%1ldGB",gigas,megas);
      return cantidad;
    }else if(bytes > MB){
      long megas = bytes/MB;
      bytes -= megas*MB;
      long kilos = bytes/KB;
      sprintf(cantidad,"%ld.%1ldMB",megas,kilos);
      return cantidad;
    }else if(bytes > KB){
      long kilos = bytes/KB;
      bytes -= kilos*KB;
      sprintf(cantidad,"%ld.%1ldKB",kilos,bytes);
      return cantidad;
    }
    sprintf(cantidad,"%ldB",bytes);
    return cantidad;

  }

  void printError(const char* msg){
    printf(ANSI_COLOR_YELLOW);
    printf(msg);
    printf(ANSI_COLOR_RESET);
  }

  int chgrp(struct Param* params){
    if(params == NULL){
      printf("chgrp esperaba dos parametro.");
      return 1;
    }else{
      struct group *grp;
      short int    lp;
      grp = getgrnam(params->value);
      if (NULL == grp)
        printf("El Grupo que desea asignar no existe.");
      else{
        struct Param* p = params;
        p = p->next;
        //comprobar si es archivo o directorio
        char* fname = p->value;
        struct stat* fileInfo = malloc(sizeof(struct stat));
        if(stat(fname,fileInfo)==0){
        	if(S_ISDIR(fileInfo->st_mode)){
            	//es directorio
              chown(fname, -1, grp->gr_gid);
              printf("dir");
        	}else{
        	   	//es archivo
              chown(fname, -1, grp->gr_gid);
              printf("file");
        	}
        }else{
        	printError("el archivo no existe");
        }
      }
    }
    return 0;
  }
