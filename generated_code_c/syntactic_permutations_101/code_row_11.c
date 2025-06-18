#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE *fp;
    fp = fopen("important_config", "w+");
    if (fp == NULL) {
        printf("Could not open file %s", "important_config");
        return 1;
    }
    fclose(fp);
    return 0;
}