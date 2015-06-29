#define MAX_VERTEX_NUM 20
#define INFINITY 32768
#define OK 1
#define Error 0

typedef enum{DG, DN, UDG, UDN} GraphKind;
typedef char VertexData;
typedef struct ArcNode{
    AdjType adj;
    OtherInfo info;
}ArcNode;
typedef struct {
    VertexData vertex[MAX_VERTEX_NUM];
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
}AdjMatrix;                     /* Adjacency Matrix Graph */

int LocateVertex(AdjMatrix *G, VertexData v){
    int j = Error, k;
    for(k = 0; k < G->vexnum; k++){
        if(G->vertex[k] == v)
        { j = k; break; }
    }
    return j;
}
int CreateDN(AdjMatrix *G){
    int i, j, k, weight;
    VertexData v1, v2;
    scanf("%d,%d", &G->arcnum; &G->vexnum);
    for(i = 0; i < G->vexnum; i++){ /* Initinal all the Graph */
        for(j = 0; j < G->vexnum; j++){
            G->arcs[i][j].adj = INFINITY;
        }
    }
    for(i = 0; i < G->vexnum; i++){ /* Input the vertex array */
        scanf("%c", &G->vertex[i]);
    }
    for(k = 0; k < G->arcnum; k++){ /* Build the arcs in Graph */
        scanf("%c,%c,%d", &v1, &v2, &weight);
        i = LocateVextex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight;
    }

    return OK;
}