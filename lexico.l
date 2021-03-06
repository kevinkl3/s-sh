digito [0-9]
letra [a-zA-Z]
otro "-"
simbolo [\[\]\{\}\^\$\+\*\.\\]
punto "."
pleca "/"
bajo "_"
parametro ({punto}+|({letra}+({digito}|{letra})*)|{pleca}|{otro}|{simbolo}|{digito}|{bajo})+
%{
#include <stdio.h>
#include "sintactico.tab.h"
%}

%%

"ls"												 {return LS;}
"cd"												 {return CD;}
"mkdir" 										 {return MKDIR;}
"chgrp" 										 {return CHGRP;}
"chmod" 										 {return CHMOD;}
"chown" 										 {return CHOWN;}
"find"											 {return FIND;}
"clear"											{return CLEAR;}
"mv"											 	{return MV;}
"rm"												 {return RM;}
"exit"											 { printf("\x1b[36mGoodBye!\x1b[0m"); exit(0); }

"+" 		{return MAS;}
"-" 		{return MENOS;}
"*" 		{return POR;}
"/" 		{return ENTRE;}
"^" 		{return POTENCIA;}
"(" 		{return PAR_IZQ;}
")" 		{return PAR_DER;}
"\n" 	 {return EOL;} //FIN DE LINEA
[ \t\v\f]		{  }
{parametro}	{char* val = malloc( strlen(yytext)-1 ); strcpy(val,yytext); yylval.cadena = val; return PARAMETRO; }
. 			{ printf("Error %s, comando invalido.\n",yytext);}

%%

int yywrap(){
	return(1);
}
