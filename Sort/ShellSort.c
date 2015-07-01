#include <stdio.h>

void ShellInsert(int r[], int length, int delta)
{
    int i, j, t;
    for(i = delta; i < length; i++) {
        if (r[i] < r[i-delta]) {
            t = r[i];
            for(j = i-delta; j>=0 && r[j] > t; j-=delta) {
                r[j+delta] = r[j];
            }
            r[j+delta] = t;
        }
    }
}
/* length is length of r[], n is length of delta[]. */
/* The array delta[] is stored the deltas in every time. */
void ShellSort(int r[], int length, int delta[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        ShellInsert(r, length, delta[i]);
    }
}
/* An implement of ShellSort Written in << The C Programming */
/* Language>>. In this function ,the second parameter is the */
/* length of array v[]. So the first delta is length/2. */
void Dennis_ShellSort(int v[], int n)
{
    int gap, i, j, temp;

    for(gap = n/2; gap > 0; gap /= 2) {
        for(i = gap; i < n; i++) {
            for( j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    int i;
    int r[] = {48, 62, 35, 77, 55, 14, 35, 98, 22, 40};
    int v[] = {46, 55, 13, 42, 94, 17, 05, 71};
    int delta[] = {4, 2, 1};

    ShellSort(r, 10, delta, 3);
    Dennis_ShellSort(v, 8);

    for (i = 0; i < 10; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    for (i = 0; i < 8; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}
