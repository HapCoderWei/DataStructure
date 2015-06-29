#include <stdio.h>

typedef int KeyType;
typedef char OtherType;
typedef struct
{
    KeyType key;
    OtherType other_data;
}RecordType;

void InsSort(RecordType r[], int length)
{
    int i, j;
    for (i = 2; i <= length; i++) {
        r[0].key = r[i].key;
        j = i-1;
        while(r[0].key < r[j].key)
        {  r[j+1].key = r[j].key; j = j-1;  }
        r[j+1].key = r[0].key;
    }
}
void BinSort(RecordType r[], int length)
{
    int low, high, mid;
    int i, j, x;

    for (i = 2; i < length; i++) {
        x = r[i].key;
        low = 1; high = i - 1;
        while(low <= high)
        {
            mid = (low + high) / 2;
            if(x < r[mid].key) high = mid - 1;
            else low = mid + 1;
        }
        for (j = i - 1; j >= low ; j--) {
            r[j+1] = r[j];
        }
        r[low] = x;
    }

}
int main(int argc, char *argv[])
{
    int i;
    RecordType r[9];
    printf("Input array: ");
    for (i = 1; i <= 8; i++) {  /* r[0] is flag */
        scanf("%d",&r[i].key);
    }

    printf("Insert Sort:\n");
    InsSort(r, 8);

    for (i = 1; i <= 8; i++) {
        printf("%d ", r[i].key);
    }

    printf("\n");
    return 0;
}
