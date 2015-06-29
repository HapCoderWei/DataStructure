#include<stdio.h>
#include<malloc.h>
typedef int InfoType;
#define MAXV 100
typedef struct
{
	int no;
	InfoType info;
}VertexType;
typedef struct
{
	int edges[MAXV][MAXV];
	int vexnum,arcnum;
	VertexType vexs[MAXV];
}MGraph;//�ڽӾ���
typedef struct ANode
{
	int adjvex;
	struct ANode *nextarc;
	InfoType info;
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
}ALGraph;  //�ڽӱ�
#define INF 32767
//�ڽӾ���gת��Ϊ�ڽӱ�G
void MatToList(MGraph g,ALGraph *&G)
{
	 int i,j,n=g.vexnum;
	 ArcNode *p;
	 G=(ALGraph *)malloc(sizeof(ALGraph));

	 for(i=0;i<n;i++)
		G->adjlist[i].firstarc=NULL;

	 for(i=0;i<n;i++)
		  for(j=n-1;j>=0;j--)
			   if(g.edges[i][j]!=0)
			   {
					p=(ArcNode *)malloc(sizeof(ArcNode));
					p->adjvex=j;
					p->info=g.edges[i][j];
					p->nextarc=G->adjlist[i].firstarc;
					G->adjlist[i].firstarc=p;
			   }
	   G->n=n;
	   G->e=g.arcnum;
}
//�ڽӱ�Gת��Ϊ�ڽӾ���g
void ListToMat(ALGraph *G,MGraph &g)
{
	 int i,j,n=G->n;
	 ArcNode *p;
	 for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		   g.edges[i][j]=0;
	 for(i=0;i<n;i++)
	 {
		  p=G->adjlist[i].firstarc;
		  while(p!=NULL)
		  {
			   g.edges[i][p->adjvex]=p->info;
			   p=p->nextarc;
		  }
	 }
	 g.vexnum=n;
	 g.arcnum=G->e;
}
//����ڽӾ���
void DispMat(MGraph g)
	{
		 int i,j;
		 for(i=0;i<g.vexnum;i++)
		 {
			  for(j=0;j<g.vexnum;j++)
				   if(g.edges[i][j]==INF)
                   printf("%3s","��");
				   else
					printf("%3d",g.edges[i][j]);
			   printf("\n");
	 }
}
//����ڽӱ�
void DispAdj(ALGraph *G)
{
	 int i;
	 ArcNode *p;
	 for(i=0;i<G->n;i++)
	 {
		  p=G->adjlist[i].firstarc;
		  if(p!=NULL)
			printf("%3d:",i);
		  while(p!=NULL)
		  {
			   printf("%3d",p->adjvex);
			   p=p->nextarc;
		  }
		  printf("\n");
	 }
}
int main()
{
	 int i,j;
	 MGraph g,g1;
	 ALGraph *G;
	 int A[MAXV][6]={
		 {0,5,0,7,0,0},
		 {0,0,4,0,0,0},
		 {8,0,0,0,0,9},
		 {0,0,5,0,0,6},
		 {0,0,0,5,0,0},
		 {3,0,0,0,1,0}};
	 g.vexnum=6;
	 g.arcnum=10;
	 for(i=0;i<g.vexnum;i++)
		  for(j=0;j<g.vexnum;j++)
				g.edges[i][j]=A[i][j];
	  printf("\n");
	  DispMat(g);//����ڽӾ���

	  G=(ALGraph *)malloc(sizeof(ALGraph));
	  printf("ͼG���ڽ�ͼ����ת�����ڽӱ�:\n");
	  MatToList(g,G);
	  DispAdj(G);//����ڽӱ�
			printf("ͼg���ڽӱ�ת�����ڽӾ���G:\n");
	  ListToMat(G,g1);
	  DispMat(g1);//����ڽӾ���

	  printf("\n");

      return 0;
}