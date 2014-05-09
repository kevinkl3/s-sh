%{
#include <stdio.h>
#include <stdlib.h>     /* atoi */
    int potencia(int a, int b){
        return b <= 0 ? 1 : a * potencia(a,b-1);
    }
extern char *yytext;
%}

%token NUMERO VARIABLE PAR_IZQ PAR_DER LS CD MKDIR CHGRP CHMOD CHOWN RM FIND
%left MAS MENOS
%left POR ENTRE
%right POTENCIA
%token EOL

%start salida

%%


salida : /*null*/{printf("\n>");}
        | salida expresion EOL {printf(" %d\n>",$2);}
        | salida EOL {printf("\n>");}
;

expresion : fcall | operacion;

operacion :   operacion MAS operacion {$$= $1 + $3;}
            | operacion MENOS operacion {$$ = $1 - $3;}
            | operacion POR operacion {$$ = $1 * $3;}
            | operacion ENTRE operacion {$$ = $1 / $3;}
            | operacion POTENCIA operacion {$$ = potencia($1,$3);}
            | PAR_IZQ operacion PAR_DER {$$ = ($2);}
            | NUMERO
;

fcall  :     LS          {$$ = 0; printf("ls");}
          |  CD          {$$ = 0; printf("cd");}
          |  MKDIR       {$$ = 0; printf("mkdir");}
          |  CHGRP       {$$ = 0; printf("chgrp");}
          |  CHMOD       {$$ = 0; printf("chmod");}
          |  CHOWN       {$$ = 0; printf("chown");}
          |  RM          {$$ = 0; printf("rm");}
          |  FIND        {$$ = 0; printf("find");}
;


%%

#include <stdio.h>

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("Error: %s", s);
}
