/* */
#include <LinkList.h>

void Transposition(LinkList L, int n) {
    Node *p, *trs;

    p = L->next;
    while(p->next->next != NULL) {
        trs = p->next;
        p->next = trs->next;
        trs->next = L->next;
        L->next = trs;

        p = p->next;
    }
}
