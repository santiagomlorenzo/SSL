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
	int aux;

	Inicio: {
		c = getchar();
		switch(c){
			case '/': goto PossibleComment;
			case '"': case '\'':
				putchar(c);
				goto CadenaOCaracter;
			
			case ENDING: goto Final;
			default: 
				putchar(c);
				goto Inicio;			
		}
	}

	CadenaOCaracter: {
		c= getchar();
		putchar(c);
		switch(c){
			case '"': case '\'': goto Inicio;
			default: goto CadenaOCaracter;
		}
	}

	PossibleComment: {
		c= getchar();
		switch(c){
			case '*': goto MultiLineComment;
			case '/': goto SingleLineComment;
			default:
				putchar('/');
				putchar(c);
				goto Inicio;
		}
	}

	MultiLineComment: {
		c= getchar();
		switch(c){
			case '*': goto PossibleEnding;
			default: goto MultiLineComment;
		}
	}

	PossibleEnding: {
		c= getchar();
		switch(c){
			case '/':
				putchar(' ');
				goto Inicio;
			
			default: goto MultiLineComment;
		}
	}

	SingleLineComment: {
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
	}

	Final: {
		return 0;
	}

}
