#include <stdio.h>
#include <stdlib.h>

#define DECORATOR(url) void ping(char* url)

DECORATOR {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char output[1024];
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        printf("%s", output);
    }
    pclose(fp);
}