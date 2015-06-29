#include "SeqQueue.h"

void InitQueue(SeqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
}
int GetHead(SeqQueue Q, QueueElementType *x) {
    if(Q.front == Q.rear) return (FALSE);
    *x = Q.element[Q.front];
    return (TRUE);
}
int EnterQueue(SeqQueue *Q, QueueElementType x) {
    if((Q->rear+1)%MAXSIZE == Q->front) return (FALSE);
    Q->element[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return (TRUE);
}
int DeleteQueue(SeqQueue *Q, QueueElementType *x) {
    if(Q->front == Q->rear) return (FALSE);
    *x = Q->element[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return (TRUE);
}
int Empty(SeqQueue Q) {
    if(Q.front == Q.rear) return (TRUE);
    return (FALSE);
}