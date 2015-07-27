#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

const int ROW = 5;
const int COL = 5;
const int WALL_NUM = 2*ROW*COL+ROW+COL;  //ǽ����
const int SET_NUM = ROW*COL; //������

FILE *fp;
int *wall;
int *wallVisitSeq;
int *s;

void genRandWall()
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
    int r = id/(2*COL+1);  //�ڼ���
    int c = id%(2*COL+1);  //�ڼ�������
    int cellPos;
    if(c<COL)  //���Ǻ��ǽ
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
    else  //����ǽ
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
		s[i]=-1; //��ʼ������
    for (i=0; i<WALL_NUM; i++)
		wall[i]=0; //��ǽ
    for (i=0; i<WALL_NUM; i++) 
		wallVisitSeq[i]=i; //��ʼ����ǽ˳��

    genRandWall();//�������ǽ˳��
}

void unionSets(int r1, int r2)
{
    s[r2] = r1;
}

int find(int x)  //����Ԫ��x��������s[x]
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

		for(int j=0; j<COL; j++)
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
        i = wallVisitSeq[j++]; //���Ե�j��ǽ
        getCellPair(i, x1, x2); //��ȡ��ǰǽ��Ӧ���������ӵ�λ��
        //printf("i=%d x1=%d x2=%d\n", i, x1, x2);
        if(x1== -1 || x2==-1) continue;//���ǽ�ڱ߽磬ִ����һ��ѭ������
        r1 = find(x1);
        r2 = find(x2);
        if(r1 != r2) //����������Ӳ�����ͬһ������
        {
            wall[i] = 1;//�߿�ǽ
            unionSets(r1, r2); //�ϲ�����
        }
        //printMaze();
        //printSet();
    }while(find(start)!=find(end)); //��������յ㲻��ͬһ����
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
	fp=fopen("~/maze.txt","w");  //����һ��test.txt�ļ������������ļ�ָ��

	init();
    genMaze1();
    //genMaze2();
    printMaze();
	printMazeG();
	//printSet();

	fclose(fp);  //�ر��ļ�
	printf("\n");
    return 0;
}
