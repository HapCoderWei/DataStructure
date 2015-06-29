#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"
#include "SeqList.h"

//#include "MFSet.h"


#define MAX_VERTEX_NUM 20
#define INFINITY 32768
#define OK 1
#define Error 0

typedef enum{DG, DN, UDG, UDN} GraphKind;

typedef char VertexData;        /* Data type in Graph */
typedef int AdjType;            /* Define for ArcNode */
typedef char OtherInfo;         /* Define for ArcNode */

typedef struct ArcNode{         /* Arc in Graph */
    AdjType adj;                /* Weight of Arc */
    OtherInfo info;
}ArcNode;

struct miniedge{
    VertexData adjvex;
    int lowcost;
}closedge[MAX_VERTEX_NUM];      /* For MiniSpanTree_Prim */

typedef struct {                       /* Graph of AdjMatrix */
    VertexData vertex[MAX_VERTEX_NUM];            /* Vertex Data */
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /* AdjMatrix */
    int vexnum, arcnum;
    GraphKind kind;
}AdjMatrix;

int visited[MAX_VERTEX_NUM] = {0};

int LocateVertex(AdjMatrix *G, VertexData v){ /* Locate Vertex in Graph */
    int j = Error, k;
    for(k = 0; k < G->vexnum; k++){
        if(G->vertex[k] == v)
        { j = k; break; }
    }
    return j;
}

VertexData FirstAdjVertex(AdjMatrix *G, VertexData v){
    int index,i,k = Error;
    for (i = 0; i < G->vexnum; i++) {
        if(v == G->vertex[i]) { index = i; break;}
    }
    for (i = 0; i < G->vexnum; i++) {
        if(G->arcs[index][i].adj != 0) { /* In DN/UDN, condition is '!= INFINITY' */
            k = i;
            break;
        }
    }
    return G->vertex[k];
}
VertexData NextAdjVertex(AdjMatrix *G, VertexData v, VertexData w) {
    int i,k = -1,windex,vindex;         /* k should be Error, but Error is 0 */

    vindex = LocateVertex(G, v);
    windex = LocateVertex(G, w);
    for (i = windex + 1; i < G->vexnum; i++) {
        if(G->arcs[vindex][i].adj != 0) {
            k = i; break;
        }
    }
    if(k == -1) {
        return '#';             /* Not Find! */
    } else
        return G->vertex[k];
}

int CreateDN(AdjMatrix *G){     /* Create a Direction Network with Weight */
    int i, j, k, weight;
    VertexData v1, v2;
    printf("Please input the vertex numbers and arcs numbers: ");
    scanf("%d,%d", &G->vexnum, &G->arcnum);

    for(i = 0; i < G->vexnum; i++){ /* Initinal the whole Graph */
        for(j = 0; j < G->vexnum; j++){
            G->arcs[i][j].adj = INFINITY; /* Set every weight as infinity */
        }
    }

    printf("Input the vertex: ");
    for(i = 0; i < G->vexnum; i++){ /* Input the vertex array */
        scanf("%c", &G->vertex[i]);
    }

    printf("Input the vertex pairs and their weight :(like A,B,3)\n");
    for(k = 0; k < G->arcnum; k++){ /* Build the arcs in Graph */
        scanf("%c,%c,%d", &v1, &v2, &weight);
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight;
    }

    return OK;
}
int CreateUDN(AdjMatrix *G){     /* Create a UnDirection Network with Weight */
    int i, j, k, weight;
    VertexData v1, v2;
    printf("Please input the vertex numbers and arc numbers: ");
    scanf("%d,%d", &G->vexnum, &G->arcnum);
    getchar();

    for(i = 0; i < G->vexnum; i++){ /* Initinal the whole Graph */
        for(j = 0; j < G->vexnum; j++){
            G->arcs[i][j].adj = INFINITY; /* Set every weight as infinity */
        }
    }

    printf("Input the vertex: ");
    for(i = 0; i < G->vexnum; i++){ /* Input the vertex array */
        scanf("%c", &G->vertex[i]);
        getchar();
    }

    printf("Input the vertex pairs and their weight :(like A,B,3)\n");
    for(k = 0; k < G->arcnum; k++){ /* Build the arcs in Graph */
        scanf("%c,%c,%d", &v1, &v2, &weight);
        getchar();
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight;
        G->arcs[j][i].adj = weight; /* UnDirection is a Symmetrical Graph */
    }

    return OK;
}

int CreateDG(AdjMatrix *G){     /* Create a Direction Graph */
    int i, j, k;
    int weight = 1;             /* In Graph weight is always 1 */
    VertexData v1, v2;

    printf("Please input the DG vertex numbers and arc numbres: ");
    scanf("%d,%d", &G->vexnum, &G->arcnum);
    getchar();

    for(i = 0; i < G->vexnum; i++){
        for (j = 0; j < G->vexnum; j++) {
            G->arcs[i][j].adj = 0;  /* Initial Graph's weight as 0 */
        }
    }

    printf("Input every vertex:\n");
    for (i = 0; i < G->vexnum; i++) { /* Add vertex */
        scanf("%c", &G->vertex[i]);
        getchar();
    }

    printf("Input the vertex pairs with arcs(like A,B):\n");
    for (k = 0; k < G->arcnum; k++) { /* Add arcs */
        scanf("%c,%c", &v1, &v2);
        getchar();
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight; /* In Graph, weight is always 1 */
    }

    return OK;
}
int CreateUDG(AdjMatrix *G){     /* Create a UnDirection Graph */
    int i, j, k;
    int weight = 1;             /* In Graph weight is always 1 */
    VertexData v1, v2;

    /* char verd[] = {'a','b','c','d','e','f','g','h','i'}; */
    /* char arcd[10][2] = {{'a','b'},{'a','d'},{'a','e'},{'b','c'},{'b','d'},{'c','f'},{'d','g'},{'e','g'},{'g','h'},{'h','i'}}; */
    printf("Please input the UDG vertex numbers and arc numbres: ");
    scanf("%d,%d", &G->vexnum, &G->arcnum);
    getchar();

    for(i = 0; i < G->vexnum; i++){
        for (j = 0; j < G->vexnum; j++) {
            G->arcs[i][j].adj = 0;  /* Initial Graph's weight as 0 */
        }
    }

    printf("Input every vertex:\n");
    for (i = 0; i < G->vexnum; i++) { /* Add vertex */
        scanf("%c", &G->vertex[i]);
        getchar();
    }

    printf("Input the vertex pairs with arcs(like A,B):\n");
    for (k = 0; k < G->arcnum; k++) { /* Add arcs */
        scanf("%c,%c", &v1, &v2);
        getchar();
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight; /* In Graph, weight is always 1 */
        G->arcs[j][i].adj = weight; /* UDN is Symmetrical Matrix */
    }

    return OK;
}

void GDFS(AdjMatrix G, int v){ /* Visit Graph from Vertex at index v */
    int i;
    printf("%c ",G.vertex[v]);
    visited[v] = 1;
    for (i = 0; i < G.vexnum; i++) {
        if(visited[i] == 0 && G.arcs[v][i].adj != 0){
            GDFS(G, i);
        }
    }
}
void GDFSTravers(AdjMatrix G){
    int i;
    for (i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }
    for (i = 0; i < G.vexnum; i++) {
        if(visited[i] == 0){
            GDFS(G,i);
        }
    }
 }

void NDFS(AdjMatrix G, int v){ /* Visit Network from Vertex at index v */
    int i;
    printf("%c ",G.vertex[v]);
    visited[v] = 1;
    for (i = 0; i < G.vexnum; i++) {
        if(visited[i] == 0 && G.arcs[v][i].adj < INFINITY){
            GDFS(G, i);
        }
    }
}
void NDFSTravers(AdjMatrix G){
    int i;
    for (i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }
    for (i = 0; i < G.vexnum; i++) {
        if(visited[i] == 0){
            GDFS(G,i);
        }
    }
 }

/* BFS */

void BreadthFirstSearch(AdjMatrix G) { /* Visit Graph by Breadth, but need a SeqQueue */
    int v,w;
    VertexData u,t;
    SeqQueue Q;

    for (v = 0; v < G.vexnum; v++) {
        visited[v] = 0;
    }

    for(v = 0; v < G.vexnum; v++) {
        if(!visited[v]){
            visited[v] = 1;
            printf("%c ", G.vertex[v]); /* visit v */

            InitQueue(&Q);
            EnterQueue(&Q,G.vertex[v]);
            while(!Empty(Q)){
                DeleteQueue(&Q, &u);
                for (t = FirstAdjVertex(&G,u); t != '#'; t = NextAdjVertex(&G,u,t)) {
                    w = LocateVertex(&G, t);
                    if(!visited[w]){
                        visited[w] = 1;
                        printf("%c ", G.vertex[w]);
                        EnterQueue(&Q,t);
                    } /* if */
                } /* for */
            } /* while */
        } /* if */
    } /* for */
}

int Minium(struct miniedge edge[]){
    int i, k = -1, min = INFINITY;
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        if(edge[i].lowcost != 0) {
            min = min<edge[i].lowcost?min:edge[i].lowcost;
        }
    }
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        if(min == edge[i].lowcost){
            k = i; break;
        }
    }
    return k;
}

void MiniSpanTree_Prim(AdjMatrix G, VertexData u) { /* As Name */

    int i, k, e;                                    /* counter */
    VertexData k0, u0, v0;                                 /* temp variable */

    k = LocateVertex(&G, u);
    closedge[k].lowcost = 0;    /* Initialize, U = {u} */
    for (i = 0; i < G.vexnum; i++) {
        if(i != k) {            /* For vertex in V-U, initialize closedge[i] */
            closedge[i].adjvex = u;
            closedge[i].lowcost = G.arcs[k][i].adj;
        }
    }
    for (e = 1; e <= G.vexnum-1; e++) { /* Cycle n-1 times */
        k0 = Minium(closedge);
        u0 = closedge[k0].adjvex; /* Find u0 belongs to U */
        v0 = G.vertex[k0];        /* Find v0 belongs to V-U */
        printf("%c, %c\n",u0, v0);  /* u0 and v0 are the min weight */
        closedge[k0].lowcost = 0; /* Set k0 into U */

        for (i = 0; i < G.vexnum; i++) { /* Update closedge[i] */
            if(G.arcs[k0][i].adj < closedge[i].lowcost) {
                closedge[i].lowcost = G.arcs[k0][i].adj;
                closedge[i].adjvex = v0;
            }
        }
    }

}

/* Didnot Run it */
/* void MiniSpanTree_Kruskal(AdjMatrix G, SeqList * MSTree) { */
/*     MFSet F; */
/*     int i, k; */
/*     InitSet(F, G.vexnum);       /\* Initialize F as trees set *\/ */
/*     InitList(MSTree, G.vexnum); /\* Initialize MiniSpanTree as null *\/ */
/*     i = 0; k = 1; */
/*     while(k < G.vexnum) { */
/*         e = G.arcs[i];          /\* Get mini i weight tree *\/ */
/*         r1 = fix_mfset(F, LocateVertex(e.vex1)); */
/*         r2 = fix_mfset(F, LocateVertex(e.vex2)); /\* return vertex's tree *\/ */
/*         if(r1 != r2) { */
/*             if(ListInsert(MSTree, k, e)) k++; /\* Insert MiniSpanTree *\/ */
/*             mix_mfset(F, r1, r2); /\* Merge two tree *\/ */
/*         } */
/*         i++ */
/*     } */
/*     DestroySet(F); */
/* } */

int FindZeroCol(AdjMatrix G, int sorted[]){
    int i,j,col = -1;
    int flag = 0;
    for (i = 0; i < G.vexnum; i++) {
        for (j = 0; j < G.vexnum; j++) {
            if(G.arcs[j][i].adj != 0) {
                flag = 0;
                break;
            }
            flag = 1;
        }
        if(flag == 1 && sorted[i] == 0) {
            col = i;
            break;
        }
    }
    return col;
}
void TopoSortAdjMatrix(AdjMatrix G) {
    int i, j,order;
    int sorted[MAX_VERTEX_NUM];
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        sorted[i] = 0;
    }
    order = 1;
    while(1) {
        j = FindZeroCol(G, sorted);
        if(j == -1) {           /* Search End */
            for (i = 0; i < G.vexnum; i++) {
                if(sorted[i] == 0){ /* Round Graph */
                    break;
                }
            }
            if(i < G.vexnum) {
                printf("Round Graph");
                break;
            }
            else {
                printf("Sorted End");
                break;
            }
        }

        printf("%c ", G.vertex[j]); /* print vertex */
        sorted[j] = order;
        for (i = 0; i < G.vexnum; i++) {
            G.arcs[j][i].adj = 0;
        }
        order++;
    }
}

int CreateGraph(AdjMatrix *G) {
    int kind;
    printf("Which Graph?\nInput 1 for DG, 2 for DN, 3 for UDG, 4 for UDN:");
    scanf("%d",&kind);
    getchar();

    switch (kind-1) {
        case DG:  return CreateDG(G);  break;
        case DN:  return CreateDN(G);  break;
        case UDG: return CreateUDG(G); break;
        case UDN: return CreateUDN(G); break;
    }
}

/* Dijkstra Algorithm */
typedef unsigned int WeightType;
typedef WightType AdjType;
typedef SeqList VertexSet;

void ShortestPath_DJS(AdjMatrix G, int v0,
                      WeightType dist[MAX_VERTEX_NUM],
                      VertexSet path[MAX_VERTEX_NUM])
{
    int i, t, k,min;
    VertexSet s;

    for (i = 0; i < G.vexnum; i++) {
        InitList(&path[i]);
        dist[i] = G.arcs[v0][i].adj;
        if(dist[i] < INFINITY) {
            AddTail(&path[i], G.vertex[v0]);
            AddTail(&path[i], G.vertex[i]);
        }
    }
    InitList(&s);
    AddTail(&s, G.vertex[v0]);

    for (t = 1; t <= G.vexnum-1; t++) {
        min = INFINITY;
        for (i = 0; i < G.vexnum; i++) {
            if(!Member(G.vertex[i], s) && dist[i] < min)
            {  k = i; min = dist[i];}
        }
        if(min == INFINITY) return;
        AddTail(&s, G.vertex[k]);

        for (i = 0; i < G.vexnum; i++) { /* Update dist[i], i belongs to V-S */
            if(!Member(G.vertex[i], s) &&
                G.arcs[k][i].adj != INFINITY &&
                (dist[k] + G.arcs[k][i].adj < dist[i]))
            {
                dist[i] = dist[K] + G.arcs[k][i].adj;
                path[i] = path[k];
                AddTail(&path[i], G.vertex[i]);
            }
        }
    }
}

void ShortestPath_Floyd(AdjMatrix G,
                        WeightType dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM],
                        VertexSet path[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
    int i,j,k;
    for (i = 0; i < G.vexnum; i++) { /* Initialize dist[i][j] and path[i][j] */
        for (j = 0; j < G.vexnum; j++) {
            InitList(&path[i][j]);
            dist[i][j] = G.arcs[i][j].adj;
            if(dist[i][j] < INFINITY) {
                AddTail(&path[i][j], G.vertex[i]);
                AddTail(&path[i][j], G.vertex[j]);
            }
        }
    }

    for (k = 0;; k < G.vexnum; k++) {
        for (i = 0; i < G.vexnum; i++) {
            for (j = 0; j < G.vexnum; j++) {
                if(dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = JoinList(path[i][k], path[k][j]); /* Merge path[i][k] and path[k][j] */
                }
            }
        }
    }
}
/* int main(int argc, char *argv[]) */
/* { */
/*     AdjMatrix G; */

/*     /\*if (CreateUDN(&G)) { *\/ //This is for Test MiniSpanTree_Prim  */
/*     /\*     printf("UDN MiniSpanTree is: \n"); *\/ */
/*     /\*     MiniSpanTree_Prim(G, G.vertex[0]); *\/ */
/*         /\* } *\/ */

/*     /\* if(CreateGraph(&G)) { *\/ */
/*     /\*     printf("UDG Visited sequence is :\n"); *\/ */
/*     /\*     (G.kind%2==0)?GDFSTravers(G):NDFSTravers(G); *\/ */
/*     /\* } *\/ */
/*     putchar('\n'); */
/*     return 0; */
/* } */

/* Test For TopoSort with AdjMatrix */
/* int main(int argc, char *argv[]) */
/* { */
/*     AdjMatrix G; */
/*     if(CreateDG(&G)) { */
/*         printf("The TopoSort is: \n"); */
/*         TopoSortAdjMatrix(G); */
/*     } */
/*     putchar('\n'); */
/*     return 0; */
/* } */

