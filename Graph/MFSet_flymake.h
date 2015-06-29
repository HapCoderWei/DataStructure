#include "SeqList.c"

#define ERROR -1
#define OK 1
/* Use Tree Parent Struct */
#define MAX 100
#define DataType char           /* Need Changed */

typedef struct TNode {
    DataType data;
    int parent;
} TNode;
typedef struct {
    TNode tree[MAX];
    int nodenum;
} ParentTree;

typedef ParentTree ParentForst;
typedef ParentForst MFSet;

/* Initialize n trees as a forest with parent is -1 */
void Initialization(MFSet *SS, SeqList *S);
int Find(MFSet *SS, DataType x);
int Merge(MFSet *SS, int root1, int root2);