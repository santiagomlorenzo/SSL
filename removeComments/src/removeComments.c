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

   int a;
   goto Inicio;

   Inicio:
      a = getchar();
      switch(a){
         case '/': goto PossibleComment;
         case '"': 
		 	putchar(a); 
			goto EnCadena;
         case '\'': 
		 	putchar(a);
			goto EnCaracter;
         case ENDING: goto Final;
         default:
            putchar(a);
            goto Inicio;
      }
	
	EnCaracter:
      a = getchar();
      switch(a){
         case ENDING: goto Problem;
         case '\'': goto Problem;
         case '\\': 
			putchar(a);
			goto EscapeCaracter;
			
        default: 
			putchar(a);
			goto EnCaracterSinEscape;
      }

   EnCaracterSinEscape:
   	   a = getchar();
   	   switch(a){
   	   	   case ENDING: goto Problem;
		   case '\'':
		   putchar(a);
		   goto Inicio;
		   
		default:
			putchar(a);
			goto EnCaracterSinEscape;
		}
	
	EscapeCaracter:
      a = getchar();
      switch(a){
         case 'n': case 't': case'v': case 'b': case 'r': case 'f': case 'a': case '\\': case '?': case '\'': case '"':
			putchar(a);
			goto LastEscapeChar;

         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
         	putchar(a);
            goto Octal1;

         case 'x':
		 	putchar(a);
			goto PreHexa;
         
		default: goto Problem;
      }
	

	LastEscapeChar:
      a = getchar();
      switch(a){
         case '\'':
		 	putchar(a);
			goto Inicio;
         
		default: goto Problem;
      }


   PreHexa:
   	a = getchar();
      switch(a){
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case'8': case '9':
         case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
         case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            putchar(a);
			goto Hexa;

         case '\'': goto Problem;
         default: goto Problem;
	}

   Hexa:
      a = getchar();
      switch(a){
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case'8': case '9':
         case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
         case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            putchar(a);
			goto Hexa;

         case '\'': goto Inicio;
         default: goto Problem;
      }
      

   Octal1:
      a = getchar();
      switch(a){
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
         	putchar(a);
            goto Octal2;

         case '\'':
		 	putchar(a);
		 	goto Inicio;
        
		default: goto Problem;
      }


   Octal2:
      a = getchar();
      switch(a){
         case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
         	putchar(a);
            goto Octal3;

         case '\'':
		 	putchar(a);
			goto Inicio;
         
		 default: goto Problem;
      }

   Octal3:
      a = getchar();
      switch(a){
         case '\'':
		 	putchar(a);
			goto Inicio;
         
		 default: goto Problem;
      }

    EnCadena:
      a = getchar();
      switch(a){
         case ENDING: goto Problem;
         case '\\':
		 	putchar(a);
			 goto EscapeCadena;
         
		case '"': 
			putchar(a);
			goto Inicio;
         
		 default: 
		 	putchar(a);
			goto EnCadena;
      }
      
    EscapeCadena:
   	   a = getchar();
       switch(a){
       	   case '"': goto Problem;
       	   case '\\': case '\?': case '\'': case '\a': case '\n': case '\t':
       	   		putchar(a);
				goto EnCadena;
					  	
       	   default:
			  putchar(a);
			  goto EnCadena;
       }

   PossibleComment:
      a = getchar();
      switch(a){
         case '*': goto MultiLineComment;
         case '/': goto SingleLineComment;
         default:
            putchar('/');
            putchar(a);
            goto Inicio;
      }

   MultiLineComment:
      a = getchar();
      switch(a){
         case '*': goto PossibleEnding;
         default: goto MultiLineComment;
      }

   PossibleEnding:
      a = getchar();
      switch(a){
         case '/':
            putchar(' ');
            goto Inicio;

         default: goto MultiLineComment;
      }

   SingleLineComment:
      a = getchar();
      switch(a){
      case ENDING:
         putchar(' ');
         goto Final;

      case '\n':
         putchar(' ');
         goto Inicio;

      default: goto SingleLineComment;
      }

   Problem:
      printf("\n \a Error: Su entrada contiene literales o cadenas incorrectas");
      return 0;

   Final:
      return 0;
}
