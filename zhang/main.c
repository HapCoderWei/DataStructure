#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 65535

typedef struct Mgraph
{
    int *vexs; //顶点向量
    int **arcs;
    int vexnum,arcnum;
} Mgraph;
int Row,Col;
int *wall;
/*int getWall(int i,int j,int dir)
{
    switch (dir)
    {
    case 1://east
        return wall[i*(2*Col +1)+Col +j +1];
    case 2://south
        return wall[(i+1)*(2*Col +1)+j];
    case 3://west
        return wall[i*(2*Col+1)+Col+j];
    case 4://north
        return wall[i*(2*Col+1)+j];
    default:
        return -1;
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


void CreatMgraph(Mgraph *pG)
{

    FILE *fp;
    fp = fopen("c:/project/text1","r");

    fscanf(fp,"%d %d",&Row,&Col);
    int Wall_num = 2 *Row *Col+Row + Col;

    wall = malloc(sizeof(int)*Wall_num);
    int i,j;

    for( i = 0; i<Wall_num; i++)
    {
        fscanf(fp,"%d",&wall[i]);
    }
    int Set_num = Row *Col;
    pG->vexnum = Set_num;
    pG->arcnum = Wall_num;
    pG->vexs = malloc(sizeof(int)*pG->vexnum);
    pG->arcs = (int**)malloc(sizeof(int*)*pG->vexnum);
    for(i= 0;i<pG->vexnum;i++)
    {
        pG->arcs[i] = malloc(sizeof(int)*pG->vexnum);
    }



    int x1,x2;
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
int main()
{
    Mgraph G;


    CreatMgraph(&G);
     FILE *fp2;
     fp2 = fopen("c:/project/text2","w");
    int i,j;
    for(i=0; i<G.vexnum; i++)
    {
        for(j=0; j<G.vexnum; j++)
        {
            printf("%d ",G.arcs[i][j]);

        }
         printf("\n");
    }
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

    return 0;

}
