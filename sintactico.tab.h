/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARIABLE = 258,
     PAR_IZQ = 259,
     PAR_DER = 260,
     LS = 261,
     CD = 262,
     MV = 263,
     MKDIR = 264,
     CHGRP = 265,
     CHMOD = 266,
     CHOWN = 267,
     RM = 268,
     FIND = 269,
     CLEAR = 270,
     PARAMETRO = 271,
     NUMERO = 272,
     MENOS = 273,
     MAS = 274,
     ENTRE = 275,
     POR = 276,
     POTENCIA = 277,
     EOL = 278
   };
#endif
/* Tokens.  */
#define VARIABLE 258
#define PAR_IZQ 259
#define PAR_DER 260
#define LS 261
#define CD 262
#define MV 263
#define MKDIR 264
#define CHGRP 265
#define CHMOD 266
#define CHOWN 267
#define RM 268
#define FIND 269
#define CLEAR 270
#define PARAMETRO 271
#define NUMERO 272
#define MENOS 273
#define MAS 274
#define ENTRE 275
#define POR 276
#define POTENCIA 277
#define EOL 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 5 "sintactico.y"
{
	struct Param* param;
	int entero;
	char* cadena;
}
/* Line 1529 of yacc.c.  */
#line 101 "sintactico.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

