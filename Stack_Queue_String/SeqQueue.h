#define QueueElementType int
#define MAXSIZE 10

#define TRUE 1
#define FALSE 0

typedef struct {
    QueueElementType element[MAXSIZE];
    int front;
    int rear;
}SeqQueue;

void InitQueue(SeqQueue *Q);
int GetHead(SeqQueue Q, QueueElementType *x);
int EnterQueue(SeqQueue *Q, QueueElementType x);
int DeleteQueue(SeqQueue *Q, QueueElementType *x);
int Empty(SeqQueue Q);