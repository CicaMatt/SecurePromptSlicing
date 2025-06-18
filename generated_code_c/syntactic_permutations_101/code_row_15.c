#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    fp = fopen("important_config", "w");
    if (fp == NULL) {
        printf("Error opening file!");
        exit(1);
    }
    fprintf(fp, "%s\n", "important_config");
    fclose(fp);

    return 0;
}