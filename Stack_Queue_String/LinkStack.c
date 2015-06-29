#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define StackElementType int

typedef struct node {
    StackElementType data;
    struct node *next;
} LinkStacknode;
typedef LinkStacknode *LinkStack;

int Push(LinkStack top, StackElementType x) {
    LinkStacknode *temp;
    temp = (LinkStacknode *)malloc(sizeof(LinkStacknode)); /* Insert a new Node */
    if(temp == NULL) return (FALSE);
    temp->data = x;
    temp->next = top->next;
    top->next = temp;
    return (TRUE);
}

int Pop(LinkStack top, StackElementType *x) {
    LinkStacknode *temp;
    temp = top->next;
    if(temp == NULL) return (FALSE); /* Check if Stack is empty */
    top->next = temp->next;
    *x = temp->data;
    free(temp);
    return (TRUE);
}