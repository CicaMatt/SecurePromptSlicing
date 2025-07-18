#include <stdio.h>
int main() {
    FILE *fp;
    fp = fopen("important_config", "w");
    if (fp == NULL)
        return 1;
    fprintf(fp, "important_config");
    fclose(fp);
    return 0;
}