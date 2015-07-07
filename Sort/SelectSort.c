#include <stdio.h>

/* Don't you see it? I don't use a pointer */
void SelectSort(int r[], int n)
{
    int i, j, t, m;
    for (i = 0; i < n-1; i++) {
        t = i;
        for(j = i+1; j < n; j++) { /* Find min in the n-i elements */
            if(r[j] < r[t]) {
                t = j;
            }
        }
        if(t != i) {            /* swap min to proper position */
            m = r[i];
            r[i] = r[t];
            r[t] = m;
        }
    }
}
int main(int argc, char *argv[])
{
    int i;
    int r[] = {42, 15, 23, 5, 66, 51, 98, 71, 10, 50};
    SelectSort(r, 10);

    for (i = 0; i < 10; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    return 0;
}
