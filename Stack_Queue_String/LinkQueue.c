#define TRUE 1
#define FALSE 0

#define QueueElementType int

typedef struct Node {
    QueueElementType data;
    struct Node *next;
}LinkQueueNode;

typedef struct {
    LinkQueueNode *front;
    LinkQueueNode *rear;
}LinkQueue;

int InitQueue(LinkQueue *Q) {
    Q->front = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(Q->front != NULL) {
        Q->rear= Q->front;
        Q->front->next = NULL;
        return (TRUE);
    }
    else return (FALSE);
}

int EnterQueue(LinkQueue *Q, QueueElementType x){
    LinkQueueNode *NewNode;
    NewNode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(NewNode != NULL) {
        NewNode->data = x;
        NewNode->next = Q->rear->next;
        Q->rear->next = NewNode;
        Q->rear = NewNode;
        return (TURE);
    }
    else return (FALSE);
}

int DeleteQueue(LinkQueue *Q, QueueElementType *x) {
    LinkQueueNode *p;
    if(Q->front == Q->rear) {
        return (FALSE);
    }
    p = Q->front->next;
    Q->front->next = p->next;
    if(Q->rear == p) { Q->rear = Q->front; }
    *x = p->data;
    free(p);
    return (TRUE);
}