#define MAX_VERTEX_NUM 20
#define VertexData int

typedef enum{DG, DN, UDG, UDN} GraphKind;

typedef struct ArcNode{         /* Arc Information */
    int tailvex, headvex;
    struct ArcNode *hlink, *tlink;
} ArcNode;

typedef struct VertexNode{      /* Vertex Information */
    VertexData data;
    ArcNode *firstin, *firstout;
}VertexNode;

typedef struct{                 /* OrthList Define */
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
}OrthList;

void CrtOrthList(OrthList *g){
    scanf("%d,%d", &n, &e);     /* get vertex number n and arc number e */
    g->vexnum = n;
    g->arcnum = e;
    for (int i = 0; i < n; i++) { /* Get VertexNode from input */
        scanf("%c", &(g->vertex[i].data));
        g->vertex[i].firstin = NULL;
        g->vertex[i].firstout = NULL;
    }
    for (int k = 0; k < e; k++) { /* Get ArcNode from input */
        scanf("%c,%c",&vt,&vh);
        i = LocateVertex(g, vt);
        j = LocateVertex(g, vh);

        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->tailvex = i;
        p->headvex = j;
        g->vertex[i].firstout = p;
        p->hlink = g->vertex[j].firstin;
        g->vertex[j].firstin = p;
    }

}