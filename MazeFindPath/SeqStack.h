#include <stdlib.h>

// #define Stack_Size 50

#define TRUE 1
#define FALSE 0

#define StackElementType Pos

typedef struct {
    int x;
    int y;
    int di;
}Pos;
typedef struct {
    StackElementType *elem;
    int top;
}SeqStack;

void InitStack(SeqStack *S, int size);
int Push(SeqStack *S, StackElementType x);
int Pop(SeqStack *S, StackElementType *x);
int GetTop(SeqStack *S, StackElementType *x);
int IsEmpty(SeqStack S);