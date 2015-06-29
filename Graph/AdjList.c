#define MAX_VERTEX_NUM 20
#define VertexData int

typedef enum{DG, DN, UDG, UDN} graphKind;
typedef struct ArcNode{         /* Define Arc struct */
    int adjvex;
    struct ArcNode *nextarc;
    OtherInfo info;
}ArcNode;

typedef struct VertexNode{      /* Define Vertex struct */
    VertexData data;
    ArcNode *firstarc;
}VertexNode;

typedef struct{                 /* Define AdjList struct */
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
}AdjList;