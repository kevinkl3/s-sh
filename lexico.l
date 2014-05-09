digito [0-9]
letra [a-zA-Z]

%{
#include <stdio.h>
#include "sintactico.tab.h"
%}

%%


{digito}+ 									 {yylval = atoi(yytext);return NUMERO;}
{digito}+"\."{digito}+ 			{yylval = atof(yytext);return NUMERO;}
"ls"												 {return LS;}
"cd"												 {return CD;}
"mkdir" 										 {return MKDIR;}
"chgrp" 										 {return CHGRP;}
"chmod" 										 {return CHMOD;}
"chown" 										 {return CHOWN;}
"find"											 {return FIND;}
"rm"												 {return RM;}
"exit"											 { printf("GoodBye!"); exit(0); }

"+" 		{return MAS;}
"-" 		{return MENOS;}
"*" 		{return POR;}
"/" 		{return ENTRE;}
"^" 		{return POTENCIA;}
"(" 		{return PAR_IZQ;}
")" 		{return PAR_DER;}
"\n" 	 {return EOL;} //FIN DE LINEA
[ \t\v\f]		{  }

{letra}+({digito}|{letra})*	{ printf("Error %s, comando invalido.\n",yytext);}

. 			{ printf("Error %s, comando invalido.\n",yytext);}

%%

yywrap(){
	return(1);
}
