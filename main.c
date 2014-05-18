#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
extern int yyparse(void);

int main () {
	currentUser = getenv("USER");
	gethostname(hostName,HOST_NAME_MAX);
	return yyparse();
}
