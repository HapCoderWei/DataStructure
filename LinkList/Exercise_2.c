#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    int passwd;
    struct Node *next;
}Node, *LinkList;

void InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->id = -1;
    (*L)->next = *L;
}

void CreateLinkList(LinkList L,int num) {
    Node *p, *q;
    p = L;

    printf("Input everyone's passwd: ");
    for(int i = 0; i < num; i++) {
        q = (Node *)malloc(sizeof(Node));
        scanf("%d", &(q->passwd));
        q->id = i+1;

        q->next = p->next;
        p->next = q;
        p = q;
    }
}

void Run(LinkList L, int m) {
    int key = m;
    Node *pre, *q;
    pre = L;
    while(pre->next != pre) {
        for (int i = 0; i < key-2; i++) {
            if(pre->id == -1) { pre = pre->next; }
            pre = pre->next;
        }
        if(pre->next->id == -1) { pre = pre->next; }
        q = pre->next;
        pre->next = q->next;
        printf("%d ", q->id);
        key = q->passwd;
        free(q);
        pre = pre->next;
    }
}

int main() {
    LinkList L;
    int num, m;

    printf("Input your n: ");
    scanf("%d", &num);
    printf("Input your m: ");
    scanf("%d", &m);

    InitList(&L);
    CreateLinkList(L, num);

    Run(L, m);

    free(L);

    return 0;
}
/*
3 1 7 2 4 8 4
 */