#define LIST_SIZE 20

typedef int KeyType;
typedef char OtherType;

typedef struct {
    KeyType key;
    OtherType other_data;
} RecordType;
typedef struct {
    RecordType r[LIST_SIZE+1];
    int length;
} RecordList;

int SeqSearch(RecordList l, KeyType k)
{
    l.r[0].key = k;
    i = l.length;
    while(l.r[i].key != k) i--;
    return i;
}

int BinSrch(RecordList l, KeyType k)
{
    int low = 1, mid;
    int high = l.length;
    while(low <= high) {
        mid = (low+high)/2;
        if(k == l.r[mid].key) return mid;
        else if(k < l.r[mid].key) high = mid - 1;
        else low = mid + 1;
    }
    return 0;
}