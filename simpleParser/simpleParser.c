/*
 ============================================================================
 Name        : simpleParser.c
 Author      : Santiago Lorenzo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 100

struct Stack {
    int     data[STACK_MAX];
    int     size;
};

typedef struct Stack Stack;

void Stack_Init(void);
void Stack_Push( int d);
int Stack_Pop(void);

Stack s;

int main(void) {

	int a;
	Stack_Init();
	goto Inicio;

	Inicio: {

		a=getchar();
		if(isColon(a))
		{
			Stack_Push(a);
			goto BetweenColons;
		}
		else
		{
			if(isOpeningChar(a)){Stack_Push(oposite(a)); goto EnBloque;}
			else{
				if(isClosingChar(a))
				{
					if(a==Stack_Pop()){goto CierraBloque;}
				}
				else
				{
					if(a==EOF){goto Final;}
					else {goto Inicio;}
				}
			}
		}

	}

	BetweenColons: {
		a=getchar();

		if(isColon(a)==Stack_Pop()){goto Inicio;}
		else{
			if(a=='\\'){goto Escape;}
			else{goto BetweenColons;}
		}
	}

	EnBloque: {
		a=getchar();
		if(isColon(a))
				{
					Stack_Push(a);
					goto BetweenColons;
				}
				else
				{
					if(isOpeningChar(a)){Stack_Push(oposite(a)); goto EnBloque;}
					else{
						if(isClosingChar(a))
						{
							if(a==Stack_Pop()){goto CierraBloque;}
						}
						else{goto Inicio;}
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
		if (isOneDigitEscapeChar(a)){goto LastEscapeChar;}
		else{
			if(a=='x'){goto Hexa;}
			else
			{
				if(isOctal(a)){goto Octal;}
			}
		}
	}

	Hexa: {
		a=getchar();
		if(isNumeric(a)){goto Hexa;}
		else{
			if(a==' '){goto BetweenColons;}
		}
	}

	Octal: {
		int aux=1;
		a=getchar();
		if(isOctal(a)&&aux<2){aux++;goto Octal;}
		else{
			if(isOctal(a)&&aux==2){goto BetweenColons;}
		}
	}

	LastEscapeChar: {

	}

	Final: {
		return 1;
	}



}

int isNumeric(int a)
{
	return a>=48 || a<=57;
}

int isOctal(int a)
{
	return a>=48 || a<=55;
}

int isOneDigitEscapeChar(int a)
{
	int i;
	char b[]= {'n','t','v','b','r','f','a','\\','?','\'','"'};
	for(i= 0;i<11;i++)
	{
		if(b[i]==a){return 1;}
	}
	return 0;
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

void Stack_Init(void)
{
	s.data[0]='$';
    s.size = 1;
}

void Stack_Push(int d)
{
    if (s.size < STACK_MAX)
        s.data[s.size++] = d;
}

int Stack_Pop(void)
{
	int aux;
    aux=s.data[s.size];
    s.size--;
    return aux;
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
