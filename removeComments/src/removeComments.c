/*
 ============================================================================
 Name        : removeComments.c
 Author      : Santiago M. Lorenzo
 Version     :
 Copyright   : Your copyright notice
 Description : Remove Comments in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	FILE *f,*fo;
	f= fopen("someCCode","r");
	fo= fopen("cOutput","w");

	int c,openChar;

	Inicio: {
		c= getc(f);
		if (c=='/'){goto PossibleComment;}
		else {
			if (c==EOF){goto Final;}
			else {
				putc(c,fo);
				if(c=='"'){
					openChar= c;
					goto NotComment;
				}
					else{
					goto Inicio;
					}
			}
		}
	}

	NotComment: {

		c= getc(f);
				if (c==openChar) {
					putc(c,fo);
					goto Inicio;
				}
				else {
					if (c=='/') {goto SingleLineComment;}
					else {
						putc('/',fo);
						putc(c,fo);
						goto Inicio;
					}
				}

	}


	PossibleComment: {
		c= getc(f);
		if (c=='*') {goto MultiLineComment;}
		else {
			if (c=='/') {goto SingleLineComment;}
			else {
				putchar('/');
				putc(c,fo);
				goto Inicio;
			}
		}
	}

	MultiLineComment: {
		c= getc(f);
		if (c=='*') {goto PossibleEnding;}
		else {goto MultiLineComment;}
	}

	PossibleEnding: {
		c= getc(f);
		if (c=='/'){
			putchar(' ');
			goto Inicio;
		}
	}

	SingleLineComment: {
		c= getc(f);
		if (c!='\n' && c!=EOF){goto SingleLineComment;}
		else {
			putchar(' ');
			if(c==EOF){goto Final;}
			else{goto Inicio;}
		}

	}

	Final: {
		return 0;
	}

}

