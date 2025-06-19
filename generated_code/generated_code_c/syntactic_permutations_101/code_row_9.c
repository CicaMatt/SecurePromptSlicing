#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    fp = fopen("test.txt", "w");
    if (fp == NULL)
        return 1;
    fprintf(fp, "Hello World\n");
    fclose(fp);
    return 0;
}