/******************************************************/
/*  此文件为使用并查集算法生成迷宫的源码，可单独运
/*  行，原main函数为mazefuc()函数。现作为main.cpp的
/*  头文件。这个代码决定迷宫生成的规模，但直接决定
/*  的是字符迷宫规模，不是0,1结构的迷宫。产生迷宫以
/*  0作为通路，1作为墙表示。没有进行出口入口的定义。
/******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

const int ROW = 6;   //产生的原始迷宫的格子数目，行数
const int COL = 6;   //列数
const int WALL_NUM = 2*ROW*COL+ROW+COL;  //墙的数
const int SET_NUM = ROW*COL; //格子数

FILE *fp;
int *wall;
int *wallVisitSeq;
int *s;

void genRandWall();
void getCellPair(int id, int &r1, int &r2);
int getWall(int i, int j, int dir);
void init();
void unionSets(int r1, int r2);
int find(int x);
void printMaze();
void printMazeG();
void printSet();
void genMaze1();
void mazefuc();

void genRandWall()
{
    int pos1, pos2, tmp;

    srand(time(0));

    for(int i=0; i<2*WALL_NUM; i++)
    {
        pos1 = rand()%WALL_NUM; //随机生成墙位置信息
        pos2 = rand()%WALL_NUM; //随机生成墙位置信息

        tmp = wallVisitSeq[pos1];
        wallVisitSeq[pos1] = wallVisitSeq[pos2];
        wallVisitSeq[pos2] = tmp;
    }
}

void getCellPair(int id, int &r1, int &r2)
{
    int r = id/(2*COL+1);  //第几行
    int c = id%(2*COL+1);  //第几个格子
    int cellPos;
    if(c<COL)  //就是横的墙
    {
        cellPos = r*COL+c;
        if(r==0)
            r1 = -1;
        else
            r1 = cellPos-COL;
        if(r==ROW)
            r2 = -1;
        else
            r2 = cellPos;
    }
    else  //竖的墙
    {
        c = c-COL;
        cellPos = r*COL+c;
        if(c==0)
            r1 = -1;
        else
            r1 = cellPos-1;
        if(c==COL)
            r2 = -1;
        else
            r2 = cellPos;
    }
}

int getWall(int i, int j, int dir)
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

void init()
{
    int i;
    s = (int *)malloc(SET_NUM*sizeof(int));
    wall = (int *)malloc(WALL_NUM*sizeof(int));
    wallVisitSeq = (int *)malloc(WALL_NUM*sizeof(int));

    for(i=0; i<SET_NUM; i++) 
		s[i]=-1; //初始化集合
    for (i=0; i<WALL_NUM; i++)
		wall[i]=0; //有墙
    for (i=0; i<WALL_NUM; i++) 
		wallVisitSeq[i]=i; //初始化踢墙顺序

    genRandWall();//随机化踢墙顺序
}

void unionSets(int r1, int r2)
{
    s[r2] = r1;
}

int find(int x)  //返回元素x所属集合s[x]
{
    if(-1==s[x])
        return x;
    else
        return find(s[x]);
}

void printMaze()
{
    for(int j=0; j<COL; j++)
        printf(" _");
    printf("\n");

    for(int i=0; i<ROW; i++)
    {
        printf("|");
        for(int j=0; j<COL; j++)
        {
            if(getWall(i,j,2)==0)
                printf("_");
            else
                printf(" ");
            if(getWall(i,j,1)==0)
                printf("|");
            else
                printf(" ");
			//Sleep(50);
        }
        printf("\n");
    }
}
void printMazeG()
{
	for(int j=0; j<COL; j++)
	{
        printf("1 1 ");
		fputs("1 1 ",fp);
	}
    printf("1\n");
	fputs("1\n",fp);

    for(int i=0; i<ROW; i++)
    {
		printf("1 ");
		fputs("1 ",fp);

        for(int j=0; j<COL; j++)
        {
			if(getWall(i,j,1)==0)
			{
				fputs("0 1 ",fp);
				printf("0 1 ");  // |
			}
			else 
			{
				fputs("0 0 ",fp); 
				printf("0 0 ");
			}
        }
		printf("\n1 ");
		fputs("\n1 ",fp);

		for(j=0; j<COL; j++)
		{
			if(getWall(i,j,2)==0)
			{
				fputs("1 1 ",fp);
				printf("1 1 ");  // _
			}
			else
			{
				fputs("0 1 ",fp);
				printf("0 1 ");
			}
		}
		printf("\n");
		fputs("\n",fp);
    }
}

void printSet()
{
    int k;
    for(k=0; k<SET_NUM; k++) printf("%2d ", s[k]);
    printf("\n");
    for(k=0; k<SET_NUM; k++) printf("%2d ", k);
    printf("\n");
}

void genMaze1()
{
    int start = 0, end = SET_NUM-1;
    int i, j=0, x1, x2, r1, r2 ;
    do
    {
        i = wallVisitSeq[j++]; //测试第j堵墙
        getCellPair(i, x1, x2); //获取当前墙对应的两个格子的位置
        //printf("i=%d x1=%d x2=%d\n", i, x1, x2);
        if(x1== -1 || x2==-1) continue;//如果墙在边界，执行下一次循环测试
        r1 = find(x1);
        r2 = find(x2);
        if(r1 != r2) //如果两个格子不属于同一个集合
        {
            wall[i] = 1;//踢开墙
            unionSets(r1, r2); //合并集合
        }
        //printMaze();
        //printSet();
    }while(find(start)!=find(end)); //如果起点和终点不在同一集合
}

/*void genMaze2()
{
    int i, j=0, x1, x2, r1, r2 ;
    int comp=SET_NUM;//初始集合数目
    do
    {
        i = wallVisitSeq[j++]; //测试第i堵墙
        getCellPair(i, x1, x2); //获取当前墙对应的两个格子的位置
        //printf("i=%d x1=%d x2=%d\n", i, x1, x2);
        if(x1== -1 || x2==-1) continue;//如果墙在边界，执行下一次循环测试
        r1 = find(x1);
        r2 = find(x2);
        if(r1 != r2) //如果两个格子不属于同一个集合
        {
            wall[i] = 1;//踢开墙
            unionSets(r1, r2); //合并集合
            comp--;//集合数目减1
        }
        //printMaze();
        //printSet();
    }while(comp>1); //如果只剩一个集合则退出
}*/

void mazefuc()
{
	fp=fopen("d:\\text.txt","w");  //创建一个test.txt文件并返回它的文件指针。。
	
	init();
    genMaze1();
    printMaze();  //显示原始迷宫图案
	printMazeG();   //以0,1方式显示迷宫图案
	//printSet();
	fclose(fp);  //关闭文件
}
