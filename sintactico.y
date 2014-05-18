%{
	#include "functions.h"
%}

%union{
	struct Param* param;
	int entero;
	char* cadena;
}
%token 		VARIABLE PAR_IZQ PAR_DER LS CD MKDIR CHGRP CHMOD CHOWN RM FIND
%token		 <cadena> PARAMETRO
%token 		 <entero> NUMERO

%type			<param>	params
%type			<entero> operacion fcall salida
%left 		 MAS MENOS
%left 		 POR ENTRE
%right 		POTENCIA
%token 		EOL

%start salida

%%


salida : /*null*/{$$=0;printf("\n%s@%s> ",currentUser,hostName);}
        | salida operacion EOL {printf(" %d\n%s@%s> ",$2,currentUser,hostName);}
				| salida fcall EOL {printf("\n%s@%s> ",currentUser,hostName);}
				| salida PARAMETRO {printf("\x1b[33mError %s, comando invalido.\n\x1b[0m",$2);}
        | salida EOL {printf("\n%s@%s> ",currentUser,hostName);}
;

operacion :   operacion MAS operacion {$$= $1 + $3;}
            | operacion MENOS operacion {$$ = $1 - $3;}
            | operacion POR operacion {$$ = $1 * $3;}
            | operacion ENTRE operacion {$$ = $1 / $3;}
            | operacion POTENCIA operacion {$$ = potencia($1,$3);}
            | PAR_IZQ operacion PAR_DER {$$ = ($2);}
            | NUMERO {$$ = $1;}
;

fcall  :     LS       params   {$$ = ls($2);}
          |  CD       params   {$$ = cd($2);}
          |  MKDIR    params   {$$ = makedir($2);}
          |  CHGRP    params   {$$ = 0; printf("chgrp");}
          |  CHMOD    params   {$$ = 0; printf("chmod");}
          |  CHOWN    params   {$$ = 0; printf("chown");}
          |  RM       params   {$$ = 0; printf("rm");}
          |  FIND     params   {$$ = 0; printf("find");}
;

params :  PARAMETRO params{
						$$ = newParam($1,$2);
					}
					|/*null*/ {$$ = NULL}
;

%%

#include <stdio.h>

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("Error: %s", s);
}
