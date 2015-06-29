#include <stdio.h>
#include <stdlib.h>

#define ERROR 1
#define OK    0

//typedef int ElemType;
typedef char ElemType;

typedef struct Node {
    ElemType data;
    struct Node* next;
} Node, *LinkList;

void InitList(LinkList *L) {

    /* malloc a node for linklist head L */
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
}

/*    Create LinkList   */
void CreateFromHead(LinkList L) {
    /* Create LinkList from head, read input from keyboard */

    Node *s;
    char c;
    int flag = 1;
    while(flag) {
        c = getchar();
        /* '$' is a end flag */
        if (c != '$') {
            s = (Node*)malloc(sizeof(Node));
            s->data = c;
            s->next = L->next;
            L->next = s;
        }
        else {
            flag = 0;
        }
    }
}
void CerateFromTail(LinkList *L) {
    /* Create Linklist from tail */

    Node *s, *r;
    int flag = 1;
    char c;
    r = L;
    while(flag) {

        c = getchar();
        if(c != '$') {
            s = (Node *)malloc(sizeof(Node));
            s->data = c;
            r->next = s;
            r = s;
        }
        else {
            flag = 0;
            r->next = NULL;
        }
    }
}

/*   Search LinkList   */
Node* Get(LinkList L, int i) {
    /* Search according index */

    int j;
    Node *p;
    if (i<0) return NULL;           /* if i<0, return error*/
    p = L; j = 0;                 /* scan Node from head L */
    while((p->next !- NULL) && (j<i)) {
        p = p->next;                      /* scan next Node*/
        j++;                   /* counter for scanned Node */
    }
    if (i == j) return p;          /* Find Node at index i */
    else return NULL;     /* Cannot find. i<=0 or i> length*/
}
Node *Locate(LinkList L, ElemType key) {
    /* Search according value */

    Node *p;
    p = L->next;                    /* From the first Node */
    while(p != NULL) {           /* While LinkList not end */
        if(p->data == key)
        return p;       /* if find Node = key, return Node */
        else p = p->next;
    }
    return p;
}

/*   Get LinkList Length  */
int ListLength(LinkList L) {
    /* Return the length of LinkList with a head Node */

    Node *p;
    int length = 0;   /* Save the length returned at last */
    p = L->next;
    while(p != NULL) {
        p = p->next;
        length++;
    }

    return length;
}

/*   Insert to LinkList  */
void InsList(LinkList L, int i, ElemType e) {
    /* Insert element e at index i to                      */
    /* LinkList L with a head node                         */

    Node *pre, *s;
    int k;

    if(i<=0) return NULL;
    pre = L; k = 0;                 /* Find from head node */
    while(pre != NULL && k < i-1) { /* Locate at index i-1 */
        pre = pre->next;
        k++;
    }
    if(!pre) {       /* If pre is NUll, location incorrext */
        printf("Incorrect insert location!");
        return NULL;
    }
    
    s = (Node *)malloc(sizeof(Node));
    s->data = e;
    s->next = pre->next;
    pre->next = s;

    //return OK;
}

/*   Delete   */
int DelList(LinkList L, int i, ElemType *e) {
    /* Delete element locate at i, and stored the element in e */

    Node *pre, *r;
    int k = 0;

    pre = L;
    while(pre->next != NULL && k < i-1) {
          /* Find the previous of node i, and let pre points it*/
        pre = pre->next;
        k++;
    }
    if(!(pre->next)) {
               /* If pre->next=null, cannot find delete index i*/
        printf("Delete error, cannot locate i.");
        return ERROR;
    }
    r = pre->next;
    pre->next = r->next;
    *e = r->data;
    free(r);                 /* Free the space of deleted node */
    return OK;
}

/*    Merge two sorted LinkList to one LinkList  */
LinkList MergeLinkList(LinkList LA, LinkList LB) {
    Node *pa, *pb, *r;
    LinkList LC;

    pa = LA->next;
    pb = LB->next;
    LC = LA;
    LC->next = NULL; r = LC;  /* LC initial to empty LinkList. */

    while(pa != NULL && pb != NULL) {
        if(pa->data <= pb->data) {
            r->next = pa;
            r = pa;
            pa = pa->next;
        }
        else {
            r->next = pb;
            r = pb;
            pb = pb->next;
        }
    }
    if(pa) r->next = pa;
    else r->next = pb;

    free(LB);
    return LC;
}