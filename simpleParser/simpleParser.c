/*
 ============================================================================
 Name        : simpleParser.c
 Author      : Santiago M. Lorenzo
 Version     : Final
 Copyright   : Your copyright notice
 Description : Simple Parser in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define ENDING '#'

struct stack
{
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;
STACK s;

//stack functions
void Stack_Push(int a);
int  Stack_Pop(void);
void Stack_Init(void);

//other functions

int isHexa(int a);
int isOctal(int a);
int isOneDigitEscapeChar(int a);
int isOpeningChar(int a);
int isClosingChar(int a);
int isColon(int a);
int oposite(int c);

int main(void) {
	int a,octalaux=1;
	Stack_Init();
	goto Inicio;	
	
	Inicio: {
		a=getchar();
		int aux= isColon(a);
		if(aux==1){Stack_Push(a);goto BetweenColons;}
		else
		{
			aux=isOpeningChar(a);
			if(aux==1){int x = oposite(a);Stack_Push(x);goto EnBloque;}
			else{
				aux=isClosingChar(a);
				if(aux==1){
						int x= Stack_Pop();
						if(a==x){goto CierraBloque;}
						else{goto Problem;}
						}
				else
				{
					if(a==ENDING){goto Final;}
					else {goto Inicio;}
				}
			}
		}

	}

	BetweenColons: {
		a=getchar();
		int b= Stack_Pop();
		if(a==b){goto Inicio;}
		else{
			if(a=='\\' && b=='\''){goto Escape;}
			else{
			if(a==ENDING){goto Problem;}
			else{Stack_Push(a);goto BetweenColons;}
			}
		}
	}

	EnBloque: {
		int aux;
		a=getchar();
		if(a==ENDING){goto Problem;}
		else{
		aux= isColon(a);
		if(aux==1)
				{
					Stack_Push(a);
					goto BetweenColons;
				}
				else
				{
					aux= isOpeningChar(a);
					if(aux==1){Stack_Push(oposite(a)); goto EnBloque;}
					else{
						aux= isClosingChar(a);
						if(aux==1)
						{
							int x= Stack_Pop();
							if(a==x){goto CierraBloque;}
							else{goto Problem;}
							}
						else{goto Inicio;}
					}
				}
	}
}

	CierraBloque: {
		int aux;
		aux= Stack_Pop();
		Stack_Push(aux);
		if(aux=='$'){goto Inicio;}
		else{goto EnBloque;}
	}


	Escape: {
		a=getchar();
		int b= isOneDigitEscapeChar(a);
		if (b==1){goto LastEscapeChar;}
		else{
			if(a=='x'){goto Hexa;}
			else
			{
				b=isOctal(a);
				if(b==1) {goto Octal;} else {goto Problem;}
				}
			}
		}

	Hexa: {
		a=getchar();
		int b= isHexa(a);
		if(b){goto Hexa;}
		else{
			if(a=='\'') {goto Inicio;} else {goto Problem;}
		}
	}

	Octal: {
		int b;
		a=getchar();
		b= isOctal(a);
		if(b==1&&octalaux<2){octalaux++;goto Octal;}
		else{
			a=getchar();
			if(b==1 &&octalaux==2 && a=='\''){goto Inicio;} else{goto Problem;}
			}
		}

	LastEscapeChar: {
		a= getchar();
		if(a=='\''){goto Inicio;} else {goto Problem;}
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

void Stack_Init(void)
{
	s.stk[0]='$';
    s.top = 0;
}

void Stack_Push (int d)
{
    s.top = s.top + 1;
    s.stk[s.top] = d;
}

int Stack_Pop(void)
{
    int num = s.stk[s.top];
    s.top = s.top - 1;
    return num;
    
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


int isHexa(int a)
{
	return (a>=48 && a<=57) || (a>=65 && a<=70) || (a>97 && a<102);
}

int isOctal(int a)
{	
	int aux= a>=48 && a<=55;
	return aux;
}

int isOneDigitEscapeChar(int a)
{
	int i,aux=0;
	char b[]= {'n','t','v','b','r','f','a','\\','?','\'','"'};
	for(i= 0;i<11;i++)
	{
		if(b[i]==a){aux=1;}
	}
	return aux;
}

int isOpeningChar(int a)
{
	return (a=='{'||a=='['||a=='(');
}

int isClosingChar(int a)
{
	return (a=='}'||a==']'||a==')');
}

int isColon(int a)
{
	return (a=='"'||a=='\'');
}
