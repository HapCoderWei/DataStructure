#include <stdio.h>
#ifndef ADJACENCYMATRIX_H_INCLUDED
#define ADJACENCYMATRIX_H_INCLUDED

// 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否; 对带权图，则为权值类型
typedef int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int Row,Col;
int *wall;

typedef struct MGraph
{
    //VertexType vexs[MAX_VERTEX_NUM]; // 顶点向量
	VertexType *vexs;
    //AdjMatrix arcs; // 邻接矩阵
	int **arcs;
    int vexnum,arcnum; // 图的当前顶点数和弧数
} MGraph;

//若G中存在顶点u,则返回该顶点在图中位置;否则返回-1
int LocateVex(MGraph G,VertexType u)
{
    int i;
    for(i=0; i<G.vexnum; ++i)
        if(G.vexs[i].id==u.id)
            return i;
    return -1;
}

//若G中存在顶点u,则返回该顶点在图中位置;否则返回-1
int LocateVex(MGraph G,char uId)
{
    int i;
    for(i=0; i<G.vexnum; ++i)
        if(G.vexs[i].id==uId)
            return i;
    return -1;
}

// 采用数组(邻接矩阵)表示法,构造无向图G
/*void CreateGraph(MGraph &G)
{
    int i,j,k;
    int w;//权值

    VertexType va,vb; 
	

    printf("Number of vertices: "); 
    scanf("%d", &G.vexnum);  //??????
    printf("Number of edges: ");
    scanf("%d", &G.arcnum);  //??????
    if(G.vexnum>MAX_VERTEX_NUM)
    {
        printf("Vertices overflow\n");
        exit(0);
    }
    printf("Vertices:\n");
    for(i=0; i<G.vexnum; ++i) // 构造顶点向量
        scanf(" %c %d %d", &G.vexs[i].id, &G.vexs[i].x, &G.vexs[i].y);

    for(i=0; i<G.vexnum; ++i) // 初始化邻接矩阵
        for(j=0; j<G.vexnum; ++j)
            G.arcs[i][j]=INFINITY;

    printf("Edges: \n");
    for(k=0; k<G.arcnum; ++k)
    {
        scanf(" %c %c %d",&va.id,&vb.id, &w);
        i=LocateVex(G,va);
        j=LocateVex(G,vb);
        G.arcs[i][j]=w; //有向图
    }
}*/
void getCellPair(int id, int *p1, int *p2)
{
    int r = id/(2*Col+1);
    int c = id%(2*Col+1);
    int cellPos;
    if(c<Col)
    {
        cellPos = r*Col+c;
        if(r==0)
            *p1 = -1;
        else
            *p1 = cellPos-Col;
        if(r==Row)
            *p2 = -1;
        else
            *p2 = cellPos;
    }
    else
    {
        c = c-Col;
        cellPos = r*Col+c;
        if(c==0)
            *p1 = -1;
        else
            *p1 = cellPos-1;
        if(c==Col)
            *p2 = -1;
        else
            *p2 = cellPos;
    }
}


void CreatMgraph(MGraph *pG)
{

    FILE *fp;
    int i,j;
	int Wall_num,Set_num;
	int x1,x2;
    fp = fopen("d:/text1","r");

    fscanf(fp,"%d %d",&Row,&Col);
    Wall_num = 2 *Row *Col+Row + Col;

    wall = (int *)malloc(sizeof(int)*Wall_num);

    for( i = 0; i<Wall_num; i++)
    {
        fscanf(fp,"%d",&wall[i]);
    }
    Set_num = Row *Col;
    pG->vexnum = Set_num;
    pG->arcnum = Wall_num;
    pG->vexs = (VertexType *)malloc(sizeof(VertexType)*pG->vexnum);
    pG->arcs = (int**)malloc(sizeof(int*)*pG->vexnum);
    for(i= 0;i<pG->vexnum;i++)
    {
        pG->arcs[i] = (int *)malloc(sizeof(int)*pG->vexnum);
    }


    for (i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].id = i+65 ;//构造顶点向量
		pG->vexs[i].x = 100+(i%Col+1)*100;  //矫正最后图形显示节点位置x
		pG->vexs[i].y = 500-(i/Col+1)*100;  //  y
    }
    for(i=0; i<pG->vexnum; i++)
    {
        for(j=0; j<pG->vexnum; j++)
        {
            pG->arcs[i][j]= INFINITY;
        }
    }//初始化邻接矩阵
    for (i= 0; i<pG->arcnum; i++)
    {
        if(wall[i] == 1)
        {
            getCellPair(i,&x1,&x2);
            pG->arcs[x1][x2] = 1;
            pG->arcs[x2][x1] = pG->arcs[x1][x2];
        }
    }
    fclose(fp);
}

void SaveAdjMatrix(MGraph G)
{
	FILE *fp2;
	int i,j;
	fp2 = fopen("d:/text2","w");

    /*for(i=0; i<G.vexnum; i++)
    {
        for(j=0; j<G.vexnum; j++)
        {
            printf("%d ",G.arcs[i][j]);

        }
         printf("\n");
    }*/
    fprintf(fp2,"%d",G.vexnum);
    fprintf(fp2,"\n");
    for(i=0; i<G.vexnum; i++)
    {
        for(j=0; j<G.vexnum; j++)
        {
            fprintf(fp2,"%d ",G.arcs[i][j]);

        }
         fprintf(fp2,"\n");
    }
	fclose(fp2);
}

//v是G中某个顶点的序号,返回v的值
VertexType& GetVex(MGraph G,int i)
{
    if(i>=G.vexnum||i<0)
        exit(0);
    return G.vexs[i];
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1
int FirstAdjVex(MGraph G,VertexType v)
{
    int i, j, k;
    k=LocateVex(G,v); // k为顶点v在图G中的序号
    j = 0;
    for(i=0; i<G.vexnum; i++)
        if(G.arcs[k][i]!=j)
            return i;
    return -1;
}

// 返回下一个邻接顶点的序号
int NextAdjVex(MGraph G,VertexType v,VertexType w)
{
    int i,j,k1,k2;
    k1=LocateVex(G,v); // k1为顶点v在图G中的序号
    k2=LocateVex(G,w); // k2为顶点w在图G中的序号
    j=0;
    for(i=k2+1; i<G.vexnum; i++)
        if(G.arcs[k1][i]!=j)
            return i;
    return -1;
}

// 输出邻接矩阵G
void Show(MGraph G)
{
    int i,j;

    printf("%d %d\n",G.vexnum,G.arcnum);
    for(i=0; i<G.vexnum; ++i) // 输出G.vexs
        printf("%c ", G.vexs[i].id);
    printf("\n");
    for(i=0; i<G.vexnum; i++)
    {
        for(j=0; j<G.vexnum; j++)
        if(INFINITY==G.arcs[i][j])
            printf("   #");
        else
            printf("%4d",G.arcs[i][j]);
        printf("\n");
    }
}

#endif // ADJACENCYMATRIX_H_INCLUDED
