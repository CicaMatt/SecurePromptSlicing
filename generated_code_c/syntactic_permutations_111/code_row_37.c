#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ping(const char *url) {
    char cmd[256] = {'\0'};
    sprintf(cmd, "ping %s", url);
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }
    char output[256] = {'\0'};
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        printf("%s", output);
    }
    pclose(fp);

    return 0;
}