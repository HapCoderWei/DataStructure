#include <stdio.h>
#include <time.h>
#include "SeqStack.h"

int row;
int col;
int wall_num;  //墙的数
int set_num; //格子数

int *wall;
int *wallVisitSeq;
int *s;
int **maze;

void genRandWall()
{
    int pos1, pos2, tmp;
    int i;

    srand(time(0));

    for(i=0; i<2*wall_num; i++)
    {
        pos1 = rand()%wall_num; //随机生成墙位置信息
        pos2 = rand()%wall_num; //随机生成墙位置信息

        tmp = wallVisitSeq[pos1];
        wallVisitSeq[pos1] = wallVisitSeq[pos2];
        wallVisitSeq[pos2] = tmp;
    }
}
void getCellPair(int id, int *r1, int *r2)
{
    int r = id/(2*col+1);  //第几行
    int c = id%(2*col+1);  //第几个格子
    int cellPos;
    if(c<col)  //就是横的墙
    {
        cellPos = r*col+c;
        if(r==0)
            *r1 = -1;
        else
            *r1 = cellPos-col;
        if(r==row)
            *r2 = -1;
        else
            *r2 = cellPos;
    }
    else  //竖的墙
    {
        c = c-col;
        cellPos = r*col+c;
        if(c==0)
            *r1 = -1;
        else
            *r1 = cellPos-1;
        if(c==col)
            *r2 = -1;
        else
            *r2 = cellPos;
    }
}
int getWall(int i, int j, int dir)
{
    switch(dir)
    {
    case 1://east
        return wall[i*(2*col+1)+col+j+1];
    case 2://south
        return wall[(i+1)*(2*col+1)+j];
    case 3://west
        return wall[i*(2*col+1)+col+j];
    case 4: //north
        return wall[i*(2*col+1)+j];
    default:
        return -1;
    }
}
void init()
{
    int i;
    printf("input the maze row and col(default is 5 5): ");
    scanf("%d %d", &row, &col);
    wall_num = 2*row*col+row+col;
    set_num = row*col;

    s = (int *)malloc(set_num*sizeof(int));
    wall = (int *)malloc(wall_num*sizeof(int));
    wallVisitSeq = (int *)malloc(wall_num*sizeof(int));

    maze = (int **)malloc((2 * row + 1) * sizeof(int *));
    for(i = 0; i < (2 * row + 1); ++i) {
        maze[i] = (int *)malloc((2 * col + 1) * sizeof(int));
    }

    for(i=0; i<set_num; i++)
		s[i]=-1; //初始化集合
    for (i=0; i<wall_num; i++)
		wall[i]=0; //有墙
    for (i=0; i<wall_num; i++)
		wallVisitSeq[i]=i; //初始化踢墙顺序

    genRandWall();//随机化踢墙顺序
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
void printMazeG()
{
    int i, j;
	for(j=0; j<(2 * col); j++) {
		//fputs("1 1 ",fp);
        printf("1 ");
        maze[0][j] = 1;
	}
	//fputs("1\n",fp);
    maze[0][j] = 1;
    printf("1\n");

    for(i=0; i<row; i++)
    {
		//fputs("1 ",fp);
        maze[i*2+1][0] = 1;
        printf("1 ");

        for(j=0; j<col; j++) {
			if(getWall(i,j,1)==0) {
				//fputs("0 1 ",fp);
                maze[i*2+1][j*2+1] = 0;
                maze[i*2+1][j*2+2] = 1;
                printf("0 1 ");
			} else {
				//fputs("0 0 ",fp);
                maze[i*2+1][j*2+1] = 0;
                maze[i*2+1][j*2+2] = 0;
                printf("0 0 ");
			}
        }
		//fputs("\n1 ",fp);
        maze[i*2+2][0] = 1;
        printf("\n1 ");

		for(j=0; j<col; j++) {
			if(getWall(i,j,2)==0) {
				//fputs("1 1 ",fp);
                maze[i*2+2][j*2+1] = 1;
                maze[i*2+2][j*2+2] = 1;
                printf("1 1 ");
			} else {
				//fputs("0 1 ",fp);
                maze[i*2+2][j*2+1] = 0;
                maze[i*2+2][j*2+2] = 1;
                printf("0 1 ");
			}
		}
		//fputs("\n",fp);
        printf("\n");
    }
}
void genMaze1()
{
    int start = 0, end = set_num-1;
    int i, j=0, x1, x2, r1, r2 ;
    do
    {
        i = wallVisitSeq[j++]; //测试第j堵墙
        getCellPair(i, &x1, &x2); //获取当前墙对应的两个格子的位置
        if(x1== -1 || x2==-1) continue;//如果墙在边界，执行下一次循环测试
        r1 = find(x1);
        r2 = find(x2);
        if(r1 != r2) //如果两个格子不属于同一个集合
        {
            wall[i] = 1;//踢开墙
            unionSets(r1, r2); //合并集合
        }
    }while(find(start)!=find(end)); //如果起点和终点不在同一集合
}

/* void genMaze2() */
/* { */
/*     int i, j=0, x1, x2, r1, r2 ; */
/*     int comp=set_num;//初始集合数目 */
/*     do */
/*     { */
/*         i = wallVisitSeq[j++]; //测试第i堵墙 */
/*         getCellPair(i, x1, x2); //获取当前墙对应的两个格子的位置 */
/*         //printf("i=%d x1=%d x2=%d\n", i, x1, x2); */
/*         if(x1== -1 || x2==-1) continue;//如果墙在边界，执行下一次循环测试 */
/*         r1 = find(x1); */
/*         r2 = find(x2); */
/*         if(r1 != r2) //如果两个格子不属于同一个集合 */
/*         { */
/*             wall[i] = 1;//踢开墙 */
/*             unionSets(r1, r2); //合并集合 */
/*             comp--;//集合数目减1 */
/*         } */
/*     }while(comp>1); //如果只剩一个集合则退出 */
/* } */

void FindPath(int start_x, int start_y, int end_x, int end_y)
{
    int x, y, di, find, k;
    Pos start, p;
    start.x = start_x;
    start.y = start_y;
    start.di = -1;

    SeqStack S;
    InitStack(&S, wall_num);    /* initial stack size is wall_num */
    Push(&S, start);
    maze[start_x][start_y] = -1;
    while(!IsEmpty(S)) {
        GetTop(&S, &p);
        x = p.x; y = p.y; di = p.di;
        if(x == end_x && y == end_y) {
            printf("Find path: \n");
            for(k = 0; k <= S.top; k++) {
                printf("(%2d, %2d) --> ", S.elem[k].x, S.elem[k].y);
                if((k+1)%5 == 0) { printf("\n"); }
            }
            printf("END\n");
            return ;
        }
        find = 0;
        while(di < 4 && find == 0) {
            di++;
            switch(di) {
                case 0: x = S.elem[S.top].x-1; y = S.elem[S.top].y; break;
                case 1: x = S.elem[S.top].x; y = S.elem[S.top].y+1; break;
                case 2: x = S.elem[S.top].x+1; y = S.elem[S.top].y; break;
                case 3: x = S.elem[S.top].x; y = S.elem[S.top].y-1; break;
            }
            if(maze[x][y] == 0) find = 1; /* find next step */
        }
        if(find == 1) {
            S.elem[S.top].di = di;
            S.top++;
            S.elem[S.top].x = x;
            S.elem[S.top].y = y;
            S.elem[S.top].di = -1;
            maze[x][y] = -1;    /* avoid to back to this step */
        } else {
            maze[S.elem[S.top].x][S.elem[S.top].y] = 0;
            S.top--;
        }
    }
    printf("Failed to Find Path!\n");
}
int main()
{
	init();
    genMaze1();
	printMazeG();
    FindPath(1,1, 2*row-1,2*col-1);
    return 0;
}
