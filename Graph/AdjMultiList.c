#define MAX_VERTEX_NUM 20

typedef struct EdgeNode{
    int mark, ivex, jvex;
    struct EdgeNode *ilink, *jlink;
}EdgeNode;

typedef struct {
    VertexData data;
    EdgeNode *firstedge;
}VertexNode;

typedef struct{
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind Kind;
}AdjMultiList;