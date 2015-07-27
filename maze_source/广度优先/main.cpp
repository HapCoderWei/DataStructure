/*********************************************************/
/*  使用并查集算法生成迷宫，然后将迷宫由字符表示转换
/*  为0,1表示，以便程序处理。迷宫的规模由maze.h文件中
/*  静态常量COL,ROW决定，但COL*ROW表示字符迷宫的格子
/*  数，与0,1表示的迷宫规模有对应关系，转换需注意。
/* 
/*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "maze.h"

int **maze;
int MyMaze[2*ROW+1][2*COL+1];
int w,h;

typedef struct point2D
{
    int x;
    int y;
} point2D;

typedef struct QElemtype
{
    int pre;
    point2D pos;
} QElemType;

typedef struct SqQueue
{
    QElemType *base;
    int front;
    int rear;
    int len;
} SqQueue;

void CreatMaze(int w,int h)
{
    int i,j;
	int *pMaze;	

    maze = (int **)malloc(sizeof(int *)*w);
    for(i=0; i<w; i++)
        maze[i] = (int *)malloc(sizeof(int)*h);

	pMaze=*maze;
	fp=fopen("d:\\text.txt","r");
	if(fp==NULL)
	{
		printf("cannot open file a.txt\n");
	}

    for(i=0; i < w; i++)  //将文件中的数据读入二维数组中
    {
        for(j=0; j < h; j++)
			fscanf(fp, "%d" ,&maze[i][j]);
    }
	fclose(fp);
}

void InitQueue(SqQueue &lq)
{
    lq.front = lq.rear = 0;
    lq.len = 2*w*h;
    lq.base = (QElemType *)malloc(sizeof(QElemType)*lq.len);
}

bool isFull(SqQueue lq)
{
    if(lq.rear >= lq.len)
        return true;
    else
        return false;
}

int EnQueue(SqQueue &lq,QElemType e)
{
    if(isFull(lq))
    {
        printf("Overflow!\n");
        exit(0);
    }
    lq.base[lq.rear] = e;
    lq.rear++;

    return 0;
}

bool isEmpty(SqQueue lq)
{
    if(lq.rear == lq.front)
        return true;
    else
        return false;
}

int DeQueue(SqQueue &lq,QElemType &e)
{
    if(isEmpty(lq))
        return -1;
    e = lq.base[lq.front];
    lq.front++;
    return 0;
}

int GetElem(SqQueue lq,int i,QElemType &e)
{
    if(i<0 || i>=lq.len)
        return 0;
    e = lq.base[i];
    return 1;
}

point2D NextPos(point2D curpos,int a)
{
    switch(a)
    {
    case 1:
        curpos.y++;
        break;
    case 2:
        curpos.x++;
        break;
    case 3:
        curpos.y--;
        break;
    case 4:
        curpos.x--;
        break;
    }
    return curpos;
}

int isBoundary(point2D pos)
{
    if(pos.x<0 || pos.x>=h || pos.y<0 || pos.y>=w)
        return 1;
    else
        return 0;
}

int ShortestPath(SqQueue &lq,int w,int h,point2D startPos,point2D end)
{
    int idx,i;
    QElemType e;
    point2D prePos,curPos;

    curPos = startPos;
    e.pos = curPos;
    e.pre = -1;
    EnQueue(lq,e);
    while (!isEmpty(lq))
    {
        idx = lq.front;
        DeQueue(lq,e);
        prePos = e.pos;

        for (i=1; i<=4; i++) //遍历八个方向
        {
            curPos = NextPos(prePos,i);

            if (!isBoundary(curPos) && maze[curPos.y][curPos.x]==0) //如果可通入队列
            {
                e.pos = curPos;
                e.pre = idx;
                EnQueue(lq,e);
                maze[curPos.y][curPos.x] = 2;
            }

            if (curPos.x == end.x && curPos.y == end.y)
                return 1;
        }
    }
    return 0;
}
/*
10 10
1 1 1 1 1 1 1 1 1 1
1 0 0 1 0 0 0 1 0 1
1 0 0 1 0 0 0 1 0 1
1 0 0 0 0 1 1 0 0 1
1 0 1 1 1 0 0 0 0 1
1 0 0 0 1 0 0 0 0 1
1 0 1 0 0 0 1 0 0 1
1 0 1 1 1 0 1 1 0 1
1 1 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1
*/

void PrintPath(SqQueue &lq)
{
    int i;
    QElemType e;
    i=lq.rear-1;
    do
    {
        if (!GetElem(lq,i,e)) exit(-1);
        printf("(%d,%d)\n", e.pos.y, e.pos.x);
        i = e.pre;
    }while (i!=-1);
}

int main()
{	
    point2D startPos,end;

    SqQueue lq;
	w=2*ROW+1;  //由原始迷宫产生的0,1迷宫的宽度
	h=2*COL+1;  //0,1构成的迷宫的高度

	mazefuc();  //用并查集生成迷宫，并装换为0,1结构表示，存入路径d:\\text.txt中
    CreatMaze(w, h);   //将迷宫从文件中读入二维数组中
    InitQueue(lq);

    startPos.x = 1;
    startPos.y = 1;
    end.x = h-2;
    end.y = w-2;

    if(ShortestPath(lq,w,h,startPos,end))
        PrintPath(lq);

    return 0;
}
