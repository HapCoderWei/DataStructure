#define Elemtype char
#define MAXSIZE 100

#define OK 1
#define ERROR 0

typedef struct {
    ElemType elem[MAXSIZE];
    int last;
} SeqList;

void InitList(SeqList *L);
int Locate(SeqList L, Elemtype e);
int InsList(SeqList *L, int i, Elemtype e);
int DelList(SeqList *L, int i, Elemtype *e);
void AddTail(SeqList *L, Elemtype e);
int Member(Elemtype e, SeqList L);
