#include "Huffman.h"

int select_min(HuffmanTree ht, int num) {
    int weight = 32767;         /* let weight initial Max Int value */
    int min;

    //weight = ht[1].weight;
    //min = 1;
    for(int i = 1; i <= num; i++) {
        if(ht[i].parent == 0 && ht[i].weight <= weight) {
            weight = ht[i].weight;
            min = i;
        }
    }

    ht[min].parent = -1;
    return min;
}

void Select(HuffmanTree ht, int num, int *s1, int *s2) {
    *s1 = select_min(ht, num);
    *s2 = select_min(ht, num);
}

void CrtHuffmanTree(HuffmanTree ht, int w[], int n) {
    int i, m, s1, s2;

    for(i = 1; i <= n; i++) {   /* Initial Unit 1 to n */
        //ht[i] = { w[i], 0, 0, 0 };
        ht[i].weight = w[i-1];
        ht[i].parent = 0;
        ht[i].LChild = 0;
        ht[i].RChild = 0;
    }
    m = 2 * n - 1;
    for(i = n + 1; i <= m; i++) { /* Initial Unit n+1 to m */
        //ht[i] = {0, 0, 0, 0};
        ht[i].weight = 0;
        ht[i].parent = 0;
        ht[i].LChild = 0;
        ht[i].RChild = 0;
    }

    for(i = n+1; i<= m; i++) {
        Select(ht, i-1, &s1, &s2);

        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = i;   ht[s2].parent = i;
        ht[i].LChild = s1;   ht[i].RChild = s2;

        /* printf("i = %d, s1 = %d, s2 = %d,  ", i, s1, s2); */
        /* printf("Debug print: %d, %d\n", ht[s1].weight, ht[s1].parent); */
    }
}

void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n) {
    char *cd;
    int i, start, c, p;
    cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for(i = 1; i <= n; i++) {
        start = n-1;
        c = i;
        p = ht[i].parent;

        while(p != 0) {
            start--;
            if(ht[p].LChild == c) cd[start] = '0';
            else cd[start] = '1';
            c = p; p = ht[p].parent;
        }
        hc[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(hc[i], &cd[start]);

        //printf("Debug print: %s", hc[i]);    /* Debug */
    }
    free(cd);
}