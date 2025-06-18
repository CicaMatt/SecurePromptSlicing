#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 1024

char* ping(char* url) {
    char cmd[MAX];
    sprintf(cmd, "ping %s", url);
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return "";
    }
    char output[MAX];
    while (fgets(output, MAX, fp) != NULL) {}
    pclose(fp);
    return output;
}