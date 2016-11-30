#include "stack.h"

STACK s;

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
