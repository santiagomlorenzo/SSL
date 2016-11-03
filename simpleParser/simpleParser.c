/*
 ============================================================================
 Name        : simpleParser.c
 Author      : Santiago M. Lorenzo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

char oposite (char c);
void push(int* ip, char a);
char pop(int* ip);

int main(void) {


}

void push(int *ip,char a)
{
}

char pop(int *ip)
{
}

char oposite(char c) {
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
