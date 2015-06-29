#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"

#define Error 0
#define OK 1

#define MAX_VERTEX_NUM 20
#define VertexData char

typedef enum{DG, DN, UDG, UDN} GraphKind;
typedef struct {
    int weight;
} OtherInfo;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
    OtherInfo info;
}ArcNode;

typedef struct VertexNode {
    VertexData data;
    ArcNode *firstarc;
}VertexNode;

typedef struct {
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
}AdjList;                       /* Adjacency List Graph */

int LocateVertex(AdjList *G, VertexData v) {
    int j = -1, k;
    for (k = 0; k < G->vexnum; k++) {
        if(G->vertex[k].data == v) {
            j = k;
            break;
        }
    }
    return j;
}

int CreateDN(AdjList *G) {
    int i, j, k;
    VertexData v1, v2;
    ArcNode *node, *p;

    printf("Please input vertex number and arcs number: ");
    scanf("%d,%d", &G->vexnum, &G->arcnum);
    getchar();

    printf("Input vertex name:\n");
    for (i = 0; i < G->vexnum; i++) {
        scanf("%c", &(G->vertex[i].data));
        getchar();
        G->vertex[i].firstarc = NULL;
    }

    printf("Input the vertex pairs:(like A,B)\n");
    for (k = 0; k < G->arcnum; k++) {
        scanf("%c,%c", &v1, &v2);
        getchar();
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        node = (ArcNode *)malloc(sizeof(ArcNode));
        node->adjvex = j;
        if(G->vertex[i].firstarc == NULL) {
            G->vertex[i].firstarc = node;
            node->nextarc = NULL;
        }
        else {
            p = G->vertex[i].firstarc;
            while(p->nextarc != NULL){
                p = p->nextarc;
            } /* Find last ArcNode */
            p->nextarc = node;
            node->nextarc = NULL;
        }
    }
    return OK;
}
int CreateDG(AdjList *G) {
    int i, j, k,weight;
    VertexData v1, v2;
    ArcNode *node, *p;

    printf("Please input vertex number and arcs number: ");
    scanf("%d,%d", &G->vexnum, &G->arcnum);
    getchar();

    printf("Input vertex name:\n");
    for (i = 0; i < G->vexnum; i++) {
        scanf("%c", &(G->vertex[i].data));
        getchar();
        G->vertex[i].firstarc = NULL;
    }

    printf("Input the vertex pairs:(like A,B,5)\n");
    for (k = 0; k < G->arcnum; k++) {
        scanf("%c,%c,%d", &v1, &v2, &weight);
        getchar();
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        node = (ArcNode *)malloc(sizeof(ArcNode));
        node->adjvex = j;
        node->info.weight = weight;
        if(G->vertex[i].firstarc == NULL) {
            G->vertex[i].firstarc = node;
            node->nextarc = NULL;
        }
        else {
            p = G->vertex[i].firstarc;
            while(p->nextarc != NULL){
                p = p->nextarc;
            } /* Find last ArcNode */
            p->nextarc = node;
            node->nextarc = NULL;
        }
    }
    return OK;
}

void FindID(AdjList G, int indegree[MAX_VERTEX_NUM]) {
    int i; ArcNode *p;
    for (i = 0; i < G.vexnum; i++) {
        indegree[i] = 0;
    }
    for (i = 0; i < G.vexnum; i++) {
        p = G.vertex[i].firstarc;
        while(p != NULL) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}

int TopoSortAdjList(AdjList G) {
    SeqStack S;
    int indegree[MAX_VERTEX_NUM];
    int i, count, k;
    ArcNode *p;
    FindID(G, indegree);
    InitStack(&S);
    for (i = 0; i < G.vexnum; i++) {
        if(indegree[i] == 0) Push(&S, i);
    }
    count = 0;
    while(!IsEmpty(S)) {
        Pop(&S, &i);
        printf("%d ", i + 1);
        //printf("%c", G.vertex[i].data);
        count++;
        p = G.vertex[i].firstarc;
        while(p != NULL) {
            k = p->adjvex;
            indegree[k]--;
            if(indegree[k] == 0) Push(&S, k);
            p = p->nextarc;
        }
    }
    if(count < G.vexnum) return Error;
    else return OK;
}

int ve[MAX_VERTEX_NUM];         /* Earliest time */
int TopoOrderUpdate(AdjList G, SeqStack *T)
{
    int count, i, j, k;
    ArcNode *p;
    int indgree[MAX_VERTEX_NUM];
    SeqStack S;

    InitStack(T);
    InitStack(&S);
    FindID(G, indgree);
    for (i = 0; i < G.vexnum; i++) {
        if(indgree[i] == 0) Push(&S, i);
    }
    count = 0;
    for (i = 0; i < G.vexnum; i++) {
        ve[i] = 0;              /* Initialize Earliest time */
    }
    while(!IsEmpty(S))
    {
        Pop(&S, &j);
        Push(T, j);
        count++;
        p = G.vertex[j].firstarc;
        while(p != NULL)
        {
            k = p->adjvex;
            indgree[k]--;
            if(indgree[k] == 0) Push(&S, k);
            if(ve[j] + p->info.weight > ve[k]) ve[k] = ve[j] + p->info.weight;
            p = p->nextarc;
        }
    } /* while */
    if(count < G.vexnum) return Error;
    else return OK;
}
int CriticalPath(AdjList G)
{
    ArcNode *p;
    int i, j, k, dut, ei, li;
    char tag;
    int vl[MAX_VERTEX_NUM];
    SeqStack T;

    if(!TopoOrderUpdate(G, &T)){ /* Get Earlist time and Stack T */
        return Error;
    }
    for (i = 0; i < G.vexnum; i++) {
        vl[i] = ve[G.vexnum - 1];
    }
    while(!IsEmpty(T)) {
        Pop(&T, &j);
        p = G.vertex[j].firstarc;
        while(p != NULL){
            k = p->adjvex;
            dut = p->info.weight;
            if(vl[k] - dut < vl[j]) vl[j] = vl[k] -dut;
            p = p->nextarc;
        } /* while */
    }     /* while */
    for (j = 0; j < G.vexnum; j++) {
        p = G.vertex[j].firstarc;
        while(p != NULL){
            k = p->adjvex;
            dut = p->info.weight;
            ei = ve[j];
            li = vl[k] - dut;
            tag = (ei == li)?'*':' ';
            printf("%c,%c,%d,%d,%d,%c\n", G.vertex[j].data,G.vertex[k].data,dut,ei,li,tag);
            p = p->nextarc;
        }
    }
    return OK;
}
/* int main(int argc, char *argv[]) */
/* { */
/*     AdjList G; */
/*     if(CreateDN(&G)) { */
/*         printf("TopoSort Output is:\n"); */
/*         TopoSortAdjList(G); */
/*     } */
/*     putchar('\n'); */
/*     return 0; */
/* } */
/* int main(int argc, char *argv[]) */
/* { */
/*     AdjList G; */
/*     if(CreateDG(&G)) { */
/*         printf("The Critical Path is:\n"); */
/*         CriticalPath(G); */
/*     } */
/*     putchar('\n'); */
/*     return 0; */
/* } */
/* /\* ****************** *\/ */
/* wei@wei-Lenovo-G480:~/program/DataStructure/Graph$ !gcc */
/* gcc -g CreateGraphAdjList.c SeqStack.c -o CreateGraphAdjList */
/* wei@wei-Lenovo-G480:~/program/DataStructure/Graph$ ./CreateGraphAdjList */
/* Please input vertex number and arcs number: 9,11 */
/* Input vertex name: */
/* a */
/* b */
/* c */
/* d */
/* e */
/* f */
/* g */
/* h */
/* i */
/* Input the vertex pairs:(like A,B,5) */
/* a,b,6 */
/* a,c,4 */
/* a,d,5 */
/* b,e,1 */
/* c,e,1 */
/* d,f,2 */
/* e,g,9 */
/* e,h,7 */
/* f,h,4 */
/* g,i,2 */
/* h,i,4 */
/* The Critical Path is: */
/* a,b,6,0,0,* */
/* a,c,4,0,2,  */
/* a,d,5,0,3,  */
/* b,e,1,6,6,* */
/* c,e,1,4,6,  */
/* d,f,2,5,8,  */
/* e,g,9,7,7,* */
/* e,h,7,7,7,* */
/* f,h,4,7,10,  */
/* g,i,2,16,16,* */
/* h,i,4,14,14,* */

