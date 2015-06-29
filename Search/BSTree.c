#include <stdio.h>
#include <stdlib.h>

#define KeyType int

typedef struct node {
    KeyType key;
    struct node *lchild, *rchild;
}BSTNode, *BSTree;

void InsertBST(BSTree *bst, KeyType key)
{
    BSTree s;
    if(*bst == NULL)
    {
        s = (BSTree)malloc(sizeof(BSTNode));
        s->key = key;
        s->lchild = NULL;
        s->rchild = NULL;
        *bst = s;
    }
    else if(key < (*bst)->key)
    {
        InsertBST(&((*bst)->lchild), key);
    }
    else if(key > (*bst)->key)
    {
        InsertBST(&((*bst)->rchild), key);
    }
}
void CreateBST(BSTree *bst)
{
    KeyType key;
    *bst = NULL;
    scanf("%d", &key);
    while(key != -1)
    {
        InsertBST(bst, key);
        scanf("%d", &key);
    }
}

BSTree SearchBST(BSTree bst, KeyType key)
{
    if(!bst) return NULL;       /* Search Failed */
    else if(bst->key == key) return bst;
    else if(bst->key > key)
    {
        return SearchBST(bst->lchild, key);
    }
    else
    {
        return SearchBST(bst->rchild, key);
    }
}
BSTree SearchBST_NR(BSTree bst, KeyType key)
{
    BSTree q;
    q = bst;
    while(q) {
        if(q->key == key) return q;
        else if(q->key > key) q = q->lchild;
        else q = q->rchild;
    }
    return NULL;                /* Searvch Failed */
}

BSTNode *DelBST(BSTree t, KeyType k) /* Delete node from BSTree */
{
    BSTNode *p, *f, *s, *q;
    p = t; f = NULL;
    while(p)
    {
        if(p->key == k) break;
        f = p;
        if(p->key > k) p = p->lchild;
        else p = p->rchild;
    }
    if(p == NULL) return t;     /* Not Find k in t */
    if(p->lchild == NULL)       /* p haven't left child */
    {
        if(f == NULL) t = p->rchild; /* p is root */
        else if(f->lchild == p) f->lchild = p->rchild; /* p is f left child */
        else f->rchild = p->rchild;                    /* p is f right child */
        free(p);
    }
    else                        /* p have left child */
    {
        q = p;
        s = p->lchild;
        while(s->rchild)        /* Find p most right in p left child */
        {
            q = s;
            s = s->rchild;
        }
        if(q == p) q->lchild = s->lchild; /* s haven't right child */
        else q->rchild = s->lchild;
        p->key = s->key;
        free(s);
    }
    return t;
}

void InOrder(BSTree bst)
{
    if(bst != NULL)
    {
        InOrder(bst->lchild);
        printf("%d ", bst->key);
        InOrder(bst->rchild);
    }
}
void RInOrder(BSTree bst)
{
    if(bst != NULL)
    {
        RInOrder(bst->rchild);
        printf("%d ", bst->key);
        RInOrder(bst->lchild);
    }
}
int main(int argc, char *argv[])
{
    BSTree bst;

    printf("Input number:\n");
    CreateBST(&bst);
    InOrder(bst);
    putchar('\n');
    RInOrder(bst);
    putchar('\n');
    return 0;
}
