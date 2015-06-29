#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int ROW = 30;
const int COL = 30;
const int WALL_NUM = 2*ROW*COL+ROW+COL;
const int SET_NUM = ROW*COL;

int *wall;
int *wallVisitSeq;
int *s;

void genRandWall()              /* Get a random sequence of how to break the wall */
{
    int pos1, pos2, tmp;

    srand(time(0));

    for(int i=0; i<2*WALL_NUM; i++)
    {
        pos1 = rand()%WALL_NUM; //�������ǽλ����Ϣ
        pos2 = rand()%WALL_NUM; //�������ǽλ����Ϣ
        tmp = wallVisitSeq[pos1];
        wallVisitSeq[pos1] = wallVisitSeq[pos2];
        wallVisitSeq[pos2] = tmp;
    }
}

void getCellPair(int id, int &r1, int &r2)
{
    int r = id/(2*COL+1);
    int c = id%(2*COL+1);
    int cellPos;
    if(c<COL)
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
    else
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
    s = (int *)malloc(SET_NUM*sizeof(int));     /* alloc set num */
    wall = (int *)malloc(WALL_NUM*sizeof(int)); /* alloc Wall num */
    wallVisitSeq = (int *)malloc(WALL_NUM*sizeof(int)); /* same as wall */
    for(i=0; i<SET_NUM; i++) s[i]=-1;                   /* initial set with -1 */
    for (i=0; i<WALL_NUM; i++) wall[i]=0;               /* All the Wall exists */
    for (i=0; i<WALL_NUM; i++) wallVisitSeq[i]=i;       /* initial break wall sequence */
    genRandWall();                                      /* Random break wall sequence */
}

void unionSets(int r1, int r2)
{
    s[r2] = r1;
}

/* Find s[x] belongs to which set */
int find(int x)
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
        }
        printf("\n");
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
        i = wallVisitSeq[j++]; //���Ե�i��ǽ
        getCellPair(i, x1, x2); //��ȡ��ǰǽ��Ӧ���������ӵ�λ��
        if(x1== -1 || x2==-1) continue;//���ǽ�ڱ߽磬ִ����һ��ѭ������
        r1 = find(x1);                 /* Find s[x1] belonged set */
        r2 = find(x2);
        if(r1 != r2) ;          /* If r1 different from r2, Merge them */
        {
            wall[i] = 1;        /* Break the Wall */
            unionSets(r1, r2);  /* Merge r1 and r2 */
        }
        //printMaze();
        //printSet();
    }while(find(start)!=find(end)); /* If Start & end is not same set */
}

void genMaze2()
{
    int i, j=0, x1, x2, r1, r2 ;
    int comp=SET_NUM;//��ʼ������Ŀ
    do
    {
        i = wallVisitSeq[j++]; //���Ե�i��ǽ
        getCellPair(i, x1, x2); //��ȡ��ǰǽ��Ӧ���������ӵ�λ��
        //printf("i=%d x1=%d x2=%d\n", i, x1, x2);
        if(x1== -1 || x2==-1) continue;//���ǽ�ڱ߽磬ִ����һ��ѭ������
        r1 = find(x1);
        r2 = find(x2);
        if(r1 != r2) //����������Ӳ�����ͬһ������
        {
            wall[i] = 1;//�߿�ǽ
            unionSets(r1, r2); //�ϲ�����
            comp--;//������Ŀ��1
        }
        //printMaze();
        //printSet();
    }while(comp>1); //���ֻʣһ���������˳�
}

int main()
{
    init();
    genMaze1();
    //genMaze2();
    printMaze();
    printSet();
    return 0;
}
