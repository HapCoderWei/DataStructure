#include "SeqList.h"

void InitList(SeqList *L)
{
    L->last = -1;
}
int Locate(SeqList L, ElemType e) {
    int i = 0;
    while((i <= L.last) && (L.elem[i] != e))
        i++;
    if(i <= L.last) {
        return i+1;
    }
    return -1;
}
int InsList(SeqList *L, int i, Elemtype e)
{
    int k;
    if((i < 1) || (i > L->last+2))
    {
        printf("Invalid Insert Index.");
        return ERROR;
    }
    if(L->last >= MAXSIZE - 1)
    {
        printf("List Overflow.");
        return ERROR;
    }
    for (k = L->last; k >= i - 1; k--) {
        L->elem[k+1] = L->elem[k];
    }
    L->elem[i - 1] = e;
    L->last++;
    return OK;
}
int DelList(SeqList *L, int i, Elemtype *e)
{
    int k;
    if((i < 1) || (i > L->last+1))
    {
        printf("Invalid Delete Index.");
        return ERROR;
    }
    *e = L->elem[i-1];
    for (k = i; k <= L->last; k++) {
        L->elem[k-1] = L->elem[k];
    }
    return OK;
}
void Addtail(SeqList *L, Elemtype e)
{
    L->last++;
    L->elem[L->last] = e;
}
int Member(Elemtype e, SeqList L)
{
    if(Locate(L, e) > -1)  return OK;
    else return ERROR;
}