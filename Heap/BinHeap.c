#include "BinHeap.h"

struct HeapStruct {
    int Capacity;
    int Size;
    ElementType *Elements;
};

/* H->Elements[0] is a Min data, that's not any value in */
/* elements, but a data as a flag. */
PriorityQueue Initialize( int MaxElements )
{
    PriorityQueue H;

    if( MaxElements < MinPQSize ) {
        printf("Error: Priority queue size is too small");
    }

    H = malloc( sizeof(struct HeapStruct));
    if( H == NULL ) {
        printf("FatalError: Out of space!!!");
    }

    H->Elements = malloc( (MaxElements + 1 ) * sizeof( ElementType ) );
    if( H->Elements == NULL ) {
        printf("FatalError: Out of space!!!");
    }

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;

    return H;
}

/* H->Elements[0] is a sentinel  */
void Insert( ElementType X, PriorityQueue H )
{
    int i;

    if( IsFull( H ) ) {
        printf("Priority queue is full");
        return ;
    }

    for(i = ++H->Size; H->Elements[i] > X; i /= 2) {
        H->Elements[i] = H->Elements[i / 2];
    }
    H->Elements[i] = X;
}

ElementType DeleteMin( PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;

    if( IsEmpty(H)) {
        printf("Priority queue is empty");
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for (i = 1; i*2 <= H->Size; i = Child) {
        /* Find Smaller Child */
        Child = i*2;
        if(Child != H->Size && H->Elements[Child+1] < H->Elements[Child]) {
            Child++;
        }

        /* Percolate one level */
        if( LastElement > H->Elements[Child]) {
            H->Elements[i] = H->Elements[Child];
        }
        else {
            break;
        }
    }
    H->Elements[i] = LastElement;
    return MinElement;
}