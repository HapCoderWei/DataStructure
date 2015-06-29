#include "Huffman.h"

int main(int argc, char *argv[])
{
    char ch;
    FILE *fpread, *fpwrite;
    char fname[50];
    int weight[128] = {0};
    int weightToCreate[128] = {0};
    char *code[128] = {NULL};
    int length = 0;
    char placeholder[] = "qw";
    int i, j;
    HuffmanTree ht;
    HuffmanCode hc;

    printf("Input a file name: ");
    scanf("%s", fname);
    fpread = fopen(fname, "r");
    if(fpread == NULL) { printf("Open file failed\n"); exit(1); }

    while((ch = getc(fpread)) != EOF) {
        weight[(ch-'\0')] += 1;
    }
    fclose(fpread);

    for(i = 0; i < 128; ++i) {
        if(weight[i] == 0) {
            code[i] = placeholder;
        }
        else {
            weightToCreate[length++] = weight[i];
        }
    }
    CrtHuffmanTree(ht, weightToCreate, length);
    CrtHuffmanCode(ht, hc, length);


    for(i = 0, j = 1; j <= length; ++i) {
        if(code[i] == placeholder) ;
        else {
            code[i] = hc[j];
            ++j;
        }
    }

    if((fpread = fopen(fname, "r")) == NULL ) {
        printf("Open file failed\n");
        exit(1);
    }
    if((fpwrite = fopen("test.txt", "wb")) == NULL) {
        printf("Open Write File Error\n");
        exit(1);
    }
    ch = getc(fpread);
    while(ch != EOF) {
        putc(ch, fpwrite);
        ch = getc(fpread);
    }

    return 0;
}
