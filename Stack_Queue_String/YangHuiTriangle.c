#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"

int main() {
    int x,temp;

    SeqQueue Q;

    InitQueue(&Q);
    EnterQueue(&Q,1);
    for(int n = 2; n <= 7; n++) {
        EnterQueue(&Q,1);
        for(int i = 1; i <= n-2; i++) {
            DeleteQueue(&Q, &temp);
            printf("%d ", temp);
            GetHead(Q, &x);
            temp = temp + x;
            EnterQueue(&Q, temp);
        }
        DeleteQueue(&Q, &x);
        printf("%d ", x);
        EnterQueue(&Q, 1);
        printf("\n");
    }
    while(!Empty(Q)) {
        DeleteQueue(&Q, &x);
        printf("%d ", x);
    }
    putchar('\n');

    return 0;
}