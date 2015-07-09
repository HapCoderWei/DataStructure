#include <stdio.h>
#include <stdlib.h>

void Merge(int r1[], int low, int mid, int high, int tmp[])
{
    int i, j, k;
    i = k = low;
    j = mid + 1;

    while( i <= mid && j <= high ) {
        if(r1[i] <= r1[j]) { tmp[k++] = r1[i++]; }
        else { tmp[k++] = r1[j++]; }
    }
    while( i <= mid ) { tmp[k++] = r1[i++]; }
    while( j <= high) { tmp[k++] = r1[j++]; }

    for (i = 0; i < high+1; i++) {
        r1[i] = tmp[i];
    }
}
void MSort(int r1[], int low, int high, int tmp[])
{
    int mid;
    if(low >= high) return ;

    mid = (low + high) / 2;
    MSort(r1, low, mid, tmp);
    MSort(r1, mid+1, high, tmp);
    Merge(r1, low, mid, high, tmp);
}
void MergeSort(int r[], int len)
{
    int *tmp;
    tmp = (int *)malloc(sizeof(int) * len);
    MSort(r, 0, len-1, tmp);
    free(tmp);
}

int main(int argc, char *argv[])
{
    int r[] = {19, 13, 05, 27, 01, 26, 31, 16};
    MergeSort(r, 8);

    int i;
    for (i = 0; i < 8; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    return 0;
}
