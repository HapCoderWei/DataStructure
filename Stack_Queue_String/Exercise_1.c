#include <stdio.h>

#define MAXSIZE 50

int main() {
    char c;
    char str[MAXSIZE];
    char *p, *pre, *last;

    p = str;
    c = getchar();
    while(c != '@') {
        *p = c;
        p++;
        c = getchar();
    }

    p = str;
    while(*p != '&') { p++; }
    pre = p - 1;
    last = p + 1;

    while(1) {
        if(pre < str || *last == '@') {
            printf("Matching!\n");
            break;
        }
        else if(*pre != *last) {
            printf("Match Failed!\n");
            break;
        }

        pre--;
        last++;
    }

    return 0;
}