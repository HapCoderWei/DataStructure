#include <stdio.h>
#include <stdlib.h>

#define ERROR 1
#define OK    0

typedef char ElemType;
//typedef int  ElemType;

typedef struct Node {
    ElemType data;
    struct Node* next;
}  Node, *LinkList;

void InitList(LinkList *L);

void CreateFromHead(LinkList L);
void CreateFromTail(LinkList L);

Node* Get(LinkList L, int i);
Node* Locate(LinkList L, ElemType key);

int ListLength(LinkList L);

void InsList(LinkList L, int i, ElemType e);

int DelList(LinkList L, int i, ElemType *e);

LinkList MergeLinkList(LinkList LA, LinkList LB);