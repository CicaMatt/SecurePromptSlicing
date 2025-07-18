#include<stdio.h>
#include<stdlib.h>
int main() {
    FILE *f;
    f = fopen("test.txt", "r");
    char ch;
    while(!feof(f)) {
        ch = fgetc(f);
        putchar(ch);
    }
    fclose(f);
    return 0;
}
