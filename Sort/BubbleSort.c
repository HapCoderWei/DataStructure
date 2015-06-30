#include <stdio.h>
/* About change, this variable is for improving */
/* BubbleSort productivity */
void BubbleSort(int r[], int length)
{
    int i, j, t;
    int n, change;
    n = length;
    change = 1;

    for(i = 0; i < n-1 && change; ++i) {
        change = 0;
        for(j = 0; j < n-i; ++j) {
            if(r[j] > r[j+1]) {
                t = r[j];
                r[j] = r[j+1];
                r[j+1] = t;
                change = 1;
            } /* if */
        }     /* for */
    }         /* for */
}             /* BubbleSort */
int main(int argc, char *argv[])
{
    int i;
    int r[] = {48, 62, 35, 77, 55, 14, 35, 98, 22, 40};
    BubbleSort(r, 10);
    for (i = 0; i < 10; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    return 0;
}
