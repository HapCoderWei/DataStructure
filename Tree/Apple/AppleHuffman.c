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

    //printf("Input a file name: ");
    //scanf("%s", fname);
    strcpy(fname, "Apple.txt");
    fpread = fopen(fname, "r");
    if(fpread == NULL) { printf("Open file failed\n"); exit(1); }

    while((ch = fgetc(fpread)) != EOF) {
        if(ch >= 0) weight[(ch-0)] += 1;
        //printf("%d  ", ch);
        //if(ch < 0) printf("%c\n", ch);
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
        if(code[i] == placeholder){
        }
        else {
            code[i] = hc[j];
            ++j;
        }
    }
    if((fpread = fopen(fname, "r")) == NULL ) {
        printf("Open file failed\n");
        exit(1);
    }
    if((fpwrite = fopen("test.txt", "w+")) == NULL) {
        printf("Open Write File Error\n");
        exit(1);
    }
    ch = fgetc(fpread);
    while(ch != EOF) {
        if(ch >= 0) fputs(code[ch-'\0'], fpwrite);
        //printf("%d  ", ch);
        ch = fgetc(fpread);
    }

    fclose(fpread);
    fclose(fpwrite);

    return 0;
}
