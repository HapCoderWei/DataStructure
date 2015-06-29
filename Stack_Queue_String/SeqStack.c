#define Stack_Size 50

#define TRUE 1
#define FALSE 0

#define StackElementType int

typedef struct {
    StackElementType elem[Stack_Size];
    int top;
}SeqStack;

void InitStack(SeqStack *S) {
    S->top = -1;
}

int Push(SeqStack *S, StackElementType x) {
    if(S->top == Stack_Size - 1) { return (FALSE); } /* Check if stack is full */
    S->top++;
    S->elem[S->top] = x;
    return (TRUE);
}

int Pop(SeqStack *S, StackElementType *x) {
    if(S->top == -1) { return (FALSE); } /* Check if Stack is empty */
    *x = S->elem[S->top];
    S->top--;
    return (TRUE);
}

int GetTop(SeqStack *S, StackElementType *x) {
    if(S->top == Stack_Size - 1) { return (FALSE); }
    *x = S->elem[S->top];
    return (TRUE);
}

int IsEmpty(SeqStack S) {
    return S->top==-1?TRUE:FALSE;
}