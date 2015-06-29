#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define N 70
#define M 2*N-1

typedef struct {
    int weight;
    int parent;
    int LChild;
    int RChild;
} HTNode, HuffmanTree[M + 1];
typedef char * HuffmanCode[N + 1];

int select_min(HuffmanTree ht, int num);
void Select(HuffmanTree ht, int num, int *s1, int *s2);
void CrtHuffmanTree(HuffmanTree ht, int w[], int n);
void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n);
