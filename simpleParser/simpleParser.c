/*
 ============================================================================
 Name        : simpleParser.c
 Author      : Group x
 Version     : 1.1
 Copyright   : All rights reserved
 Description : Simple Parser in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define ENDING '#'

/*stack functions
void Stack_Push(int a);
int  Stack_Pop(void);
void Stack_Init(void);
*/

//other functions

int oposite(int c);

int main(void) {
	int a, octalaux = 1, x, b, aux;
	Stack_Init();
	goto Inicio;	
	
	Inicio: {
		a = getchar();
		switch(a){
			case '"': case '\'':
				Stack_Push(a);
				goto BetweenColons;
			
			case '{': case '[': case '(':
				Stack_Push(oposite(a));
				goto EnBloque;
				
			case '}': case ']': case ')':
				x = Stack_Pop();
				if(a==x) goto CierraBloque;
					else goto Problem;
		
			case ENDING: goto Final;
			default: goto Inicio;
		}
	}

	BetweenColons: {
		a = getchar();
		b = Stack_Pop();
		
		switch(a){
			case ENDING: goto Problem;		
			case '\\': 
				if(b == '\'') goto Escape;
			
			default:
				if(a == b) goto Inicio;
					else{
						Stack_Push(a);
						goto BetweenColons;
					}
		}
	}


	EnBloque: {
		int aux;
		a = getchar();
		switch(a){
			case ENDING: goto Problem;
			case '"': case '\'':
				Stack_Push(a);
				goto BetweenColons;
			
			case '{': case '[': case '(':
				Stack_Push(oposite(a));
				goto EnBloque;
				
			case '}': case ']': case ')':
				x = Stack_Pop();
				if(a==x) goto CierraBloque;
					else goto Problem;
			
			default: goto Inicio;
		}
	}


	CierraBloque: {
		aux = Stack_Pop();
		Stack_Push(aux);
		switch(aux){
			case '$': goto Inicio;
			default: goto EnBloque;
		}
	}


	Escape: {
		a = getchar();
		switch(a){
			case 'n': case 't': case'v': case 'b': case 'r': case 'f': case 'a': case '\\': case '?': case '\'': case '"':
				goto LastEscapeChar;
				
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
				goto Octal1;
			
			case 'x': goto Hexa;
			default: goto Problem;
		}
	}

	Hexa: {
		a = getchar();
		switch(a){
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case'8': case '9':
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
			case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
				goto Hexa;
			
			case '\'': goto Inicio;
			default: goto Problem;
			
		}
	}

	Octal1: {
		a = getchar();
		switch(a){
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
				goto Octal2;
				
			case '\'': goto Inicio;
			default: goto Problem;
		}
	}


	Octal2: {
		a = getchar();
		switch(a){
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
				goto Octal3;
				
			case '\'': goto Inicio;
			default: goto Problem;
		}
	}
	
	
	Octal3: {
		a = getchar();
		switch(a){
			case '\'': goto Inicio;
			default: goto Problem;
		}
	}
	
	
	LastEscapeChar: {
		a = getchar();
		switch(a){
			case '\'': goto Inicio;
			default: goto Problem;
		}
	}

	Final: {
		printf("Funciona!\n");
		return 1;
	}
	
	Problem: {
		printf("Su entrada no es reconocida por este parser");
		return 0;
	}
}


int oposite(int c) {
	switch(c) {
		case '{':
			return '}';

		case '[':
			return ']';

		case '(':
			return ')';

		default:
			return c;
	}
}
