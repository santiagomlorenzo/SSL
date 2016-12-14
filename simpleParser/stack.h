#define MAXSIZE 100

struct stack
{
    int stk[MAXSIZE];
    int top;
};

typedef struct stack STACK;

void Stack_Init(void);
void Stack_Push (int d);
int Stack_Pop(void);
