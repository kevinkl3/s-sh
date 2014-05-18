#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
extern int yyparse(void);

int main () {
	currentUser = getenv("USER");
	if(currentPath == NULL){
		currentPath = (char*)malloc(3);
		sprintf(currentPath,"./");
	}
	gethostname(hostName,HOST_NAME_MAX);
	return yyparse();
}
