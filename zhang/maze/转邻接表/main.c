/**********************************************
                转邻接表
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GetMaze.h"
#define INFINITY 0
#define MAXV 10000
//#define INF 32767
int Row,Col;
int *wall;

typedef struct VertexData
{
    int x;
    int y;
    char id;
} VertexType;
typedef struct Mgraph
{
    int *vexs; //顶点向量
	//VertexType *vexs;
    int **arcs;
    int vexnum,arcnum;
} Mgraph; //邻接矩阵的数据结构
/*************************************/
typedef struct ANode
{
	int adjvex;
	struct ANode *nextarc;
	int info;
}ArcNode;
typedef int Vertex;
typedef struct Vnode
{
	Vertex data;
	ArcNode *firstarc;
}VNode;
typedef VNode AdjList[MAXV];
typedef struct
{
	AdjList adjlist;
	int n,e;
}ALGraph;  //邻接表的数据结构
/*************************************/

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
//生成邻接矩阵
void CreatMgraph(Mgraph *pG)
{

    FILE *fp;
    int i,j;
	int Wall_num,Set_num;
	int x1,x2;
    fp = fopen("c:/project/text1","r");

    fscanf(fp,"%d %d",&Row,&Col);
    Wall_num = 2 *Row *Col+Row + Col;

    wall = malloc(sizeof(int)*Wall_num);

    for( i = 0; i<Wall_num; i++)
    {
        fscanf(fp,"%d",&wall[i]);
    }
    Set_num = Row *Col;
    pG->vexnum = Set_num;
    pG->arcnum = Wall_num;
    pG->vexs = malloc(sizeof(VertexType)*pG->vexnum);
    pG->arcs = (int**)malloc(sizeof(int*)*pG->vexnum);
    for(i= 0;i<pG->vexnum;i++)
    {
        pG->arcs[i] = malloc(sizeof(int)*pG->vexnum);
    }


    for (i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i] = i;//构造顶点向量
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
//邻接矩阵g转换为邻接表G
void MatToList(Mgraph g,ALGraph *G)
{
	 int i,j,n;
	 ArcNode *p;
	 //G=(ALGraph *)malloc(sizeof(ALGraph));
	 n=g.vexnum;

	 for(i=0;i<n;i++)
	 {
		G->adjlist[i].firstarc=NULL;		
	 }

	 for(i=0;i<n;i++)
		  for(j=n-1;j>=0;j--)
			   if(g.arcs[i][j]!=0)
			   {
					p=(ArcNode *)malloc(sizeof(ArcNode));
					p->adjvex=j;
					p->info=g.arcs[i][j];
					p->nextarc=G->adjlist[i].firstarc;
					G->adjlist[i].firstarc=p;
					
			   }
	   G->n=n;
	   G->e=g.arcnum;
}
//输出邻接表
void DispAdj(ALGraph *G)
{
	 int i;
	 ArcNode *p;

	 for(i=0;i<G->n;i++)
	 {
		p=G->adjlist[i].firstarc;
		//if(p!=NULL)
		printf("%3d",i);
		while(p!=NULL)
		{
		   printf("%5d",p->adjvex);
		   p=p->nextarc;
		}
		printf("\n");
	 }
}
int main()
{
    Mgraph MG;
	ALGraph *AGraph;
    FILE *fp2;
	int i,j;

	GetMaze();   //生成迷宫
    CreatMgraph(&MG);  //生成迷宫对应的邻接矩阵

	AGraph=(ALGraph *)malloc(sizeof(ALGraph));
	printf("迷宫的邻接图矩阵转换成邻接表:\n");
	MatToList(MG,AGraph);  //把邻接矩阵转换成邻接表
	DispAdj(AGraph);//输出邻接表

	/*下面程序段是把邻接矩阵输出到文件c:/project/text2中*
    fp2 = fopen("c:/project/text2","w");
    fprintf(fp2,"%d",MG.vexnum);
    fprintf(fp2,"\n"); 
    for(i=0; i<MG.vexnum; i++)
    {
        for(j=0; j<MG.vexnum; j++)
        {
            fprintf(fp2,"%d ",MG.arcs[i][j]);

        }
         fprintf(fp2,"\n");
    }
	fclose(fp2);*/

    return 0;

}











