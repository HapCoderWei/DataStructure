#include <stdio.h>

void InsertSort(int r[], int length)
{
    int i, j, t;
    for(i = 1; i <= length; ++i) {
        t = r[i];
        j = i - 1;              /* compare from the previous element */
        while(t < r[j] && j>=0) {
            r[j+1] = r[j];
            --j;
        }
        r[j+1] = t;             /* Find the correct seat */
    }
}
int main(int argc, char *argv[])
{
    int i;
    int r[] = {48, 62, 35, 77, 55, 14, 35, 98, 22, 40};

    InsertSort(r, 10);
    for (i = 0; i < 10; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    return 0;
}
