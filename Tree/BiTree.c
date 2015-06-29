#define DataType int

typedef struct Node {
    DataType data;
    struct Node *LChild;
    struct Node *RChild;
}BiTNode, *BiTree;

void PreOrder(BiTree root) {
    if(root != NULL) {
        Visit(root->data); /* Visit root data */
        PreOrder(root->LChild); /* Visit left child */
        PreOrder(root->RChild); /* Visit right child */
    }
}

void InOrder(BiTree root) {
    if(root != NULL) {
        InOrder(root->LChild);  /* Visit root left  child */
        Visit(root->data);      /* Visit root data */
        InOrder(root->RChild);  /* Visit root right child */
    }
}

void PostOrder(BiTree root) {
    if(root != NULL) {
        PostOrder(root->LChild); /* Visit root right child */
        PostOrder(root->RChild); /* Visit root left  child */
        Visit(root->data);       /* Visit root data */
    }
}

/* Create BiTree */
void CreateBiTree(BiTree *bt) {
    char ch;
    ch = getchar();
    if(ch == '.') *bt = NULL;   /* Null Node */
    else {
        *bt = (BiTree)malloc(sizeof(BiTNode));
        (*bt)->data = ch;               /* Save root data */
        CreateBiTree(&((*bt)->LChild)); /* Create left child */
        CreateBiTree(&((*bt)->RChild)); /* Create right child */
    }
}

/* Get deepth by post vosit */
int PostTreeDepth(BiTree bt) {
    int hl, hr, max;
    if(bt != NULL){
        hl = PostTreeDepth(bt->LChild);
        hr = PostTreeDepth(bt->RChild);
        max = hl>hr?hl:hr;
        return (max + 1);
    }
    else return 0;
}

/* InOrder Non recursion */
/* s[m] is Stack, top is Stack top pointer */
void inorder(BiTree root) {
    BiTNode *p;
    int top = 0;
    p = root;
    do {
        while(p != NULL) {
            if(top > m) return;
            top = top + 1;
            s[top] = p;
            p = p->LChild;
        }
        if(top != 0) {
            p = s[top];
            top = top - 1;
            Visit(p->data);
            p = p->RChild;
        }
    } while(p != NULL || top != 0)
}

/* InOrder Non recursion */
/* By Stack */
void InOrder(BiTree root) {
    InitStack(&S);
    p = root;
    while(p != NULL || !IsEmpty(S)) {
        if(p!=NULL) {
            Push(&S, p);
            p = p->LChild;
        }
        else {
            Pop(&S, &p);
            Visit(p->data);
            p = p->RChild;
        }
    }
}

/* Thread a BiTree, pre is a global varibal, and initial as NULL */
/* InOrder thread a BiTree */
void Inthread(BiTree root) {
    if(root != NULL) {
        Inthread(root->LChild);

        /* ------------------------------------- */
        if(root->LChild == NULL) {
            root->Ltag = 1;
            root->LChild = pre;
        }
        if(pre != NULL && pre->RChild == NULL) {
            pre->RChild = root;
            pre->Rtag = 1;
        }
        pre = root;
        /* ------------------------------------- */

        Inthread(root->RChild);
    }
}

/* PreOrder thread a BiTree */
void Prethread(BiTree root) {
    if(root != NULL) {

        /* ---------------------------------------- */
        if(root->LChild == NULL) {
            root->LChild = pre;
            root->Ltag = 1;
        }
        if(pre != NULL && pre->RChild == NULL) {
            pre->RChild = root;
            pre->Rtag = 1;
        }
        /* ---------------------------------------- */

        Prethread(root->LChild);
        Prethread(root->RChild);
    }
}

/* PostOrder thread a BiTree */
void Postthread(BiTree root) {
    if(root != NULL) {
        Postthread(root->LChild);
        Postthread(root->RChild);

        /* ---------------------------------------- */
        if(root->LChild == NULL) {
            root->LChild = pre;
            root->Ltag = 1;
        }
        if(pre != NULL && pre->RChild == NULL) {
            pre->RChild = root;
            pre->Rtag = 1;
        }
        /* ---------------------------------------- */
    }
}

/* Find a Node's preNode and NextNode */
/* ********************************** */
/* Find p's preNode in InthreadTree */
BiTNode *InPre(BiTree *p) {
    BiTNode *pre, *q;

    if(p->Ltag == 1) pre = p->LChild;
    else {
        for(q = p->LChild; q->Rtag == 0; q = q->RChild);
        pre = q;
    }
    return pre;
}

/* Find p's Next Node in Inthread */
BiTNode *InNext(BiTNode *p) {
    BiTNode *Next, *q;
    if(p->Rtag == 1) Next = p->RChild;
    else {
        for(q = p->RChild; q->Ltag == 0; q = q->LChild);
        Next = q;
    }
    return Next;
}

/* Find p's preNode in PreNodeTree */
BiTNode *PrePre(BiTree *p) {
    /* Didn't find solution */
}

/* Find p's Next Node in PrethreadTree */
BiTNode *PreNext(BiTNode *p) {
    BiTNode *Next, *p;

    if(p->Ltag == 0) Next = p->LChild;
    else Next = p->RChild;

    return Next;
}

/* Find p's preNode in NextthreadTree */
BiTNode *NextPre(BiTree *p) {
    /* Didn't find solution */
}

/* Find p's NextNode in NextthreadTree */
BiTNode *NextNext(BiTree *p) {
    /* Didn't find solution */
}

/* Ergodic InthreadTree */
/* Find the First Node in Inthread Ergodic */
BiTNode * InFirst(BiTree Bt) {
    BiTNode *p= Bt;

    if(!p) return NULL;
    while(p->Ltag == 0) p = p->LChild;
    return p;
}
void TInOrder(BiTree Bt) {
    BiTNode *p;

    p = InFirst(Bt);            /* Find the First visited Node in InOrder */
    while(p) {
        visit(p);
        p = InNext(p);          /* Find next Node in turn */
    }
}
