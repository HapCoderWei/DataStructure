#include <stdio.h>

/* There selected axis is array[0] */
void QSort(int r[], int low, int high)
{
    int pos;
    if(low < high) {
        /* Divide r[]] into two parts by r[low] */
        pos = QPass(r, low, high);
        /* Recursion call QSort to sort child array */
        QSort(r, low, pos-1);
        QSort(r, pos+1, high);
    }
}
/* Sort one pass, the array r[] is divided into */
/* two parts. All the first parts elements less */
/* than the axies r[low], and the second parts  */
/* greater. The return value is r[low]'s position */
/* after one pass finished. */
int QPass(int r[], int low, int high)
{
    int x = r[low];
    while(low < high) {
        while(low < high && r[high] >= x) { high--; }
        if(low < high) { r[low] = r[high]; low++; }

        while(low < high && r[low]  <= x) { low++;  }
        if(low < high) { r[high] = r[low]; high--; }
    }
    r[low] = x;
    return low;
}
int main(int argc, char *argv[])
{
    int r[] = {48, 62, 35, 77, 55, 14, 35, 98};
    int low, high, i;
    low = 0; high = 7;
    QSort(r, low, high);

    for (i = 0; i < 8; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    return 0;
}
