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

int main(void) {

	int c;

	Inicio: {
		c= getchar();
		if (c=='/'){goto PossibleComment;}
		else {
			if (c=='eof'){goto Final;}
			else {
				putchar(c);
				goto Inicio;
			}
		}
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
	}

	SingleLineComment: {
		c= getchar();
		if (c!='\n' && c!='eof'){goto SingleLineComment;}
		else {
			putchar(' ');
			if(c=='eof'){goto Final;}
			else{goto Inicio;}
		}

	}

	Final: {
		return 0;
	}

}
