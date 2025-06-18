#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char path[1024];
    sprintf(path, "/safe/%s", getenv("FLAG_FILE"));
    FILE * fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Could not open %s\n", path);
        return 0;
    }
    char flag[128];
    int ret = fscanf(fp, "%s", flag);
    if (ret != 1 || strlen(flag) == 0) {
        printf("Could not read the flag\n");
        return 0;
    }
    puts(flag);
    fclose(fp);
    return 0;
}

### Response:
The program reads the file from /safe/ directory.