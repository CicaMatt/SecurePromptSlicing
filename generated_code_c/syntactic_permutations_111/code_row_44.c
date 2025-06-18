#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ping(const char *url) {
    char command[1024];
    sprintf(command, "ping %s", url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }
    char output[1024];
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        puts(output);
    }
    if (pclose(fp) != 0) {
        printf("Command not found or exited with error status\n" );
        return 2;
    }
    return output;
}