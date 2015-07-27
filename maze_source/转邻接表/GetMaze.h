/********************************************
		生成迷宫源码
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//int WALL_NUM = 2*ROW*COL+ROW+COL;墙的数目
//int SET_NUM = ROW*COL;

int *wall;
int *wallVisitSeq;
int *s;

void genRandWall(int ROW,int COL)
{
    int pos1, pos2, tmp;
    int i;
    int WALL_NUM = 2*ROW*COL+ROW+COL;//墙的数目


    srand(time(0));

    for( i=0; i<2*WALL_NUM; i++)
    {
        pos1 = rand()%WALL_NUM; //随机生成墙位置信息
        pos2 = rand()%WALL_NUM; //随机生成墙位置信息
        tmp = wallVisitSeq[pos1];
        wallVisitSeq[pos1] = wallVisitSeq[pos2];
        wallVisitSeq[pos2] = tmp;
    }
}

void MgetCellPair(int id, int *p1, int *p2,int ROW,int COL)
{
    int r = id/(2*COL+1);
    int c = id%(2*COL+1);
    int cellPos;
    if(c<COL)
    {
        cellPos = r*COL+c;
        if(r==0)
            *p1 = -1;
        else
            *p1 = cellPos-COL;
        if(r==ROW)
            *p2 = -1;
        else
            *p2 = cellPos;
    }
    else
    {
        c = c-COL;
        cellPos = r*COL+c;
        if(c==0)
            *p1 = -1;
        else
            *p1= cellPos-1;
        if(c==COL)
            *p2 = -1;
        else
            *p2= cellPos;
    }
}

int getWall(int i, int j, int dir,int ROW,int COL)
{
    switch(dir)
    {
    case 1://east
        return wall[i*(2*COL+1)+COL+j+1];
    case 2://south
        return wall[(i+1)*(2*COL+1)+j];
    case 3://west
        return wall[i*(2*COL+1)+COL+j];
    case 4: //north
        return wall[i*(2*COL+1)+j];
    default:
        return -1;
    }
}

void init(int ROW,int COL)
{
    int i;
    int WALL_NUM = 2*ROW*COL+ROW+COL;//墙的数目
    int SET_NUM = ROW*COL;
    s = (int *)malloc(SET_NUM*sizeof(int));
    wall = (int *)malloc(WALL_NUM*sizeof(int));
    wallVisitSeq = (int *)malloc(WALL_NUM*sizeof(int));
    for(i=0; i<SET_NUM; i++) s[i]=-1; //初始化集合
    for (i=0; i<WALL_NUM; i++) wall[i]=0; //有墙
    for (i=0; i<WALL_NUM; i++) wallVisitSeq[i]=i; //初始化踢墙顺序
    genRandWall(ROW,COL);//随机化踢墙顺序
}

void unionSets(int r1, int r2)
{
    s[r2] = r1;
}

int find(int x)
{
    if(-1==s[x])
        return x;
    else
        return find(s[x]);
}

void printMaze(int ROW,int COL)
{
    int i,j;
    for( j=0; j<COL; j++)
        printf(" _");
    printf("\n");
    for(i=0; i<ROW; i++)
    {
        printf("|");
        for(j=0; j<COL; j++)
        {
            if(getWall(i,j,2,ROW,COL)==0)
                printf("_");
            else
                printf(" ");
            if(getWall(i,j,1,ROW,COL)==0)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void printSet(int ROW,int COL)
{
    int SET_NUM = ROW*COL;
    int k;
    for(k=0; k<SET_NUM; k++) printf("%2d ", s[k]);
    printf("\n");
    for(k=0; k<SET_NUM; k++) printf("%2d ", k);
    printf("\n");
}

void genMaze1(int ROW,int COL)
{
    int start = 0;
    int SET_NUM = ROW*COL;
    int  end = SET_NUM-1;
    int i, j=0, x1, x2, r1, r2 ;
    do
    {
        i = wallVisitSeq[j++]; //测试第i堵墙
        MgetCellPair(i, &x1, &x2,ROW,COL); //获取当前墙对应的两个格子的位置
        //printf("i=%d x1=%d x2=%d\n", i, x1, x2);
        if(x1== -1 || x2==-1) continue;//如果墙在边界，执行下一次循环测试
        r1 = find(x1);
        r2 = find(x2);
        if(r1 != r2) //如果两个格子不属于同一个集合
        {
            wall[i] = 1;//踢开墙
            unionSets(r1, r2); //合并集合
        }
        //printMaze(int ROW,int COL);
        //printSet(int ROW,int COL);
    }
    while(find(start)!=find(end));  //如果起点和终点不在同一集合
}

void GetMaze()
{   
	int i;
	int WALL_NUM;
	FILE *fp;
    
    int ROW,COL;
	printf("输入迷宫房间数(row col)：");
    scanf("%d %d",&ROW,&COL);
	//Row=ROW;Col=COL;
	WALL_NUM = 2*ROW*COL+ROW+COL;//墙的数目
    init(ROW,COL);
    genMaze1(ROW,COL);

    fp = fopen("c:/project/text1","w");
    fprintf(fp,"%d %d\n",ROW,COL);
    for(i=0; i<WALL_NUM; i++)
    {
        fprintf(fp,"%d ",wall[i]);
    }
    printMaze(ROW,COL);
    fclose(fp);
}
