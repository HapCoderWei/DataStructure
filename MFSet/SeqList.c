
#define Elemtype int
#define MAXSIZE 100

typedef struct {
    ElemType elem[MAXSIZE];
    int last;
} SeqList;

int Locate(SeqList L, ElemType e) {
    int i = 0;
    while((i <= L.last) && (L.elem[i] != e))
        i++;
    if(i <= L.last) {
        return i+1;
    }
    return -1;
}