#include "MFSet.h"
/* #include "SeqList.c" */

/* #define ERROR -1 */
/* #define OK 1 */
/* /\* Use Tree Parent Struct *\/ */
/* #define MAX 100 */
/* #define DataType char           /\* Need Changed *\/ */

/* typedef struct TNode { */
/*     DataType data; */
/*     int parent; */
/* } TNode; */
/* typedef struct { */
/*     TNode tree[MAX]; */
/*     int nodenum; */
/* } ParentTree; */

/* typedef ParentTree ParentForst; */
/* typedef ParentForst MFSet; */

/* Initialize n trees as a forest with parent is -1 */
void Initialization(MFSet *SS, SeqList *S) {
    int i;
    SS->nodenum = S->last + 1;
    for (i = 0; i < SS->nodenum; i++) {
        SS->tree[i].data = S->elem[i];
        SS->tree[i].parent = -1;
    }
}

/*
*  Find if element x exists in MFSet SS.
*  If exists, return x belonged tree's index.
*  If NOT, return -1.
*/
int Find(MFSet *SS, DataType x) {
    int pos, i;
    pos = Locate(SS,x);
    if(pos < 0) return -1;
    i = pos;
    while(SS->tree[i].parent > 0) {
        i = SS->tree[i].parent;
    }
    return i;
}

int Merge(MFSet *SS, int root1, int root2) {
    if(root1 < 0 || root1 > SS->nodenum - 1) return ERROR;
    if(root2 < 0 || root2 > SS->nodenum - 1) return ERROR;
    SS->tree[root2].parent = root1;
    return OK;
}