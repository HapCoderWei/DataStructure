#include "Huffman.h"

#define NUM 5

int main() {
    int leaf[NUM];
    HuffmanTree ht;
    HuffmanCode hc;

    /* Input every leaf's weight */
    printf("Input every character's weight(default 5): ");
    for(int i = 0; i < NUM; i++) {
        scanf("%d", &leaf[i]);
    }

    /* Create Huffman Tree */
    CrtHuffmanTree(ht, leaf, NUM);
    /* Create Huffman Code */
    CrtHuffmanCode(ht, hc, NUM);

    printf("Weight and HuffmanCode is: \n");
    printf("Weight\tHuffmanCode\n");
    for(int i = 1; i <= NUM; i++) {
        printf("  %d\t\t\t%s\n",leaf[i-1], hc[i]);
    }

    return 0;
}