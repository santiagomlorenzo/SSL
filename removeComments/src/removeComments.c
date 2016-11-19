/*
 ============================================================================
 Name        : removeComments.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
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
		c= getchar();
		if (c=='/'){goto PossibleComment;}
		else {
			if(c=='"'||c=='\'')
			{
				aux=c;
				putchar(c);
				goto CadenaOCaracter;
			}
				if (c==ENDING){goto Final;}
				else {
					putchar(c);
					goto Inicio;
				}
		}
	}

	CadenaOCaracter: {
		c= getchar();
		putchar(c);
		if(c==aux){goto Inicio;}else{goto CadenaOCaracter;}

	}

	PossibleComment: {
		c= getchar();
		if (c=='*') {goto MultiLineComment;}
		else {
			if (c=='/') {goto SingleLineComment;}
			else {
				putchar('/');
				putchar(c);
				goto Inicio;
			}
		}
	}

	MultiLineComment: {
		c= getchar();
		if (c=='*') {goto PossibleEnding;}
		else {goto MultiLineComment;}
	}

	PossibleEnding: {
		c= getchar();
		if (c=='/'){
			putchar(' ');
			goto Inicio;
		}
		else{goto MultiLineComment;}
	}

	SingleLineComment: {
		c= getchar();
		if (c!='\n' && c!=ENDING){goto SingleLineComment;}
		else {
			putchar(' ');
			if(c==ENDING){goto Final;}
			else{putchar('\n'); goto Inicio;}
		}

	}

	Final: {
		return 0;
	}

}
