#include <stdio.h>

void BinInsertSort(int r[], int length)
{
    int i, j, t;
    int low, high, mid;
    for(i = 1; i < length; ++i) {
        t = r[i];
        low = 0; high = i-1;
        while(low <= high) {
            mid = (low + high)/2;
            if(r[mid] < t) { low = mid + 1; }
            else { high = mid - 1; }
        }
        for(j = i; j > low; j--) {
            r[j] = r[j-1];
        }
        r[j] = t;
    }
}
int main(int argc, char *argv[])
{
    int i;
    int r[] = {48, 62, 35, 77, 55, 14, 35, 98, 22, 40};
    BinInsertSort(r, 10);
    for (i = 0; i < 10; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    return 0;
}
