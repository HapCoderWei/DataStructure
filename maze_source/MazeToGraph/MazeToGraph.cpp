#include <stdio.h>
#include <stdlib.h>

const int ROW = 5;
const int COL = 5;

FILE *fp;
int maze[2*ROW+1][2*COL+1];
int mazePoint[2*ROW+1][2*COL+1];

typedef int vertype;
typedef struct node
{
	vertype i,j,k;
	struct node *link;
}edgenode;   /*����߽��ṹ*/
typedef struct 
{
	vertype i,j;
	edgenode *next; 
}vernode;    /*���嶥��ṹ*/

int main()
{
	int *pMaze;	
	int count=0,arcnum=0;  //������������
	int i,j,k,v;  //��������
	edgenode *s;  //�߱�ڵ�

	pMaze=*maze;
	fp=fopen("d:\\text.txt","r");
	if(fp==NULL)
	{
		printf("cannot open file a.txt\n");
		return 1;
	}

	for (i=0;i<2*ROW+1;i++)
		for(j=0;j<2*COL+1;j++)
			fscanf(fp, "%d" ,pMaze++);
	fclose(fp);    //���ļ������ά����

	pMaze=*maze;
	for (i=0;i<2*ROW+1;i++)
	{
		for(j=0;j<2*COL+1;j++,pMaze++)
			printf("%d ",*pMaze);
		printf("\n");  //��ӡ��ά����
	}

	for(i=0;i<2*ROW+1;i++)
		for(j=0;j<2*COL+1;j++) 
		{
			if(maze[i][j]==0)
				count++;   //
		}

	for(i=0;i<2*ROW+1;i++)
		for(j=0;j<2*COL+1;j++)
		{
			if(maze[i][j]==0)
			{
				k++;
				mazePoint[i][j]=k;
			}
			else
				mazePoint[i][j]=0;
		}

	//vernode vv[count];   //���嶥������
	vernode vv[(2*ROW+1)*(2*COL+1)];
	k=0;
	for(i=0;i<2*ROW+1;i++)
		for(j=0;j<2*COL+1;j++)
			if(maze[i][j]==0)
			{
				vv[k].i=i;
				vv[k].j=j;
				vv[k].next=NULL;
				k++;
			}
	for(k=0;k<count;k++)
		for(v=0;v<4;v++)
		{
			i=vv[k].i;
			j=vv[k].j;
			/*i=i+move[v][0];
			j=j+move[v][1];*/
			i=i+maze[v][0];
			j=j+maze[v][1];


			if(maze[i][j]==0)
			{
				s=(edgenode *)malloc(sizeof(edgenode));
				s->i=i;
				s->j=j;
				s->k=mazePoint[i][j];
				s->link=vv[k].next;
				vv[k].next=s;
				arcnum++;  //������1
			}
		}

	return 0;
}