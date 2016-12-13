/*
 ============================================================================
 Name        : removeComments.c
 Author      : Group x
 Version     : 1.1
 Copyright   : All rights reserved
 Description : Comments remover for C and derivates
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define ENDING '#'

int main(void) {

   int c;
   goto Inicio;

   Inicio:
      c = getchar();
      switch(c){
         case '/': goto PossibleComment;
         case '"': putchar(c); goto EnCadena;
         case '\'': putchar(c); goto EnCaracter;
         case ENDING: goto Final;
         default:
            putchar(c);
            goto Inicio;
      }

	EnCaracter:
		b = getchar();
		switch(b){
			case ENDING: goto Problem;
			case '\'': goto Inicio;
			case '\\': goto EscapeCaracter;
			default: goto EnCaracterSinEscape;
	}

   EnCaracterSinEscape:
   	   b = getchar();
   	   switch(b){
   	   	   case ENDING: goto Problem;
		   case '\'': goto Inicio;
		   default: goto EnCaracterSinEscape;

    EnCadena:
      a = getchar();
      switch(a){
         case ENDING: goto Problem;
         case '\\': goto EscapeCadena;
         case '"': goto Inicio;
         default: goto EnCadena;
      }

   EscapeCadena:
   	   a = getchar();
       switch(a){
       	   case'"': putchar('"');goto EnCadena;
       }

   EscapeCaracter:
      a = getchar();
      switch(a){
         case 'n': case 't': case'v': case 'b': case 'r': case 'f': case 'a': case '\\': case '?': case '\'': case '"':
            goto LastEscapeChar;

         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
            goto Octal1;

         case 'x': goto Hexa;

         default: goto Problem;
      }

   Hexa:
      a = getchar();
      switch(a){
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case'8': case '9':
         case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
         case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            goto Hexa;

         case '\'': goto Inicio;
         default: goto Problem;

      }

   Octal1:
      a = getchar();
      switch(a){
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
            goto Octal2;

         case '\'': goto Inicio;
         default: goto Problem;
      }


   Octal2:
      a = getchar();
      switch(a){
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
            goto Octal3;

         case '\'': goto Inicio;
         default: goto Problem;
      }

   Octal3:
      a = getchar();
      switch(a){
         case '\'': goto Inicio;
         default: goto Problem;
      }

   LastEscapeChar:
      a = getchar();
      switch(a){
         case '\'': goto Inicio;
         default: goto Problem;
      }

   PossibleComment:
      c= getchar();
      switch(c){
         case '*': goto MultiLineComment;
         case '/': goto SingleLineComment;
         default:
            putchar('/');
            putchar(c);
            goto Inicio;
      }

   MultiLineComment:
      c= getchar();
      switch(c){
         case '*': goto PossibleEnding;
         default: goto MultiLineComment;
      }

   PossibleEnding:
      c= getchar();
      switch(c){
         case '/':
            putchar(' ');
            goto Inicio;

         default: goto MultiLineComment;
      }

   SingleLineComment:
      c= getchar();
      switch(c){
      case ENDING:
         putchar(' ');
         goto Final;

      case '\n':
         putchar(' ');
         goto Inicio;

      default: goto SingleLineComment;
      }

   Final:
      return 0;
}
